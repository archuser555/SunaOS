#ifndef EXEC_H
#define EXEC_H

#include "syscall.h"
#include "drivers/memory/mem.h"
#include "strings.h"
#include "drivers/vga.h"
void exec(char *input) {
    if (strcmp(input, "reboot") == 0) {
        puts("reboot exec, See You Later, DOG!\n");
        reboot();
    }
    puts("Unknown command: ");
    puts(input);
    puts("\n> ");
}
#endif
