# Measure temperature with PIC16F1579 and LM35 sensor

Here is my first project where I plan to measure temperature using
LM35 sensor (which converts temperature to linear voltage delta)
and PIC16F1579.

Also it is my first project where I'm playing with [MCC Melody] code
generator tool.

Status:
- just blinks LED on RB7 (PIN10) at 1s rate (toggle rate 0.5s) using
  Detail function in `main()` (no interrupt and/or Timer used, yet...)

WARNING!

Chip PIC16F1579 has important Design limitations that are not obvious at first sight:
- no I2C module, no SPI module (in other words there is no single MSSP module)
- there is no external Crystal and/or Resonator support. The only external clock
  source is full digital Clock Input (but there is no inverting amplifier between
  CLKI/CLKO so no way how to make external passive parts oscillating ...) However
  there is at least internal oscillator (INTOSC) capable of do up to 16 MHz and
  also there is 4xPLL

# Hardware Requirements

- PICDEM-DM163045 development board (you can use any PIC board that supports 20 pin
  PIC16F1579
- PIC16F1579
- LM35 Temperature-to-Voltage sensor

# Software Requirements

TODO:

# Setup

TODO:
