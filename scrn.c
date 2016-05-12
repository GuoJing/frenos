#include <system.h>

/*
Address like below:

This buffer is located at 0xB8000, in physical memory.
The buffer is of the datatype 'short', meaning that each item in this text memory array takes up 16-bits
rather than the usual 8-bits that you might expect.

Each 16-bit element in the text memory buffer can be broken into an 'upper' 8-bits and a 'lower' 8-bits.
The lower 8 bits of each element tells the display controller what character to draw on the screen.
The upper 8-bits is used to define the foreground and background colors of which to draw the character.


15             12  11         8  7           0
 ---------------- ------------- -------------
|    Backcolor   |  Forecolor  |  Character  |
 ---------------- ------------- -------------

The upper 8-bits of each 16-bit text element is called an 'attribute byte', and the lower 8-bits is called the 'character byte'.

0 BLACK       8  DARK GREY
1 BLUE        9  LIGHT BLUE
2 GREEN       10 LIGHT GREEN
3 CYAN        11 LIGHT CYAN
4 RED         12 LIGHT RED
5 MAGENTA     13 LIGHT MAGENTA
6 BROWN       14 LIGHT BROWN
7 LIGHT GREY  15 WHITE
*/

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void scroll(void)
{
    unsigned blank, temp;

    blank = 0x20 | (attrib << 8);

    if(csr_y >= 25)
    {
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

void move_csr(void)
{
    unsigned temp;

    temp = csr_y * 80 + csr_x;

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void cls()
{
    unsigned blank;
    int i;

    blank = 0x20 | (attrib << 8);

    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);

    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    else if(c == '\r')
    {
        csr_x = 0;
    }
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;
        csr_x++;
    }

    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    scroll();
    move_csr();
}

void puts(char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}

void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void init_video(void)
{
    textmemptr = (unsigned short *)0xB8000;
    cls();
}
