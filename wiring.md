# Collegamenti

## Partendo da: ESP-32
### Alimentazione
|PIN        |DESTINAZIONE                |
|-----------|----------------------------|
|**5V**     |RDM6300: **VCC**            |
|**GND**    |RDM6300: **GND**            |
### Seriali software
|PIN        |DESTINAZIONE                |OPT|
|-----------|----------------------------|---|
|**GPIO 22**|Modulo illuminazione: **RX**|no |
|**GPIO 21**|Modulo garage: **TX**       |yes|
|**GPIO 19**|Modulo garage: **RX**       |no |
|**GPIO 18**|Modulo ventilazione: **TX** |yes|
|**GPIO 5** |Modulo ventilazione: **RX** |no |
|**GPIO 2** |Modulo irrigazione: **TX**  |yes|
|**GPIO 15**|Modulo irrigazione: **RX**  |no |
### Seriali hardware
|PIN        |DESTINAZIONE                |OPT|
|-----------|----------------------------|---|
|**GPIO 16**|RDM6300: **TX**             |no |
|**GPIO 17**|RDM6300: **RX**             |yes|

## Partendo da: RDM6300
|PIN        |DESTINAZIONE                |OPT|
|-----------|----------------------------|---|
|**ANT 1**  |Induttore                   |no |
|**ANT 2**  |Induttore                   |no |
|**VCC**    |ESP-32: **5V**              |no |
|**GND**    |ESP-32: **GND**             |no |
|**TX**     |ESP-32: **GPIO 16**         |no |