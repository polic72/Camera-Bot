//#include <stdio.h>

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

        //Move up.
      }
      else if (strcmp(buff, "Down") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Move down.
      }
      else if (strcmp(buff, "Left") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Move left.
      }
      else if (strcmp(buff, "Right") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Move right.
      }
      else if (strcmp(buff, "StopUp") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Stop moving up.
      }
      else if (strcmp(buff, "StopDown") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Stop moving down.
      }
      else if (strcmp(buff, "StopLeft") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Stop moving left.
      }
      else if (strcmp(buff, "StopRight") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Stop moving right.
      }
      else if (strcmp(buff, "Stop") == 0)
      {
        Serial.write(Ok, OK_LEN);

        //Stop moving at all.
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
