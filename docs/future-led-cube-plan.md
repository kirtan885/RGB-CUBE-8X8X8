# Future LED Cube Plan

The single 74HC595 block is intended as a hardware-validation step for a larger LED-cube project.

## Shift-register scaling

```text
1 × 74HC595  → 8 channels
2 × 74HC595  → 16 channels
8 × 74HC595  → 64 channels
24 × 74HC595 → 192 channels
```

Registers are chained through Q7S/QH':

```text
First 74HC595 Q7S → Next 74HC595 DS
Next Q7S           → Next DS
```

The DATA line enters only the first register. CLOCK and LATCH are shared.

## Traditional multiplexed RGB cube direction

The broader design concept uses:

- Common-anode RGB LEDs
- Multiple 74HC595 shift registers
- Low-side current-sink/transistor stages
- Separate high-side layer switching
- Arduino Uno / UNO R4 WiFi / ESP32 as possible controllers

The exact final PCB architecture should be treated as a separate design stage after the driver block has been validated.

## Alternative addressable direction

Another explored architecture uses WS2812B/SK6812/WS2813-style addressable LEDs.

That approach is significantly different electrically and should not be mixed with the 74HC595 driver-block design without a new schematic and power analysis.
