/*
** This is the MQTT version of the original 5x5 Matrix (WIP)
**
** Basics: print touch press to MQTT topic.
**
** License: GPLv3.0 ( GNU General Public License v3.0 )
*/

#include <WiFi.h>
#include <PubSubClient.h>

#if defined(DONTUSEHDR)
// Replace the next variables with your SSID/Password combination
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";

#else
#include "my-details.h"
#endif

#define TOPIC "home/touchpad"

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int  value = 0;

// ------------------------------------------------------------------------------
//
//
//
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//
//
//
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void touch_detected(int touchpad){
  // put your code here, to run while touchpads detect anything;
  
  Serial.print("\nT");
  Serial.print(touchpad);

  //client.publish(TOPIC, touchpad);

}

// ------------------------------------------------------------------------------

// https://fastled.io/
// #include <FastLED.h> // No LED on the board

int threshold = 5;

bool touch[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //touch values array

void gotTouch0() {touch[0] = true;}
void gotTouch1() {touch[1] = true;}
void gotTouch2() {touch[2] = true;}
void gotTouch3() {touch[3] = true;}
void gotTouch4() {touch[4] = true;}
void gotTouch5() {touch[5] = true;}
void gotTouch6() {touch[6] = true;}
void gotTouch7() {touch[7] = true;}
void gotTouch8() {touch[8] = true;}
void gotTouch9() {touch[9] = true;}

CRGB leds[1];

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Touch Matrix");
  
  //FastLED.addLeds<SK6822, 23, GRB>(leds, 1);

  //
  // Setup WiFi here (put WiFi details in a .h file)
  //
  setup_wifi();
  
  //
  // MQTT setup needs to be done here
  //
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  touchAttachInterrupt(T8, gotTouch0, threshold);
  touchAttachInterrupt(T6, gotTouch1, threshold);
  touchAttachInterrupt(T5, gotTouch2, threshold);
  touchAttachInterrupt(T4, gotTouch3, threshold);
  touchAttachInterrupt(T1, gotTouch4, threshold);
  touchAttachInterrupt(T9, gotTouch5, threshold);
  touchAttachInterrupt(T7, gotTouch6, threshold);
  touchAttachInterrupt(T3, gotTouch7, threshold);
  touchAttachInterrupt(T0, gotTouch8, threshold);
  touchAttachInterrupt(T2, gotTouch9, threshold);
}

/*
     A  B  C  D  F
     |  |  |  |  |
 a --*--*--*--*--*--
     |  |  |  |  |
 b --*--*--*--*--*--
     |  |  |  |  |
 c --*--*--*--*--*--
     |  |  |  |  |
 d --*--*--*--*--*--
     |  |  |  |  |
 e --*--*--*--*--*--
     |  |  |  |  |

touch[0] = GPIO 4
touch[1] = GPIO 0
touch[2] = GPIO 2
touch[3] = GPIO 15
touch[4] = GPIO 13
touch[5] = GPIO 12
touch[6] = GPIO 14
touch[7] = GPIO 27
touch[8] = GPIO 33
touch[9] = GPIO 32

  |----------------------+--------+------|
  | Touch sensor channel | Pin    | GPIO |
  |----------------------+--------+------|
  | T0                   | GPIO4  |    4 |
  | T1                   | GPIO0  |    0 |
  | T2                   | GPIO2  |    2 |
  | T3                   | MTDO   |   15 |
  | T4                   | MTCK   |   13 |
  | T5                   | MTDI   |   12 |
  | T6                   | MTMS   |   14 |
  | T7                   | GPIO27 |   27 |
  | T8                   | 32K_XN |   33 |
  | T9                   | 32K_XP |   32 |
  |----------------------+--------+------|

  https://github.com/espressif/esp-iot-solution/blob/release/v1.0/documents/touch_pad_solution/touch_sensor_design_en.md

 */
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  if (touch[0] && touch[5]) {touch[0] = false; touch[5] = false; touch_detected(1);}
  if (touch[0] && touch[6]) {touch[0] = false; touch[6] = false; touch_detected(2);}
  if (touch[0] && touch[7]) {touch[0] = false; touch[7] = false; touch_detected(3);}
  if (touch[0] && touch[8]) {touch[0] = false; touch[8] = false; touch_detected(4);}
  if (touch[0] && touch[9]) {touch[0] = false; touch[9] = false; touch_detected(5);}
  
  if (touch[1] && touch[5]) {touch[1] = false; touch[5] = false; touch_detected(6);}
  if (touch[1] && touch[6]) {touch[1] = false; touch[6] = false; touch_detected(7);}
  if (touch[1] && touch[7]) {touch[1] = false; touch[7] = false; touch_detected(8);}
  if (touch[1] && touch[8]) {touch[1] = false; touch[8] = false; touch_detected(9);}
  if (touch[1] && touch[9]) {touch[1] = false; touch[9] = false; touch_detected(10);}
  
  if (touch[2] && touch[5]) {touch[2] = false; touch[5] = false; touch_detected(11);}
  if (touch[2] && touch[6]) {touch[2] = false; touch[6] = false; touch_detected(12);}
  if (touch[2] && touch[7]) {touch[2] = false; touch[7] = false; touch_detected(13);}
  if (touch[2] && touch[8]) {touch[2] = false; touch[8] = false; touch_detected(14);}
  if (touch[2] && touch[9]) {touch[2] = false; touch[9] = false; touch_detected(15);}
  
  if (touch[3] && touch[5]) {touch[3] = false; touch[5] = false; touch_detected(16);}
  if (touch[3] && touch[6]) {touch[3] = false; touch[6] = false; touch_detected(17);}
  if (touch[3] && touch[7]) {touch[3] = false; touch[7] = false; touch_detected(18);}
  if (touch[3] && touch[8]) {touch[3] = false; touch[8] = false; touch_detected(19);}
  if (touch[3] && touch[9]) {touch[3] = false; touch[9] = false; touch_detected(20);}
  
  if (touch[4] && touch[5]) {touch[4] = false; touch[5] = false; touch_detected(21);}
  if (touch[4] && touch[6]) {touch[4] = false; touch[6] = false; touch_detected(22);}
  if (touch[4] && touch[7]) {touch[4] = false; touch[7] = false; touch_detected(23);}
  if (touch[4] && touch[8]) {touch[4] = false; touch[8] = false; touch_detected(24);}
  if (touch[4] && touch[9]) {touch[4] = false; touch[9] = false; touch_detected(25);}

  //client.publish("esp32/temperature", tempString);

}

# Local Variables:
# mode: c++
# End:
