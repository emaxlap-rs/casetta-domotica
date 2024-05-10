# Collegamenti

## ESP-32

### Alimentazione RDM6300
|PIN        |DESTINAZIONE                |
|-----------|----------------------------|
|**5V**     |RDM6300: **VCC**            |
|**GND**    |RDM6300: **GND**            |

### Seriali software
|PIN        |DESTINAZIONE                |
|-----------|----------------------------|
|**GPIO 32**|Modulo illuminazione: **RX**|
|**GPIO 33**|Modulo garage: **RX**       |
|**GPIO 25**|Modulo ventilazione: **RX** |
|**GPIO 26**|Modulo irrigazione: **RX**  |
|**GPIO 27**|Modulo porta: **RX**        |

### Seriali hardware
|PIN        |DESTINAZIONE                |
|-----------|----------------------------|
|**GPIO 16**|RDM6300: **TX**             |
|**GPIO 17**|RDM6300: **RX**             |

## RDM6300
|PIN        |DESTINAZIONE                |
|-----------|----------------------------|
|**ANT 1**  |Induttore                   |
|**ANT 2**  |Induttore                   |
|**VCC**    |ESP-32: **5V**              |
|**GND**    |ESP-32: **GND**             |
|**TX**     |ESP-32: **GPIO 16**         |