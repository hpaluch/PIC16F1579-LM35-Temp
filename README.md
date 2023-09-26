# Measure temperature with PIC16F1579 and LM35 sensor

Here is my first project where I plan to measure temperature using
[LM35][LM35] sensor (which converts temperature to linear voltage delta)
and [PIC16F1579][PIC16F1579].

Also it is my first project where I'm playing with [MCC Melody][MCC Melody]
code generator tool.

Status:
- just blinks LED on RB7 (PIN10) at 1s rate (toggle rate 0.5s) using
  Detail function in `main()` (no interrupt and/or Timer used, yet...)

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
* MCC Melody Core 5.5.7

# Setup

TODO:

# Resources


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
