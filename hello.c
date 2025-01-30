#include <am.h>
#include <klib.h>

int main() {
    print_vga("Hello, World! This text is showing on VCG window.");
    print("Hello, World! This text is showing on serial console.\n");
    while(1);
    return 0;
}
