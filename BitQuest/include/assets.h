// define los caracteres visuales para cada elemento del juego, usando ASCII art para darle un estilo más bonito

#ifndef ASSETS_H
#define ASSETS_H

// para la matriz 
#define CHAR_PARED   '#'
#define CHAR_LIBRE   '.'
#define CHAR_JUGADOR 'P'
#define CHAR_MONEDA  'M'
#define CHAR_LLAVE   'K'
#define CHAR_PUERTA  'D'
#define CHAR_SALIDA  'E'

//con ASCII para el punto extra y para que se vea más bonito el juego, aunque no es necesario para el funcionamiento del mismo
#define VISUAL_PARED   "##"
#define VISUAL_LIBRE   "  "
#define VISUAL_JUGADOR "/\"
#define VISUAL_MONEDA  "o "
#define VISUAL_LLAVE   "! "
#define VISUAL_PUERTA  "[]"
#define VISUAL_SALIDA  "><"

#endif // ASSETS_H
