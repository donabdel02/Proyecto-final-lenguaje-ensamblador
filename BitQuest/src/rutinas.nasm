; rutinas.nasm

bits 64
default rel

global contarCaracterMapa

section .text

;int contarCaracterMapa(char *mapa, int totalCeldas, char caracterBuscado)
; rcx = posicion 
; rdx = candidad de celdas 
; r8b = que tipo de celda se quiere contar 
; rax = cuantas veces aparece lo que se quiere contar 

contarCaracterMapa:
    xor  rax, rax 
    test rdx, rdx ; los compara para ver si esta vacio o no 
    jz   .fin ; si esta vacio pues muere el conteo 

.recorrer:
    cmp  byte [rcx], r8b ; revisa si la celda en posicion es el caracter deseado 
    jne  .siguiente ; si no es se va 
    inc  rax ; si si es aumenta el contador de sis

.siguiente:
    inc  rcx ; avanza a la siguente celda del mapa 
    dec  rdx
    jnz  .recorrer ; repite hasta revisar todas las celdas

.fin:
    ret
