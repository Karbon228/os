bits 32
section .text
global HandlerCallerKB
extern HandlerKB

; Функция для вызова драйвера клавиатуры
HandlerCallerKB:
    call HandlerKB
    iretd