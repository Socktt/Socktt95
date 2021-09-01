#include "system.h"

extern isr0();
extern isr1();

void isrs_install()
{
    idt_set_gate(0, (unsigned)isr0, 8, 0x8e);
    idt_set_gate(1, (unsigned)isr1, 8, 0x8e);
}

unsigned char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
};

void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        
    }
}