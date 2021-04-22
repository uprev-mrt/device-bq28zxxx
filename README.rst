
BQ28Z
=====

- Generated with `MrT Device Utility <https://github.com/uprev-mrt/mrtutils/wiki/mrt-device>`_
- Bus:  I2C
- RegMap: `Register Map <Regmap.html>`_
- Datasheet: `http://www.ti.com/lit/ds... <http://www.ti.com/lit/ds/symlink/bq28z610.pdf>`_
- DigiKey: `296-43394-1-ND <https://www.digikey.com/products/en?KeyWords=296-43394-1-ND>`_
- I2C Address: 0xAA


Description
-----------

Battery Fuel Gauge

.. *user-block-description-start*

.. *user-block-description-end*





Register Map
------------

=================     ================     ================     ================     ================     ================
Name                    Address             Type                  Access              Default               Description
=================     ================     ================     ================     ================     ================
DUMMY_                 0x00                 uint16               R                    0xDEAD               dummy register       
ManufacturerAccess_ControlStatus_0x00                 uint16               RW                   0x0000               Control Register     
AtRate_                0x02                 int16                RW                   0x0000               Read/Write. The value is a signed integer with the negative value indicating a discharge current value. The default value is 0 and forces AtRateTimeToEmpty() to return 65535.
AtRateTimeToEmpty_     0x04                 uint16               R                    0x0000               This read-only function returns an unsigned integer value to predict remaining operating time based on battery discharge at the AtRate() value in minutes with a range of 0 to 65534. A value of 65535 indicates AtRate() = 0. The gas gauge updates the AtRateTimeToEmpty() within 1 s after the system sets the AtRate() value. The gas gauge updates these parameters every 1 s. The commands are used in NORMAL mode.
Temperature_           0x06                 uint16               R                    0x0000               This read-only function returns an unsigned integer value of temperature in units ( 0.1 k) measured by the gas gauge and is used for the gauging algorithm. It reports either InternalTemperature() or external thermistor temperature depending on the setting of the TEMPS bit in Pack configuration.
Voltage_               0x08                 uint16               R                    0x0000               This read-only function returns an unsigned integer value of the measured cell pack in mV with a range of 0 12000 mV.
BatteryStatus_         0x0A                 uint16               R                    0x0000               See the Flags register.
Current_               0x0C                 int16                R                    0x0000               This read-only function returns a signed integer value that is the instantaneous current flow through the sense resistor. The value is updated every 1 s. Units are mA.
MaxError_              0x0E                 uint8                R                    0x00                 This read-word function returns the expected margin of error
RemainingCapacity_     0x10                 uint16               R                    0x0000               This read-only command returns the predicted remaining capacity based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.
FullChargeCapacity_    0x12                 uint16               R                    0x0000               This read-only command returns the predicted capacity of the battery at full charge based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.
AverageCurrent_        0x14                 int16                R                    0x0000               This read-only function returns a signed integer value that is the average current flow through the sense resistor. The value is updated every 1 s. Units are mA.
AverageTimeToEmpty_    0x16                 uint16               R                    0x0000               Uses average current value with a time constant of 15 s for this method. A value of 65535 means the battery is not being discharged.
AverageTimeToFull_     0x18                 uint16               R                    0x0000               This read-only function returns a unsigned integer value predicting time to reach full charge for the battery in units of minutes based on AverageCurrent(). The computation accounts for the taper current time extension from linear TTF computation based on a fixed AverageCurrent() rate of charge accumulation. A value of 65535 indicates the battery is not being charged.
StandbyCurrent_        0x1A                 int16                R                    0x0000               This read-only function returns a signed integer value of measured standby current through the sense resistor. The StandbyCurrent() is an adaptive measurement. Initially it will report the standby current programmed in initial standby and after several seconds in standby mode will report the measured standby. The register value is updated every 1 s when measured current is above the deadband and is less than or equal to 2 × initial standby. The first and last values that meet these criteria are not averaged in since they may not be stable values. To approximate to a 1-min time constant each new value of StandbyCurrent() is computed by taking approximate 93% weight of the last standby current and approximate 7% of the current measured average current.
StandbyTimeToEmpty_    0x1C                 uint16               R                    0x0000               This read-only function returns a unsigned integer value predicting remaining battery life at standby rate of discharge in units of minutes. The computation uses Nominal Available Capacity (NAC) for the calculation. A value of 65535 indicates the battery is not being discharged.
MaxLoadCurrent_        0x1E                 int16                R                    0x0000               This read-only function returns a signed integer value in units of mA of maximum load conditions. The MaxLoadCurrent() is an adaptive measurement which is initially reported as the maximum load current programmed in initial Max Load Current register. If the measured current is ever greater than the initial Max Load Current then the MaxLoadCurrent() updates to the new current. MaxLoadCurrent() is reduced to the average of the previous value and initial Max Load Current whenever the battery is charged to full after a previous discharge to an SOC of less than 50%. This will prevent the reported value from maintaining an unusually high value.
MaxLoadTimeToEmpty_    0x20                 uint16               R                    0x0000               This read-only function returns a unsigned integer value predicting remaining battery life at the maximum discharge load current rate in units of minutes. A value of 65535 indicates that the battery is not being discharged.
AveragePower_          0x22                 int16                R                    0x0000               This read-only function returns a signed integer value of average power during battery charging and discharging. It is negative during discharge and positive during charge. A value of 0 indicates that the battery is not being discharged. The value is reported in units of mW.
BTPDischargeSet_       0x24                 int16                RW                   0x0000               This command sets the OperationStatusA BTP_INT and the BTP_INT pin will be asserted when the RemCap drops below the set threshold in DF register.
BTPChargeSet_          0x26                 int16                RW                   0x0000               This command clears the OperationStatusA BTP_INT and the BTP_INT pin will be deasserted.
InternalTemperature_   0x28                 uint16               R                    0x0000               This read-only function returns an unsigned integer value of the measured internal temperature of the device in 0.1-k units measured by the gas gauge.
CycleCount_            0x2A                 uint16               R                    0x0000               This read-only function returns an unsigned integer value of the number of cycles the battery has experienced a discharge (range 0 to 65535). One cycle occurs when accumulated discharge greater than or equal to CC threshold.
RelativeStateOfCharge_ 0x2C                 uint8                R                    0x00                 This read-only function returns an unsigned integer value of the predicted remaining battery capacity expressed as percentage of FullChargeCapacity() with a range of 0% to 100%.
StateOfHealth_         0x2E                 uint8                R                    0x00                 This read-only function returns an unsigned integer value expressed as a percentage of the ratio of predicted FCC (25C SoH Load Rate) over the DesignCapacity(). The range is 0x00 to 0x64 for 0% to 100% respectively.
ChargeVoltage_         0x30                 uint16               R                    0x0000               Returns the desired charging voltage in mV to the charger
ChargeCurrent_         0x32                 uint16               R                    0x0000               Returns the desired charging current in mA to the charger
DesignCapacity_        0x3C                 uint16               R                    0x0000               In SEALED and UNSEALED access This command returns the value stored in Design Capacity and is expressed in mAh. This is intended to be a theoretical or nominal capacity of a new pack but should have no bearing on the operation of the gas gauge functionality.
AltManufacturerAccess_ 0x3E                 uint16               R                    0x0000               MAC Data block command
MACData_               0x40                 uint16               R                    0x0000               MAC Data block       
SafetyAlert_           0x50                 uint32               R                    0x00000000           This command returns the SafetyAlert flags on AltManufacturerAccess or MACData.
MACDataSum_            0x60                 uint8                R                    0x00                 MAC Data block checksum
MACDataLen_            0x61                 uint8                R                    0x00                 MAC Data block length
=================     ================     ================     ================     ================     ================





Registers
---------





----------

.. _DUMMY:

DUMMY
-----

:Address: **[0x00]**
:Default: **[0xDEAD]**

dummy register

.. *user-block-dummy-start*

.. *user-block-dummy-end*

+------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
|Bit         |15       |14       |13       |12       |11       |10       |9        |8        |7        |6        |5        |4        |3        |2        |1        |0        |
+============+=========+=========+=========+=========+=========+=========+=========+=========+=========+=========+=========+=========+=========+=========+=========+=========+
| **Field**  |                                                                                                                                 |BIT1     |BIT0               |
+------------+---------------------------------------------------------------------------------------------------------------------------------+---------+-------------------+

Flags
~~~~~

:BIT0: creates a flag at bit 0 of the DUMMY register
:BIT1: creates a flag at bit 1 of the DUMMY register

Fields
~~~~~~

:REMAINING: creates a 14 bit field using the remaing bits

=====================     ================     ================================================================
Name                       Value               Descriptions
=====================     ================     ================================================================
MIN                         x00                     creates a macro for the minimum 14 bit value
MAX                         x3fff                   creates a macro for the maximum 14 bit value
=====================     ================     ================================================================




----------

.. _ManufacturerAccess_ControlStatus:

ManufacturerAccess_ControlStatus
--------------------------------

:Address: **[0x00]**
:Default: **[0x0000]**

Control Register

.. *user-block-manufactureraccess_controlstatus-start*

.. *user-block-manufactureraccess_controlstatus-end*

+------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
|Bit         |15           |14           |13           |12           |11           |10           |9            |8            |7            |6            |5            |4            |3            |2            |1            |0            |
+============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+
| **Field**  |SECURITY_Mode              |AUTHCALM                                 |CheckSumValid              |BTP_INT                                                |LDMD         |R_DIS        |VOK          |QMax                       |
+------------+---------------------------+-----------------------------------------+---------------------------+-------------------------------------------------------+-------------+-------------+-------------+---------------------------+

Flags
~~~~~

:AUTHCALM: Automatic Calibration Mode
:CheckSumValid: Checksum Valid
:BTP_INT: Battery Trip Point Interrupt. Setting and clearing this bit depends on various conditions
:LDMD: LOAD Mode
:R_DIS: Resistance Updates
:VOK: Voltage OK for QMax Update
:QMax: QMax Updates. This bit toggles after every QMax update.

Fields
~~~~~~

:SECURITY_Mode: Security Mode

=====================     ================     ================================================================
Name                       Value               Descriptions
=====================     ================     ================================================================
Reserved                    b00                     Reserved
Full_Access                 b01                     Full Access
Unsealed                    b10                     Unsealed
Sealed                      b11                     Sealed
=====================     ================     ================================================================




----------

.. _AtRate:

AtRate
------

:Address: **[0x02]**
:Default: **[0x0000]**

Read/Write. The value is a signed integer with the negative value indicating a discharge current value. The default value is 0 and forces AtRateTimeToEmpty() to return 65535.

.. *user-block-atrate-start*

.. *user-block-atrate-end*

+------------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
|Bit         |15    |14    |13    |12    |11    |10    |9     |8     |7     |6     |5     |4     |3     |2     |1     |0     |
+============+======+======+======+======+======+======+======+======+======+======+======+======+======+======+======+======+
| **Field**  |                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:AtRate: Read/Write. The value is a signed integer with the negative value indicating a discharge current value. The default value is 0 and forces AtRateTimeToEmpty() to return 65535.



----------

.. _AtRateTimeToEmpty:

AtRateTimeToEmpty
-----------------

:Address: **[0x04]**
:Default: **[0x0000]**

This read-only function returns an unsigned integer value to predict remaining operating time based on battery discharge at the AtRate() value in minutes with a range of 0 to 65534. A value of 65535 indicates AtRate() = 0. The gas gauge updates the AtRateTimeToEmpty() within 1 s after the system sets the AtRate() value. The gas gauge updates these parameters every 1 s. The commands are used in NORMAL mode.

.. *user-block-atratetimetoempty-start*

.. *user-block-atratetimetoempty-end*

+------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
|Bit         |15               |14               |13               |12               |11               |10               |9                |8                |7                |6                |5                |4                |3                |2                |1                |0                |
+============+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+
| **Field**  |                                                                                                                                                                                                                                                                                               |
+------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:AtRateTimeToEmpty: This read-only function returns an unsigned integer value to predict remaining operating time based on battery discharge at the AtRate() value in minutes with a range of 0 to 65534. A value of 65535 indicates AtRate() = 0. The gas gauge updates the AtRateTimeToEmpty() within 1 s after the system sets the AtRate() value. The gas gauge updates these parameters every 1 s. The commands are used in NORMAL mode.



----------

.. _Temperature:

Temperature
-----------

:Address: **[0x06]**
:Default: **[0x0000]**

This read-only function returns an unsigned integer value of temperature in units ( 0.1 k) measured by the gas gauge and is used for the gauging algorithm. It reports either InternalTemperature() or external thermistor temperature depending on the setting of the TEMPS bit in Pack configuration.

.. *user-block-temperature-start*

.. *user-block-temperature-end*

+------------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
|Bit         |15         |14         |13         |12         |11         |10         |9          |8          |7          |6          |5          |4          |3          |2          |1          |0          |
+============+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+===========+
| **Field**  |                                                                                                                                                                                               |
+------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:Temperature: This read-only function returns an unsigned integer value of temperature in units ( 0.1 k) measured by the gas gauge and is used for the gauging algorithm. It reports either InternalTemperature() or external thermistor temperature depending on the setting of the TEMPS bit in Pack configuration.



----------

.. _Voltage:

Voltage
-------

:Address: **[0x08]**
:Default: **[0x0000]**

This read-only function returns an unsigned integer value of the measured cell pack in mV with a range of 0 12000 mV.

.. *user-block-voltage-start*

.. *user-block-voltage-end*

+------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
|Bit         |15     |14     |13     |12     |11     |10     |9      |8      |7      |6      |5      |4      |3      |2      |1      |0      |
+============+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+
| **Field**  |                                                                                                                               |
+------------+-------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:Voltage: This read-only function returns an unsigned integer value of the measured cell pack in mV with a range of 0 12000 mV.



----------

.. _BatteryStatus:

BatteryStatus
-------------

:Address: **[0x0A]**
:Default: **[0x0000]**

See the Flags register.

.. *user-block-batterystatus-start*

.. *user-block-batterystatus-end*

+------------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+
|Bit         |15        |14        |13        |12        |11        |10        |9         |8         |7         |6         |5         |4         |3         |2         |1         |0         |
+============+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+
| **Field**  |TCA                  |OTA       |TDA                  |RCA       |RTA       |INIT      |DSG       |FC        |FD        |Error_Code                                            |
+------------+---------------------+----------+---------------------+----------+----------+----------+----------+----------+----------+------------------------------------------------------+

Flags
~~~~~

:FD: Fully Discharged
:FC: Fully Charged
:DSG: Discharging
:INIT: Initialization
:RTA: Remaining Time Alarm
:RCA: Remaining Capacity Alarm
:TDA: Terminate Discharge Alarm
:OTA: Overtemperature Alarm
:TCA: Terminate Charge Alarm
:OCA: Overcharged Alarm

Fields
~~~~~~

:Error_Code: Error Code

=====================     ================     ================================================================
Name                       Value               Descriptions
=====================     ================     ================================================================
OK                          b0000                   OK
Busy                        b0001                   Busy
Reserved_Command            b0010                   Reserved_Command
Unsupported_Command         b0011                   Unsupported_Command
AccessDenied                b0100                   AccessDenied
Overflow_Underflow          b0101                   Overflow_Underflow
BadSize                     b0110                   BadSize
UnknownError                b0111                   UnknownError
=====================     ================     ================================================================




----------

.. _Current:

Current
-------

:Address: **[0x0C]**
:Default: **[0x0000]**

This read-only function returns a signed integer value that is the instantaneous current flow through the sense resistor. The value is updated every 1 s. Units are mA.

.. *user-block-current-start*

.. *user-block-current-end*

+------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
|Bit         |15     |14     |13     |12     |11     |10     |9      |8      |7      |6      |5      |4      |3      |2      |1      |0      |
+============+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+
| **Field**  |                                                                                                                               |
+------------+-------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:Current: This read-only function returns a signed integer value that is the instantaneous current flow through the sense resistor. The value is updated every 1 s. Units are mA.



----------

.. _MaxError:

MaxError
--------

:Address: **[0x0E]**
:Default: **[0x00]**

This read-word function returns the expected margin of error

.. *user-block-maxerror-start*

.. *user-block-maxerror-end*

+------------+--------+--------+--------+--------+--------+--------+--------+--------+
|Bit         |7       |6       |5       |4       |3       |2       |1       |0       |
+============+========+========+========+========+========+========+========+========+
| **Field**  |                                                                       |
+------------+-----------------------------------------------------------------------+


Fields
~~~~~~

:MaxError: This read-word function returns the expected margin of error



----------

.. _RemainingCapacity:

RemainingCapacity
-----------------

:Address: **[0x10]**
:Default: **[0x0000]**

This read-only command returns the predicted remaining capacity based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.

.. *user-block-remainingcapacity-start*

.. *user-block-remainingcapacity-end*

+------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
|Bit         |15               |14               |13               |12               |11               |10               |9                |8                |7                |6                |5                |4                |3                |2                |1                |0                |
+============+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+
| **Field**  |                                                                                                                                                                                                                                                                                               |
+------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:RemainingCapacity: This read-only command returns the predicted remaining capacity based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.



----------

.. _FullChargeCapacity:

FullChargeCapacity
------------------

:Address: **[0x12]**
:Default: **[0x0000]**

This read-only command returns the predicted capacity of the battery at full charge based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.

.. *user-block-fullchargecapacity-start*

.. *user-block-fullchargecapacity-end*

+------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+
|Bit         |15                |14                |13                |12                |11                |10                |9                 |8                 |7                 |6                 |5                 |4                 |3                 |2                 |1                 |0                 |
+============+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+
| **Field**  |                                                                                                                                                                                                                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:FullChargeCapacity: This read-only command returns the predicted capacity of the battery at full charge based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.



----------

.. _AverageCurrent:

AverageCurrent
--------------

:Address: **[0x14]**
:Default: **[0x0000]**

This read-only function returns a signed integer value that is the average current flow through the sense resistor. The value is updated every 1 s. Units are mA.

.. *user-block-averagecurrent-start*

.. *user-block-averagecurrent-end*

+------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+
|Bit         |15            |14            |13            |12            |11            |10            |9             |8             |7             |6             |5             |4             |3             |2             |1             |0             |
+============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+
| **Field**  |                                                                                                                                                                                                                                               |
+------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:AverageCurrent: This read-only function returns a signed integer value that is the average current flow through the sense resistor. The value is updated every 1 s. Units are mA.



----------

.. _AverageTimeToEmpty:

AverageTimeToEmpty
------------------

:Address: **[0x16]**
:Default: **[0x0000]**

Uses average current value with a time constant of 15 s for this method. A value of 65535 means the battery is not being discharged.

.. *user-block-averagetimetoempty-start*

.. *user-block-averagetimetoempty-end*

+------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+
|Bit         |15                |14                |13                |12                |11                |10                |9                 |8                 |7                 |6                 |5                 |4                 |3                 |2                 |1                 |0                 |
+============+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+
| **Field**  |                                                                                                                                                                                                                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:AverageTimeToEmpty: Uses average current value with a time constant of 15 s for this method. A value of 65535 means the battery is not being discharged.



----------

.. _AverageTimeToFull:

AverageTimeToFull
-----------------

:Address: **[0x18]**
:Default: **[0x0000]**

This read-only function returns a unsigned integer value predicting time to reach full charge for the battery in units of minutes based on AverageCurrent(). The computation accounts for the taper current time extension from linear TTF computation based on a fixed AverageCurrent() rate of charge accumulation. A value of 65535 indicates the battery is not being charged.

.. *user-block-averagetimetofull-start*

.. *user-block-averagetimetofull-end*

+------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+
|Bit         |15               |14               |13               |12               |11               |10               |9                |8                |7                |6                |5                |4                |3                |2                |1                |0                |
+============+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+=================+
| **Field**  |                                                                                                                                                                                                                                                                                               |
+------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:AverageTimeToFull: This read-only function returns a unsigned integer value predicting time to reach full charge for the battery in units of minutes based on AverageCurrent(). The computation accounts for the taper current time extension from linear TTF computation based on a fixed AverageCurrent() rate of charge accumulation. A value of 65535 indicates the battery is not being charged.



----------

.. _StandbyCurrent:

StandbyCurrent
--------------

:Address: **[0x1A]**
:Default: **[0x0000]**

This read-only function returns a signed integer value of measured standby current through the sense resistor. The StandbyCurrent() is an adaptive measurement. Initially it will report the standby current programmed in initial standby and after several seconds in standby mode will report the measured standby. The register value is updated every 1 s when measured current is above the deadband and is less than or equal to 2 × initial standby. The first and last values that meet these criteria are not averaged in since they may not be stable values. To approximate to a 1-min time constant each new value of StandbyCurrent() is computed by taking approximate 93% weight of the last standby current and approximate 7% of the current measured average current.

.. *user-block-standbycurrent-start*

.. *user-block-standbycurrent-end*

+------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+
|Bit         |15            |14            |13            |12            |11            |10            |9             |8             |7             |6             |5             |4             |3             |2             |1             |0             |
+============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+
| **Field**  |                                                                                                                                                                                                                                               |
+------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:StandbyCurrent: This read-only function returns a signed integer value of measured standby current through the sense resistor. The StandbyCurrent() is an adaptive measurement. Initially it will report the standby current programmed in initial standby and after several seconds in standby mode will report the measured standby. The register value is updated every 1 s when measured current is above the deadband and is less than or equal to 2 × initial standby. The first and last values that meet these criteria are not averaged in since they may not be stable values. To approximate to a 1-min time constant each new value of StandbyCurrent() is computed by taking approximate 93% weight of the last standby current and approximate 7% of the current measured average current.



----------

.. _StandbyTimeToEmpty:

StandbyTimeToEmpty
------------------

:Address: **[0x1C]**
:Default: **[0x0000]**

This read-only function returns a unsigned integer value predicting remaining battery life at standby rate of discharge in units of minutes. The computation uses Nominal Available Capacity (NAC) for the calculation. A value of 65535 indicates the battery is not being discharged.

.. *user-block-standbytimetoempty-start*

.. *user-block-standbytimetoempty-end*

+------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+
|Bit         |15                |14                |13                |12                |11                |10                |9                 |8                 |7                 |6                 |5                 |4                 |3                 |2                 |1                 |0                 |
+============+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+
| **Field**  |                                                                                                                                                                                                                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:StandbyTimeToEmpty: This read-only function returns a unsigned integer value predicting remaining battery life at standby rate of discharge in units of minutes. The computation uses Nominal Available Capacity (NAC) for the calculation. A value of 65535 indicates the battery is not being discharged.



----------

.. _MaxLoadCurrent:

MaxLoadCurrent
--------------

:Address: **[0x1E]**
:Default: **[0x0000]**

This read-only function returns a signed integer value in units of mA of maximum load conditions. The MaxLoadCurrent() is an adaptive measurement which is initially reported as the maximum load current programmed in initial Max Load Current register. If the measured current is ever greater than the initial Max Load Current then the MaxLoadCurrent() updates to the new current. MaxLoadCurrent() is reduced to the average of the previous value and initial Max Load Current whenever the battery is charged to full after a previous discharge to an SOC of less than 50%. This will prevent the reported value from maintaining an unusually high value.

.. *user-block-maxloadcurrent-start*

.. *user-block-maxloadcurrent-end*

+------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+
|Bit         |15            |14            |13            |12            |11            |10            |9             |8             |7             |6             |5             |4             |3             |2             |1             |0             |
+============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+
| **Field**  |                                                                                                                                                                                                                                               |
+------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:MaxLoadCurrent: This read-only function returns a signed integer value in units of mA of maximum load conditions. The MaxLoadCurrent() is an adaptive measurement which is initially reported as the maximum load current programmed in initial Max Load Current register. If the measured current is ever greater than the initial Max Load Current then the MaxLoadCurrent() updates to the new current. MaxLoadCurrent() is reduced to the average of the previous value and initial Max Load Current whenever the battery is charged to full after a previous discharge to an SOC of less than 50%. This will prevent the reported value from maintaining an unusually high value.



----------

.. _MaxLoadTimeToEmpty:

MaxLoadTimeToEmpty
------------------

:Address: **[0x20]**
:Default: **[0x0000]**

This read-only function returns a unsigned integer value predicting remaining battery life at the maximum discharge load current rate in units of minutes. A value of 65535 indicates that the battery is not being discharged.

.. *user-block-maxloadtimetoempty-start*

.. *user-block-maxloadtimetoempty-end*

+------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+------------------+
|Bit         |15                |14                |13                |12                |11                |10                |9                 |8                 |7                 |6                 |5                 |4                 |3                 |2                 |1                 |0                 |
+============+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+==================+
| **Field**  |                                                                                                                                                                                                                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:MaxLoadTimeToEmpty: This read-only function returns a unsigned integer value predicting remaining battery life at the maximum discharge load current rate in units of minutes. A value of 65535 indicates that the battery is not being discharged.



----------

.. _AveragePower:

AveragePower
------------

:Address: **[0x22]**
:Default: **[0x0000]**

This read-only function returns a signed integer value of average power during battery charging and discharging. It is negative during discharge and positive during charge. A value of 0 indicates that the battery is not being discharged. The value is reported in units of mW.

.. *user-block-averagepower-start*

.. *user-block-averagepower-end*

+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+
|Bit         |15          |14          |13          |12          |11          |10          |9           |8           |7           |6           |5           |4           |3           |2           |1           |0           |
+============+============+============+============+============+============+============+============+============+============+============+============+============+============+============+============+============+
| **Field**  |                                                                                                                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:AveragePower: This read-only function returns a signed integer value of average power during battery charging and discharging. It is negative during discharge and positive during charge. A value of 0 indicates that the battery is not being discharged. The value is reported in units of mW.



----------

.. _BTPDischargeSet:

BTPDischargeSet
---------------

:Address: **[0x24]**
:Default: **[0x0000]**

This command sets the OperationStatusA BTP_INT and the BTP_INT pin will be asserted when the RemCap drops below the set threshold in DF register.

.. *user-block-btpdischargeset-start*

.. *user-block-btpdischargeset-end*

+------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+
|Bit         |15             |14             |13             |12             |11             |10             |9              |8              |7              |6              |5              |4              |3              |2              |1              |0              |
+============+===============+===============+===============+===============+===============+===============+===============+===============+===============+===============+===============+===============+===============+===============+===============+===============+
| **Field**  |                                                                                                                                                                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:BTPDischargeSet: This command sets the OperationStatusA BTP_INT and the BTP_INT pin will be asserted when the RemCap drops below the set threshold in DF register.



----------

.. _BTPChargeSet:

BTPChargeSet
------------

:Address: **[0x26]**
:Default: **[0x0000]**

This command clears the OperationStatusA BTP_INT and the BTP_INT pin will be deasserted.

.. *user-block-btpchargeset-start*

.. *user-block-btpchargeset-end*

+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+------------+
|Bit         |15          |14          |13          |12          |11          |10          |9           |8           |7           |6           |5           |4           |3           |2           |1           |0           |
+============+============+============+============+============+============+============+============+============+============+============+============+============+============+============+============+============+
| **Field**  |                                                                                                                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:BTPChargeSet: This command clears the OperationStatusA BTP_INT and the BTP_INT pin will be deasserted.



----------

.. _InternalTemperature:

InternalTemperature
-------------------

:Address: **[0x28]**
:Default: **[0x0000]**

This read-only function returns an unsigned integer value of the measured internal temperature of the device in 0.1-k units measured by the gas gauge.

.. *user-block-internaltemperature-start*

.. *user-block-internaltemperature-end*

+------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+
|Bit         |15                 |14                 |13                 |12                 |11                 |10                 |9                  |8                  |7                  |6                  |5                  |4                  |3                  |2                  |1                  |0                  |
+============+===================+===================+===================+===================+===================+===================+===================+===================+===================+===================+===================+===================+===================+===================+===================+===================+
| **Field**  |                                                                                                                                                                                                                                                                                                                               |
+------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:InternalTemperature: This read-only function returns an unsigned integer value of the measured internal temperature of the device in 0.1-k units measured by the gas gauge.



----------

.. _CycleCount:

CycleCount
----------

:Address: **[0x2A]**
:Default: **[0x0000]**

This read-only function returns an unsigned integer value of the number of cycles the battery has experienced a discharge (range 0 to 65535). One cycle occurs when accumulated discharge greater than or equal to CC threshold.

.. *user-block-cyclecount-start*

.. *user-block-cyclecount-end*

+------------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+
|Bit         |15        |14        |13        |12        |11        |10        |9         |8         |7         |6         |5         |4         |3         |2         |1         |0         |
+============+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+==========+
| **Field**  |                                                                                                                                                                               |
+------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:CycleCount: This read-only function returns an unsigned integer value of the number of cycles the battery has experienced a discharge (range 0 to 65535). One cycle occurs when accumulated discharge greater than or equal to CC threshold.



----------

.. _RelativeStateOfCharge:

RelativeStateOfCharge
---------------------

:Address: **[0x2C]**
:Default: **[0x00]**

This read-only function returns an unsigned integer value of the predicted remaining battery capacity expressed as percentage of FullChargeCapacity() with a range of 0% to 100%.

.. *user-block-relativestateofcharge-start*

.. *user-block-relativestateofcharge-end*

+------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+
|Bit         |7                    |6                    |5                    |4                    |3                    |2                    |1                    |0                    |
+============+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+
| **Field**  |                                                                                                                                                                               |
+------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:RelativeStateOfCharge: This read-only function returns an unsigned integer value of the predicted remaining battery capacity expressed as percentage of FullChargeCapacity() with a range of 0% to 100%.



----------

.. _StateOfHealth:

StateOfHealth
-------------

:Address: **[0x2E]**
:Default: **[0x00]**

This read-only function returns an unsigned integer value expressed as a percentage of the ratio of predicted FCC (25C SoH Load Rate) over the DesignCapacity(). The range is 0x00 to 0x64 for 0% to 100% respectively.

.. *user-block-stateofhealth-start*

.. *user-block-stateofhealth-end*

+------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
|Bit         |7            |6            |5            |4            |3            |2            |1            |0            |
+============+=============+=============+=============+=============+=============+=============+=============+=============+
| **Field**  |                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:StateOfHealth: This read-only function returns an unsigned integer value expressed as a percentage of the ratio of predicted FCC (25C SoH Load Rate) over the DesignCapacity(). The range is 0x00 to 0x64 for 0% to 100% respectively.



----------

.. _ChargeVoltage:

ChargeVoltage
-------------

:Address: **[0x30]**
:Default: **[0x0000]**

Returns the desired charging voltage in mV to the charger

.. *user-block-chargevoltage-start*

.. *user-block-chargevoltage-end*

+------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
|Bit         |15           |14           |13           |12           |11           |10           |9            |8            |7            |6            |5            |4            |3            |2            |1            |0            |
+============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+
| **Field**  |                                                                                                                                                                                                                               |
+------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:ChargeVoltage: Returns the desired charging voltage in mV to the charger



----------

.. _ChargeCurrent:

ChargeCurrent
-------------

:Address: **[0x32]**
:Default: **[0x0000]**

Returns the desired charging current in mA to the charger

.. *user-block-chargecurrent-start*

.. *user-block-chargecurrent-end*

+------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+
|Bit         |15           |14           |13           |12           |11           |10           |9            |8            |7            |6            |5            |4            |3            |2            |1            |0            |
+============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+=============+
| **Field**  |                                                                                                                                                                                                                               |
+------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:ChargeCurrent: Returns the desired charging current in mA to the charger



----------

.. _DesignCapacity:

DesignCapacity
--------------

:Address: **[0x3C]**
:Default: **[0x0000]**

In SEALED and UNSEALED access This command returns the value stored in Design Capacity and is expressed in mAh. This is intended to be a theoretical or nominal capacity of a new pack but should have no bearing on the operation of the gas gauge functionality.

.. *user-block-designcapacity-start*

.. *user-block-designcapacity-end*

+------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+
|Bit         |15            |14            |13            |12            |11            |10            |9             |8             |7             |6             |5             |4             |3             |2             |1             |0             |
+============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+==============+
| **Field**  |                                                                                                                                                                                                                                               |
+------------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:DesignCapacity: In SEALED and UNSEALED access This command returns the value stored in Design Capacity and is expressed in mAh. This is intended to be a theoretical or nominal capacity of a new pack but should have no bearing on the operation of the gas gauge functionality.



----------

.. _AltManufacturerAccess:

AltManufacturerAccess
---------------------

:Address: **[0x3E]**
:Default: **[0x0000]**

MAC Data block command

.. *user-block-altmanufactureraccess-start*

.. *user-block-altmanufactureraccess-end*

+------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+
|Bit         |15                   |14                   |13                   |12                   |11                   |10                   |9                    |8                    |7                    |6                    |5                    |4                    |3                    |2                    |1                    |0                    |
+============+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+=====================+
| **Field**  |                                                                                                                                                                                                                                                                                                                                                               |
+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:AltManufacturerAccess: MAC Data block command



----------

.. _MACData:

MACData
-------

:Address: **[0x40]**
:Default: **[0x0000]**

MAC Data block

.. *user-block-macdata-start*

.. *user-block-macdata-end*

+------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+
|Bit         |15     |14     |13     |12     |11     |10     |9      |8      |7      |6      |5      |4      |3      |2      |1      |0      |
+============+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+=======+
| **Field**  |                                                                                                                               |
+------------+-------------------------------------------------------------------------------------------------------------------------------+


Fields
~~~~~~

:MACData: MAC Data block



----------

.. _SafetyAlert:

SafetyAlert
-----------

:Address: **[0x50]**
:Default: **[0x00000000]**

This command returns the SafetyAlert flags on AltManufacturerAccess or MACData.

.. *user-block-safetyalert-start*

.. *user-block-safetyalert-end*

+------------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
|Bit         |31  |30  |29  |28  |27  |26  |25  |24  |23  |22  |21  |20  |19  |18  |17  |16  |15  |14  |13  |12  |11  |10  |9   |8   |7   |6   |5   |4   |3   |2   |1   |0   |
+============+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+
| **Field**  |              |UTD |UTC                     |CTOS     |PTOS                         |OTD |OTC      |ASCD     |ASCC     |AOLD     |OCD      |OCC |COV |CUV      |
+------------+--------------+----+------------------------+---------+-----------------------------+----+---------+---------+---------+---------+---------+----+----+---------+

Flags
~~~~~

:UTD: Undertemperature During Discharge
:UTC: Undertemperature During Charge
:CTOS: Charge Timeout Suspend
:PTOS: Precharge Timeout Suspend
:OTD: Overtemperature During Discharge
:OTC: Overtemperature During Charge
:ASCD: Short-Circuit During Discharge
:ASCC: Short-Circuit During Charge
:AOLD: Overload During Discharge
:OCD: Overcurrent During Discharge
:OCC: Overcurrent During Charge
:COV: Cell Overvoltage
:CUV: Cell Undervoltage



----------

.. _MACDataSum:

MACDataSum
----------

:Address: **[0x60]**
:Default: **[0x00]**

MAC Data block checksum

.. *user-block-macdatasum-start*

.. *user-block-macdatasum-end*

+------------+----------+----------+----------+----------+----------+----------+----------+----------+
|Bit         |7         |6         |5         |4         |3         |2         |1         |0         |
+============+==========+==========+==========+==========+==========+==========+==========+==========+
| **Field**  |                                                                                       |
+------------+---------------------------------------------------------------------------------------+


Fields
~~~~~~

:MACDataSum: MAC Data block checksum



----------

.. _MACDataLen:

MACDataLen
----------

:Address: **[0x61]**
:Default: **[0x00]**

MAC Data block length

.. *user-block-macdatalen-start*

.. *user-block-macdatalen-end*

+------------+----------+----------+----------+----------+----------+----------+----------+----------+
|Bit         |7         |6         |5         |4         |3         |2         |1         |0         |
+============+==========+==========+==========+==========+==========+==========+==========+==========+
| **Field**  |                                                                                       |
+------------+---------------------------------------------------------------------------------------+


Fields
~~~~~~

:MACDataLen: MAC Data block length

