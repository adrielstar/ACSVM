/**Arduuino Controler Vending Machine**/
#include <SoftwareSerial.h>

#define RELAY1  A0
#define RELAY2  A1
#define RELAY3  A2
#define RELAY4  A3
#define RELAY5  A4
#define RELAY6  A5

int bluetoothTx = 2; // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3; // RX-I pin of bluetooth mate, Arduino D3
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

int rotationTime = 10000;
int waitShort = 100;

void setup()
{
  Serial.begin(9600);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
  digitalWrite(RELAY5, HIGH);
  digitalWrite(RELAY6, HIGH);

  bluetooth.begin(115200); // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$"); // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$"); // Enter command mode
  delay(100); // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N"); // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600); // Start bluetooth serial at 9600
  delay(1000);

}

void loop()
{
  // Check Android Bluetooth
  if (bluetooth.available() > 0)
  {
    byte mByte = bluetooth.read();
    Serial.println(mByte, DEC);
    String newString = String(mByte, DEC);
    Serial.println(newString);

    if (newString) {
      rotateMotor(mByte);
    }
  }

  // Check Android NFC

  // Check iOS Bluetooth
}

/**
   Turn the relay on so that the motor can be turned on.
   After the rotation time it will be turned off automaticly.
*/
void rotateMotor(int productId)
{
  switch (productId) {
    case '0':
      digitalWrite(RELAY1, LOW);
      delay(rotationTime);
      digitalWrite(RELAY1, HIGH);
      break;
    case '1':
      digitalWrite(RELAY2, LOW);
      delay(rotationTime);
      digitalWrite(RELAY2, HIGH);
      break;
    case '2':
      digitalWrite(RELAY3, LOW);
      delay(rotationTime);
      digitalWrite(RELAY3, HIGH);
      break;
    case '3':
      digitalWrite(RELAY4, LOW);
      delay(rotationTime);
      digitalWrite(RELAY4, HIGH);
      break;
    case '4':
      digitalWrite(RELAY5, LOW);
      delay(rotationTime);
      digitalWrite(RELAY5, HIGH);
      break;
    case '5':
      digitalWrite(RELAY6, LOW);
      delay(rotationTime);
      digitalWrite(RELAY6, HIGH);
      break;
    default:
      break;
  }
}








