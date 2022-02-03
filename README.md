# ESP32-5x5-TouchPad

This board is an ESP32 WiFi based capacitive touch pad that I want to take advantage of to access MQTT and home automation. A new layout of the touch pad designed specifically for on/off and dim/bright. The idea being that a WiFi switch would allow control of a group of lights, such as the kitchen lights even if the different technologies such as ZigBee or Z-Wave. 

I found this ESP32-5x5-TouchPad board on Tindie and ordered two. Eventually I'll design my own but it's good to have something you can easily experiment with to do your research first. The company's web site is at [Electro Point4U](https://electropoint4u.com/product/esp32-touch-matrix/). There was no special reason I chose this one other that it was convient at the time. It did take time to ship from India.

And I found their code on github, which I forked here. The original code is Arduino/ESP32 enviroment base (use the Arduino IDE).

## Image of the front of the board

Image inline
![ESP32-5x5-board](Docs/ESP32-5x5-board-small.png "Front view of the ESP32 5x5 Touch Pad")

Note that this board doesn't come with the FastLED ()

## Keypad layout

need a table here of the touch pads

| col 1 | col 2 | col 3 | col 4 | col 5|  |
| --- | --- | --- | --- | --- | --- |
| T1 | T6 | T11 | T16 | T21 | row 1 |
| T2 | T7 | T12 | T17 | T22 | row 2 |
| T3 | T8 | T13 | T18 | T23 | row 3 |
| T4 | T9 | T14 | T19 | T24 | row 4 |
| T5 | T10 | T15 | T20 | T25 | row 5 |

## License

Since the original License was GPLv3.0. Since this code is based on the code, it will continue to use the GPLv3.0 License.

## ESP32 Chips :dizzy: :construction:

Which chips have built-in support for touch sensor technology.

| Chip | Notes |
| --- | --- |
| ESP32 | No -S or -C |
| ESP32-C | |
| ESP32-S | |
| 8266 | |

## Links :circus_tent:

* [Espressif ESP32 Docs](https://www.espressif.com/en/products/socs/esp32)
* [ESP32 Hardware Design Guidelines (English)](https://www.espressif.com/sites/default/files/documentation/esp32_hardware_design_guidelines_en.pdf)
* [Touch Sensor Design (English)](https://github.com/ESP32DE/esp-iot-solution-1/blob/master/documents/touch_pad_solution/touch_sensor_design_en.md)
