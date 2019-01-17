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

void taskWifi(void* pvParameters)
{
    while (1)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            WiFi.mode(WIFI_STA);
            WiFi.disconnect();
            WiFi.begin(HIDREMO_WIFI_SSID, HIDREMO_WIFI_PASSPHRASE, NULL, NULL, true);
            while (WiFi.status() != WL_CONNECTED)
            {
                Serial.println(WiFi.status());
                delayTask(1000);
            }
            Serial.println("Wi-Fi: connected.");
        }
        delayTask(1000);
    }
}

void startWifiTask()
{
    xTaskCreatePinnedToCore(
        taskWifi,
        "TaskWifi",
        1024 * 2.5,
        NULL,
        100,
        NULL,
        0
    );
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) { delayTask(10); }

    startWifiTask();
}

void loop()
{

}
