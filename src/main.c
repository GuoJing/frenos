#include <system.h>

void *memcpy(void *dest, const void *src, size_t count)
{
  const char *sp = (const char *)src;
  char *dp = (char *)dest;
  for(; count != 0; count--) *dp++ = *sp++;
  return dest;
}

void *memset(void *dest, char val, size_t count)
{
  char *temp = (char *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
  unsigned short *temp = (unsigned short *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

size_t strlen(char *str)
{
  size_t retval;
  for(retval = 0; *str != '\0'; str++) retval++;
  return retval;
}

unsigned char inportb(unsigned short _port)
{
  unsigned char rv;
  __asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (_port));
  return rv;
}

void outportb(unsigned short _port, unsigned char _data)
{
  __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

int main()
{
  // init kernel
  init_video();         puts("[OK] VIDEO INIT DONE");
  gdt_install();        puts("[OK] GDT INIT DONE\n");
  idt_install();        puts("[OK] IDT INIT DONE\n");
  isrs_install();       puts("[OK] ISRS INIT DONE\n");
  irq_install();        puts("[OK] IRQ INIT DONE\n");
  timer_install();      puts("[OK] TIMER INIT DONE\n");
  keyboard_install();   puts("[OK] KEYBOARD INIT DONE\n");

  __asm__ __volatile__ ("sti");

  settextcolor(2, 0);

  puts("\n************************\n");
  puts("   Welcome to frenOS\n");
  puts("  A toy unix like OS \n");
  puts("************************\n\n");

  settextcolor(15, 0);
  puts("login:");

  for(;;);
  return 0;
}
