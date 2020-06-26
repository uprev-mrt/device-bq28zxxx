
<h1>BQ28Z Device</h1>
<ul>
  <li> Generated with <a href="https://github.com/uprev-mrt/mrtutils/wiki/mrt-device">MrT Device Utility</a> </li>
  <li> Bus:  I2C</li>
  <li> RegMap: <a href="Regmap.html">Register Map</a>
  <li>Datasheet: <a href="http://www.ti.com/lit/ds/symlink/bq28z610.pdf">http://www.ti.com/lit/ds...</a> </li>
  <li> DigiKey: <a href="https://www.digikey.com/products/en?KeyWords=296-43394-1-ND">296-43394-1-ND</a></li>
  <li> I2C Address: 0xAA</li>
</ul>
<hr/>
<h2>Description: </h2>
<p>Battery Fuel Gauge</p>

<!--*user-block-description-start*-->

<!--*user-block-description-end*-->
<br/>


<hr class="section">
<h2 class="right"> Register Map</h2>
<hr class="thick">

<table class="fields">
    <tr>
        <th>Name</th>
        <th>Address</th>
        <th>Type</th>
        <th>Access</th>
        <th>Default</th>
        <th>Description</th>
    </tr>
    <tr>
        <td><a href="#register_dummy_detail">DUMMY</a></td>
        <td>0x00</td>
        <td>uint16</td>
        <td>R</td>
        <td>0xDEAD</td>
        <td>dummy register</td>
    </tr>
    <tr>
        <td><a href="#register_manufactureraccess_controlstatus_detail">ManufacturerAccess_ControlStatus</a></td>
        <td>0x00</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>Control Register</td>
    </tr>
    <tr>
        <td><a href="#register_atrate_detail">AtRate</a></td>
        <td>0x02</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>Read/Write. The value is a signed integer with the negative value indicating a discharge current value. The default value is 0 and forces AtRateTimeToEmpty() to return 65535.</td>
    </tr>
    <tr>
        <td><a href="#register_atratetimetoempty_detail">AtRateTimeToEmpty</a></td>
        <td>0x04</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This read-only function returns an unsigned integer value to predict remaining operating time based on battery discharge at the AtRate() value in minutes with a range of 0 to 65534. A value of 65535 indicates AtRate() = 0. The gas gauge updates the AtRateTimeToEmpty() within 1 s after the system sets the AtRate() value. The gas gauge updates these parameters every 1 s. The commands are used in NORMAL mode.</td>
    </tr>
    <tr>
        <td><a href="#register_temperature_detail">Temperature</a></td>
        <td>0x06</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This read-only function returns an unsigned integer value of temperature in units ( 0.1 k) measured by the gas gauge and is used for the gauging algorithm. It reports either InternalTemperature() or external thermistor temperature depending on the setting of the TEMPS bit in Pack configuration.</td>
    </tr>
    <tr>
        <td><a href="#register_voltage_detail">Voltage</a></td>
        <td>0x08</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This read-only function returns an unsigned integer value of the measured cell pack in mV with a range of 0 12000 mV.</td>
    </tr>
    <tr>
        <td><a href="#register_batterystatus_detail">BatteryStatus</a></td>
        <td>0x0A</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>See the Flags register.</td>
    </tr>
    <tr>
        <td><a href="#register_current_detail">Current</a></td>
        <td>0x0C</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This read-only function returns a signed integer value that is the instantaneous current flow through the sense resistor. The value is updated every 1 s. Units are mA.</td>
    </tr>
    <tr>
        <td><a href="#register_maxerror_detail">MaxError</a></td>
        <td>0x0E</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This read-word function returns the expected margin of error</td>
    </tr>
    <tr>
        <td><a href="#register_remainingcapacity_detail">RemainingCapacity</a></td>
        <td>0x10</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This read-only command returns the predicted remaining capacity based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.</td>
    </tr>
    <tr>
        <td><a href="#register_fullchargecapacity_detail">FullChargeCapacity</a></td>
        <td>0x12</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This read-only command returns the predicted capacity of the battery at full charge based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.</td>
    </tr>
    <tr>
        <td><a href="#register_averagecurrent_detail">AverageCurrent</a></td>
        <td>0x14</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns a signed integer value that is the average current flow through the sense resistor. The value is updated every 1 s. Units are mA.</td>
    </tr>
    <tr>
        <td><a href="#register_averagetimetoempty_detail">AverageTimeToEmpty</a></td>
        <td>0x16</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>Uses average current value with a time constant of 15 s for this method. A value of 65535 means the battery is not being discharged.</td>
    </tr>
    <tr>
        <td><a href="#register_averagetimetofull_detail">AverageTimeToFull</a></td>
        <td>0x18</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns a unsigned integer value predicting time to reach full charge for the battery in units of minutes based on AverageCurrent(). The computation accounts for the taper current time extension from linear TTF computation based on a fixed AverageCurrent() rate of charge accumulation. A value of 65535 indicates the battery is not being charged.</td>
    </tr>
    <tr>
        <td><a href="#register_standbycurrent_detail">StandbyCurrent</a></td>
        <td>0x1A</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns a signed integer value of measured standby current through the sense resistor. The StandbyCurrent() is an adaptive measurement. Initially it will report the standby current programmed in initial standby and after several seconds in standby mode will report the measured standby. The register value is updated every 1 s when measured current is above the deadband and is less than or equal to 2 × initial standby. The first and last values that meet these criteria are not averaged in since they may not be stable values. To approximate to a 1-min time constant each new value of StandbyCurrent() is computed by taking approximate 93% weight of the last standby current and approximate 7% of the current measured average current.</td>
    </tr>
    <tr>
        <td><a href="#register_standbytimetoempty_detail">StandbyTimeToEmpty</a></td>
        <td>0x1C</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns a unsigned integer value predicting remaining battery life at standby rate of discharge in units of minutes. The computation uses Nominal Available Capacity (NAC) for the calculation. A value of 65535 indicates the battery is not being discharged.</td>
    </tr>
    <tr>
        <td><a href="#register_maxloadcurrent_detail">MaxLoadCurrent</a></td>
        <td>0x1E</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns a signed integer value in units of mA of maximum load conditions. The MaxLoadCurrent() is an adaptive measurement which is initially reported as the maximum load current programmed in initial Max Load Current register. If the measured current is ever greater than the initial Max Load Current then the MaxLoadCurrent() updates to the new current. MaxLoadCurrent() is reduced to the average of the previous value and initial Max Load Current whenever the battery is charged to full after a previous discharge to an SOC of less than 50%. This will prevent the reported value from maintaining an unusually high value.</td>
    </tr>
    <tr>
        <td><a href="#register_maxloadtimetoempty_detail">MaxLoadTimeToEmpty</a></td>
        <td>0x20</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns a unsigned integer value predicting remaining battery life at the maximum discharge load current rate in units of minutes. A value of 65535 indicates that the battery is not being discharged.</td>
    </tr>
    <tr>
        <td><a href="#register_averagepower_detail">AveragePower</a></td>
        <td>0x22</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns a signed integer value of average power during battery charging and discharging. It is negative during discharge and positive during charge. A value of 0 indicates that the battery is not being discharged. The value is reported in units of mW.</td>
    </tr>
    <tr>
        <td><a href="#register_btpdischargeset_detail">BTPDischargeSet</a></td>
        <td>0x24</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This command sets the OperationStatusA BTP_INT and the BTP_INT pin will be asserted when the RemCap drops below the set threshold in DF register.</td>
    </tr>
    <tr>
        <td><a href="#register_btpchargeset_detail">BTPChargeSet</a></td>
        <td>0x26</td>
        <td>uint16</td>
        <td>RW</td>
        <td>0x0000</td>
        <td>This command clears the OperationStatusA BTP_INT and the BTP_INT pin will be deasserted.</td>
    </tr>
    <tr>
        <td><a href="#register_internaltemperature_detail">InternalTemperature</a></td>
        <td>0x28</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns an unsigned integer value of the measured internal temperature of the device in 0.1-k units measured by the gas gauge.</td>
    </tr>
    <tr>
        <td><a href="#register_cyclecount_detail">CycleCount</a></td>
        <td>0x2A</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns an unsigned integer value of the number of cycles the battery has experienced a discharge (range 0 to 65535). One cycle occurs when accumulated discharge greater than or equal to CC threshold.</td>
    </tr>
    <tr>
        <td><a href="#register_relativestateofcharge_detail">RelativeStateOfCharge</a></td>
        <td>0x2C</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns an unsigned integer value of the predicted remaining battery capacity expressed as percentage of FullChargeCapacity() with a range of 0% to 100%.</td>
    </tr>
    <tr>
        <td><a href="#register_stateofhealth_detail">StateOfHealth</a></td>
        <td>0x2E</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>This read-only function returns an unsigned integer value expressed as a percentage of the ratio of predicted FCC (25C SoH Load Rate) over the DesignCapacity(). The range is 0x00 to 0x64 for 0% to 100% respectively.</td>
    </tr>
    <tr>
        <td><a href="#register_chargevoltage_detail">ChargeVoltage</a></td>
        <td>0x30</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>Returns the desired charging voltage in mV to the charger</td>
    </tr>
    <tr>
        <td><a href="#register_chargecurrent_detail">ChargeCurrent</a></td>
        <td>0x32</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>Returns the desired charging current in mA to the charger</td>
    </tr>
    <tr>
        <td><a href="#register_designcapacity_detail">DesignCapacity</a></td>
        <td>0x3C</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>In SEALED and UNSEALED access This command returns the value stored in Design Capacity and is expressed in mAh. This is intended to be a theoretical or nominal capacity of a new pack but should have no bearing on the operation of the gas gauge functionality.</td>
    </tr>
    <tr>
        <td><a href="#register_altmanufactureraccess_detail">AltManufacturerAccess</a></td>
        <td>0x3E</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>MAC Data block command</td>
    </tr>
    <tr>
        <td><a href="#register_macdata_detail">MACData</a></td>
        <td>0x40</td>
        <td>uint16</td>
        <td>R</td>
        <td>0x0000</td>
        <td>MAC Data block</td>
    </tr>
    <tr>
        <td><a href="#register_macdatasum_detail">MACDataSum</a></td>
        <td>0x60</td>
        <td>uint8</td>
        <td>R</td>
        <td>0x00</td>
        <td>MAC Data block checksum</td>
    </tr>
    <tr>
        <td><a href="#register_macdatalen_detail">MACDataLen</a></td>
        <td>0x61</td>
        <td>uint8</td>
        <td>R</td>
        <td>0x00</td>
        <td>MAC Data block length</td>
    </tr>

</table>



<hr class="section">
<h2 class="right"> Registers</h2>
<hr class="thick">



<div id="register_dummy_detail" class="packet">
<h2>DUMMY </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x00]</b></li>
    <li class="note">  Default: <b>[0xDEAD]</b></li>
</ul>

<p>dummy register</p>
<!--*user-block-dummy-start*-->

<!--*user-block-dummy-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="14">REMAINING</td>
<td class="field" colspan="1">BIT1</td>
<td class="field" colspan="1">BIT0</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="one" >1</td>
      <td class="one" >1</td>
      <td class="zero" >0</td>
      <td class="one" >1</td>
      <td class="one" >1</td>
      <td class="one" >1</td>
      <td class="one" >1</td>
      <td class="zero" >0</td>
      <td class="one" >1</td>
      <td class="zero" >0</td>
      <td class="one" >1</td>
      <td class="zero" >0</td>
      <td class="one" >1</td>
      <td class="one" >1</td>
      <td class="zero" >0</td>
      <td class="one" >1</td>
   </tr>
</table>

<h2> Flags:</h2>
<b>BIT0:</b> creates a flag at bit 0 of the DUMMY register<br>
<b>BIT1:</b> creates a flag at bit 1 of the DUMMY register<br>

<h2> Fields:</h2>

<b>REMAINING:</b> creates a 14 bit field using the remaing bits
<table>
<tr><td> MIN </td><td> x00 </td><td>  creates a macro for the minimum 14 bit value</td></tr>
<tr><td> MAX </td><td> x3fff </td><td>  creates a macro for the maximum 14 bit value</td></tr>
</table>



<div id="register_manufactureraccess_controlstatus_detail" class="packet">
<h2>ManufacturerAccess_ControlStatus </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x00]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>Control Register</p>
<!--*user-block-manufactureraccess_controlstatus-start*-->

<!--*user-block-manufactureraccess_controlstatus-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="empty" colspan="1"></td>
<td class="field" colspan="2">SECURITY_Mode</td>
<td class="field" colspan="1">AUTHCALM</td>
<td class="empty" colspan="2"></td>
<td class="field" colspan="1">CheckSumValid</td>
<td class="empty" colspan="1"></td>
<td class="field" colspan="1">BTP_INT</td>
<td class="empty" colspan="3"></td>
<td class="field" colspan="1">LDMD</td>
<td class="field" colspan="1">R_DIS</td>
<td class="field" colspan="1">VOK</td>
<td class="field" colspan="1">QMax</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>

<h2> Flags:</h2>
<b>AUTHCALM:</b> Automatic Calibration Mode<br>
<b>CheckSumValid:</b> Checksum Valid<br>
<b>BTP_INT:</b> Battery Trip Point Interrupt. Setting and clearing this bit depends on various conditions<br>
<b>LDMD:</b> LOAD Mode<br>
<b>R_DIS:</b> Resistance Updates<br>
<b>VOK:</b> Voltage OK for QMax Update<br>
<b>QMax:</b> QMax Updates. This bit toggles after every QMax update.<br>

<h2> Fields:</h2>

<b>SECURITY_Mode:</b> Security Mode
<table>
<tr><td> Reserved </td><td> b00 </td><td>  Reserved</td></tr>
<tr><td> Full_Access </td><td> b01 </td><td>  Full Access</td></tr>
<tr><td> Unsealed </td><td> b10 </td><td>  Unsealed</td></tr>
<tr><td> Sealed </td><td> b11 </td><td>  Sealed</td></tr>
</table>



<div id="register_atrate_detail" class="packet">
<h2>AtRate </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x02]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>Read/Write. The value is a signed integer with the negative value indicating a discharge current value. The default value is 0 and forces AtRateTimeToEmpty() to return 65535.</p>
<!--*user-block-atrate-start*-->

<!--*user-block-atrate-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">AtRate</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>AtRate:</b> Read/Write. The value is a signed integer with the negative value indicating a discharge current value. The default value is 0 and forces AtRateTimeToEmpty() to return 65535.


<div id="register_atratetimetoempty_detail" class="packet">
<h2>AtRateTimeToEmpty </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x04]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns an unsigned integer value to predict remaining operating time based on battery discharge at the AtRate() value in minutes with a range of 0 to 65534. A value of 65535 indicates AtRate() = 0. The gas gauge updates the AtRateTimeToEmpty() within 1 s after the system sets the AtRate() value. The gas gauge updates these parameters every 1 s. The commands are used in NORMAL mode.</p>
<!--*user-block-atratetimetoempty-start*-->

<!--*user-block-atratetimetoempty-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">AtRateTimeToEmpty</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>AtRateTimeToEmpty:</b> This read-only function returns an unsigned integer value to predict remaining operating time based on battery discharge at the AtRate() value in minutes with a range of 0 to 65534. A value of 65535 indicates AtRate() = 0. The gas gauge updates the AtRateTimeToEmpty() within 1 s after the system sets the AtRate() value. The gas gauge updates these parameters every 1 s. The commands are used in NORMAL mode.


<div id="register_temperature_detail" class="packet">
<h2>Temperature </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x06]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns an unsigned integer value of temperature in units ( 0.1 k) measured by the gas gauge and is used for the gauging algorithm. It reports either InternalTemperature() or external thermistor temperature depending on the setting of the TEMPS bit in Pack configuration.</p>
<!--*user-block-temperature-start*-->

<!--*user-block-temperature-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">Temperature</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>Temperature:</b> This read-only function returns an unsigned integer value of temperature in units ( 0.1 k) measured by the gas gauge and is used for the gauging algorithm. It reports either InternalTemperature() or external thermistor temperature depending on the setting of the TEMPS bit in Pack configuration.


<div id="register_voltage_detail" class="packet">
<h2>Voltage </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x08]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns an unsigned integer value of the measured cell pack in mV with a range of 0 12000 mV.</p>
<!--*user-block-voltage-start*-->

<!--*user-block-voltage-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">Voltage</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>Voltage:</b> This read-only function returns an unsigned integer value of the measured cell pack in mV with a range of 0 12000 mV.


<div id="register_batterystatus_detail" class="packet">
<h2>BatteryStatus </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x0A]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>See the Flags register.</p>
<!--*user-block-batterystatus-start*-->

<!--*user-block-batterystatus-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="1">OCA</td>
<td class="field" colspan="1">TCA</td>
<td class="empty" colspan="1"></td>
<td class="field" colspan="1">OTA</td>
<td class="field" colspan="1">TDA</td>
<td class="empty" colspan="1"></td>
<td class="field" colspan="1">RCA</td>
<td class="field" colspan="1">RTA</td>
<td class="field" colspan="1">INIT</td>
<td class="field" colspan="1">DSG</td>
<td class="field" colspan="1">FC</td>
<td class="field" colspan="1">FD</td>
<td class="field" colspan="4">Error_Code</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>

<h2> Flags:</h2>
<b>FD:</b> Fully Discharged<br>
<b>FC:</b> Fully Charged<br>
<b>DSG:</b> Discharging<br>
<b>INIT:</b> Initialization<br>
<b>RTA:</b> Remaining Time Alarm<br>
<b>RCA:</b> Remaining Capacity Alarm<br>
<b>TDA:</b> Terminate Discharge Alarm<br>
<b>OTA:</b> Overtemperature Alarm<br>
<b>TCA:</b> Terminate Charge Alarm<br>
<b>OCA:</b> Overcharged Alarm<br>

<h2> Fields:</h2>

<b>Error_Code:</b> Error Code
<table>
<tr><td> OK </td><td> b0000 </td><td>  OK</td></tr>
<tr><td> Busy </td><td> b0001 </td><td>  Busy</td></tr>
<tr><td> Reserved_Command </td><td> b0010 </td><td>  Reserved_Command</td></tr>
<tr><td> Unsupported_Command </td><td> b0011 </td><td>  Unsupported_Command</td></tr>
<tr><td> AccessDenied </td><td> b0100 </td><td>  AccessDenied</td></tr>
<tr><td> Overflow_Underflow </td><td> b0101 </td><td>  Overflow_Underflow</td></tr>
<tr><td> BadSize </td><td> b0110 </td><td>  BadSize</td></tr>
<tr><td> UnknownError </td><td> b0111 </td><td>  UnknownError</td></tr>
</table>



<div id="register_current_detail" class="packet">
<h2>Current </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x0C]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns a signed integer value that is the instantaneous current flow through the sense resistor. The value is updated every 1 s. Units are mA.</p>
<!--*user-block-current-start*-->

<!--*user-block-current-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">Current</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>Current:</b> This read-only function returns a signed integer value that is the instantaneous current flow through the sense resistor. The value is updated every 1 s. Units are mA.


<div id="register_maxerror_detail" class="packet">
<h2>MaxError </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x0E]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-word function returns the expected margin of error</p>
<!--*user-block-maxerror-start*-->

<!--*user-block-maxerror-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">MaxError</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>MaxError:</b> This read-word function returns the expected margin of error


<div id="register_remainingcapacity_detail" class="packet">
<h2>RemainingCapacity </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x10]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only command returns the predicted remaining capacity based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.</p>
<!--*user-block-remainingcapacity-start*-->

<!--*user-block-remainingcapacity-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">RemainingCapacity</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>RemainingCapacity:</b> This read-only command returns the predicted remaining capacity based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.


<div id="register_fullchargecapacity_detail" class="packet">
<h2>FullChargeCapacity </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x12]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only command returns the predicted capacity of the battery at full charge based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.</p>
<!--*user-block-fullchargecapacity-start*-->

<!--*user-block-fullchargecapacity-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">FullChargeCapacity</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>FullChargeCapacity:</b> This read-only command returns the predicted capacity of the battery at full charge based on rate (per configured Load Select) temperature present depth-of-discharge and stored impedance. Values are reported in mAh.


<div id="register_averagecurrent_detail" class="packet">
<h2>AverageCurrent </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x14]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns a signed integer value that is the average current flow through the sense resistor. The value is updated every 1 s. Units are mA.</p>
<!--*user-block-averagecurrent-start*-->

<!--*user-block-averagecurrent-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">AverageCurrent</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>AverageCurrent:</b> This read-only function returns a signed integer value that is the average current flow through the sense resistor. The value is updated every 1 s. Units are mA.


<div id="register_averagetimetoempty_detail" class="packet">
<h2>AverageTimeToEmpty </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x16]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>Uses average current value with a time constant of 15 s for this method. A value of 65535 means the battery is not being discharged.</p>
<!--*user-block-averagetimetoempty-start*-->

<!--*user-block-averagetimetoempty-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">AverageTimeToEmpty</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>AverageTimeToEmpty:</b> Uses average current value with a time constant of 15 s for this method. A value of 65535 means the battery is not being discharged.


<div id="register_averagetimetofull_detail" class="packet">
<h2>AverageTimeToFull </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x18]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns a unsigned integer value predicting time to reach full charge for the battery in units of minutes based on AverageCurrent(). The computation accounts for the taper current time extension from linear TTF computation based on a fixed AverageCurrent() rate of charge accumulation. A value of 65535 indicates the battery is not being charged.</p>
<!--*user-block-averagetimetofull-start*-->

<!--*user-block-averagetimetofull-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">AverageTimeToFull</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>AverageTimeToFull:</b> This read-only function returns a unsigned integer value predicting time to reach full charge for the battery in units of minutes based on AverageCurrent(). The computation accounts for the taper current time extension from linear TTF computation based on a fixed AverageCurrent() rate of charge accumulation. A value of 65535 indicates the battery is not being charged.


<div id="register_standbycurrent_detail" class="packet">
<h2>StandbyCurrent </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x1A]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns a signed integer value of measured standby current through the sense resistor. The StandbyCurrent() is an adaptive measurement. Initially it will report the standby current programmed in initial standby and after several seconds in standby mode will report the measured standby. The register value is updated every 1 s when measured current is above the deadband and is less than or equal to 2 × initial standby. The first and last values that meet these criteria are not averaged in since they may not be stable values. To approximate to a 1-min time constant each new value of StandbyCurrent() is computed by taking approximate 93% weight of the last standby current and approximate 7% of the current measured average current.</p>
<!--*user-block-standbycurrent-start*-->

<!--*user-block-standbycurrent-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">StandbyCurrent</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>StandbyCurrent:</b> This read-only function returns a signed integer value of measured standby current through the sense resistor. The StandbyCurrent() is an adaptive measurement. Initially it will report the standby current programmed in initial standby and after several seconds in standby mode will report the measured standby. The register value is updated every 1 s when measured current is above the deadband and is less than or equal to 2 × initial standby. The first and last values that meet these criteria are not averaged in since they may not be stable values. To approximate to a 1-min time constant each new value of StandbyCurrent() is computed by taking approximate 93% weight of the last standby current and approximate 7% of the current measured average current.


<div id="register_standbytimetoempty_detail" class="packet">
<h2>StandbyTimeToEmpty </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x1C]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns a unsigned integer value predicting remaining battery life at standby rate of discharge in units of minutes. The computation uses Nominal Available Capacity (NAC) for the calculation. A value of 65535 indicates the battery is not being discharged.</p>
<!--*user-block-standbytimetoempty-start*-->

<!--*user-block-standbytimetoempty-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">StandbyTimeToEmpty</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>StandbyTimeToEmpty:</b> This read-only function returns a unsigned integer value predicting remaining battery life at standby rate of discharge in units of minutes. The computation uses Nominal Available Capacity (NAC) for the calculation. A value of 65535 indicates the battery is not being discharged.


<div id="register_maxloadcurrent_detail" class="packet">
<h2>MaxLoadCurrent </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x1E]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns a signed integer value in units of mA of maximum load conditions. The MaxLoadCurrent() is an adaptive measurement which is initially reported as the maximum load current programmed in initial Max Load Current register. If the measured current is ever greater than the initial Max Load Current then the MaxLoadCurrent() updates to the new current. MaxLoadCurrent() is reduced to the average of the previous value and initial Max Load Current whenever the battery is charged to full after a previous discharge to an SOC of less than 50%. This will prevent the reported value from maintaining an unusually high value.</p>
<!--*user-block-maxloadcurrent-start*-->

<!--*user-block-maxloadcurrent-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">MaxLoadCurrent</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>MaxLoadCurrent:</b> This read-only function returns a signed integer value in units of mA of maximum load conditions. The MaxLoadCurrent() is an adaptive measurement which is initially reported as the maximum load current programmed in initial Max Load Current register. If the measured current is ever greater than the initial Max Load Current then the MaxLoadCurrent() updates to the new current. MaxLoadCurrent() is reduced to the average of the previous value and initial Max Load Current whenever the battery is charged to full after a previous discharge to an SOC of less than 50%. This will prevent the reported value from maintaining an unusually high value.


<div id="register_maxloadtimetoempty_detail" class="packet">
<h2>MaxLoadTimeToEmpty </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x20]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns a unsigned integer value predicting remaining battery life at the maximum discharge load current rate in units of minutes. A value of 65535 indicates that the battery is not being discharged.</p>
<!--*user-block-maxloadtimetoempty-start*-->

<!--*user-block-maxloadtimetoempty-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">MaxLoadTimeToEmpty</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>MaxLoadTimeToEmpty:</b> This read-only function returns a unsigned integer value predicting remaining battery life at the maximum discharge load current rate in units of minutes. A value of 65535 indicates that the battery is not being discharged.


<div id="register_averagepower_detail" class="packet">
<h2>AveragePower </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x22]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns a signed integer value of average power during battery charging and discharging. It is negative during discharge and positive during charge. A value of 0 indicates that the battery is not being discharged. The value is reported in units of mW.</p>
<!--*user-block-averagepower-start*-->

<!--*user-block-averagepower-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">AveragePower</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>AveragePower:</b> This read-only function returns a signed integer value of average power during battery charging and discharging. It is negative during discharge and positive during charge. A value of 0 indicates that the battery is not being discharged. The value is reported in units of mW.


<div id="register_btpdischargeset_detail" class="packet">
<h2>BTPDischargeSet </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x24]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This command sets the OperationStatusA BTP_INT and the BTP_INT pin will be asserted when the RemCap drops below the set threshold in DF register.</p>
<!--*user-block-btpdischargeset-start*-->

<!--*user-block-btpdischargeset-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">BTPDischargeSet</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>BTPDischargeSet:</b> This command sets the OperationStatusA BTP_INT and the BTP_INT pin will be asserted when the RemCap drops below the set threshold in DF register.


<div id="register_btpchargeset_detail" class="packet">
<h2>BTPChargeSet </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x26]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This command clears the OperationStatusA BTP_INT and the BTP_INT pin will be deasserted.</p>
<!--*user-block-btpchargeset-start*-->

<!--*user-block-btpchargeset-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">BTPChargeSet</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>BTPChargeSet:</b> This command clears the OperationStatusA BTP_INT and the BTP_INT pin will be deasserted.


<div id="register_internaltemperature_detail" class="packet">
<h2>InternalTemperature </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x28]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns an unsigned integer value of the measured internal temperature of the device in 0.1-k units measured by the gas gauge.</p>
<!--*user-block-internaltemperature-start*-->

<!--*user-block-internaltemperature-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">InternalTemperature</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>InternalTemperature:</b> This read-only function returns an unsigned integer value of the measured internal temperature of the device in 0.1-k units measured by the gas gauge.


<div id="register_cyclecount_detail" class="packet">
<h2>CycleCount </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x2A]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns an unsigned integer value of the number of cycles the battery has experienced a discharge (range 0 to 65535). One cycle occurs when accumulated discharge greater than or equal to CC threshold.</p>
<!--*user-block-cyclecount-start*-->

<!--*user-block-cyclecount-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">CycleCount</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>CycleCount:</b> This read-only function returns an unsigned integer value of the number of cycles the battery has experienced a discharge (range 0 to 65535). One cycle occurs when accumulated discharge greater than or equal to CC threshold.


<div id="register_relativestateofcharge_detail" class="packet">
<h2>RelativeStateOfCharge </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x2C]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns an unsigned integer value of the predicted remaining battery capacity expressed as percentage of FullChargeCapacity() with a range of 0% to 100%.</p>
<!--*user-block-relativestateofcharge-start*-->

<!--*user-block-relativestateofcharge-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">RelativeStateOfCharge</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>RelativeStateOfCharge:</b> This read-only function returns an unsigned integer value of the predicted remaining battery capacity expressed as percentage of FullChargeCapacity() with a range of 0% to 100%.


<div id="register_stateofhealth_detail" class="packet">
<h2>StateOfHealth </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x2E]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>This read-only function returns an unsigned integer value expressed as a percentage of the ratio of predicted FCC (25C SoH Load Rate) over the DesignCapacity(). The range is 0x00 to 0x64 for 0% to 100% respectively.</p>
<!--*user-block-stateofhealth-start*-->

<!--*user-block-stateofhealth-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">StateOfHealth</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>StateOfHealth:</b> This read-only function returns an unsigned integer value expressed as a percentage of the ratio of predicted FCC (25C SoH Load Rate) over the DesignCapacity(). The range is 0x00 to 0x64 for 0% to 100% respectively.


<div id="register_chargevoltage_detail" class="packet">
<h2>ChargeVoltage </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x30]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>Returns the desired charging voltage in mV to the charger</p>
<!--*user-block-chargevoltage-start*-->

<!--*user-block-chargevoltage-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">ChargeVoltage</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>ChargeVoltage:</b> Returns the desired charging voltage in mV to the charger


<div id="register_chargecurrent_detail" class="packet">
<h2>ChargeCurrent </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x32]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>Returns the desired charging current in mA to the charger</p>
<!--*user-block-chargecurrent-start*-->

<!--*user-block-chargecurrent-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">ChargeCurrent</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>ChargeCurrent:</b> Returns the desired charging current in mA to the charger


<div id="register_designcapacity_detail" class="packet">
<h2>DesignCapacity </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x3C]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>In SEALED and UNSEALED access This command returns the value stored in Design Capacity and is expressed in mAh. This is intended to be a theoretical or nominal capacity of a new pack but should have no bearing on the operation of the gas gauge functionality.</p>
<!--*user-block-designcapacity-start*-->

<!--*user-block-designcapacity-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">DesignCapacity</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>DesignCapacity:</b> In SEALED and UNSEALED access This command returns the value stored in Design Capacity and is expressed in mAh. This is intended to be a theoretical or nominal capacity of a new pack but should have no bearing on the operation of the gas gauge functionality.


<div id="register_altmanufactureraccess_detail" class="packet">
<h2>AltManufacturerAccess </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x3E]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>MAC Data block command</p>
<!--*user-block-altmanufactureraccess-start*-->

<!--*user-block-altmanufactureraccess-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">AltManufacturerAccess</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>AltManufacturerAccess:</b> MAC Data block command


<div id="register_macdata_detail" class="packet">
<h2>MACData </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x40]</b></li>
    <li class="note">  Default: <b>[0x0000]</b></li>
</ul>

<p>MAC Data block</p>
<!--*user-block-macdata-start*-->

<!--*user-block-macdata-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 15</th>
    <th> 14</th>
    <th> 13</th>
    <th> 12</th>
    <th> 11</th>
    <th> 10</th>
    <th> 9</th>
    <th> 8</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="16">MACData</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>MACData:</b> MAC Data block


<div id="register_macdatasum_detail" class="packet">
<h2>MACDataSum </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x60]</b></li>
    <li class="note">  Default: <b>[0x00]</b></li>
</ul>

<p>MAC Data block checksum</p>
<!--*user-block-macdatasum-start*-->

<!--*user-block-macdatasum-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="8">MACDataSum</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>MACDataSum:</b> MAC Data block checksum


<div id="register_macdatalen_detail" class="packet">
<h2>MACDataLen </h2>
<hr/>
<ul>
    <li class="note">  Address: <b>[0x61]</b></li>
    <li class="note">  Default: <b>[0x00]</b></li>
</ul>

<p>MAC Data block length</p>
<!--*user-block-macdatalen-start*-->

<!--*user-block-macdatalen-end*-->
<table class="fields" width="80%">
  <tr>
    <th class="smallCell">bit</th>
    <th> 7</th>
    <th> 6</th>
    <th> 5</th>
    <th> 4</th>
    <th> 3</th>
    <th> 2</th>
    <th> 1</th>
    <th> 0</th>
  </tr>
  <tr>
    <th class="smallCell">Field</th>
   <td class="field" colspan="8">MACDataLen</td>

  </tr>
  <tr>
    <th class="smallCell">Default</th>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
      <td class="zero" >0</td>
   </tr>
</table>


<h2> Fields:</h2>

<b>MACDataLen:</b> MAC Data block length

