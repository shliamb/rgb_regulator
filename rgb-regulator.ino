#include "Adafruit_NeoPixel.h" // подключаем библиотеку
#define PIN  4              // указываем пин для подключения ленты
#define NUMPIXELS 10  // указываем количество светодиодов в ленте

Adafruit_NeoPixel strip (NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // создаем объект strip с нужными характеристиками

int j;
int i;

void setup() {
  strip.begin(); // инициализируем ленту
  pinMode(7, OUTPUT); // пищалка
  pinMode(5, INPUT_PULLUP); // поддтягивает в внутренней конфигурации контроллера резистор к пиатнию для высокого уровня
  pinMode(6, INPUT_PULLUP);
  strip.setBrightness (255); //макс яркость
  j=150; //начальное значение переменной j для яркости RGB
}

bool flag = false;
bool flag6 = false;
//bool doubleclik = false;
uint32_t btnTimer = 0;
uint32_t btnTimer6 = 0;

void loop() {
  bool btnState = !digitalRead(5); // инверсия значения кнопки
  bool btnState6 = !digitalRead(6); // инверсия значения кнопки
//5 кнопка
  if (btnState && !flag && millis() - btnTimer > 100 && j <= 240) {  // обработчик нажатия с защитой от дребезжания + 15
    flag = true;
    btnTimer = millis();
    j = j + 15;
    i = 0;
    if (btnState && j == 255) {
        digitalWrite(7, 1);
        delay(100);
        digitalWrite(7, 0);
        delay(100);
        digitalWrite(7, 1);
        delay(100);
        digitalWrite(7, 0);
        //delay(500);  
    }
  }
  
   if (btnState && flag && millis() - btnTimer > 500) { // обработчик зажатия в максимум освещения
    btnTimer = millis();
    j = 255;
    i = 0;
  }
  if (!btnState && flag && millis() - btnTimer > 100) { // обработчик отпускания нажатой кнопки с защитой от дребезжания
    flag = false;
    btnTimer = millis();
  }

//6 кнопка
  if (btnState6 && !flag6 && millis() - btnTimer6 > 100 && j >= 15) {  // обработчик нажатия с защитой от дребезжания + 15
    flag6 = true;
    btnTimer6 = millis();
    j = j - 15;
    i = 0;
    if (btnState6 && j == 0) {
        digitalWrite(7, 1);
        delay(100);
        digitalWrite(7, 0);
        delay(100);
        digitalWrite(7, 1);
        delay(100);
        digitalWrite(7, 0);
        //delay(500);  
    }
  }
  
   if (btnState6 && flag6 && millis() - btnTimer6 > 500) { // обработчик зажатия в максимум освещения
    btnTimer6 = millis();
    j = 0;
    i = 0;
  }
  if (!btnState6 && flag6 && millis() - btnTimer6 > 100) { // обработчик отпускания нажатой кнопки с защитой от дребезжания
    flag6 = false;
    btnTimer6 = millis();
  }

//Адрессные светодиоды
for (int i = -1; i < NUMPIXELS; i++) {
  strip.setPixelColor(i, strip.Color(j, j, j));
  strip.show();
}

}
