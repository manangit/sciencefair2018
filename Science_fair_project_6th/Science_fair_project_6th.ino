/*
  My Science Fair Project
  The one switch Smart Home
*/
#include <TM1637Display.h>  // 4-digit Diplay library
#include <IRremote.h> //IR Sensor library

const int CLK = 6;          // Set the CLK pin connection to the display
const int DIO = 7;          // Set the DIO pin connection to the display

TM1637Display display(CLK, DIO);  // set up the 4-Digit Display.

int porchLight = 2;         // Prorch light should be conected to pin 2 on the arduino
int coachLights = 4;        // Coach lights should be conected to pin 4 on the arduino
int backyardLight = 8;      // Backyard light should be conected to pin 8 on the arduino
int switchPin = 12;         // Switch should be conected to pin 12 on the arduino
bool isPorchLightOn = false; // To track if the light is on or off
bool areCoachLightsOn = false; // To track if the light is on or off
bool isBackyardLightOn = false; // To track if the light is on or off

int RECV_PIN = 10;           //IR sensor should be conected to pin 10 on the arduino
long ONE = 16724175;
long TWO = 16718055;
long THREE = 16743045;
long FOUR = 16716015;
long FIVE = 16726215;
long timer = 0;             //

int value;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()               // It is used to initialize variables, pin modes, etc. The setup function will only run once.
{
  pinMode(porchLight, OUTPUT); // Telling the arduino that the Light pin is an output
  pinMode(coachLights, OUTPUT); // Telling the arduino that the Light pin is an output
  pinMode(backyardLight, OUTPUT); // Telling the arduino that the Light pin is an output
  pinMode(switchPin, INPUT); // Telling the arduino that Switch pin is an input
 
  display.setBrightness(10); // Set brightness of LED display to 100%

  Serial.begin(9600);       //For debugging on serial port

  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();          // Start the receiver
  Serial.println("Enabled IRin");
}

void loop()                 // This function runs forever until it is on
{
  while (digitalRead(switchPin) == HIGH) //
  {
    delay (100);                        // Delay for 100 miliseconds
    timer = timer + 100;
    display.showNumberDec(timer);
    Serial.println(timer);
  }

  if (timer > 100 && timer <= 1000)
  {
    isPorchLightOn = !isPorchLightOn;
    digitalWrite(porchLight, isPorchLightOn);
    timer = 0;
  }

  if ( timer > 1000 && timer <= 3000)
  {
    areCoachLightsOn = !areCoachLightsOn;
    digitalWrite(coachLights, areCoachLightsOn);
    timer = 0;
  }

  if (timer > 3000)
  {
    isBackyardLightOn = !isBackyardLightOn;
    digitalWrite(backyardLight, isBackyardLightOn);
    timer = 0;
  }
  display.showNumberDec(0);

  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if (results.value == ONE) {
      isPorchLightOn = !isPorchLightOn;
      digitalWrite(porchLight, isPorchLightOn);
    }
    if (results.value == TWO) {
      areCoachLightsOn = !areCoachLightsOn;
      digitalWrite(coachLights, areCoachLightsOn);
    }
    if (results.value == THREE) {
      isBackyardLightOn = !isBackyardLightOn;
      digitalWrite(backyardLight, isBackyardLightOn);
    }
    if (results.value == FOUR) {
      isPorchLightOn = true;
      digitalWrite(porchLight, isPorchLightOn);
      areCoachLightsOn = true;
      digitalWrite(coachLights, areCoachLightsOn);
      isBackyardLightOn = true;
      digitalWrite(backyardLight, isBackyardLightOn);
    }
    if (results.value == FIVE) {
      isPorchLightOn = false;
      digitalWrite(porchLight, isPorchLightOn);
      areCoachLightsOn = false;
      digitalWrite(coachLights, areCoachLightsOn);
      isBackyardLightOn = false;
      digitalWrite(backyardLight, isBackyardLightOn);
    }
  }
  irrecv.resume(); // Receive the next value
  delay(250);
}
