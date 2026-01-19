import random
import sys


# leer_tablero_y_color(str) -> list char[8][8] , char 

# leer tablero recibe la ruta del archivo generado en C
#  y retorna el tablero actual como el color actual
def leer_tablero_y_color(ruta_archivo):
    tablero = []
    color = ""
    with open(ruta_archivo, "r") as f: 
        # abrimos el archivo con with open para que se cierre automaticamente
        linea = f.readline() # leemos la primera linea 
        while linea!="": # entramos en un bulce hasta recorrer todo el archivo
            # las verificaciones de formato no deberian de ser necesarias si el archivo fue generado por el programa en C
            linea = linea.strip() # limpiamos el str
            if len(linea) == 1:  # si el largo del string es igual a uno entonces debe de ser el color 
                if len(tablero) != 8:
                    # Si encontramos una letra suelta 
                    # pero no tenemos 8 filas aun, significa que el archivo esta mal.
                    raise ValueError(f"Archivo con formato incorrecto. Se encontró el color '{linea}' pero el tablero solo tiene {len(tablero)} filas ")  
                if linea not in ["N", "B"]:
                    raise ValueError(f"Color inválido: '{linea}'. Debe ser 'N' o 'B'.")
                color = linea 
                break
            else: #  es parte del tablero
                if len(linea) != 8:
                    raise ValueError(f"Formato de fila incorrecto. Longitud: {len(linea)}. Se esperaban 8.")
                for char in linea:
                    if char not in ['X', 'N', 'B']:
                        raise ValueError(f"Carácter desconocido en el tablero: '{char}' ")
                tablero.append(list(linea))
            linea = f.readline() #leemos la siguiente linea 
    if color == "":
        raise ValueError("El archivo terminó sin encontrar el indicador de color o el formato es incorrecto.")
    return tablero, color


#imprimir_tablero(list char[8][8]) -> void

def imprimir_tablero(tablero): 
    print("  0 1 2 3 4 5 6 7") # imprimimos las cordenadas 
    for i, fila in enumerate(tablero): # usamos enumerate para obtener tambien el numero de fila 
        print(i, " ".join(fila)) # imprimos el numero junto a la fila 
 
#cambios_de_jugada(list char[8][8],char , int , int) -> list[(int,int)]
# funcion identica a la programada en C 
def cambios_de_jugada(tablero, color, fila, col):

    if tablero[fila][col] != "X": # si la posicion elegida esta ocupada 
        return [] # retorna una lista sin cambios 
    
    rival = "B" if color == "N" else "N" # guardadamos el color contrario al del mov9imiento
    cambios = [] # lista para almacenar los cambios validos
    direcciones = [
        (0, 1), (1, 0), (0, -1), (-1, 0), # horizontales y verticales
        (1, 1), (-1, -1), (1, -1), (-1, 1) # diagonales
    ]

    for df, dc in direcciones: # por cada tupla (direccion)
        #avanzamos en la direccion actual
        f = fila + df 
        c = col + dc
        camino = [] # lista para guardar las posiciones por las cuales avanzamos 

        while 0 <= f < 8 and 0 <= c < 8 and tablero[f][c] == rival:
            #si la posicion esta dentro del tablero y es del rival seguimos avanzando
            camino.append((f, c)) # vamos guardando las posiciones 
            f += df
            c += dc

        if 0 <= f < 8 and 0 <= c < 8 and tablero[f][c] == color and camino != []:
            # verificamos que salimos del bucle por encontrar nuestro color y no por otra cosa
            cambios.extend(camino) # a;adismos todos los elementos de este camino a la lista de cambios pues este camino realizo cambios  validos

    if len(cambios)>0: # si luego de recorrer todos los caminos se genero aunque sea un cambio la posicion jugada tambien es valida y se agrega a cambios 
        cambios.append((fila, col))

    return cambios # retornamos los cambios 

#obtener_movimientos_validos(list char[8][8] , char ) -> list[(int,int,[(int,int)])]
# genera una lista de los movimeitnos validos para un color en un tablero 
def obtener_movimientos_validos(tablero, color):
    movimientos = []
    ## recorre el tablero 
    for fila in range(8):
        for col in range(8):
            cambios = cambios_de_jugada(tablero, color, fila, col)
            ## si la posicion genera cambios 
            if len(cambios)>0:
                movimientos.append((fila, col, cambios)) ## guarda la posicion y los cambios 

    return movimientos

#elegir_movimiento(list[(int,int,[(int,int)])],int)-> (int,int,[(int,int)])
# esta funcion son los 2 niveles del programa 

def elegir_movimiento(movimientos, nivel):
    #nivel 0
    if nivel == 0: # para el nivel cero elige aleatoriamente uno de los movimientos validos actuales 
        return random.choice(movimientos)

    elif nivel == 1: # para el nivel uno buscamos el que genere mas cambios 
        mejor_movimiento = movimientos[0] 
        max_capturas = len(mejor_movimiento[2])
        # asumimos que el primero es el que genera mas cambios 
        for mov in movimientos: # recorremos toda la lista 
            capturas = len(mov[2]) # vemos cuantos cambios genera 

            if capturas > max_capturas: # si genera mas cambios lo reemplzamaos 
                max_capturas = capturas
                mejor_movimiento = mov
            
        return mejor_movimiento


#aplicar_jugada(list char[8][8] , list[(int,int)] , char )
def aplicar_jugada(tablero, cambios, color):
    for fila, col in cambios: # recorre la lista de cambios (fila , col)
        tablero[fila][col] = color # cambia el valor de la posicion por el color que realizo la jugada 

#contar_fichas(list char[8][8] ) -> int,int

def contar_fichas(tablero):
    negras = 0
    blancas = 0
    # recorre todo el tablero y cuenta las fichas 
    for fila in tablero:
        for celda in fila:
            if celda == "N":
                negras += 1
            elif celda == "B":
                blancas += 1

    return negras, blancas

# mostrar_resultado(list char[8][8])
# muestra quien es el ganador 
def mostrar_resultado(tablero):
    negras, blancas = contar_fichas(tablero)

    print("\nResultado final:")
    print("Negras:", negras)
    print("Blancas:", blancas)

    if negras > blancas:
        print("Ganador: Negras (N)")
    elif blancas > negras:
        print("Ganador: Blancas (B)")
    else:
        print("Empate")


#la funcion jugar es la encargada de gestionar los turnos y el flujo de juego

def jugar(tablero, color_inicial, color_jugador, nivel):
    turno = color_inicial # color actual

    print("\nTablero actual:")
    imprimir_tablero(tablero)


    while True: # bucle de juego 
        print("Turno: ", turno)
        
        movimientos = obtener_movimientos_validos(tablero, turno) # verificamos que el color aca tenga movimientos posibles 

        if len(movimientos) == 0: # si no posee movimientos verificamos que el contrincate si posea 
            
            otro = "B" if turno == "N" else "N"
            movimientos = obtener_movimientos_validos(tablero, otro)
            if len( movimientos) == 0: #si tampoco tiene la partida termino.
                print("\nFin de la partida.")
                break
            else: # en caso contrario se pasa de turno
                print("No hay movimientos posibles, se pasa el turno.")
                turno = otro
                continue
            # si hay jugadas validas y es turno del jugador 
        if turno == color_jugador:
            while True: # entramos en un bucle 
                try:
                    entrada = input("Ingrese fila y columna (ej: 3 4): ") # pedimos la entrada 
                    fila, col = map(int, entrada.split())
                    movimiento_elegido = () 
                    # definimos una variable vacia para guardar el movimiento en caso de que sea valido 

                    if not (0 <= fila < 8 and 0 <= col < 8): # verificamos que este dentro del tablero 
                        print("fuera del tablero \n")
                        continue

                    for mov in movimientos: 
                        # verificamos que este dentro de la lista de jugadas validas 
                        if mov[0] == fila and mov[1] == col:
                            movimiento_elegido = mov # si es asi lo guardamos 
                            break


                    if movimiento_elegido != ():
                        # si esta dentro de la lista aplicamos los cambios y mostramos el tablero
                        aplicar_jugada(tablero, movimiento_elegido[2], turno)
                        imprimir_tablero(tablero)
                        break # cerramos el bucle 
                    else: # si la jugda no esta dentro de la lista repetimos el bucle 
                        print("Movimiento inválido.")
                except:
                    print("Entrada inválida.")
        
        else: # en caso de que haya movimientos validos y sea turno del programa 
            mov = elegir_movimiento(movimientos, nivel) # llamamos a la funcion y le pasamos el nivel 
            fila, col, cambios = mov # abrimos la tupla 
            print(f"IA juega en ({fila},{col})") # mostramos que movimiento juea 
            aplicar_jugada(tablero, cambios, turno) # aplicamos los cambios 
            imprimir_tablero(tablero) # mostramos el tablero 


        # cambiar turno
        turno = "B" if turno == "N" else "N"

    # si salimos del bucle es porque la partida termino
    print("La partida termino.")
    mostrar_resultado(tablero) # mostramos al ganador 
        

def main():
    # verificamos que sea la cantidad necesaria de argumentos 
    if len(sys.argv) != 4:
        print("Uso: python othello.py <archivo> <color> <nivel>")
        print("Ejemplo: python othello.py partida.txt N 1")
        return
    # guardamos los argumentos 
    archivo = sys.argv[1] 
    color_jugador = sys.argv[2].upper()

    # verificamos que los argumentos pasados sean correctos 
    try:
        nivel = int(sys.argv[3])
    except ValueError:
        print("Error: el nivel debe ser un número entero (0 o 1).")
        return

    if color_jugador not in ["N", "B"]:
        print("Error: El color debe ser 'N' (Negro) o 'B' (Blanco).")
        return

    if nivel not in [0, 1]:
        print("Error: El nivel debe ser un número entero: 0  o 1 .")
        return
    # tratamos de leer el color y el tablero 
    try:
        tablero, color_inicial = leer_tablero_y_color(archivo)
    except FileNotFoundError:
        print("Error: No se pudo abrir el archivo:", archivo)
        return
    except Exception as e:
        print("Error al leer el archivo:", e)
        return
    # llamamos a la funcion principal para jugar 
    jugar(tablero, color_inicial, color_jugador, nivel)


if __name__ == "__main__":
    main()
