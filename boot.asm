[org 0x7c00]

KERNEL_LOCATION equ 0x1000

mov [BOOT_DISK], dl

mov ah, 0
mov al, 3
int 0x10

mov ah, 0
mov al, [BOOT_DISK]
int 0x13

mov ah, 2
mov al, 40
mov ch, 0
mov cl, 2
mov dh, 0
mov dl, [BOOT_DISK]
mov bx, 0
mov es, bx
mov bx, KERNEL_LOCATION

int 0x13
jc diskReadErr

cli

in al, 0x92
or al, 2
out 0x92, al

lgdt [GDT_Descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:start_protected_mode

jmp $

%include "gdt.asm"

diskReadErr:
    mov ah, 0x0e
    mov al, "D"
    int 0x10
    hlt

BOOT_DISK: db 0

[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    jmp KERNEL_LOCATION

times 510-($-$$) db 0
db 0x55, 0xaa