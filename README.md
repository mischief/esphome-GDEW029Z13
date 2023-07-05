# esphome component for the GDEW029Z13 e-paper display

i didn't have any luck with the other existing implementations so i hacked this together.

- Good Display product page ('sold out'): https://www.good-display.com/product/408.html
- Good Display reference manual: https://v4.cecdn.yun300.cn/100001_1909185148/GDEW029Z13.pdf
- Good Display reference implementation: https://github.com/GoodDisplay/E-paper-Display-Library-of-GoodDisplay/tree/main/Tri-Color_E-paper-Display/2.9inch_UC8151D_GDEW029Z13_296x128/Arduino
- Waveshare product page: https://www.waveshare.com/product/displays/e-paper/epaper-2/2.9inch-e-paper-module-b.htm
- Amazon.com product page: https://www.amazon.com/gp/product/B07P8LGGC7
- 

example configuration for esphome using a Wemos D1 mini clone:
```yaml
esphome:
  name: epaper
  friendly_name: epaper

esp8266:
  board: d1_mini

logger:

external_components:
  - source:
      type: git
      url: https://github.com/mischief/esphome-GDEW029Z13
    components: [ waveshare_epaper ]

font:
  - file: "gfonts://Roboto"
    id: roboto
    size: 32

spi:
  clk_pin: D5
  mosi_pin: D7
  miso_pin: D6

display:
  - platform: waveshare_epaper
    id: epaper
    cs_pin: D8
    dc_pin: D4
    busy_pin: D2
    reset_pin: D1
    model: gdew029z13
    update_interval: 30s
    rotation: 90
    pages:
      - id: page1
        lambda: |-
          it.print(0, 0, id(roboto), "Hello World!");
```

