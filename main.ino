

// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;
uint8_t ledPin = 4;

struct dataStruct
{
  uint8_t buttonState;
  char data[10];
} myData;

//===========

void setup()
{
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  Serial.println("SimpleRx Starting");
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.startListening();
}

//=============

void loop()
{
  getData();
  showData();
}

//==============

void getData()
{
  if (radio.available())
  {
    radio.read(&myData, sizeof(myData));
    newData = true;
  }
}

void showData()
{
  if (newData == true)
  {
    Serial.print("Data received ");
    Serial.println(myData.data);
    digitalWrite(ledPin, myData.buttonState);
    newData = false;
  }
}