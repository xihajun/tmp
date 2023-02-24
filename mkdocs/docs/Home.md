
| Setup    | Benchmarking       | Submission |
| ------------------------ | ------------------------ | ------------------------ |
| [![](https://raw.githubusercontent.com/xihajun/image/main/img/20221214114517.png)](DockerSetup.md) | [![](https://raw.githubusercontent.com/xihajun/image/main/img/20221214120130.png)](QuickBenchmarking.md) | ![](https://raw.githubusercontent.com/xihajun/image/main/img/20230131120342.png)|
 

<!--Diagram Start-->

<!--Diagram End-->


Here is the diagram of the whole process:

```mermaid
flowchart LR
    subgraph SetupEnv[Setup]
        step1[Setup Mindset] --> step2[<a href='#setup-ck'>Setup CK</a> & <a href='#setup-user'>Setup User</a>]
        subgraph OS-Dependent
            DIR("<img src='https://raw.githubusercontent.com/docker-library/docs/c350af05d3fac7b5c3f6327ac82fe4d990d8729c/docker/logo.png'; width='30' />")
        end
        step2 --> OS-Dependent
        subgraph Edge
            step4[<a href='../AEDKSetup'>Setup AEDK</a>]
        end
        OS-Dependent --> Edge
    end
    subgraph Benchmarking
        subgraph ImageClassification
            ResNet50
        end
        subgraph ObjectDetection
            RetinaNet
            SSD-ResNet34
        end
        subgraph NLP
            BERT-99
            BERT-99.9
        end
        subgraph Tools
            Cmdgen
            Cmdgengen
        end
    end
    subgraph Submission
        step6[<a href='#Submission'>Submission</a>]
    end
    SetupEnv --> Benchmarking
    Benchmarking --> Submission
```