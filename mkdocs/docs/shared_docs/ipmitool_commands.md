
=== "Read the fan speed"
    === "Gigabyte R282-Z93"
        ```
        sudo ipmitool sensor get BPB_FAN_1A
        ```
        <details><pre>
        Locating sensor record...
        Sensor ID              : BPB_FAN_1A (0xa0)
         Entity ID             : 29.1
         Sensor Type (Threshold)  : Fan
        <b> Sensor Reading        : 8100 (+/- 0) RPM</b>
         Status                : ok
         Lower Non-Recoverable : na
         Lower Critical        : 1200.000
         Lower Non-Critical    : 1500.000
         Upper Non-Critical    : na
         Upper Critical        : na
         Upper Non-Recoverable : na
         Positive Hysteresis   : Unspecified
         Negative Hysteresis   : 150.000
         Assertion Events      :
         Assertions Enabled    : lnc- lcr-
         Deassertions Enabled  : lnc- lcr-
        </pre></details>
    === "Gigabyte G292-Z43"
        ```
        sudo ipmitool sensor get SYS_FAN2
        ```
        <details><pre>
        Locating sensor record...
        Sensor ID              : SYS_FAN2 (0xa3)
         Entity ID             : 29.4
         Sensor Type (Threshold)  : Fan
         <b>Sensor Reading        : 10800 (+/- 0) RPM</b>
         Status                : ok
         Lower Non-Recoverable : 0.000
         Lower Critical        : 1200.000
         Lower Non-Critical    : 1500.000
         Upper Non-Critical    : 38250.000
         Upper Critical        : 38250.000
         Upper Non-Recoverable : 38250.000
         Positive Hysteresis   : Unspecified
         Negative Hysteresis   : 150.000
         Assertion Events      :
         Assertions Enabled    : lnc- lnc+ lcr- lcr+ lnr- lnr+ unc- unc+ ucr- ucr+ unr- unr+
         Deassertions Enabled  : lnc- lnc+ lcr- lcr+ lnr- lnr+ unc- unc+ ucr- ucr+ unr- unr+
        </pre></details>
=== "Set the fan speed"
    === "Gigabyte R282-Z93, G292-Z43"
        ```
        Value | Speed, RPM
        -|-
        0     | 3,000
        25    | 4,200
        50    | 5,550
        75    | 6,750
        100   | 8,100
        125   | 9,450
        150   | 10,800
        200   | 13,350
        250   | 15,900
        ```
        For example, to set the fan speed to 8,100 RPM, use <b>100</b>:
        ```
        sudo ipmitool raw 0x2e 0x10 0x0a 0x3c 0 64 1 <b>100</b> 0xFF
        ```