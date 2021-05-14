#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <CuteBuzzerSounds.h>
#include <Wire.h>

#include "Consolas-Bold7pt7b.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C

#define BUZZER_PIN   6
#define READY_PIN   11
#define ADVANCE_PIN 13


int sounds[20] = { S_CONNECTION, S_DISCONNECTION, S_BUTTON_PUSHED, S_MODE1, S_MODE2, S_MODE3, S_SURPRISE, S_OHOOH, S_OHOOH2, S_CUDDLY, S_SLEEPING, S_HAPPY, S_SUPER_HAPPY, S_HAPPY_SHORT, S_SAD, S_CONFUSED, S_FART1, S_FART2, S_FART3, S_JUMP };
int ind = 0;
bool btnUp = true;


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()  {
  Serial.begin(9600);
  
  pinMode(ADVANCE_PIN, INPUT);
  pinMode(READY_PIN, OUTPUT);
  cute.init(BUZZER_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  
  } else {
    delay(333);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setFont(&Consolas_Bold7pt7b);
    display.setCursor(4, 16);
    display.print("SFX #1 Ready!");
    display.display();
    analogWrite(READY_PIN, 128);
  }
}

void loop() {
  if (digitalRead(ADVANCE_PIN) == HIGH && btnUp) {
//    Serial.println("BTN DN");

    analogWrite(READY_PIN, 0);
    
    display.clearDisplay();
    display.setCursor(4, 16);
    display.print("SFX #");
    display.print(ind + 1);
    display.print(" GO!");
    display.display();
    
    if (++ind >= 20) {
      ind =0;
    }

    cute.play(sounds[ind]);
    delay(125);
//    cute.play(S_BUTTON_PUSHED);
//    delay(333);
//    cute.play(S_SAD);

    display.clearDisplay();
    display.setCursor(4, 16);
    display.print("SFX #");
    display.print(ind + 1);
    display.println(" Ready!");

    int brite = 0;
    for (byte i=0; i<8; i++) { 
      analogWrite(READY_PIN, brite);
      brite += 16;
      delay(15);

      if (i == 80) {
        display.display();
      }
    }
    
    display.display();
    btnUp = false;
  }

  if (digitalRead(ADVANCE_PIN) == LOW && !btnUp) {
//    Serial.println("BTN UP");
    btnUp = true;
  }
}
