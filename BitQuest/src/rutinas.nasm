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

; int calcularPuntaje(int monedas, int pasos, int nivelesCompletados)

calcularPuntaje:
    mov  rax, rcx ; monedas
    imul rax, 250 ; multiplica las monedas por su valor en puntos

    mov  r10, r8 ; nivelesq
    imul r10, 1000 ; calcula los puntos por nivel completado 

    add  rax, r10 ; suma los puntos de nivel completado al puntaje que habia 

    mov  r10, rdx ;pasos 
    imul r10, 1 ; calcula cuantos puntos quita cada paso 

    sub  rax, r10 ; resta los puntos de los pasos 

    cmp  rax, 0
    jge  .fin_puntaje ; verificacion si el puntaje es positivo 

    xor  rax, rax ; si es negativo se queda en 0

.fin_puntaje:
    ret


; int detectarObjeto(char *mapa, int columnas, int fila, int columna, char objeto)
detectarObjeto:
    mov  rax, r8 ; fila 

    imul rax, rdx ; multiplica la fila por el num de columnas

    add  rax, r9 ; columna 

    mov  r10b, byte [rsp + 40] ; obtiene el parametro del objeto 

    cmp  byte [rcx + rax], r10b ; compara la celda con el objeto 

    je   .encontrado ; si son iguales lo logro 

    xor  rax, rax ; si no pues rip y manda 0
    ret

.encontrado:
    mov  rax, 1 ; 1 de positivo 
    ret


; int contarCeldasLibres(char *mapa, int totalCeldas)
contarCeldasLibres:
    xor  rax, rax ; cantidad de .

    test rdx, rdx ; verificacion para el total de celdas si es igual a 0 
    jz   .fin_libres ; si es 0 esta vacia y salta 

.recorrer_libres:
    cmp  byte [rcx], '.' ; compara la celda actual con . que es para camino libre 

    jne  .siguiente_libre ; si no es libre el contador no aumenta 

    inc  rax ; el contador aumenta si esta libre 

.siguiente_libre:
    inc  rcx ; va a la siguente celda en el mapa 

    dec  rdx ; decrementan las celdas por revisar 

    jnz  .recorrer_libres ; para repetir si aun faltan 

.fin_libres:
    ret