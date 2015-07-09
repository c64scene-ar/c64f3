//#include <Console.h>
#include <stdarg.h>

int iToPC, iToC64;
char format[100];

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

void waitForPeer(void)
{
  //Console.begin();
  Serial.begin(9600);
  while (! Serial); // Wait until Serial is ready - Leonardo

  //printf("waiting...\n");
}

void setup() {
  // Now we're ready to wait for the PI to respond to our connection attempts.
  // initial connection handling.
  waitForPeer();
  
  pinMode(pushButton, INPUT);
}

void loop() {
  //
  // First stage: PC -> C64
  //
  if (Serial.available() > 0) {
    iToC64 = Serial.read();
    
    snprintf(format, sizeof(format), "ATN : %d - CLK : %d - DATA : %d\r", (iToC64 & 1), ((iToC64 >> 1) & 1), ((iToC64 >> 2) & 1));
    
    Serial.print(format);
  }

  //
  // Second stage: C64 -> PC
  //
  /*
  if (Serial.available() > 0) {
    iToC64 = Serial.read();
    
    Serial.println("ATN : %d - CLK : %d - DATA : %d", (iToC64 & 1), ((iToC64 >> 1) & 1), ((iToC64 >> 2) & 1));
  }
  */
  
  delay(1000);

}
