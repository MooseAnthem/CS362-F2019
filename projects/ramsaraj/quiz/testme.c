#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //inputChar() returns a random char value from the ASCII character set, not including
    //control characters. This is ASCII range 32 - 126:

    return (rand() % (126 - 32 + 1)) + 32;
}

char *inputString()
{
    //returns a random string of length 6 (with index [5] being the null terminator).
    //This small string is primarily a viability test. I should come and make this more
    //robust before turning it in!

    int strLength = 100;
    char* randomStr = malloc(sizeof(char) * strLength);
    
    for(int i = 0; i <= strLength - 1; i++) {
        char lowerAlpha = inputChar();
        do {
            lowerAlpha = inputChar();
        } while(!(lowerAlpha >= 97 && lowerAlpha <= 122));

        randomStr[i] = lowerAlpha;
    }
    randomStr[5] = '\0';

    return randomStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      free(s);
      exit(200);
    }
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
