bits 32
section .text:
global readPort
global writePort
global loadIDT

; Чтение данных по порту
readPort:
    mov edx, [esp+4]
    in  al,   dx
    ret

; Передача данных по порту
writePort:
    mov edx, [esp+4]
    mov al,  [esp+8]
    out dx,   al
    ret

; Загрузка IDT
loadIDT:
    mov edx, [esp+4]
    lidt [edx]
    sti
    ret