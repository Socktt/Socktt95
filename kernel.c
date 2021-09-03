#include "idt.h"
#include "vga.h"
#include "system.h"
#include "mouse.h"

extern void kernMain(){
    idt_install();
    irq_install();
    //timer_install();
    //keyboard_install();
    mouse_install();
    __asm__ __volatile__ ("sti"); 

    for(;;)
    {
        ProcessMousePacket();
    }
    return;
}