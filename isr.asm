global isr0
global isr1

isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

isr1:
    pushad
    mov [0xb8000], byte "I"
    popad
    iret

extern fault_handler

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop es
    pop ds
    popa
    add esp, 8
    iret