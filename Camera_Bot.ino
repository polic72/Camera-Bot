//#include <stdio.h>

#define PWM_A 10
#define PWM_B 11

#define PWM_SPEED_A 40
#define PWM_SPEED_B 52

#define PWM_SPEED_BRAKE 24


#define PIN_A1 4
#define PIN_A2 5

#define PIN_B1 6
#define PIN_B2 7


#define STOP_DELAY 40


#define ENCODER_A1 7
#define ENCODER_A2 6

#define ENCODER_B1 5
#define ENCODER_B2 4



#define BUFFER_SIZE 64

char buff[BUFFER_SIZE];


#define OK_LEN 3
#define BAD_LEN 4

char Ok[] = {'O', 'k', '|'};
char Bad[] = {'B', 'a', 'd', '|'};


char letter;
int counter;


bool is_moving = false;
bool last_is_moving = false;


void setup()
{
  //PWM
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  analogWrite(PWM_A, PWM_SPEED_BRAKE);  //The bot starts not moving.
  analogWrite(PWM_B, PWM_SPEED_BRAKE);


  //Motor
  pinMode(PIN_A1, OUTPUT);
  pinMode(PIN_A2, OUTPUT);

  pinMode(PIN_B1, OUTPUT);
  pinMode(PIN_B2, OUTPUT);


  //Encoder
  pinMode(ENCODER_A1, INPUT);
  pinMode(ENCODER_A2, INPUT);

  pinMode(ENCODER_B1, INPUT);
  pinMode(ENCODER_B2, INPUT);

  
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

        setMoving(true);

        digitalWrite(PIN_A1, HIGH);
        digitalWrite(PIN_A2, LOW);
      }
      else if (strcmp(buff, "Down") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_A1, LOW);
        digitalWrite(PIN_A2, HIGH);

        setMoving(true);
      }
      else if (strcmp(buff, "Left") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_B1, HIGH);
        digitalWrite(PIN_B2, LOW);

        setMoving(true);
      }
      else if (strcmp(buff, "Right") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_B1, LOW);
        digitalWrite(PIN_B2, HIGH);

        setMoving(true);
      }
      else if (strcmp(buff, "StopUp") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_A1, LOW);
        digitalWrite(PIN_A2, HIGH);

        delay(STOP_DELAY);

        digitalWrite(PIN_A1, LOW);
        digitalWrite(PIN_A2, LOW);

        setMoving(false);
      }
      else if (strcmp(buff, "StopDown") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_A1, HIGH);
        digitalWrite(PIN_A2, LOW);

        delay(STOP_DELAY);

        digitalWrite(PIN_A1, LOW);
        digitalWrite(PIN_A2, LOW);

        setMoving(false);
      }
      else if (strcmp(buff, "StopLeft") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_B1, LOW);
        digitalWrite(PIN_B2, HIGH);

        delay(STOP_DELAY);

        digitalWrite(PIN_B1, LOW);
        digitalWrite(PIN_B2, LOW);

        setMoving(false);
      }
      else if (strcmp(buff, "StopRight") == 0)
      {
        Serial.write(Ok, OK_LEN);

        digitalWrite(PIN_B1, HIGH);
        digitalWrite(PIN_B2, LOW);

        delay(STOP_DELAY);

        digitalWrite(PIN_B1, LOW);
        digitalWrite(PIN_B2, LOW);

        setMoving(false);
      }
      else if (strcmp(buff, "Stop") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Stop moving at all.
        //Put all PINs to LOW and set STBY to LOW.
        setMoving(false);
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
  else
  {
    if (!is_moving && last_is_moving)
    {
      digitalWrite(PIN_A1, HIGH);
      digitalWrite(PIN_A2, HIGH);
  
      digitalWrite(PIN_B1, HIGH);
      digitalWrite(PIN_B2, HIGH);

      last_is_moving = false;
    }
    else if (is_moving && !last_is_moving)
    {
      last_is_moving = true;
    }







    
//    int state = digitalRead(ENCODER_A1);
//
//    if (state == HIGH)
//    {
//      counter
//    }


    
//    digitalWrite(PIN_A1, HIGH);
//    digitalWrite(PIN_A2, LOW);
//
//    digitalWrite(PIN_B1, HIGH);
//    digitalWrite(PIN_B2, LOW);
//
//
//    delay(STOP_DELAY / 16);
//    
//
//    digitalWrite(PIN_A1, LOW);
//    digitalWrite(PIN_A2, HIGH);
//
//    digitalWrite(PIN_B1, LOW);
//    digitalWrite(PIN_B2, HIGH);
//
//
//    delay(STOP_DELAY / 16);
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


//Sets whether or not the bot is currently moving.
void setMoving(bool moving)
{
  if (moving)
  {
    analogWrite(PWM_A, PWM_SPEED_A);
    analogWrite(PWM_B, PWM_SPEED_B);
    
    is_moving = true;
  }
  else
  {
    analogWrite(PWM_A, PWM_SPEED_BRAKE);
    analogWrite(PWM_B, PWM_SPEED_BRAKE);

    is_moving = false;
  }
}

