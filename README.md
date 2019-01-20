# hidremo

Toys of REST controllable Bluetooth HID for home automation.

## Important notice

This project is currently work in progress. Don't use in production environment.

## Demos

- [Turn-on Android TV via Slackbot](https://twitter.com/shuma_yoshioka/status/1086584038419095552)

## Installation

1. Deploy [`/backend`](./backend) module to cloud.
2. Rewrite constants in [`/esp32dev/src/main.cpp`](./esp32dev/src/main.cpp).
3. Flash [`/esp32dev`](./esp32dev) module to [ESP32-DevKitC](http://akizukidenshi.com/catalog/g/gM-11819/) or [other compatible board](https://amzn.to/2CwFyQx).


## License

```
Copyright 2019 Shuma Yoshioka

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
