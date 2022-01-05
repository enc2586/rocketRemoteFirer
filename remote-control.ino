#include <IRremote.h>

#define RECV_PIN 2
#define RELAY_PIN 3
#define RED_LED 13
#define GREEN_LED 12

#define USELESS_VALUE 0xFFFFFFFF
#define PLAY_BUTTON 0xFFC23D

IRrecv irrecv(RECV_PIN);
decode_results results;

bool powerStatus = false;

void reverseMode()
{
  if (powerStatus == false)
    {
      Serial.println("setting mode to true");
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(RELAY_PIN, HIGH);
      powerStatus = true;
    } else {
      Serial.println("setting mode to false");
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(RELAY_PIN, LOW);
      powerStatus = false;
    }
    return;
}

void setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results))
  {
    if (results.value != USELESS_VALUE)
    {
      
      Serial.print("vaild signal recieved: ");
      Serial.println(results.value, HEX);

      if (results.value == PLAY_BUTTON)
      {
        reverseMode();
      }
    }
    irrecv.resume();
  }
}
