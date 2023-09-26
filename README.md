# Measure temperature with PIC16F1579 and LM35 sensor

Here is my first project where I plan to measure temperature using
[LM35][LM35] sensor (which converts temperature to linear voltage delta)
and [PIC16F1579][PIC16F1579].

Also it is my first project where I'm playing with [MCC Melody][MCC Melody]
code generator tool.

Status:
- prints debug messages on UART, PIN2, RA5, as TX every 2s. You have to set your PC to:
  - Speed: 19200 Baud - can't use higher speed, because BRG (Baud Rate Generator) is very
    gross and higher speeds has unacceptable timing errors (like 3% or so), see data sheet
    at `DS40001782C-page 207 to page 208`
  - Data: 8-bit
  - Stop: 1 stop bit
  - Parity: None
  - Flow Control: None
- in future I will print Temperature on UART
- I was able to map UART pin only thanks good guys on Forum:
  - https://forum.microchip.com/s/topic/a5C3l000000MdMJEA0/t381350

Debug messages on UART:
```
L66: App v1.0
L70: C=1
L70: C=2
```
- legend:
  - `Lxx`: Line number in [PIC16-LM35-Melody.X/main.c](PIC16-LM35-Melody.X/main.c) source file
  - `C=x`: simple counter that increments with each `printf(3)` in `while` loop
- messages are as short as possible to deal well with relatively slow UART speed.

- blinks LED on RB7 (PIN10) around 4s rate (toggle rate 2s) using
  Detail function in `main()` (no interrupt and/or Timer used, yet...).
  - I slowed it down to not overflow UART at 19200 Baud.

Used MCC Melody Components
* [MCC UART Driver](https://onlinedocs.microchip.com/oxy/GUID-420E6AAC-9141-47BF-A4C7-A6EA17246D0D-en-US-17/GUID-BC229F28-29AC-46A3-9FAA-1681C2E93A5C.html#GUID-1D120597-A740-428D-B577-02558CF88F8A)
* [MCC UART PLIB](https://onlinedocs.microchip.com/oxy/GUID-420E6AAC-9141-47BF-A4C7-A6EA17246D0D-en-US-17/GUID-D7E1665E-7BE5-456B-90BA-836DEC19A726.html#GUID-D7E1665E-7BE5-456B-90BA-836DEC19A726)

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
- [PIC16F1579][PIC16F1579]
- [LM35][LM35] Temperature-to-Voltage sensor

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

[XC compilers]: https://www.microchip.com/mplab/compilers
[MPLAB X IDE]: https://www.microchip.com/mplab/mplab-x-ide
[DM163045]: https://www.microchip.com/en-us/development-tool/dm163045
[PIC16F1579]: https://www.microchip.com/en-us/product/pic16f1579
[LM35]: https://www.ti.com/lit/ds/symlink/lm35.pdf
[MCC Melody]: https://onlinedocs.microchip.com/oxy/GUID-5A03F818-B7FC-4062-9792-57D08543B586-en-US-7/GUID-4FF6C8DE-2375-4456-9150-3ECCDAEB82B4.html
