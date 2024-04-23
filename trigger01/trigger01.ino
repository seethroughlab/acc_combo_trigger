#define Z_LIFT_THRESH 0.2
#define Z_STILL_THRESH 0.1

#include <Wire.h>
#include <Adafruit_ADXL343.h>
#include <BleKeyboard.h>
#include <BleMouse.h>

Adafruit_ADXL343 accel = Adafruit_ADXL343(0x53, &Wire1);
float z_eased = 0;
bool debounce = true;
float stillTimer = 0;
sensors_event_t event;

void setup() {
  Serial.begin(115200);

  if (!accel.begin()) {
    Serial.println("Ooops, no ADXL343 detected ... Check your wiring!");
  }
  accel.setDataRate(ADXL343_DATARATE_50_HZ);
  accel.setRange(ADXL343_RANGE_8_G);

  bleDevice.setName("STL Trigger");

  Keyboard.begin();
}

void loop() {

  accel.getEvent(&event);

  // Minus acceleration due to gravity, and swap down/up
  float z = (event.acceleration.z - 9.8) * -1.0;
  z_eased = (z - z_eased) / 20.0;

  // Add to the "stillTimer" if movement is below the Z_STILL_THRESH
  if (z_eased < Z_STILL_THRESH) {
    stillTimer += 1000 / 50;
  } else {
    stillTimer = 0;
  }

  if (stillTimer > 1000) {
    debounce = true;
  }

  if (z_eased > Z_LIFT_THRESH) {
    if (debounce) {
      Serial.println("Trigger");
      if (bleDevice.isConnected()) {
        Keyboard.print("5");
        delay(250);

        Mouse.press(MOUSE_LEFT);
        delay(3000);
        Mouse.release(MOUSE_LEFT);

        //Mouse.click(MOUSE_LEFT);
      }
      debounce = false;
    }
  }

  // Update the BLE Battery level
  analogReadResolution(10);
  int pinValue = analogRead(A2);
  float voltage = pinValue * 2.0 * 3.3 / 1023.0;
  uint8_t pct = (voltage / 3.3) * 100;
  bleDevice.setBatteryLevel(pct);

  delay(1000 / 50);
}
