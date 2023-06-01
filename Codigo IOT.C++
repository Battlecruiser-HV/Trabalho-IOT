#include <EspMQTTClient.h>

//Para saber mais sobre esta biblioteca, acessar https://github.com/plapointe6/EspMQTTClient

//Definicoes e constantes
char SSIDName[] = "704cyan_2g_repetidor"; //nome da rede WiFi
char SSIDPass[] = "EFD89B25"; //senha da rede WiFI

const int INPUT_PIN = 12; //terminal do sensor de movimento
int pirState = LOW;             
int valor = 0;

char BrokerURL[] = "broker.hivemq.com"; //URL do br'oker MQTT
char BrokerUserName[] = ""; //nome do usuario para autenticar no broker MQTT
char BrokerPassword[] = ""; //senha para autenticar no broker MQTT
char MQTTClientName[] = "projeto sensor-movimento"; //nome do cliente MQTT
int BrokerPort = 1883; //porta do broker MQTT

String TopicoPrefixo = "GHVSensor"; //prefixo do topico
String Topico_01 = TopicoPrefixo+"/movimento"; //nome do topico 01

EspMQTTClient clienteMQTT(SSIDName, SSIDPass, BrokerURL, BrokerUserName, BrokerPassword, MQTTClientName, BrokerPort); //inicializa o cliente MQTT

void onConnectionEstablished() {
}


void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT_PIN, INPUT);
  Serial.begin(115200);
  clienteMQTT.enableDebuggingMessages();
}
void loop() {
  clienteMQTT.loop(); //funcao necessaria para manter a conexao com o broker MQTT ativa e coletar as mensagens recebidas
  valor = digitalRead(INPUT_PIN);
  if(valor == HIGH){
    if (pirState == LOW){
      Serial.println("movimento detectado");
      clienteMQTT.publish(Topico_01, String("Movimento detectado")); // dados sendo enviados ao broker MQTT
    }
  }
  else{
    if(pirState == HIGH){
      Serial.println("movimento não sendo mais detectado");
      clienteMQTT.publish(Topico_01, String("Movimento não mais detectado")); // dados sendo enviados ao broker MQTT
    }
  }

  if (clienteMQTT.isWifiConnected() == 1) {
    Serial.println("Conectado ao WiFi!");
  } else {
    Serial.println("Nao conectado ao WiFi!");
  }

  if (clienteMQTT.isMqttConnected() == 1) {
    Serial.println("Conectado ao broker MQTT!");
  } else {
    Serial.println("Nao conectado ao broker MQTT!");
  }

  Serial.println("Nome do cliente: " + String(clienteMQTT.getMqttClientName())
    + " / Broker MQTT: " + String(clienteMQTT.getMqttServerIp())
    + " / Porta: " + String(clienteMQTT.getMqttServerPort())
  );

  delay(5000);
}
