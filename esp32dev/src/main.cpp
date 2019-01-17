#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <BLEDevice.h>
#include <freertos/task.h>

#include "BLEHIDDevice.h"

#define HIDREMO_DEVICE_NAME "MyBLEDevice"
#define HIDREMO_MANUFACTURER "Shuma Yoshioka"

#define HIDREMO_WIFI_SSID "dummy"
#define HIDREMO_WIFI_PASSPHRASE "dummy"

#define HIDREMO_WS_ENDPOINT_HOST = "example.com"
#define HIDREMO_WS_ENDPOINT_PORT = 80
#define HIDREMO_WS_ENDPOINT_PATH = "/ws"

#define HIDREMO_REPORTID_KEYBOARD 1
#define HIDREMO_REPORTID_CONSUMER 2

static const uint8_t HIDREMO_REPORT_MAP[] = {
    USAGE_PAGE(1), 0x01,
    USAGE(1), 0x06,
        COLLECTION(1), 0x01,
            // modifiers
            REPORT_ID(1), HIDREMO_REPORTID_KEYBOARD,
            USAGE_PAGE(1), 0x07,
            USAGE_MINIMUM(1), 0xe0,
            USAGE_MAXIMUM(1), 0xe7,
            LOGICAL_MINIMUM(1), 0x00,
            LOGICAL_MAXIMUM(1), 0x01,
            REPORT_COUNT(1), 0x08,
            REPORT_SIZE(1), 0x01,
            // reserved
            HIDINPUT(1), 0x02,
            REPORT_COUNT(1), 0x01,
            REPORT_SIZE(1), 0x08,
            HIDINPUT(1), 0x01,
            // keys
            REPORT_COUNT(1), 0x06,
            REPORT_SIZE(1), 0x08,
            LOGICAL_MINIMUM(1), 0x00,
            LOGICAL_MAXIMUM(1), 0xff,
            USAGE_PAGE(1), 0x07,
            USAGE_MINIMUM(1), 0x00,
            USAGE_MAXIMUM(1), 0xff,
            HIDINPUT(1), 0x00,
        END_COLLECTION(0),
    USAGE_PAGE(1), 0x0c,
    USAGE(1), 0x01,
        COLLECTION(1), 0x01,
            REPORT_ID(1), HIDREMO_REPORTID_CONSUMER,
            USAGE_PAGE(1), 0x0c,
            REPORT_COUNT(1), 0x06,
            REPORT_SIZE(1), 0x08,
            LOGICAL_MINIMUM(1), 0x00,
            LOGICAL_MAXIMUM(1), 0x01,
            USAGE_PAGE(1), 0x0c,
            USAGE_MINIMUM(1), 0x00,
            USAGE_MAXIMUM(1), 0xff,
            HIDINPUT(1), 0x00,
            HIDINPUT(1), 0x00, //padding
        END_COLLECTION(0)
};

static bool bleConnected = false;

static BLECharacteristic* inputKeyboard;
static BLECharacteristic* inputConsumer;

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

class MyBleCallbacks : public BLEServerCallbacks
{

    void onConnect(BLEServer* svr)
    {
        bleConnected = true;
        Serial.println("BLE: connected.");
    }

    void onDisconnect(BLEServer* svr)
    {
        bleConnected = false;
        Serial.println("BLE: disconnected.");
    }

};

void startBleServer()
{
    BLEDevice::init(HIDREMO_DEVICE_NAME);
    BLEServer* svr = BLEDevice::createServer();
    svr->setCallbacks(new MyBleCallbacks());

    BLEHIDDevice* hid = new BLEHIDDevice(svr);

    inputKeyboard = hid->inputReport(HIDREMO_REPORTID_KEYBOARD);
    inputConsumer = hid->inputReport(HIDREMO_REPORTID_CONSUMER);

    hid->manufacturer()->setValue(HIDREMO_MANUFACTURER);
    hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
    hid->hidInfo(0x00, 0x01);
    hid->reportMap((uint8_t*) HIDREMO_REPORT_MAP, sizeof(HIDREMO_REPORT_MAP));
    hid->startServices();

    BLESecurity *sec = new BLESecurity();
    sec->setAuthenticationMode(ESP_LE_AUTH_BOND);

    BLEAdvertising* adv = svr->getAdvertising();
    adv->setAppearance(ESP_BLE_APPEARANCE_HID_KEYBOARD);
    adv->addServiceUUID(hid->hidService()->getUUID());
    adv->start();

    Serial.println("BLE: start advertising.");
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) { delayTask(10); }

    startWifiTask();
    startBleServer();
}

void loop()
{

}
