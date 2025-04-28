/*
  Serhii: 
  Device ver 2025.3
  Release day: 05.04.2025
  Copy project: Rui Santos - Complete project details at https://RandomNerdTutorials.com/telegram-control-esp32-esp8266-nodemcu-outputs/
  
  Project created using Brian Lough's Universal Telegram Bot Library: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
  Example based on the Universal Arduino Telegram Bot Library: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/FlashLED/FlashLED.ino
*/

#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>  // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

// Serhii Credentials ------------------------------------------------------------------------------------------------------
// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

const char* ssid_2 = "REPLACE_WITH_YOUR_SSID";
const char* password_2 = "REPLACE_WITH_YOUR_PASSWORD";

const char* ssid_3 = "REPLACE_WITH_YOUR_SSID";
const char* password_3 = "REPLACE_WITH_YOUR_PASSWORD";

// Initialize Telegram BOT
#define BOTtoken "XXXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
// List of people who has access to bot
#define ID_User_1 "xxxxxxxxx"
#define ID_User_2 "xxxxxxxxx"
#define ID_User_3 "xxxxxxxxx"
// Team id
#define ID_User_4 "xxxxxxxxx"
#define ID_User_5 "xxxxxxxxx"
#define ID_User_6 "xxxxxxxxx"
#define ID_User_7 "xxxxxxxxx"
#define ID_User_8 "xxxxxxxxx"

// Serhii Credentials ------------------------------------------------------------------------------------------------------

#ifdef ESP8266
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int hubPin_1 = 13;
const int hubPin_2 = 33;
const int hubPin_3 = 26;
const int hubPin_4 = 25;
const int hubPin_5 = 15;
const int hubPin_6 = 17;
const int hubPin_7 = 22;
const int hubPin_8 = 21;
const int computerPin = 27;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != ID_User_1 
      && chat_id != ID_User_2 
      && chat_id != ID_User_3 
      && chat_id != ID_User_4
      && chat_id != ID_User_5
      && chat_id != ID_User_6 
      && chat_id != ID_User_7 
      && chat_id != ID_User_8 ) {
      bot.sendMessage(chat_id, "Unauthorized user. For access, please contact Serhii_H (Intrusion team)!", "");
      continue;
    }

    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/reboot_hub_1 to reboot Hub 1 \n";
      welcome += "/reboot_hub_2 to reboot Hub 2 \n";
      welcome += "/reboot_hub_3 to reboot Hub 3 \n";
      welcome += "/reboot_hub_4 to reboot Hub 4 \n";
      welcome += "/reboot_hub_5 to reboot Hub 5 \n";
      welcome += "/reboot_hub_6 to reboot Hub 6 \n";
      welcome += "/reboot_hub_7 to reboot Hub 7 \n";
      welcome += "/reboot_hub_8 to reboot Hub 8 \n";
      welcome += "/reboot_all_hubs to reboots all Hubs one by one \n";
      welcome += "/reboot_computer to reboot computer \n";
      welcome += " © Powered by Intrusion Team, ver 2025.3\n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/reboot_hub_1") {
      rebootHub(1, hubPin_1, chat_id);
    }
    if (text == "/reboot_hub_2") {
      rebootHub(2, hubPin_2, chat_id);
    }
    if (text == "/reboot_hub_3") {
      rebootHub(3, hubPin_3, chat_id);
    }
    if (text == "/reboot_hub_4") {
      rebootHub(4, hubPin_4, chat_id);
    }
    if (text == "/reboot_hub_5") {
      rebootHub(5, hubPin_5, chat_id);
    }
    if (text == "/reboot_hub_6") {
      rebootHub(6, hubPin_6, chat_id);
    }
    if (text == "/reboot_hub_7") {
      rebootHub(7, hubPin_7, chat_id);
    }
    if (text == "/reboot_hub_8") {
      rebootHub(8, hubPin_8, chat_id);
    }
    if (text == "/reboot_all_hubs") {
      String telegramMessage = "Start reboot All hubs 🙉";
      bot.sendMessage(chat_id, telegramMessage, "");
      rebootHub(1, hubPin_1, chat_id);
      rebootHub(2, hubPin_2, chat_id);
      rebootHub(3, hubPin_3, chat_id);
      rebootHub(4, hubPin_4, chat_id);
      rebootHub(5, hubPin_5, chat_id);
      rebootHub(6, hubPin_6, chat_id);
      rebootHub(7, hubPin_7, chat_id);
      rebootHub(8, hubPin_8, chat_id);
      telegramMessage = " All hubs reboted. Enjoy 🎉";
      bot.sendMessage(chat_id, telegramMessage, "");
    } if (text == "/reboot_computer") {
      rebootComputer(computerPin, chat_id);
    }
  }
}

// ребут хабів
void rebootHub(int hubNumber, int hubPin, String chat_ID) {
  String telegramMessage = "😭 Kurwa bobr! Hub " + String(hubNumber) + " start reboot,  please wait 30 sec ... 😏";
  bot.sendMessage(chat_ID, telegramMessage, "");

  // натискаємо (вимикаємо хаб)
  digitalWrite(hubPin, LOW);
  delay(10000);
  // відтискаємо
  digitalWrite(hubPin, HIGH);
  delay(10000);

  // натискаємо (вкл хаб)
  digitalWrite(hubPin, LOW);
  delay(2000);
  // відтискаємо
  digitalWrite(hubPin, HIGH);
  delay(5000);

  telegramMessage = "✅ Hub " + String(hubNumber) + " rebooted! Enjoy  🎉";
  bot.sendMessage(chat_ID, telegramMessage, "");
}

// ребут компа
void rebootComputer(int compPin, String chat_ID){
  String telegramMessage = " 😭 Kurwa bobr! Computer start reboot. Wait 30 sec ... 😏";
  bot.sendMessage(chat_ID, telegramMessage, "");

  // замикаємо ресет
  digitalWrite(compPin, LOW);
  delay(2000);

  // розмикаємо
  digitalWrite(compPin, HIGH);
  delay(28000);

  telegramMessage = "✅ Computer rebooted! Enjoy  🎉";
  bot.sendMessage(chat_ID, telegramMessage, "");
}

// Реле управляється GND, тобто щоб спрацювало реле треба подати мінус
// тому за замовчанням подаємо + (HIGH), щоб реле не мпрацьовувало
void initPinRele(int hubPin) {
  pinMode(hubPin, OUTPUT);
  digitalWrite(hubPin, HIGH);
}


// підключення до мережі WIFI. Почергове педключення якщо одна з мереж недоступна то підключаємось до іншої інша.
bool connectToWiFi() {
  WiFi.disconnect(true);  // повністю обірвати поточне з'єднання
  WiFi.mode(WIFI_STA);

  const char* ssids[] = { ssid, ssid_2, ssid_3 };
  const char* passwords[] = { password, password_2, password_3 };

  for (int i = 0; i < 3; i++) {
    Serial.print("Trying WiFi ");
    Serial.println(ssids[i]);

    WiFi.begin(ssids[i], passwords[i]);

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
      delay(500);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n✅ Connected to:");
      Serial.println(ssids[i]);
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      return true;
    } else {
      Serial.println("\n❌ Failed to connect to:");
      Serial.println(ssids[i]);
    }
  }

  Serial.println("⚠ Failed to connect to all available WiFi networks.");
  return false;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Serhii:  device ver 2025.3");
  Serial.println("Serhii: for start bot use /start - return all comands in telegram");

#ifdef ESP8266
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  client.setTrustAnchors(&cert);     // Add root certificate for api.telegram.org
#endif

  initPinRele(hubPin_1);
  initPinRele(hubPin_2);
  initPinRele(hubPin_3);
  initPinRele(hubPin_4);
  initPinRele(hubPin_5);
  initPinRele(hubPin_6);
  initPinRele(hubPin_7);
  initPinRele(hubPin_8);
  initPinRele(computerPin);

  connectToWiFi();

#ifdef ESP32
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org
#endif
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("⚠ WiFi lost. Attempting reconnection...");
    connectToWiFi();
  }

  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
