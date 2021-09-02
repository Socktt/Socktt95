#include "idt.h"
#include "vga.h"
#include "system.h"

extern void kernMain(){
    idt_install();
    irq_install();
    //timer_install();
    keyboard_install();
    __asm__ __volatile__ ("sti"); 
    Print("test\n");
    return;
}