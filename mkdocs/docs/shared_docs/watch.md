=== "Device frequency"
    ```
    watch -n 1 "/opt/qti-aic/tools/qaic-util -q | grep NSP\ Fr | cut -c 15-"
    ```
=== "Device power"
    ```
    watch -n 1 "sensors | grep qaic-pci -A7 | grep power1 | cut -c 10-"
    ```
=== "Device temperature"
    ```
    watch -n 1 "sensors | grep qaic-pci -A7 | grep temp2 | cut -c 10-"
    ```
=== "Active users"
    ```
    watch -n 10 "who -a | grep -v old | grep -v exit=0 | grep -v LOGIN | grep -v system | grep -v run-level"
    ```
=== "Docker images"
    ```
    watch -n 60 "docker image ls | head -n 5"
    ```