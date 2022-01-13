#include "uart_frame.h"
#include "string.h"
#include "stdio.h"
#include <math.h>
#include "uart.h"

Control_Relay vrcr_RelayStt;
void reverse(char* str, int len);
void decToHexa(int n);
int ahex2int(char a, char b);
int intToStr(int x, char str[], int d);


int ahex2int(char a, char b) {

  a = (a <= '9') ? a - '0' : (a & 0x7) + 9;
  b = (b <= '9') ? b - '0' : (b & 0x7) + 9;

  return (a << 4) + b;
}

void detect_string(char arr[])
{
  char *temp[20], i = 0;
  if (checksumRX(RRX, vruc_ArrayCheckSum))
  {
    temp[0] = strtok(arr, ",");
    while (temp[i] != NULL)
    {
      i++;
      temp[i] = strtok(NULL, ",");
    }
    
    if (strstr(temp[0], "$code") != NULL)
    {
      if (strstr(temp[1], "1") != NULL)
      {
        vrcr_RelayStt.Relay0 = 1;
      }
      else 
      {
        vrcr_RelayStt.Relay0 = 0;
      }

      if (strstr(temp[2], "1") != NULL)
      {
        vrcr_RelayStt.Relay1 = 1;
      }
      else 
      {
        vrcr_RelayStt.Relay1 = 0;
      }
    }
  }
}

char checksumRX(char arr1[], char arr2[])
{
  unsigned char vruc_CreateCheckSum = 0;
  for (int i = 0; i < strlen(arr1); i++)
  {
    vruc_CreateCheckSum ^= arr1[i];
  }
  if (vruc_CreateCheckSum == ahex2int(arr2[0], arr2[1])) {
    return 1;
  }
  return 0;
}

void reverse(char* str, int len)
{
  int i = 0, j = len - 1, temp;
  while (i < j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

int intToStr(int x, char str[], int d)
{
  int i = 0;
  while (x) {
    str[i++] = (x % 10) + '0';
    x = x / 10;
  }
  while (i < d)
    str[i++] = '0';

  reverse(str, i);
  str[i] = '\0';
  return i;
}

void ftoa(float n, char* res, int afterpoint)
{
  int ipart = (int)n;
  float fpart = n - (float)ipart;
  int i = intToStr(ipart, res, 1);
  if (afterpoint != 0) {
    res[i] = '.'; 
    fpart = fpart * pow(10, afterpoint);
    intToStr((int)fpart, res + i + 1, afterpoint);
  }
}

void create_string_data(float arr[], char *str)
{
  unsigned char i = 0, vruc_CreateCheckSum = 0;
  char res1[5];
  sprintf(str, "$code");
  for (i = 0; i < 20; i++)
  {
    if (i < 16)
    {
      char res[10];
      ftoa(arr[i], res, 0);
      strcat(str, ",");
      strcat(str, res);
    }
    else
    {
      if (arr[i] >= 1)
      {
        strcat(str, ",");
        strcat(str, "1");
      }
      else if (arr[i] == 0)
      {
        strcat(str, ",");
        strcat(str, "0");
      }
    }
  }
  for (int i = 0; i < strlen(str); i++)
  {
    vruc_CreateCheckSum ^= str[i];
  }
  strcat(str, "*");
  
  if (vruc_CreateCheckSum < 16)
  {
    sprintf(res1, "%x", vruc_CreateCheckSum);
    strcat(str, "0");
    strcat(str, res1);
  }
  else
  {
    sprintf(res1, "%x", vruc_CreateCheckSum);
    strcat(str, res1);
  }
}

