; ============================================================
; rutinas.asm - Funciones obligatorias en NASM de 64 bits
; BitQuest: Explorador de Matrices con C y NASM
;
; Convencion de llamadas System V AMD64 (Linux/macOS):
;   Parametros enteros: rdi, rsi, rdx, rcx, r8, r9
;   Valor de retorno  : rax
;   Registros que el llamado DEBE preservar: rbx, rbp, r12-r15
;
; Nota para Windows (x64 ABI):
;   Si se compila en Windows, cambiar parametros a:
;   rcx, rdx, r8, r9 (primeros cuatro enteros/punteros)
;   y reservar 32 bytes de shadow space en el prologo.
;   Las funciones estan escritas con la convencion Linux/macOS.
;   Para portar a Windows, ver comentarios en cada funcion.
; ============================================================

section .text

; ============================================================
; Funcion 1: contar_caracter
;
; Descripcion:
;   Recorre la matriz (interpretada como arreglo lineal) y
;   cuenta cuantas veces aparece el caracter indicado.
;
; Prototipo C:
;   long contar_caracter(char *mapa, long total_celdas, char caracter);
;
; Parametros (Linux/macOS):
;   rdi = puntero al inicio del mapa
;   rsi = total de celdas (filas * columnas)
;   rdx = caracter a buscar (byte)
;
; Retorno:
;   rax = numero de veces que aparece el caracter
; ============================================================
global contar_caracter
contar_caracter:
    ; Inicializar contador en cero
    xor     rax, rax        ; rax = 0 (contador de coincidencias)
    xor     rcx, rcx        ; rcx = 0 (indice del ciclo)

    ; Si total_celdas == 0, salir inmediatamente
    test    rsi, rsi
    jz      .fin_contar

.ciclo_contar:
    ; Comparar celda actual con el caracter buscado
    movzx   r8d, byte [rdi + rcx]   ; Cargar byte en r8 (zero-extend)
    cmp     r8b, dl                  ; Comparar con caracter buscado (dl = byte bajo de rdx)
    jne     .siguiente_celda         ; Si no coincide, ir al siguiente

    inc     rax                      ; Coincidencia: incrementar contador

.siguiente_celda:
    inc     rcx                      ; Avanzar al siguiente indice
    cmp     rcx, rsi                 ; Ver si llegamos al final
    jl      .ciclo_contar            ; Si no, continuar el ciclo

.fin_contar:
    ret                              ; rax contiene el resultado


; ============================================================
; Funcion 2: validar_movimiento
;
; Descripcion:
;   Determina si una posicion (fila, col) del mapa puede ser
;   ocupada por el jugador. Retorna 1 si es valido, 0 si no.
;   Un movimiento NO es valido si la celda es una pared '#'.
;
; Prototipo C:
;   long validar_movimiento(char *mapa, long cols,
;                           long nueva_fila, long nueva_col);
;
; Parametros (Linux/macOS):
;   rdi = puntero al inicio del mapa
;   rsi = numero de columnas del mapa
;   rdx = nueva fila propuesta
;   rcx = nueva columna propuesta
;
; Retorno:
;   rax = 1 si el movimiento es valido, 0 si esta bloqueado
; ============================================================
global validar_movimiento
validar_movimiento:
    ; Calcular indice lineal: indice = fila * cols + col
    mov     rax, rdx        ; rax = nueva_fila
    imul    rax, rsi        ; rax = nueva_fila * cols
    add     rax, rcx        ; rax = nueva_fila * cols + nueva_col

    ; Cargar el caracter en esa posicion del mapa
    movzx   r8d, byte [rdi + rax]   ; r8 = caracter en la posicion calculada

    ; Verificar si es una pared
    cmp     r8b, '#'
    je      .movimiento_invalido     ; Es pared: retornar 0

    ; No es pared: movimiento valido
    mov     rax, 1
    ret

.movimiento_invalido:
    xor     rax, rax                 ; rax = 0
    ret


; ============================================================
; Funcion 3: calcular_puntaje
;
; Descripcion:
;   Calcula el puntaje final del jugador usando la formula:
;   puntaje = (monedas * 100) - (pasos * 2) + (niveles * 500)
;
;   Cada moneda vale 100 puntos.
;   Cada paso resta 2 puntos (penaliza recorridos largos).
;   Cada nivel completado suma 500 puntos de bonus.
;   El puntaje minimo es 0 (no puede ser negativo).
;
; Prototipo C:
;   long calcular_puntaje(long monedas, long pasos, long niveles);
;
; Parametros (Linux/macOS):
;   rdi = monedas recolectadas
;   rsi = pasos realizados
;   rdx = niveles completados
;
; Retorno:
;   rax = puntaje calculado (>= 0)
; ============================================================
global calcular_puntaje
calcular_puntaje:
    ; Calcular bonus por monedas: monedas * 100
    mov     rax, rdi
    imul    rax, 100                ; rax = monedas * 100

    ; Calcular penalizacion por pasos: pasos * 2
    mov     r8, rsi
    imul    r8, 2                   ; r8 = pasos * 2

    ; Restar penalizacion
    sub     rax, r8                 ; rax = monedas*100 - pasos*2

    ; Calcular bonus por niveles: niveles * 500
    mov     r9, rdx
    imul    r9, 500                 ; r9 = niveles * 500

    ; Sumar bonus de niveles
    add     rax, r9                 ; rax = total

    ; Asegurarse de que el puntaje no sea negativo
    test    rax, rax
    jns     .puntaje_ok             ; Si es positivo o cero, esta bien
    xor     rax, rax                ; Si es negativo, forzar a 0

.puntaje_ok:
    ret


; ============================================================
; Funcion 4: detectar_objeto
;
; Descripcion:
;   Verifica si en la celda (fila, col) del mapa se encuentra
;   el objeto (caracter) indicado. Retorna 1 si lo encuentra,
;   0 si no.
;
; Prototipo C:
;   long detectar_objeto(char *mapa, long cols,
;                        long fila, long col, char objeto);
;
; Parametros (Linux/macOS):
;   rdi = puntero al inicio del mapa
;   rsi = numero de columnas
;   rdx = fila a revisar
;   rcx = columna a revisar
;   r8  = caracter del objeto a buscar (byte)
;
; Retorno:
;   rax = 1 si el objeto esta en la celda, 0 si no
; ============================================================
global detectar_objeto
detectar_objeto:
    ; Calcular indice lineal: indice = fila * cols + col
    mov     rax, rdx        ; rax = fila
    imul    rax, rsi        ; rax = fila * cols
    add     rax, rcx        ; rax = fila * cols + col

    ; Cargar el caracter en esa posicion
    movzx   r9d, byte [rdi + rax]   ; r9 = caracter en la posicion

    ; Comparar con el objeto buscado
    cmp     r9b, r8b                 ; Comparar bytes
    je      .objeto_encontrado

    ; No encontrado: retornar 0
    xor     rax, rax
    ret

.objeto_encontrado:
    mov     rax, 1
    ret


; ============================================================
; Funcion 5: contar_celdas_libres
;
; Descripcion:
;   Recorre el mapa completo (como arreglo lineal) y cuenta
;   cuantas celdas representan camino libre ('.').
;
; Prototipo C:
;   long contar_celdas_libres(char *mapa, long total_celdas);
;
; Parametros (Linux/macOS):
;   rdi = puntero al inicio del mapa
;   rsi = total de celdas (filas * columnas)
;
; Retorno:
;   rax = numero de celdas libres encontradas
; ============================================================
global contar_celdas_libres
contar_celdas_libres:
    xor     rax, rax        ; rax = 0 (contador de celdas libres)
    xor     rcx, rcx        ; rcx = 0 (indice del ciclo)

    ; Si no hay celdas, salir
    test    rsi, rsi
    jz      .fin_libres

.ciclo_libres:
    ; Cargar celda actual
    movzx   r8d, byte [rdi + rcx]

    ; Ver si es camino libre '.'
    cmp     r8b, '.'
    jne     .sig_libre              ; Si no es '.', no contar

    inc     rax                     ; Es libre: incrementar contador

.sig_libre:
    inc     rcx                     ; Siguiente celda
    cmp     rcx, rsi
    jl      .ciclo_libres

.fin_libres:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
