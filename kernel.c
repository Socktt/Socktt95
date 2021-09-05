#include "idt.h"
#include "vga.h"
#include "system.h"
#include "mouse.h"
#include "gui.h"

extern void kernMain(){
    idt_install();
    irq_install();
    //timer_install();
    //keyboard_install();
    mouse_install();
    __asm__ __volatile__ ("sti"); 
    //enable_cursor(0, 15);

    //Print("Joe mama");

    for(;;)
    {
        ProcessMousePacket();
    }
    return;
}