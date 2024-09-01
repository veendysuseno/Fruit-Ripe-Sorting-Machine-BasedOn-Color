#include <LiquidCrystal_I2C.h>        //Library LCD I2C
LiquidCrystal_I2C lcd(0x27,16,2);     //Alamat I2C

#define buzzer 12

#define S0 2            //S0 pada D2
#define S1 3            //S1 pada D3
#define S2 4            //S2 pada D4
#define S3 5            //S3 pada D5
#define sensorOut 10    //Out sensor pada D10

int frequencyR = 0;      //Variabel penampung data sensor
int frequencyG = 0;
int frequencyB = 0;

void setup() {
  pinMode(S0, OUTPUT);    //Setting I/O
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pinMode(buzzer, OUTPUT);
  
  lcd.init ();            //Mulai LCD
  lcd.setBacklight(HIGH); //Nyalakan backlight
}
void loop() {
  lcd.setCursor(0,0);
  lcd.print("Kematangan:");         //Tampilan

  //Setting baca merah
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  frequencyR = pulseIn(sensorOut, LOW);
  frequencyR = map(frequencyR, 29,80,255,0);
  
  //Setting baca hijau
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  frequencyG = pulseIn(sensorOut, LOW);
  frequencyG = map(frequencyG, 31,90,255,0);
  
  //Setting baca biru
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frequencyB = pulseIn(sensorOut, LOW);
  frequencyB = map(frequencyB, 51,300,255,0);
  
  if(frequencyR >= 300 && frequencyR <=330){        //Jika rentang warna R,G,B sekian, maka
    if(frequencyG >= 220 && frequencyG <=250){
      if(frequencyB >= 0 && frequencyB <=500){
        lcd.setCursor(0,1);
        lcd.print("Matang");                        //Dinyatakan matang
        digitalWrite(buzzer, HIGH);
        delay(250);
        digitalWrite(buzzer, LOW);
        delay(1000);
      } 
    }
  }
  else if(frequencyR >= 260 && frequencyR <=290){   //Jika rentang warna R,G,B sekian, maka
    if(frequencyG >= 280 && frequencyG <=310){
      if(frequencyB >= 0 && frequencyB <=500){
        lcd.setCursor(0,1);
        lcd.print("Mentah");                        //Dinyatakan mentah
        digitalWrite(buzzer, HIGH);
        delay(2000);
        digitalWrite(buzzer, LOW);
        delay(1000);
      } 
    }
  }
  
  delay(1000);
  lcd.clear();
}
