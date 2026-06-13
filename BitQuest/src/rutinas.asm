; rutinas.asm
; BitQuest - Funciones de audio en NASM 64 bits

bits 64
default rel

global reproducirSonidoMoneda
global reproducirSonidoPuerta
global reproducirSonidoVictoria

extern Beep

section .text

; void reproducirSonidoMoneda()
; Beep agudo corto al recoger moneda
reproducirSonidoMoneda:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32        ; shadow space Win64
    mov  rcx, 1000      ; frecuencia 1000 Hz
    mov  rdx, 80        ; duracion 80 ms
    call Beep
    add  rsp, 32
    pop  rbp
    ret

; void reproducirSonidoPuerta()
; Beep grave al abrir puerta
reproducirSonidoPuerta:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov  rcx, 400       ; frecuencia 400 Hz
    mov  rdx, 150       ; duracion 150 ms
    call Beep
    add  rsp, 32
    pop  rbp
    ret

; void reproducirSonidoVictoria()
; Melodia Do-Mi-Sol al completar nivel
reproducirSonidoVictoria:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov  rcx, 523       ; Do
    mov  rdx, 150
    call Beep
    mov  rcx, 659       ; Mi
    mov  rdx, 150
    call Beep
    mov  rcx, 784       ; Sol
    mov  rdx, 300
    call Beep
    add  rsp, 32
    pop  rbp
    ret
