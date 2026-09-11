# Arduino 74HC595 8-LED Driver Block Test

A Tinkercad/Arduino Uno validation project for an 8-channel LED driver block using a **74HC595 shift register** and **eight NPN transistor low-side switches**.

The purpose of this block is to validate one repeatable driver section before scaling the design into a larger multiplexed RGB LED cube system.

> **Project status:** Hardware-validation stage / prototype

## Overview

The tested block contains:

- 1 × Arduino Uno
- 1 × 74HC595 8-bit serial-to-parallel shift register
- 8 × NPN transistors (2N2222 / PN2222A or equivalent)
- 8 × LEDs
- 8 × 220 Ω LED current-limiting resistors
- 8 × 1 kΩ transistor base resistors
- 1 × 0.1 µF ceramic decoupling capacitor

The Arduino controls eight LED channels using only three digital control lines:

| Arduino | Signal | 74HC595 |
|---|---|---|
| D11 | Serial DATA | Pin 14, DS/SER |
| D13 | CLOCK | Pin 11, SHCP/SRCLK |
| D10 | LATCH | Pin 12, STCP/RCLK |

The 74HC595 converts the serial data stream into eight parallel outputs. Each output drives an NPN transistor through a 1 kΩ base resistor.

## Circuit architecture

```text
Arduino Uno
   │
   ├── D11 DATA ───────────────► 74HC595 Pin 14 (DS/SER)
   ├── D13 CLOCK ──────────────► 74HC595 Pin 11 (SHCP/SRCLK)
   └── D10 LATCH ──────────────► 74HC595 Pin 12 (STCP/RCLK)
                                  │
                 ┌────────────────┼────────────────┐
                 ▼                ▼                ▼
              Q0..Q7          8 outputs       Pin 9 Q7S
                 │
              1 kΩ each
                 │
                 ▼
            NPN transistor
                 │
        collector ──► LED + 220 Ω ──► +5 V
        emitter   ──────────────────► GND
```

### Low-side switching

For each channel, the intended current path is:

```text
+5V → LED anode → LED cathode → 220 Ω → NPN collector
NPN emitter → GND

74HC595 Q output → 1 kΩ → NPN base
```

When the 74HC595 output is HIGH, the NPN transistor turns on and completes the LED current path to ground.

**Important:** transistor lead order varies between manufacturers and packages. Verify the pin labels of the exact device before wiring a physical prototype.

## 74HC595 power/control wiring

| Arduino / Supply | 74HC595 pin | Function |
|---|---:|---|
| +5 V | 16 | VCC |
| GND | 8 | GND |
| D11 | 14 | DS / SER |
| D13 | 11 | SHCP / SRCLK |
| D10 | 12 | STCP / RCLK |
| GND | 13 | OE, active LOW |
| +5 V | 10 | SRCLR, active LOW |

Two control pins must not be left floating:

```text
74HC595 Pin 13 (OE)   → GND
74HC595 Pin 10 (SRCLR) → +5 V
```

A 0.1 µF ceramic capacitor should be placed close to the IC:

```text
74HC595 Pin 16 (VCC) ──||── 74HC595 Pin 8 (GND)
                       0.1 µF
```

## Output mapping

| Output | Physical pin | Connection |
|---|---:|---|
| Q0 | 15 | 1 kΩ → Transistor 1 base |
| Q1 | 1 | 1 kΩ → Transistor 2 base |
| Q2 | 2 | 1 kΩ → Transistor 3 base |
| Q3 | 3 | 1 kΩ → Transistor 4 base |
| Q4 | 4 | 1 kΩ → Transistor 5 base |
| Q5 | 5 | 1 kΩ → Transistor 6 base |
| Q6 | 6 | 1 kΩ → Transistor 7 base |
| Q7 | 7 | 1 kΩ → Transistor 8 base |
| Q7S / QH' | 9 | Not connected in the single-block test |

For future multi-register designs, Pin 9 (Q7S/QH') of one register connects to Pin 14 (DS/SER) of the next register.

## Bill of materials

| Qty | Component | Value / Type | Purpose |
|---:|---|---|---|
| 1 | Arduino Uno | 5 V board | Controller |
| 1 | 74HC595 | 8-bit shift register | Output expansion |
| 8 | NPN transistor | 2N2222 / PN2222A / equivalent | LED low-side switches |
| 8 | LED | Any color | Visual outputs |
| 8 | Resistor | 220 Ω | LED current limiting |
| 8 | Resistor | 1 kΩ | Transistor base current limiting |
| 1 | Capacitor | 0.1 µF / 104 ceramic | Decoupling |
| 1 | Breadboard | Full/half size | Prototype |
| Several | Jumper wires | — | Interconnects |

## Arduino test firmware

The test sketch runs five patterns:

1. All LEDs ON for approximately 1.5 s
2. All LEDs OFF for approximately 0.8 s
3. Running light from LED 1 to LED 8
4. Binary counter from 0 to 255
5. Bouncing light from one side to the other and back

The sketch uses `shiftOut()` to send eight serial bits and the latch line to update the parallel outputs.

See [`code/74hc595_8_led_test.ino`](code/74hc595_8_led_test.ino).

## Expected result

If all five patterns operate correctly, the following parts of the block have been exercised:

- Arduino-to-74HC595 serial communication
- DATA, CLOCK and LATCH connections
- 74HC595 power and control pins
- Q0–Q7 output mapping
- NPN transistor switching
- LED polarity
- LED current-limiting resistors
- transistor base resistors
- latch timing

## Troubleshooting

| Symptom | Likely cause | Check |
|---|---|---|
| No LEDs light | 74HC595 has no power | Pin 16 = +5 V, Pin 8 = GND |
| All LEDs remain off | OE floating/HIGH | Pin 13 → GND |
| LEDs behave unpredictably | SRCLR floating | Pin 10 → +5 V |
| Random/unstable behavior | Missing decoupling | Add 0.1 µF close to the IC |
| Only some LEDs work | Q-pin mapping error | Q0 = pin 15; Q1–Q7 = pins 1–7 |
| LED stays on | Transistor/LED wiring issue | Check base, collector, emitter and polarity |
| LED does not light | LED reversed | Anode toward +5 V; cathode toward resistor/transistor |
| Sequence is wrong | Physical LED order differs | Match LED order to Q0–Q7 |

## Scaling toward the LED cube

The validated block is intended as the foundation for a larger LED-cube driver.

```text
1 × 74HC595  → 8 output channels
2 × 74HC595  → 16 output channels
8 × 74HC595  → 64 output channels
24 × 74HC595 → 192 output channels
```

For chained registers:

```text
Arduino D11
   │
   ▼
74HC595 #1 DS
   │
   └── Q7S ──► 74HC595 #2 DS
                  │
                  └── Q7S ──► 74HC595 #3 DS
                                  ...
```

Clock and latch are shared:

```text
Arduino D13 → SHCP/SRCLK on every 74HC595
Arduino D10 → STCP/RCLK on every 74HC595
Arduino D11 → DS/SER on the first 74HC595
```

The larger multiplexed cube concept uses shift-register output channels for LED cathode/color control plus separate layer/plane drivers.

## Relationship to the 8×8×8 RGB LED Cube

The broader project explores two possible architectures:

### Traditional multiplexed RGB cube

The earlier design concept uses common-anode 5 mm RGB LEDs, chained shift registers, transistor/Darlington current sinks, and separate layer switching.

A PCB screenshot in the project history shows a larger multi-register driver layout and its 3D view. That design should be treated as a **separate scaling stage**, not as part of this validated single 74HC595 block.

### Addressable LED cube

A separate project direction considered WS2812B/SK6812/WS2813-style addressable LEDs to reduce driver and wiring complexity.

This repository documents the **74HC595 block validation**. The addressable architecture is therefore kept as a future/alternative direction rather than mixed into the tested circuit.

## Suggested repository structure

```text
arduino-74hc595-8-led-driver/
├── README.md
├── LICENSE
├── code/
│   └── 74hc595_8_led_test.ino
├── circuit/
│   ├── tinkercad-circuit-link.txt
│   ├── wiring-diagram.png
│   └── schematic.png
├── docs/
│   ├── connection-table.md
│   ├── troubleshooting.md
│   ├── assembly-testing-guide.md
│   └── future-led-cube-plan.md
└── images/
    ├── tinkercad-overview.png
    ├── pcb-2d.png
    └── pcb-3d.png
```

## Key learning outcomes

- Expand Arduino outputs using a 74HC595.
- Use `shiftOut()` for serial-to-parallel control.
- Use a latch signal to update multiple outputs together.
- Drive LEDs through NPN low-side switches.
- Use a 1 kΩ resistor for transistor base current limiting.
- Use a 220 Ω resistor for LED current limiting.
- Tie OE to GND and SRCLR to +5 V for stable operation.
- Add local 0.1 µF decoupling.
- Validate one repeatable block before scaling to a larger PCB/cube.

## License

Choose a license appropriate for your hardware and software. MIT is a simple option for the firmware and documentation if you want to permit reuse.
