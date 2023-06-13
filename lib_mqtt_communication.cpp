#include "lib_mqtt_communication.h"

LibMqttCommunication::LibMqttCommunication(const char *ssid, const char *password, const char *mqttServer, int mqttPort,
                                           const char *mqttUser, const char *mqttPassword) {
    this->_ssid = ssid;
    this->_password = password;
    this->_mqttPassword = mqttPassword;
    this->_mqttUser =mqttUser;
    this->_mqttServer = mqttServer;
    this->_mqttPort = mqttPort;
}

void LibMqttCommunication::setup() {
    WiFiClient wifiClient;
    PubSubClient mqttClient(wifiClient);

    this->_mqttClient = mqttClient;
    this->_wifiClient = wifiClient;

    WiFi.begin(this->_ssid, this->_password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");

    this->_mqttClient.setServer(this->_mqttServer, this->_mqttPort);

    while (!this->_mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");

        if (this->_mqttClient.connect("ESP32Client", this->_mqttUser, this->_mqttPassword)) {
            Serial.println("Connected");
        } else {
            Serial.print("Failed with state ");
            Serial.print(this->_mqttClient.state());
            delay(2000);
        }
    }
}

void LibMqttCommunication::publishData(const char *topic, const JsonObject& doc) {
    if (this->_mqttClient.connected()) {
        String jsonString;
        serializeJson(doc, jsonString);
        this->_mqttClient.publish(topic, jsonString.c_str());
    }
}

void LibMqttCommunication::connectToWiFi() {
    if (WiFi.status() == WL_CONNECTED) {
        return;
    }

    WiFi.begin(this->_ssid, this->_password);

    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Connected to WiFi");
}

void LibMqttCommunication::connectToMqtt() {
    while (!this->_mqttClient.connected()) {
        Serial.println("Connecting to MQTT server...");

        if (this->_mqttClient.connect("ESP32Client", this->_mqttUser, this->_mqttPassword)) {
            Serial.println("Connected to MQTT server");

            // Subscribe to MQTT topics here, if necessary
            // _mqttClient.subscribe("topic");
        } else {
            Serial.print("Failed to connect to MQTT server, rc=");
            Serial.print(this->_mqttClient.state());
            Serial.println(" Retrying in 5 seconds...");

            delay(5000);
        }
    }
}