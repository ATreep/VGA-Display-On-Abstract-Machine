#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int print_vga(const char *message)
{
  for (int i = 0; message[i] != '\0'; i++)
  {
    uint16_t value = (0x0F << 8) | message[i];
    asm volatile(
        "movw %1, %%gs:(%0)"
        :
        : "r"(i * 2), "r"(value)
        : "memory");
  }

  return 0;
}

int print(const char *fmt)
{
  putstr(fmt);
  return 0;
}

int printf(const char *fmt, ...)
{
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap)
{
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...)
{
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...)
{
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap)
{
  panic("Not implemented");
}

#endif
