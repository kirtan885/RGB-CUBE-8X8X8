# Troubleshooting

| Symptom | Likely cause | Fix |
|---|---|---|
| No LEDs light | 74HC595 power missing | Pin 16 → +5 V, Pin 8 → GND |
| All LEDs off | OE disabled | Pin 13 → GND |
| Unstable/random outputs | SRCLR floating | Pin 10 → +5 V |
| Unstable switching | No decoupling | Place 0.1 µF close to VCC/GND |
| Only some channels work | Wrong Q-pin mapping | Verify Q0 pin 15 and Q1–Q7 pins 1–7 |
| LED stays on | Transistor wiring error | Verify base, collector and emitter |
| LED does not light | LED polarity reversed | Anode toward +5 V |
| Wrong sequence | Physical channel order differs | Match LED order to Q0–Q7 |

For physical 2N2222/PN2222A devices, verify the package pinout from the specific manufacturer's datasheet. Do not assume every transistor has the same lead order.
