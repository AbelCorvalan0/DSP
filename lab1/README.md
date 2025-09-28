# Lab 1 - Sampling

### Objective

Manage the A/D converter module integrated in the MCXN947.

### Description

Develop an application program capable of digitizing a signal through the ADC module available on the FRDM-K64F board at different sampling rates. The required sampling rates are 8K/S, 16K/S, 22K/S, 44K/S, and 48K/S.

The sampling rate changes will be made using one of the evaluation board’s buttons, in the form of a circular buffer. Each sampling rate will be indicated through an RGB LED color. Another button on the board will enable or stop acquisition (Run/Stop).

The acquired values will be stored in memory in a circular buffer of 512 samples of type q15 (15-bit fractional) and will also be sent through the DAC (12-bit).

### Presentation

1. Show the program running.
2. Upload a file containing the following.
    - Environment configuration (screenshots of timers, ADC, etc).
    - Application design diagram explaining its components.
    - Source code of the application with the complete project.