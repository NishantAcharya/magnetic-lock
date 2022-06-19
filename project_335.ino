/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how to use BBC Micro:Bit
  to connect your project to Blynk.

  Note: This requires nRF5 support package:
    https://github.com/sandeepmistry/arduino-nRF5

  And BLEPeripheral library
    from http://librarymanager/all#BLEPeripheral
    or https://github.com/sandeepmistry/arduino-BLEPeripheral

  1. Select: Tools -> SoftDevice -> S110
  2. Select: Tools -> Programmer -> CMSIS-DAP
  3. Select: Tools -> nRF5 Flash SoftDevice
  4. Read and Accept License
  5. Verify and Upload Sketch

  NOTE: BLE support is in beta!

 *************************************************************/

#define BLYNK_USE_DIRECT_CONNECT

#define BLYNK_PRINT Serial

#include <BlynkSimpleBLEPeripheral.h>
#include <BLEPeripheral.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "wKTVL_rzdJTv_mgQZWMITBXk0OtNztyp";

const byte doorIterator = 0;
const byte lock_perm_1 = 1;
const byte lock_perm_2 = 2;
const byte lock_perm_3 = 3;
const byte debug_led = 11;
const byte lock_pin = 20;

int pushCounter = 0;
int openNum = 0;
int lock_state_1 = 0;
int lock_state_2 = 0;
boolean lock = false;

// Create ble serial instance, parameters are ignored for MicroBit
BLESerial SerialBLE(0, 0, 0);

void setup() {
  pinMode(lock_perm_1, INPUT_PULLUP);
  pinMode(lock_perm_2, INPUT_PULLUP);
  pinMode(lock_pin,INPUT_PULLUP);
  pinMode(debug_led, OUTPUT);
  pinMode(doorIterator, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(doorIterator), divisorUp, RISING);
  attachInterrupt(digitalPinToInterrupt(lock_perm_1), lock1Up, RISING);
  attachInterrupt(digitalPinToInterrupt(lock_perm_2), lock2Up, RISING);
  attachInterrupt(lock_pin, twistLock, CHANGE);
  Serial.begin(9600);

  SerialBLE.setLocalName("MicroBit");
  SerialBLE.setDeviceName("Microbit");
  SerialBLE.setAppearance(0x0080);
  SerialBLE.begin();

  Blynk.begin(SerialBLE, auth);
  Serial.println("Waiting for connections...");

 
}

void loop() {
  SerialBLE.poll();

  if (SerialBLE) {    // If BLE is connected...
    Blynk.run();
  }
    // read the pushbutton input pin:
  
}

void divisorUp(){
  openNum += 1;
  Serial.print(openNum);
  Serial.println(" Number of times the door can be opened");
  }

 void lock1Up(){
  if(!lock){
   lock_state_1 += 1;
   Serial.print(lock_state_1);
  Serial.println(" Number on lock 1");
  }
  else{
  Serial.println("Door is locked enter combination to open");
  }
  }
 void lock2Up(){
  if(!lock){
  lock_state_2 += 1;
  Serial.print(lock_state_2);
  Serial.println(" Number on lock 2");
  }
  else{
  Serial.println("Door is locked enter combination to open");
  }
  }
  void twistLock(){
    lock = true;
    Serial.print(lock);
  Serial.println(" is the door secured?");
    }

  
