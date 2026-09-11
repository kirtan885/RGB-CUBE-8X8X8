# Assembly & Testing Guide

## 1. Build the power section

Connect:

- Arduino +5 V to 74HC595 pin 16.
- Arduino GND to 74HC595 pin 8.
- 0.1 µF ceramic capacitor close to the 74HC595 between VCC and GND.

## 2. Configure the control pins

Connect:

- Arduino D11 → 74HC595 pin 14 (DATA).
- Arduino D13 → 74HC595 pin 11 (CLOCK).
- Arduino D10 → 74HC595 pin 12 (LATCH).
- 74HC595 pin 13 (OE) → GND.
- 74HC595 pin 10 (SRCLR) → +5 V.

## 3. Build one LED channel first

Before building all eight channels, test one:

```text
+5V → LED anode
LED cathode → 220 Ω
220 Ω → NPN collector
NPN emitter → GND
74HC595 Q0 → 1 kΩ → NPN base
```

Confirm that the transistor package pinout matches the device you are using.

## 4. Duplicate the channel

Repeat the same arrangement for Q1 through Q7.

## 5. Upload the firmware

Open:

`code/74hc595_8_led_test.ino`

Select the correct Arduino Uno board and serial port, then upload.

## 6. Observe the five tests

Expected sequence:

1. All LEDs ON.
2. All LEDs OFF.
3. Running light.
4. Binary counter.
5. Bouncing light.

## 7. Debug systematically

If the first channel fails, do not build the remaining seven. Verify power, OE, SRCLR, LED polarity, transistor pinout and the Q0 connection first.

Once Q0 works, duplicate the proven channel and verify Q1–Q7.

## 8. Before scaling

Only proceed to a larger PCB after the single block is stable in both simulation and physical prototype testing.
