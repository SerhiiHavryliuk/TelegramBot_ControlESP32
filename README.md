# TelegramBot_ControlESP32
This code shows how to control the ESP32 GPIOs from anywhere in the world using Telegram.

Esp32 ttgo LilyGo T-Dispaly
Do not use 2, 12 pins for rele

05.04.2025 (PolygonAjaxRebootHubs_bot branch)
  Serhii - copy project https://RandomNerdTutorials.com/telegram-control-esp32-esp8266-nodemcu-outputs/

### Telegram commands:
  /start returns to returns all command

### Message:

Use the following commands to control your outputs.

/reboot_hub_1 to reboot Hub 1 

/reboot_hub_2 to reboot Hub 2 

/reboot_hub_3 to reboot Hub 3 

/reboot_hub_4 to reboot Hub 4 

/reboot_hub_5 to reboot Hub 5 

/reboot_hub_6 to reboot Hub 6 

/reboot_hub_7 to reboot Hub 7 

/reboot_hub_8 to reboot Hub 8

/reboot_all to reboot all Hubs



### Помилка Unauthorized user виникає ось тут:

  String chat_id = String(bot.messages[i].chat_id);
  if (chat_id != CHAT_ID){
    bot.sendMessage(chat_id, "Unauthorized user", "");
    continue;
  }

Треба прописати ід всіх юзерів, кому є доступ!
todo: хотів додавати бота у спільний чаті з чату керувати ботом. Поки не вийшло! 
Бот висне, після відправки одного повідомлення. Допомогло тільки видалення та створення бота заново.
