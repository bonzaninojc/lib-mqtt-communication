//
// Created by aluno on 30/05/23.
//

#ifndef MODULOS_LIB_MQTT_COMMUNICATION_H
#define MODULOS_LIB_MQTT_COMMUNICATION_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class LibMqttCommunication {
public:
    LibMqttCommunication(const char *ssid, const char *password, const char *mqttServer, int mqttPort,
                         const char *mqttUser, const char *mqttPassword);

    void setup();
    void publishData(const char *topic, const JsonObject &doc);
    void connectToWiFi();
    void connectToMqtt();

private:
    const char *_ssid;
    const char *_password;
    const char *_mqttPassword;
    const char *_mqttUser;
    const char *_mqttServer;
    int _mqttPort;

    WiFiClient _wifiClient;
    PubSubClient _mqttClient;
};



#endif //MODULOS_LIB_MQTT_COMMUNICATION_H
