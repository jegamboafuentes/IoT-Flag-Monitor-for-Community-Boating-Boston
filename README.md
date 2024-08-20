# IoT Flag Monitor for Community Boating Boston ⛵

This project is an IoT device that displays real-time sailing conditions from Community Boating in Boston. Using a T-Display ESP32 development board, the device fetches the current flag color and status from the Community Boating API and shows it on a small TFT screen. No more manual checks—just a quick glance at the device before heading out!

![Device Displaying Real-Time Data](https://github.com/jegamboafuentes/IoT-Flag-Monitor-for-Community-Boating-Boston/blob/main/photos/IMG_1667.jpg)

## Features
- **Real-time data**: Continuously fetches and displays the current flag status.
- **Custom flag display**: Shows the flag color with a wave effect and corresponding status message.
- **WiFi-enabled**: Automatically connects to your WiFi network and retrieves data from the API.

## Materials
- T-Display ESP32 WiFi Bluetooth Development Board
- 3D-printed case and boat model

## Setup Instructions
1. Clone the repository.
2. Install the necessary libraries: `TFT_eSPI`, `WiFi`, `HTTPClient`.
3. Upload the code to your ESP32 board using the Arduino IDE.
4. Customize your WiFi credentials in the code.
5. Assemble the components and power on the device.

## Images
![Website Screenshot Showing API Data 1](https://github.com/jegamboafuentes/IoT-Flag-Monitor-for-Community-Boating-Boston/blob/main/photos/IMG_1614.jpg)
![Website Screenshot Showing API Data 2](https://github.com/jegamboafuentes/IoT-Flag-Monitor-for-Community-Boating-Boston/blob/main/photos/IMG_1641.jpg)

## More Information
For a detailed walkthrough, check out the full project write-up on [Medium](https://jegamboafuentes.medium.com/how-i-built-an-iot-device-to-monitor-sailing-conditions-at-community-boating-boston-86deacb6f715).

## License
This project is licensed under the MIT License.
