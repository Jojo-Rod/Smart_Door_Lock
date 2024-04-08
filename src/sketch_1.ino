#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

// Pin Definitions
#define SS_PIN 5
#define RST_PIN 9
#define RELAY 3 // Connect the relay to pin 3
#define BUZZER 2 // Connect the buzzer to pin 2
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

// Create MFRC522 and LCD instances
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // Initialize LCD and Serial communication
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  // Initiate SPI bus and MFRC522
  SPI.begin();
  mfrc522.PCD_Init();

  // Set pin modes
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);

  // Display welcome message on LCD and Serial monitor
  lcd.setCursor(4, 0);
  lcd.print("WELCOME!");
  lcd.setCursor(0, 1);
  lcd.print("Scan your card");
  Serial.println("Put your card to the reader for scanning ...");
  Serial.println();
}

void loop()
{
  // Check if a new card is present
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  // Read the card's UID
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  // Display the UID on the serial monitor
  Serial.print("UID tag: ");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();

  // Check if the card is authorized
  if (content.substring(1) == "33 9F 94 F5") // Replace with your own card number
  {
    // Grant authorized access
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Authorized access");
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
  }
  else
  {
    // Deny access and activate buzzer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access denied");
    Serial.println("Access denied");
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    noTone(BUZZER);
  }
}
