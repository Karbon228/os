bits 32
section .text
    ; multiboot
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

global main
extern initPIC
extern initIDT
extern clear

; Главная функция
main:
    cli
    mov esp, stack
    call clear
    call initPIC
    call initIDT
    halt:
        hlt
    jmp halt

section .bss
resb 8192
stack: