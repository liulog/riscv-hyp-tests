
#include <stdio.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include "uart8250.h"
#include <rvh_test.h>
#include <instructions.h>

// void* memset(void* dest, int byte, size_t len)
// {
//   if ((((uintptr_t)dest | len) & (sizeof(uintptr_t)-1)) == 0) {
//     uintptr_t word = byte & 0xFF;
//     word |= word << 8;
//     word |= word << 16;
//     word |= word << 16 << 16;

//     uintptr_t *d = dest;
//     while ((uintptr_t)d < (uintptr_t)(dest + len))
//       *d++ = word;
//   } else {
//     char *d = dest;
//     while (d < (char*)(dest + len))
//       *d++ = byte;
//   }
//   return dest;
// }

void* memcpy(void* dest, const void* src, size_t len)
{
  if ((((uintptr_t)dest | (uintptr_t)src | len) & (sizeof(uintptr_t)-1)) == 0) {
    const uintptr_t* s = src;
    uintptr_t *d = dest;
    while (d < (uintptr_t*)(dest + len))
      *d++ = *s++;
  } else {
    const char* s = src;
    char *d = dest;
    while (d < (char*)(dest + len))
      *d++ = *s++;
  }
  return dest;
}

int _read(int file, char *ptr, int len)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        ptr[i] = uart8250_getc();
    }

    return len;
}

int _write(int file, char *ptr, int len)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        if (ptr[i] == '\n')
        {
            uart8250_putc('\r');
        }
        uart8250_putc(ptr[i]);
    }

    return len;
}

int _lseek(int file, int ptr, int dir)
{
    //errno = ESPIPE;
    return -1;
}

int _close(int file)
{
    return -1;
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int fd)
{
    //errno = ENOTTY;
    return 0;
}

void* _sbrk(int increment)
{
    extern char _end; // From linker script
    static char* heap_end = &_end;

    char* current_heap_end = heap_end;
    heap_end += increment;

    return current_heap_end;
}

void _exit(int return_value)
{
    asm ("fence rw, rw" ::: "memory");
    while (1)
    {
        asm ("wfi" ::: "memory");
    }
}

int _getpid(void)
{
  return 1;
}

int _kill(int pid, int sig)
{
    //errno = EINVAL;
    return -1;
}

// // PMP 配置字段
// #define PMP_R (1 << 0)  // 允许读
// #define PMP_W (1 << 1)  // 允许写
// #define PMP_X (1 << 2)  // 允许执行
// #define PMP_L (1 << 7)  // 锁定配置，防止修改

// // PMP 匹配模式
// #define PMP_TOR   (1 << 3)   // Top of Range
// #define PMP_NA4   0x1   // 4-byte granularity
// #define PMP_NAPOT 0x3   // Naturally aligned power of two

// // 定义要保护的内存区域
// #define START_ADDR 0x00000000310b0000  // 起始地址
// #define END_ADDR   0x00000000310b1000  // 结束地址（TOP of range）

void _init(){
    // CSRW(mie, 0ULL);
    // CSRW(mtvec, 0x20);
//   // 设置 PMP 区域的权限和范围
//     uint64_t pmpcfg = (PMP_R | PMP_W | PMP_X | PMP_TOR);  // 配置为 TOR 模式，RWX 权限

//     // 1. 设置 PMPADDR1 为结束地址（END_ADDR >> 2，因为 PMPADDR 使用物理地址的高位）
//     CSRW(pmpaddr1, END_ADDR >> 2);

//     // 2. 设置 PMPADDR0 为起始地址（START_ADDR >> 2），通过 TOR 模式定义范围
//     CSRW(pmpaddr0, START_ADDR >> 2);

//     // 3. 配置 PMP 权限和模式到 PMPCFG0
//     uint64_t cfg = CSRR(pmpcfg0);
//     cfg &= ~0xFF;  // 清除当前条目
//     cfg |= pmpcfg; // 设置新的配置
//     CSRW(pmpcfg0, cfg);

//     // 确保配置生效
//     asm volatile("fence.i");

    // (*((volatile uint32_t*)0x310b0004) = 0);
    // (*((volatile uint32_t*)0x310b000c) = 0x80);
    // (*((volatile uint32_t*)0x310b0000) = 0x00);

    uart8250_init(VIRT_UART16550_ADDR, VIRT_UART_SHIFTREG_ADDR,
                VIRT_UART_BAUDRATE, 2, 4);
}