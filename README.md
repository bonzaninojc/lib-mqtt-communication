
# Lib de Conexão MQTT.

A Lib de Conexão MQTT é uma biblioteca que facilita a conexão e o envio de informações utilizando o protocolo MQTT (Message Queuing Telemetry Transport). Ela fornece uma interface simples para estabelecer conexões MQTT com um broker MQTT e enviar mensagens para tópicos específicos.





Informações e recursos:
- Conexão fácil e confiável com brokers MQTT.
- Envio de mensagens para tópicos MQTT.
- Configuração flexível para atender às necessidades específicas do usuário.
- Tratamento de eventos de conexão, reconexão e recebimento de mensagens.



## Como instalar

![App Screenshot](https://www.robocore.net/upload/tutoriais/32_img_2_H.png)


## Como utilizar

```#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "lib_mqtt_communication.h"

// Defina as credenciais de rede WiFi
const char* ssid = "nome-da-rede";
const char* password = "senha-da-rede";

// Defina as configurações do broker MQTT
const char* mqttServer = "endereco-do-broker";
const int mqttPort = 1883;
const char* mqttUser = "usuario-do-mqtt";
const char* mqttPassword = "senha-do-mqtt";

// Crie uma instância da biblioteca LibMqttCommunication
LibMqttCommunication mqttComm(ssid, password, mqttServer, mqttPort, mqttUser, mqttPassword);

void setup() {
  Serial.begin(115200);

  // Configure a conexão WiFi
  mqttComm.connectToWiFi();

  // Configure a conexão MQTT
  mqttComm.setup();
}

void loop() {
  // Verifique a conexão WiFi e reconecte, se necessário
  mqttComm.connectToWiFi();

  // Verifique a conexão MQTT e reconecte, se necessário
  mqttComm.connectToMqtt();

  // Crie um objeto JsonObject com os dados a serem enviados
  StaticJsonDocument<256> doc;
  doc["temperature"] = 25.0;
  doc["humidity"] = 50.0;

  // Publique os dados no tópico MQTT
  mqttComm.publishData("meu-topico", doc.as<JsonObject>());

  delay(5000);
}
