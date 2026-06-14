; rutinas.nasm

bits 64
default rel

global contarCaracterMapa
global validarMovimiento
global calcularPuntaje
global detectarObjeto
global contarCeldasLibres

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

; int validarMovimiento(char *mapa, int columnas, int fila, int columna)
; rcx = mapa
; rdx = columnas
; r8 = fila
; r9 = columna
; rax = 1 valido, 0 bloqueado
validarMovimiento:
    ; Calcula la posicion lineal dentro del mapa.
    ; Formula usada:
    ; indice = fila * columnas + columna
    mov  rax, r8

    imul rax, rdx ; multiplica la fila por el numero de columnas 

    add  rax, r9 ;suma la columna y asi esta en la celda correcta 

    cmp  byte [rcx + rax], '#' ;compara con una pared

    je   .bloqueado ; si es pared pues ya se va

    mov  rax, 1 ; y si no era pared si es valido 
    ret

.bloqueado:
    xor  rax, rax ; regresa un 0 porque esta bloqueado 
    ret