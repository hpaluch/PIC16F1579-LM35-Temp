# Measure temperature with PIC16F1579 and LM35 sensor

Here is my first project where I use [LM35][LM35]
Temperature sensor (which converts temperature to linear voltage delta) and
[PIC16F1579][PIC16F1579].

[LM35][LM35] simply outputs 10 x mV voltage in Celsius, for example 260 mV =
26.0 degrees of Celsius.  Please note that negative temperature can be sensed
only with negative bias resistor - not realized here. For such details
please see [LM35 datasheet][LM35].

Our task is to measure this Voltage using ADC (and FVREF - fixed Voltage
reference for ADC). By coincidence it is perfect fit for
[PIC16F1579][PIC16F1579] because it has ADC but not I2C nor SPI (see note
below).

Please note that minimum supply Voltage for LM35 is 4V so it may be
difficult to use with some recent boards.

Also it is my first project where I'm playing with [MCC Melody][MCC Melody]
code generator tool.

Status:
- it Works!
- example UART output:
```
L86: App v1.01
L99 FVR ready in 0 [ms]
L109: #1 Temp=28.2 [^C] V=282 [mV]
L109: #2 Temp=28.3 [^C] V=283 [mV]
L109: #3 Temp=28.2 [^C] V=282 [mV]
L109: #4 Temp=28.3 [^C] V=283 [mV]
```
- UART configuration: Speed 19200 Baud, 8-bit data, 1 stop bit, no parity, no flow control
- legend:
  - `Lxx`: Line number in [PIC16-LM35-Melody.X/main.c](PIC16-LM35-Melody.X/main.c) source file
  - `#x`: simple counter that increments with each `printf(3)` in `while` loop
  - `V=YYY [mV]` ADC input from LM35 in milivolts
  - `Temp=X.X [^C]` measured temperature in degrees of Celsius (just millivolts divided by 10)
- PIN2 RA5 - UART TX (mapped with `RA5PPS=0x9`)
- PIN8 RC6 AN8 - input from LM35 Vout (middle pin of LM35 in TO92 package)
- PIN10 RB7 - blinks LED around 4s rate (toggle rate 2s) using
  Detail function in `main()` (no interrupt and/or Timer used, yet...).
  - I slowed it down to not overflow UART at 19200 Baud.


Here is schema:

![PIC16F1579 and LM35 - schema](ExpressPCB/pic16f1579-lm35.png)

All schema files are in [ExpressPCB/](ExpressPCB/) folder.  Made
in [ExpressPCB Classic][ExpressPCB Classic].


Used MCC Melody Components
* [MCC UART Driver](https://onlinedocs.microchip.com/oxy/GUID-420E6AAC-9141-47BF-A4C7-A6EA17246D0D-en-US-17/GUID-BC229F28-29AC-46A3-9FAA-1681C2E93A5C.html#GUID-1D120597-A740-428D-B577-02558CF88F8A)
* [MCC UART PLIB](https://onlinedocs.microchip.com/oxy/GUID-420E6AAC-9141-47BF-A4C7-A6EA17246D0D-en-US-17/GUID-D7E1665E-7BE5-456B-90BA-836DEC19A726.html#GUID-D7E1665E-7BE5-456B-90BA-836DEC19A726)
* [FVR PLIB](https://onlinedocs.microchip.com/oxy/GUID-420E6AAC-9141-47BF-A4C7-A6EA17246D0D-en-US-17/GUID-E2CFC6D6-859C-486B-A5B0-606E44213C24.html#GUID-E2CFC6D6-859C-486B-A5B0-606E44213C24) - fixed
  positive Voltage reference (1.024V in my example) for ADC.
* [ADC PLIB](https://onlinedocs.microchip.com/oxy/GUID-420E6AAC-9141-47BF-A4C7-A6EA17246D0D-en-US-17/GUID-34B91501-8F37-4897-8CD9-F61B11819FB5.html#GUID-34B91501-8F37-4897-8CD9-F61B11819FB5) ADC
  to convert Voltage from LM35 ( Celsius times 10mV - 260 mV = 26.0 Degrees of Celsius) to
  Temperature and display it on UART

> WARNING!
> 
> Chip [PIC16F1579][PIC16F1579] has important Design limitations that are not apparent
> at first sight:
> - *no I2C* module, *no SPI* module (in other words there is no single MSSP module)
> - there is *no external Crystal* and/or Resonator support. The only external clock
>   source is full digital Clock Input (but there is no inverting amplifier between
>   CLKI/CLKO so no way how to make external passive parts oscillating ...) However
>   there is at least internal oscillator (INTOSC) capable of do up to 16 MHz and
>   also there is 4xPLL

# Hardware Requirements

- [PICDEM DM163045][DM163045] development board (you can use any PIC board that
  supports 20 pin [PIC16F1579][PIC16F1579]). I have one that is now 10 years old
  and I stil like it - there is everything I need to work with 8-bit PIC MCUs.

Additional parts (not included with PICDEM):
- [PIC16F1579][PIC16F1579]
- [LM35][LM35] Temperature-to-Voltage sensor
- [USB Console Cable #954][cable954] - or any other usable USB to UART adapter.
  - verify with DMM that LM317 regulator output on PICDEM board is just 5V
  - connect Black wire to Ground, and Green wire to UART TX - PIN2 RA5

# Software Requirements

* [XC8 compiler][XC compilers] - tested version v2.45
* [MPLAB X IDE][MPLAB X IDE] - tested version v6.15
* Device Family Pack `PIC12-16F1xxx_DFP` v1.7.242
* MCC Melody Tool v5.3.7, Core v5.5.7

# Setup

TODO:

# Resources

MCC Melody is unable to Map UART TX pin in GUI - UART is shown in Pin Grid,
but you can't assign pin to it. However here is solution - manually remap
pin at program startup:
- https://forum.microchip.com/s/topic/a5C3l000000MdMJEA0/t381350

You can find downloaded MCC Melody libraries under:
```
c:\Users\USERNAME\.mcc\libraries\@mchp-mcc\FOLDER
```

[ExpressPCB Classic]: https://www.expresspcb.com/expresspcb-classic-pcb-layout-software/
[cable954]: https://www.modmypi.com/raspberry-pi/communication-1068/serial-1075/usb-to-ttl-serial-cable-debug--console-cable-for-raspberry-pi
[XC compilers]: https://www.microchip.com/mplab/compilers
[MPLAB X IDE]: https://www.microchip.com/mplab/mplab-x-ide
[DM163045]: https://www.microchip.com/en-us/development-tool/dm163045
[PIC16F1579]: https://www.microchip.com/en-us/product/pic16f1579
[LM35]: https://www.ti.com/lit/ds/symlink/lm35.pdf
[MCC Melody]: https://onlinedocs.microchip.com/oxy/GUID-5A03F818-B7FC-4062-9792-57D08543B586-en-US-7/GUID-4FF6C8DE-2375-4456-9150-3ECCDAEB82B4.html
