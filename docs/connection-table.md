# Connection Table

## Arduino → 74HC595

| Arduino | 74HC595 pin | Signal |
|---|---:|---|
| 5 V | 16 | VCC |
| GND | 8 | GND |
| D11 | 14 | DS / SER |
| D13 | 11 | SHCP / SRCLK |
| D10 | 12 | STCP / RCLK |
| GND | 13 | OE |
| 5 V | 10 | SRCLR |

## 74HC595 outputs

| Output | Pin | Destination |
|---|---:|---|
| Q0 | 15 | 1 kΩ → NPN 1 base |
| Q1 | 1 | 1 kΩ → NPN 2 base |
| Q2 | 2 | 1 kΩ → NPN 3 base |
| Q3 | 3 | 1 kΩ → NPN 4 base |
| Q4 | 4 | 1 kΩ → NPN 5 base |
| Q5 | 5 | 1 kΩ → NPN 6 base |
| Q6 | 6 | 1 kΩ → NPN 7 base |
| Q7 | 7 | 1 kΩ → NPN 8 base |

Pin 9 (Q7S/QH') is unused in this single-register test.
