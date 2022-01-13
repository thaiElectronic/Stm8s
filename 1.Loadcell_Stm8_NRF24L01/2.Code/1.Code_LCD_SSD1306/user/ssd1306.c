
#include "ssd1306.h"
#include "DELAY.h"
#include "uart.h"
char ovwflg;
unsigned char xpos;
unsigned char ypos;
unsigned char xofset;
unsigned char gxstpt;
unsigned char scrnbuf[512];

char initOLED(void)
{
  const unsigned char tbl1[] = {0xae, 0xd5, 0x80, 0xa8, 0x1f, 0xd3, 0x00, 0x40, 0x8d, 0x14, 0x20, 0x00, 0xa1, 0xc8, 0xda, 0x02, 0x81, 0x8f, 0xd9, 0xf1, 0xdb, 0x40, 0xa4, 0xa6, 0xae, 0xaf, 0x22, 0x00,0xff, 0x21, 0x00, 0x7f};
  char errflg = false;
  for (int i = 0 ; i < (sizeof(tbl1)) ; i++)
  {
    SendCmd(tbl1[i]);
  }
  clearOLED(false);
  xpos = 0; ypos = 0; ovwflg = false;
  gxstpt = 64;
  return errflg;
}


void invert(bool mode) {
  SendCmd(mode ? 0xa7 : 0xa6);
}

// display ON/OFF
void displayON(bool onflg) {
  SendCmd(onflg ? 0xaf : 0xae);
}

// display character
void WriteCharacter(char character, bool neg) {
  // variables
  unsigned char data[9] = {0};

  // set data
  data[0] = 0x40; data[1] = neg ? 0xff : 0; data[7] = data[1]; data[8] = data[1];
  for (int i = 2 ; i < 7 ; i++) {
    if ((i > 1) && (i < 7)) data[i] = ASCII[character - 0x20][i - 2];
    if (neg) data[i] = ~data[i];
  }
  I2CdataTX(OLED_ad, data, 9);
  
  xpos += 8;
  if (xpos >= 128) {
    xpos = 0;
    ypos++;
    SetYX(ypos, 0);
  }
}

// set total screen position
void SetPixelXY(unsigned char x, unsigned char y) {
  unsigned char xr = x + XOFSET;
  SendCmd(0xb0 + y);
  SendCmd(xr & 0x0f);
  SendCmd(0x10 + ((xr >> 4) & 0x0f));
  xpos = x; ypos = y;
}

// set row and colum (X Y)
void SetYX(unsigned char row, unsigned char col) {
  SetPixelXY(col * 8, row);
}


// display string
void WriteString(char *characters, bool neg) {
  // write string
  while (*characters) {
    WriteCharacter(*characters, neg);
    characters++;
  }
}


// clear display
void clearOLED(bool neg) {
  // clear overwrite flag
  ovwflg = false;
  // clear screen
  unsigned char pos = 0;
  for (int j = 0 ; j < 8 ; j++) {
    SetPixelXY(0, j);
    for (int i = 0 ; i < 132 ; i++) {
      SendData(0, neg);
      if ((i >= gxstpt) && (i < (gxstpt + 64))) scrnbuf[pos++] = (neg ? 0xff : 0);
    }
  }
  SetYX(0, 0);
}


// draw frame
void DrawFrame(bool neg) {
  // variables
  char frmdat[8];

  // top line
  SetPixelXY(0, 0);
  for (int i = 0 ; i < 8 ; i++) frmdat[i] = 0x01;
  for (int i = 0 ; i < 16 ; i++) WriteExFont(frmdat, neg);
  // bottom line
  SetPixelXY(0, 7);
  for (int i = 0 ; i < 8 ; i++) frmdat[i] = 0x80;
  for (int i = 0 ; i < 16 ; i++) WriteExFont(frmdat, neg);
  // left line
  for (int i = 0 ; i < 8 ; i++) {
    SetPixelXY(0, i);
    SendData(0xff, neg);
  }
  // right line
  for (int i = 0 ; i < 8 ; i++) {
    SetPixelXY(127, i);
    SendData(0xff, neg);
  }
}


// write extra-font data (data : 8 bytes data)
void WriteExFont(char *data, bool neg) {
  // variables
  unsigned char ldata[9];

  // write data
  ldata[0] = 0x40;
  for (int i = 1 ; i < 9 ; i++) ldata[i] = neg ? ~data[i - 1] : data[i - 1];
  I2CdataTX(OLED_ad, ldata, 9);

  // update position
  xpos += 8;
  if (xpos >= 128) {
    xpos = 0;
    ypos++;
    SetYX(ypos, 0);
  }
}

void SetGraphicXY(unsigned char gx, unsigned char y) {
  SetPixelXY(gx + gxstpt, y);
}

void clearArea(unsigned char areakind, bool neg) {
  // variabales
  unsigned char xstpt = (areakind == TEXTAREA) ? ((gxstpt == 0) ? 64 : 0) : gxstpt;

  // clear overwrite flag
  if (areakind != TEXTAREA) ovwflg = false;

  // clear screen
  for (int j = 0 ; j < 8 ; j++) {
    SetPixelXY(xstpt, j);
    for (int i = xstpt ; i < (xstpt + 64) ; i++) {
      SendData(0, neg);
      xpos++;
    }
  }
}

// set pixel (gx:graphic area x axis)
void setPixel(unsigned char gx, unsigned char y, bool neg) {
  // check input parameter
  if ((gx < 64) && (y < 64)) {
    ovwflg = true;
    SetGraphicXY(gx, y >> 3);
    SendData((1 << (y % 8)), neg);
  }
}


// invert pixel (gx:graphic area x axis)
void invPixel(unsigned char gx, unsigned char y) {
  // check input parameter
  if ((gx < 64) && (y < 64)) {
    ovwflg = true;
    int bi = y % 8;
    SetGraphicXY(gx, y >> 3);
    SendData((1 << bi), ((scrnbuf[ypos * 64 + xpos - gxstpt] & (1 << bi)) != 0));
  }
}



// draw rectangle (gx1,gx2:graphic area x axis)
void drawRect(unsigned char gx1, unsigned char y1, unsigned char gx2, unsigned char y2, bool neg) {
  unsigned char tmp;

  // exchange x and y start and end
  if (gx1 > gx2) {
    tmp = gx1; gx1 = gx2; gx2 = tmp;
  }
  if (y1 > y2) {
    tmp = y1; y1 = y2; y2 = tmp;
  }

  // draw rect angle
#if 0
  drawHLine(gx1, y1, gx2 - gx1, neg);      // ng
  drawHLine(gx1, y2, gx2 - gx1, neg);      // ng
#else
  drawHLine(gx1, y2, gx2 - gx1, neg);      // ng
  drawHLine(gx1, y1, gx2 - gx1, neg);      // ng
#endif
  drawVLine(gx1, y1, y2 - y1, neg);
  drawVLine(gx2, y1, y2 - y1 + 1, neg);
}

// draw round rect (gx1,gx2:graphic area x axis)
void drawRoundRect(unsigned char gx1, unsigned char y1, unsigned char gx2, unsigned char y2, bool neg) {
  unsigned char tmp;

  if (gx1 > gx2) {
    tmp = gx1; gx1 = gx2; gx2 = tmp;
  }
  if (y1 > y2) {
    tmp = y1; y1 = y2; y2 = tmp;
  }
  if ((gx2 - gx1) > 4 && (y2 - y1) > 4)
  {
    setPixel(gx1 + 1, y1 + 1, neg);
    setPixel(gx2 - 1, y1 + 1, neg);
    setPixel(gx1 + 1, y2 - 1, neg);
    setPixel(gx2 - 1, y2 - 1, neg);
    drawHLine(gx1 + 2, y1, gx2 - gx1 - 3, neg);
    drawHLine(gx1 + 2, y2, gx2 - gx1 - 3, neg);
    drawVLine(gx1, y1 + 2, y2 - y1 - 3, neg);
    drawVLine(gx2, y1 + 2, y2 - y1 - 3, neg);
  }
}

// draw circle (gx:graphic area x axis)
void drawCircle(unsigned char gx, unsigned char y, unsigned char radius, bool neg) {
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x1 = 0;
  int y1 = radius;

  setPixel(gx, y + radius, neg);
  setPixel(gx, y - radius, neg);
  setPixel(gx + radius, y, neg);
  setPixel(gx - radius, y, neg);

  while (x1 < y1)
  {
    if (f >= 0)
    {
      y1--;
      ddF_y += 2;
      f += ddF_y;
    }
    x1++;
    ddF_x += 2;
    f += ddF_x;
    setPixel(gx + x1, y + y1, neg);
    setPixel(gx - x1, y + y1, neg);
    setPixel(gx + x1, y - y1, neg);
    setPixel(gx - x1, y - y1, neg);
    setPixel(gx + y1, y + x1, neg);
    setPixel(gx - y1, y + x1, neg);
    setPixel(gx + y1, y - x1, neg);
    setPixel(gx - y1, y - x1, neg);
  }
}

// draw bitmap data (gx:graphic area x axis)
void drawBitmap(unsigned char gx, unsigned char y, unsigned char *bitmap, unsigned char sx, unsigned char sy, bool neg) {
  unsigned char bit, data;

  for (int cy = 0 ; cy < sy ; cy++)
  {
    bit = cy % 8;
    for (int cx = 0 ; cx < sx ; cx++)
    {
      data = bitmap[cx + ((cy / 8) * sx)];
      if (data & (1 << bit)) setPixel(gx + cx, y + cy, neg);
    }
  }
}

// refresh graphic area
void refreshGraph(void) {
  // variables
  unsigned char ldata[2];

  // send data
  for (int i = 0 ; i < 8 ; i++) {   // row
    for (int j = 0 ; j < 64 ; j++) { // colum
      // set position
      SetGraphicXY(j, i);
      // send data
      ldata[0] = 0x40; ldata[1] = scrnbuf[i * 64 + j];
      I2CdataTX(OLED_ad, ldata, 2);
    }
  }
}

void SendData(unsigned char idata, bool neg) {
  // variables
  unsigned char ldata[2];
  unsigned char data = neg ? ~idata : idata;

  if ((xpos >= gxstpt) && (xpos < (gxstpt + 64))) {
    unsigned int bpt = ypos * 64 + (xpos - gxstpt);
    if (ovwflg) {
      if (neg) data &= scrnbuf[bpt];
      else data |= scrnbuf[bpt];
    }
    scrnbuf[bpt] = data;
  }
  // send command
  ldata[0] = 0x40; ldata[1] = data;
  I2CdataTX(OLED_ad, ldata, 2);
}

bool SendCmd(unsigned char cmd) {
  unsigned char ldata[2];
  ldata[0] = 0x00; ldata[1] = cmd;
  return I2CdataTX(OLED_ad, ldata, 2);
}

void drawHLine(unsigned char gx, unsigned char y, unsigned char l, bool neg) {
  if ((gx < 64) && (y < 64)) {
    for (int cx = 0 ; (cx < l) && (cx < 64) && ((gx + cx) < (gxstpt + 64))  ; cx++) setPixel(gx + cx, y, neg);
  }
}

void drawVLine(unsigned char gx, unsigned char y, unsigned char l, bool neg) {
  if ((gx < 64) && (y < 64)) {
    for (int cy = 0 ; (cy < l) && (cy < 64) && ((y + cy) < 64) ; cy++) setPixel(gx, y + cy, neg);
  }
}

void drawLine(unsigned char gx1, unsigned char y1, unsigned char gx2, unsigned char y2, bool neg) {
  unsigned char tmp;
  double delta, tx, ty;

  // draw horizontal line
  if (y1 == y2) {
    if (gx1 > gx2) {
      tmp = gx1;
      gx1 = gx2;
      gx2 = tmp;
    }
    drawHLine(gx1, y1, gx2 - gx1, neg);

    // draw vertiacl line
  } else if (gx1 == gx2) {
    if (y1 > y2) {
      tmp = y1;
      y1 = y2;
      y2 = tmp;
    }
    drawVLine(gx1, y1, y2 - y1, neg);

    // draw longer x axis tilt line
  } else if (((gx2 >= gx1) ? gx2 - gx1 : gx1 - gx2) > ((y2 >= y1) ? y2 - y1 : y1 - y2)) {
    delta = ((double)(y2 - y1) / (double)(gx2 - gx1));
    ty = (double)(y1);
    if (gx1 > gx2) {
      for (int i = gx1 ; i >= gx2 ; i--) {
        setPixel((unsigned char)i, (unsigned char)(ty + 0.5), neg);
        ty = ty - delta;
      }

    } else {
      for (int i = gx1 ; i <= gx2 ; i++) {
        setPixel((unsigned char)i, (unsigned char)(ty + 0.5), neg);
        ty = ty + delta;
      }
    }

    // draw longer y axis tilt line
  } else {
    delta = ((float)(gx2 - gx1) / (float)(y2 - y1));
    tx = (float)(gx1);
    if (y1 > y2) {
      for (int i = y1 ; i >= y2 ; i--) {
        setPixel((unsigned char)(tx + 0.5), (unsigned char)i, neg);
        tx = tx - delta;
      }
    } else {
      for (int i = y1 ; i <= y2 ; i++) {
        setPixel((unsigned char)(tx + 0.5), (unsigned char)i, neg);
        tx = tx + delta;
      }
    }
  }
}

void selectGarea(unsigned char side)
{
  gxstpt = (side == LEFTHALF) ? 0 : 64;
}

void SetOvrWflg(bool a)
{
  ovwflg = a;
}