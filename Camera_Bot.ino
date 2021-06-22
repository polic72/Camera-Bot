//#include <stdio.h>

#define PWM_A 10
#define PWM_B 11

#define PWM_SPEED 52


#define PIN_A1 2
#define PIN_A2 3

#define PIN_B1 4
#define PIN_B2 5


#define STOP_DELAY 40



#define BUFFER_SIZE 64

char buff[BUFFER_SIZE];


#define OK_LEN 3
#define BAD_LEN 4

char Ok[] = {'O', 'k', '|'};
char Bad[] = {'B', 'a', 'd', '|'};


char letter;
int counter;


void setup()
{
  //PWM
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  analogWrite(PWM_A, PWM_SPEED);
  analogWrite(PWM_B, PWM_SPEED);


  //Motor
  pinMode(PIN_A1, OUTPUT);
  pinMode(PIN_A2, OUTPUT);

  pinMode(PIN_B1, OUTPUT);
  pinMode(PIN_B2, OUTPUT);

  
  //Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);

  counter = 0;
}


void loop()
{
  if (Serial.available() > 0)
  {
    letter = Serial.read();

    if (letter == '\n' || letter == '\r')
    {
      return;
    }
    else if (letter == '|')
    {
      addToBuffer('\0');
      
      if (strcmp(buff, "Up") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_A1, HIGH);
        digitalWrite(PIN_A2, LOW);
      }
      else if (strcmp(buff, "Down") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_A1, LOW);
        digitalWrite(PIN_A2, HIGH);
      }
      else if (strcmp(buff, "Left") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_B1, HIGH);
        digitalWrite(PIN_B2, LOW);
      }
      else if (strcmp(buff, "Right") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_B1, LOW);
        digitalWrite(PIN_B2, HIGH);
      }
      else if (strcmp(buff, "StopUp") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_A1, LOW);
        digitalWrite(PIN_A2, HIGH);

        delay(STOP_DELAY);

        digitalWrite(PIN_A1, LOW);
        digitalWrite(PIN_A2, LOW);
      }
      else if (strcmp(buff, "StopDown") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_A1, HIGH);
        digitalWrite(PIN_A2, LOW);

        delay(STOP_DELAY);

        digitalWrite(PIN_A1, LOW);
        digitalWrite(PIN_A2, LOW);
      }
      else if (strcmp(buff, "StopLeft") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_B1, LOW);
        digitalWrite(PIN_B2, HIGH);

        delay(STOP_DELAY);

        digitalWrite(PIN_B1, LOW);
        digitalWrite(PIN_B2, LOW);
      }
      else if (strcmp(buff, "StopRight") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_B1, HIGH);
        digitalWrite(PIN_B2, LOW);

        delay(STOP_DELAY);

        digitalWrite(PIN_B1, LOW);
        digitalWrite(PIN_B2, LOW);
      }
      else if (strcmp(buff, "Stop") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Stop moving at all.
        //Put all PINs to LOW and set STBY to LOW.
      }
      else if (strcmp(buff, "Disconnect") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Do nothing, but that's ok.
      }
      else
      {
        Serial.write(Bad, BAD_LEN);
      }

      counter = 0;
    }
    else
    {
      addToBuffer(letter);
    }
  }
}


//Adds a character to the buffer.
void addToBuffer(char c)
{
  if (counter >= 64)
  {
    counter = 0;
  }
  
  buff[counter++] = c;
}
