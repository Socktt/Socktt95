#include "idt.h"

extern void kernMain(){
    idt_install();
    *(char*)0xb8000 = 'B';
    *(char*)0xb8002 = 'e';
    *(char*)0xb8004 = 'a';
    *(char*)0xb8006 = 'n';
    int a = 1 / 0;
    *(char*)0xb8002 = 'F';
    return;
}