//
// Copyright (c) 2018-2019 cTuning foundation.
// Copyright (c) 2019-2020 dividiti Limited.
// Copyright (c) 2021 Krai Ltd.
//
// SPDX-License-Identifier: BSD-3-Clause.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef BENCHMARK_H
#define BENCHMARK_H

#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <iterator>
#include <algorithm>
#include <chrono>
#include <cwctype>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <map>
#include <memory>
#include <string.h>
#include <vector>

#if defined(__amd64__) && defined(ENABLE_ZEN2)
#include <immintrin.h>
#include <cstdint>
#endif

#include <xopenme.h>

#include "settings.h"

#include "nms_abp.h"

#include "affinity.h"

#define DEBUG(msg) std::cout << "DEBUG: " << msg << std::endl;

#if defined(MODEL_R34)
  #define Model_Params R34_Params
#elif defined(MODEL_RX50)
  #define Model_Params RX50_Params
#else
  #define Model_Params MV1_Params
#endif


namespace CK {

//----------------------------------------------------------------------

class BenchmarkSession {
public:
  BenchmarkSession(BenchmarkSettings *settings) : _settings(settings) {}

  virtual ~BenchmarkSession() {}

  const std::vector<std::string> &
  load_filenames(std::vector<size_t> img_indices) {
    _filenames_buffer.clear();
    _filenames_buffer.reserve(img_indices.size());
    idx2loc.clear();

    auto list_of_available_imagefiles =
        _settings->list_of_available_imagefiles();
    auto count_available_imagefiles = list_of_available_imagefiles.size();

    int loc = 0;
    for (auto idx : img_indices) {
      if (idx < count_available_imagefiles) {
        _filenames_buffer.emplace_back(list_of_available_imagefiles[idx].name);
        idx2loc[idx] = loc++;
      } else {
        std::cerr << "Trying to load filename[" << idx << "] when only "
                  << count_available_imagefiles << " images are available"
                  << std::endl;
        exit(1);
      }
    }

    return _filenames_buffer;
  }

  const std::vector<std::string> &current_filenames() const {
    return _filenames_buffer;
  }

  std::map<int, int> idx2loc;

private:
  BenchmarkSettings *_settings;
  std::vector<std::string> _filenames_buffer;
};

//----------------------------------------------------------------------

template <typename TData> class StaticBuffer {
public:
  StaticBuffer(int size, const std::string &dir, TData *ptr = NULL)
      : _size(size), _dir(dir) {
    if (!ptr)
      //_buffer = (TData *)aligned_alloc(32, size);
      _buffer = new TData[size];
    else
      _buffer = ptr;
  }

  virtual ~StaticBuffer() { delete[] _buffer; }

  TData *data() const { return _buffer; }
  int size() const { return _size; }

protected:
  const int _size;
  const std::string _dir;
  TData *_buffer;
};

//----------------------------------------------------------------------

class ImageData : public StaticBuffer<uint8_t> {
public:
  ImageData(BenchmarkSettings *s, uint8_t *buf = NULL)
      : StaticBuffer(s->image_size_height() * s->image_size_width() *
                         s->num_channels() *
                         ((s->qaic_skip_stage != "convert") ? sizeof(float)
                                                            : sizeof(uint8_t)),
                     s->images_dir(), buf),
        s(s) {}

  void load(const std::string &filename, int vl) {
    auto path = _dir + '/' + filename;
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file)
      throw "Failed to open image data " + path;

    file.read(reinterpret_cast<char *>(_buffer), _size * sizeof(uint8_t));
  }

  void duplicate(const ImageData* img_from) {
    memcpy( _buffer, img_from->_buffer, _size * sizeof(uint8_t));
  }

private:
  BenchmarkSettings *s;
};

//----------------------------------------------------------------------

class ResultData {
public:
  ResultData(BenchmarkSettings *s) : _size(0) {
    _buffer = new float[s->detections_buffer_size() * 7];
  }

  ~ResultData() { delete[] _buffer; }

  int size() const { return _size; }

  void set_size(int size) { _size = size; }

  float *data() const { return _buffer; }

private:
  float *_buffer;
  int _size;
};

//----------------------------------------------------------------------

class IBenchmark {
public:
  bool has_background_class = false;

  virtual ~IBenchmark() {}
  virtual void load_images(BenchmarkSession *session) = 0;
  virtual void unload_images(size_t num_examples) = 0;
  virtual void get_next_results(std::vector<int> &image_idxs,
                                std::vector<ResultData *> &results, int dev_idx,
                                int act_idx, int set_idx) = 0;
  virtual void
  get_random_images(const std::vector<mlperf::QuerySample> &samples,
                    int dev_idx, int act_idx, int set_idx) = 0;

  virtual void *get_img_ptr(int dev_idx, int img_idx) = 0;
};

template <typename TInConverter, typename TOutConverter,
          typename TInputDataType, typename TOutput1DataType,
          typename TOutput2DataType>
class Benchmark : public IBenchmark {
public:
  void initResultsBuffer(int dev_id) {
    for (int d = 0; d < _settings->qaic_device_count; ++d) {
      
      nms_results[d].resize(_settings->qaic_activation_count);
      reformatted_results[d].resize(_settings->qaic_activation_count);
      for (int a = 0; a < _settings->qaic_activation_count; ++a) {
        nms_results[d][a].resize(_settings->qaic_set_size);
        reformatted_results[d][a].resize(_settings->qaic_set_size);
        for (int s = 0; s < _settings->qaic_set_size; ++s) {
          for (int b = 0; b <  _settings->qaic_batch_size; b++) {
            nms_results[d][a][s].push_back(std::vector<std::vector<float> >(
              0, std::vector<float>(NUM_COORDINATES + 2, 0)));
            reformatted_results[d][a][s].push_back(new ResultData(_settings));
          }
        }
      }
    }
  }

  Benchmark(
      BenchmarkSettings *settings,
      std::vector<std::vector<std::vector<void *> > > &in_ptrs,
      std::vector<std::vector<std::vector<std::vector<void *> > > > &out_ptrs)
      : _settings(settings) {
    _in_ptrs = in_ptrs;
    _out_ptrs = out_ptrs;
    _in_converter.reset(new TInConverter(settings));
    _out_converter.reset(new TOutConverter(settings));
    int dev_cnt = settings->qaic_device_count;
    _in_batch.resize(dev_cnt);
    _out_batch.resize(dev_cnt);


    nms_results.resize(dev_cnt);
    reformatted_results.resize(dev_cnt);

    for (int dev_idx = 0; dev_idx < dev_cnt; ++dev_idx) {
      std::thread t(&Benchmark::initResultsBuffer, this, dev_idx);
      unsigned coreid = AFFINITY_CARD(dev_idx);
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(coreid, &cpuset);
#ifdef R282
      if(dev_idx < 4 || _settings->qaic_device_count > 5)
#endif
      pthread_setaffinity_np(t.native_handle(), sizeof(cpu_set_t), &cpuset);
      t.join();
      //initResultsBuffer(dev_idx);
    }
    

#ifdef MODEL_R34
    std::vector<int> exclude{ 12, 26, 29, 30, 45, 66, 68, 69, 71, 83 };
#else
    std::vector<int> exclude{};
#endif

    for (int i = 0; i < 100; ++i)
      if (std::find(exclude.begin(), exclude.end(), i) == exclude.end())
        class_map.push_back(i);
  }

  ~Benchmark() {
    for (int d = 0; d < _settings->qaic_device_count; ++d)
      for (int a = 0; a < _settings->qaic_activation_count; ++a)
        for (int s = 0; s < _settings->qaic_set_size; ++s)
          for (int b = 0; b <  _settings->qaic_batch_size; b++)
            delete reformatted_results[d][a][s][b];
  }
  
  void load_images_locally(int d) {
    auto vl = _settings->verbosity_level;

    const std::vector<std::string> &image_filenames =
        session->current_filenames();

    unsigned length = image_filenames.size();
    _current_buffer_size = length;
    _in_batch[d] = new std::unique_ptr<ImageData>[length];
    _out_batch[d] = new std::unique_ptr<ResultData>[length];
    unsigned batch_size = _settings->qaic_batch_size;
    unsigned image_size = _settings->image_size_width() *
                          _settings->image_size_height() *
                          _settings->num_channels() * sizeof(TInputDataType);
    for (int i = 0; i < length; i += batch_size) {
      unsigned actual_batch_size =
          std::min(batch_size, batch_size < length ? (length - i) : length);
      uint8_t *buf = (uint8_t *)aligned_alloc(32, batch_size * image_size);
      for (auto j = 0; j < actual_batch_size; j++, buf += image_size) {
        _in_batch[d][i + j].reset(new ImageData(_settings, buf));
        _out_batch[d][i + j].reset(new ResultData(_settings));
        if(d == 0)
          _in_batch[d][i + j]->load(image_filenames[i + j], vl);
        else
          _in_batch[d][i + j]->duplicate(_in_batch[0][i + j].get());
      }
    }
  }

  void load_images(BenchmarkSession *_session) override {
    session = _session;
#if defined(G292) || defined(R282)
    for (int dev_idx = 0; dev_idx < _settings->qaic_device_count; ++dev_idx) {
      std::thread t(&Benchmark::load_images_locally, this, dev_idx);
      unsigned coreid = AFFINITY_CARD(dev_idx);
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(coreid, &cpuset);
#ifdef R282
      if(dev_idx < 4 || _settings->qaic_device_count > 5)
#endif
      pthread_setaffinity_np(t.native_handle(), sizeof(cpu_set_t), &cpuset);

      t.join();
    }
#else
    load_images_locally(0);

#endif
  }

  void unload_images(size_t num_examples) override {
    uint16_t batch_size = _settings->qaic_batch_size;
#if defined(G292) || defined(R282)
    int N = _settings->qaic_device_count;
#else
    int N = 1;
#endif
    for (int dev_idx = 0; dev_idx < N; ++dev_idx) {
      for (size_t i = 0; i < num_examples; i += batch_size) {
        delete _in_batch[dev_idx][i].get();
        delete _out_batch[dev_idx][i].get();
      }
    }
  }
  
  void get_random_images(const std::vector<mlperf::QuerySample> &samples,
                         int dev_idx, int act_idx, int set_idx) override {

for (int i = 0; i < samples.size(); ++i) {
      TInputDataType *ptr =
          ((TInputDataType *)_in_ptrs[dev_idx][act_idx][set_idx]) +
          i * _settings->image_size_width() * _settings->image_size_height() *
              _settings->num_channels();
      _in_converter->convert(
          _in_batch[dev_idx][session->idx2loc[samples[i].index]].get(), ptr);
    }
  }

  virtual void *get_img_ptr(int dev_idx, int img_idx) {
#if !defined(G292) && !defined(R282)
    return _in_batch[0][session->idx2loc[img_idx]].get()->data();
#else
    return _in_batch[dev_idx][session->idx2loc[img_idx]].get()->data();
#endif
  }

  void get_next_results(std::vector<int> &image_idxs,
                        std::vector<ResultData *> &results, int dev_idx,
                        int act_idx, int set_idx) override {

    #if defined(MODEL_RX50)
    std::vector<TOutput1DataType*> boxes_ptrs(modelParams.OUTPUT_LEVELS);
    std::vector<TOutput2DataType*> classes_ptrs(modelParams.OUTPUT_LEVELS);
    std::vector<uint64_t*> topk_ptrs(modelParams.OUTPUT_LEVELS);
    #else
    TOutput1DataType *boxes_ptr = (TOutput1DataType *) _out_ptrs[dev_idx][act_idx][set_idx][modelParams.BOXES_INDEX];
    TOutput2DataType *classes_ptr = (TOutput2DataType *) _out_ptrs[dev_idx][act_idx][set_idx][modelParams.CLASSES_INDEX];
    #endif

    for(int i = 0; i < image_idxs.size(); i++){
      nms_results[dev_idx][act_idx][set_idx][i].clear();

      // get pointers to unique buffer for device->activation->set
      std::vector<std::vector<float> > &nms_res =
          nms_results[dev_idx][act_idx][set_idx][i];
      ResultData *next_result_ptr =
          reformatted_results[dev_idx][act_idx][set_idx][i];

      if(_settings->disable_nms) {
        next_result_ptr->set_size(1 * 7);
        next_result_ptr->data()[0]=(float)image_idxs[i];
      } else {
          #if defined(MODEL_RX50)
            for(int g=0 ; g<modelParams.OUTPUT_LEVELS ; ++g) {
              TOutput1DataType *boxes_ptr = (TOutput1DataType *) _out_ptrs[dev_idx][act_idx][set_idx][modelParams.BOXES_INDEX+g];
              TOutput2DataType *classes_ptr = (TOutput2DataType *) _out_ptrs[dev_idx][act_idx][set_idx][modelParams.CLASSES_INDEX+g];
              uint64_t *topk_ptr = (uint64_t *) _out_ptrs[dev_idx][act_idx][set_idx][modelParams.TOPK_INDEX+g];

              boxes_ptrs[g]   = boxes_ptr + i * modelParams.TOTAL_NUM_BOXES * NUM_COORDINATES;
              classes_ptrs[g] = classes_ptr + i * modelParams.TOTAL_NUM_BOXES;
              topk_ptrs[g]    = topk_ptr + i * modelParams.TOTAL_NUM_BOXES;
            }
            nms_abp_processor.anchorBoxProcessing((const TOutput1DataType **)boxes_ptrs.data(),
                                                  (const TOutput2DataType **)classes_ptrs.data(),
                                                  (const uint64_t **)topk_ptrs.data(),
                                                  std::ref(nms_res), (float)image_idxs[i]);
          #else // Classes + Boxes only
            TOutput1DataType *dataLoc = boxes_ptr + i * modelParams.TOTAL_NUM_BOXES * NUM_COORDINATES;
            TOutput2DataType *dataConf = classes_ptr + i * modelParams.TOTAL_NUM_BOXES * modelParams.NUM_CLASSES;
            nms_abp_processor.anchorBoxProcessing(dataLoc, dataConf, std::ref(nms_res), (float)image_idxs[i]);
          #endif

        int num_elems = nms_res.size() < _settings->detections_buffer_size()
                            ? nms_res.size()
                            : _settings->detections_buffer_size();

        next_result_ptr->set_size(num_elems * 7);
        float *buffer = next_result_ptr->data();

        for (int j = 0; j < num_elems; j++) {
          buffer[0] = nms_res[j][0];
          buffer[1] = nms_res[j][1];
          buffer[2] = nms_res[j][2];
          buffer[3] = nms_res[j][3];
          buffer[4] = nms_res[j][4];
          buffer[5] = nms_res[j][5];
          buffer[6] = nms_res[j][6];

          //std::cout << buffer[0] << "," << buffer[1] << "," << buffer[2] << "," << buffer[3] << "," << buffer[4] << "," << buffer[5] << "," << buffer[6] << std::endl;
          buffer += 7;
        }
      }
      results.push_back(next_result_ptr);
    }
  }
#endif
private:
  BenchmarkSettings *_settings;
  BenchmarkSession *session;

  int _out_buffer_index = 0;
  int _current_buffer_size = 0;

  std::vector<std::vector<std::vector<void *> > > _in_ptrs;
  std::vector<std::vector<std::vector<std::vector<void *> > > > _out_ptrs;

  std::vector<std::unique_ptr<ImageData> *> _in_batch;
  std::vector<std::unique_ptr<ResultData> *> _out_batch;

  std::unique_ptr<TInConverter> _in_converter;
  std::unique_ptr<TOutConverter> _out_converter;


  std::vector<int> class_map;
  std::vector<const std::vector<mlperf::QuerySample>*> get_random_images_samples;
  std::vector<int> get_random_images_act_idx;
  std::vector<int> get_random_images_set_idx;
  std::vector<int> get_random_images_finished;
  std::vector<int> get_random_images_turn;



  std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<float> > > > > >
  nms_results;
  std::vector<std::vector<std::vector<std::vector<ResultData *> > > > reformatted_results;


  std::vector<std::vector<int> *> get_next_results_image_idxs;
  std::vector<std::vector<ResultData *> *> get_next_results_results;

  std::vector<int> get_next_results_act_idx;
  std::vector<int> get_next_results_set_idx;
  std::vector<int> get_next_results_finished;
  std::vector<int> get_next_results_batch_idx;
  std::vector<int> get_next_results_turn;

  NMS_ABP<TOutput1DataType, TOutput2DataType, Model_Params> nms_abp_processor;
  Model_Params modelParams;
};

//----------------------------------------------------------------------

class IinputConverter {
public:
  virtual ~IinputConverter() {}
  virtual void convert(const ImageData *source, void *target) = 0;
};

//----------------------------------------------------------------------

class InCopy : public IinputConverter {
public:
  InCopy(BenchmarkSettings *s) {
  }


  void convert(const ImageData * __restrict__ source, void * __restrict__ target) {
    size_t size = source -> size();
    uint8_t *src = source -> data();
#if defined(__amd64__) && defined(ENABLE_ZEN2)
#if !defined(MODEL_R34) && !defined(MODEL_RX50)
      __m128i *srca =  reinterpret_cast< __m128i*>(src);
      __m128i *desta = reinterpret_cast<__m128i*>(target);
      int64_t vectors = size / sizeof(*srca);
      for (; vectors > 0; vectors--, srca++, desta++) {
        const __m128i loaded = _mm_stream_load_si128(srca);
        _mm_stream_si128(desta, loaded);
      }
#else
      __m256i *srca =  reinterpret_cast< __m256i*>(src);
      __m256i *desta = reinterpret_cast<__m256i*>(target);
      int64_t vectors = size / sizeof(*srca);
      for (; vectors > 0; vectors--, srca++, desta++) {
        const __m256i loaded = _mm256_stream_load_si256(srca);
        _mm256_stream_si256(desta, loaded);
      }
#endif
      unsigned rem = size%sizeof(*srca);
      if(rem > 0) {
        memcpy((uint8_t*)desta, (uint8_t*)srca, rem);
      }
      _mm_sfence();
#else
      memcpy(target, src, size);
#endif
  }
};

//----------------------------------------------------------------------

class OutCopy {
public:
  OutCopy(BenchmarkSettings *s) : _settings(s) {

   /* std::vector<int> exclude{ 12, 26, 29, 30, 45, 66, 68, 69, 71, 83 };

    for (int i = 0; i < 100; ++i)
      if (std::find(exclude.begin(), exclude.end(), i) == exclude.end())
        class_map.push_back(i);*/
  }

  void convert(int img_idx, const float *boxes, const int64_t *classes,
               const float *scores, const int num, ResultData *target,
               int src_width, int src_height,
               std::vector<std::string> model_classes,
               bool correct_background) const {

  }

private:
  BenchmarkSettings *_settings;
  std::vector<int> class_map;
};

} // namespace CK

