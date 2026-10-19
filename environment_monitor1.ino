#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
const int Sensorpin=A0;
const int LEDpin=9;
const int Buzzerpin=10;

const float TempSafety=30.0;

void setup()
{
  pinMode(LEDpin,OUTPUT);
  pinMode(Buzzerpin,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  lcd.begin(16,2);
  lcd.print("HAB-TELEMETRY ON");
  delay(1500);
  lcd.clear();
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(50); 
  
  // 1. Read the raw analog value (0 to 1023)
  int rawvalue = analogRead(Sensorpin);
  
  // 2. Convert to voltage (0V - 5V)
  float voltage = (rawvalue / 1023.0) * 5.0;
  
  // 3. CORRECT TMP36 FORMULA: Subtract 0.5V offset, then multiply by 100
  float temperatureC = (voltage - 0.5) * 100.0;
  
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print("C    ");
  
  if(temperatureC>TempSafety){
    digitalWrite(LEDpin,HIGH);
    tone(Buzzerpin,1000);
     lcd.setCursor(0,1);
    lcd.print("STATUS: OVERHEAT!");
  }
  else{
    digitalWrite(LEDpin,LOW);
    noTone(Buzzerpin);
     lcd.setCursor(0,1);
    lcd.print("STATUS: STABLE   ");
  }
  delay(500);
}