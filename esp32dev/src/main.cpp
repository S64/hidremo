#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <BLEDevice.h>
#include <freertos/task.h>

#include "BLEHIDDevice.h"

#define HIDREMO_DEVICE_NAME "MyBLEDevice"
#define HIDREMO_WIFI_SSID "dummy"
#define HIDREMO_WIFI_PASSPHRASE "dummy"

#define HIDREMO_WS_ENDPOINT_HOST = "example.com"
#define HIDREMO_WS_ENDPOINT_PORT = 80
#define HIDREMO_WS_ENDPOINT_PATH = "/ws"

void delayTask(TickType_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) { delayTask(10); }
}

void loop()
{

}
