#include <M5Stack.h>

void IotWriteCommand(char cmd[],char date[]){
  char buf[256] = {0};

  if(cmd == NULL)
  sprintf(buf,"AT\r\n");
  else if(date == NULL)
  sprintf(buf,"AT+%s\r\n",cmd);
  else
  sprintf(buf,"AT+%s=%s\r\n",cmd,date);
  
  Serial2.write(buf);
}

void get_time(void){
  IotWriteCommand(NULL,NULL);
  while(Serial2.available()){
    uint8_t ch = Serial2.read();
    Serial.write(ch);
    M5.Lcd.write(ch);
  }
}

void setup() {
  M5.begin();
  
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  delay(3000);
  digitalWrite(2, 1);
}

void loop() {
 if(M5.BtnA.wasReleased()){
    M5.Lcd.fillScreen(TFT_BLACK); 
    M5.Lcd.setCursor(60,80,2);
    get_time();
  }
  M5.update();
}
