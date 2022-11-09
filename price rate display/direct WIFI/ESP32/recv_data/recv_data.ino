#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[16];
    char b[16];
    int c = 0;
} struct_message;

// Create a struct_message called myData
struct_message myData;
int c;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  LiquidCrystal_I2C lcd(myData.c, 16, 2);
  lcd.clear();
  Serial.print("LINE1 received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("LINE2 received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.b);
  Serial.print("ADDRESS received: ");
  Serial.println(len);
  Serial.print("int: ");
  Serial.println(myData.c);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(myData.a);
  lcd.setCursor(0,1);
  lcd.print(myData.b);
  delay(1000);
}
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
    
  }
  for (c=56;c<=63;c++)
  {
    LiquidCrystal_I2C lcd(c, 16, 2);
    lcd.init();
  }
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
  //esp_now_register_recv_cb(chang);
  
    
}
 
void loop() {
  
}
