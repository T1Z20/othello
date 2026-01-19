#include <stdio.h>
#include "othello.h"

// tomar_jugador(str) -> jugador 

// la funcion tomar_jugador inicializa una variable de tipo jugador  y recorre el str esperanzo que el mismo cumpla el formato dado (NOMBRE,COLOR) siendo color un solo char 
// a medida que recorre el str verifica no encontrarse con una coma , ni con un \0 y que el largo del nombre no sea mayor que el definido. 
// Una vez que sale del bucle , se pregunta si no esta sobre una coma , pues si es asi el formato seria incorrecto , por lo tanto se inicializa un jugador "invalido" y lo retorna 
// Si lo anterior es falso entonces el formato debe de ser correcto, le damos un fin al str del nombre y almacenamos el char siguiente a la coma en color.

jugador tomar_jugador(char *renglon) {
    jugador j = {0}; // Limpiamos la memoria
    int i = 0;
    
    while (renglon[i] != ',' && renglon[i] != '\0' && i < MAX_NOMBRE - 1) {
        j.nombre[i] = renglon[i]; // guardamos char a char 
        i++;
    }

    if (renglon[i] != ',') { //Si esto es verdadero entonces el bucle termino pq encontro un \0 o el nombre es demasiado largo 

        j.nombre[0] = '\0';
        j.color = 'X';
        return j;
    }

    j.nombre[i] = '\0'; // le damos fin al string del nombre 

    j.color = renglon[i + 1]; // guardamos la posicion donde deberia estar el color 

    return j;
}

// validar_jugador(jugador)-> int (0/1)
//La funcion validar_jugador hace las verificaciones para saber si el jugador resultante de tomar jugador es valido y se cumple el formato.

int validar_jugador(jugador j){

    if (j.nombre[0] == '\0') { // verifica que no este vacio 
        return 0;
    }

    if (j.color != 'B' && j.color != 'N') { // verifica que el color sea valido 
        return 0;
    }

    return 1;

}

//tomar_jugada(str)-> posicion
//la funcion tomar jugada recibe un str asumiendo que el formato es el correcto , primero inicializa las posiciones en valores invalidos y luego 
// se pregunta si la celda del str esta dentro del rango de juego
// en caso de no estarlo devuelve la posicion invalida 
// En caso de estarlo aplica aritmética de caracteres

posicion tomar_jugada(char *renglon){
    posicion pos ;
    pos.fila = -1;
    pos.col = -1;
    char letra = renglon[0];
    char numero = renglon[1];
    if (letra >= 'A' && letra <= 'H') {
        pos.col = letra - 'A';
    }
    if (numero >= '1' && numero <= '8') {
        pos.fila = numero - '1'; 
    }

    return pos;
}


//validar_jugada(posicion)->int(0/1)
//la funcion validar_jugada verifica que la salida de tomar_jugada no sean los valores invalidos 

int validar_jugada(posicion jugada){
    if (jugada.col != -1 && jugada.fila != -1)
    {
        return 1;
    }
    return 0;
}

//tomar_color_inicial(str)-> char
// Recibe el renglon donde se encuentra el color y lo retorna 

char tomar_color_inicial( char *renglon){
    char color=renglon[0];
    return color;
}

//valdiar_color_inicial(char)-> int (0/1)
//verifica que el color tomado por color inicial sea valido 

int valdiar_color_inicial(char color){

if (color != 'B' && color != 'N')
{
    return 0;
}

return 1;
        

}

//cargar_encabezado(FILE* , jugador* , jugador*  , char*) -> int (0/1)

//La funcion cargar_encabezado recibe las direcciones donde se almacenan los datos de jugador1 , jugador2 , el color inicial y el archivo de entrada. 
// Donde los 3 primeros renglones son los datos de jugador1 , jugador2 y el color inicial en ese orden dado . 
// por cada uno se pregunta si la lectura fue exitosa y en caso de serlo almacena los valores en sus lugares correspondientes .
// Si fue capaz de leer todos retorna 1 , esto no significa que los datos sean validos. 

int cargar_encabezado(FILE *archivo, jugador *j1, jugador *j2, char *turno_inicial) {
    char buffer[MAX_NOMBRE + 5];

    //  jugador 1
    if (fgets(buffer, MAX_NOMBRE + 5, archivo) == NULL) return 0;
    *j1 = tomar_jugador(buffer); 

    //  jugador 2
    if (fgets(buffer, MAX_NOMBRE + 5, archivo) == NULL) return 0;
    *j2 = tomar_jugador(buffer);

    //  color inicial
    if (fgets(buffer, MAX_NOMBRE + 5, archivo) == NULL) return 0;
    *turno_inicial = tomar_color_inicial(buffer);

    return 1; // Ninguna lectura presento problemas , mas no significa que los datos sean validos .
}

//validar_encabezado(jugador,jugador,char) -> int (0/1)

// validar_encabezado usa las funciones anteriores de validacion para corroborar que los datos sean validos 

int validar_encabezado(jugador j1, jugador j2, char turno_inicial) {
    
    // validar estructura  de cada jugador
    if (validar_jugador(j1) == 0) return 0;
    if (validar_jugador(j2) == 0) return 0;

    // verificar que los colores no sean iguales 
    if (j1.color == j2.color) {
        return 0; // Error: Ambos jugadores eligieron el mismo color
    }

    // validar que el turno inicial 
    if (valdiar_color_inicial(turno_inicial) == 0) return 0;

    return 1; // nignun problema.
}

//inicializar_tablero(char *) -> void

//la funcion inicializar_tablero recibe la direccion del tablero y inicializa todos los valores del mismo como el tablero inicial del othello

void inicializar_tablero(char tablero[8][8]){

for(int f=0; f<8; f++) // recorre  fila
        for(int c=0; c<8; c++) // recorre columna
            tablero[f][c] = 'X'; // inicializa el valor en "X"

    // posiciones iniciales del othello 

tablero[3][3] = 'N'; 
tablero[4][4] = 'N'; 
tablero[3][4] = 'B'; 
tablero[4][3] = 'B'; 


}


//coordenada_en_rango(int,int)-> int (0/1)
// verifica que una posicion este dentro del tablero

int coordenada_en_rango(int fila, int col) {
    return (fila >= 0 && fila < 8 && col >= 0 && col < 8);
}

//obtener_cambios(char*,posicion,char,lista_de_cambios *) -> void

//la funcion obtener_cambios , usa el puntero de  una structura para almacenar los cambios generados por una jugada junto a la cantidad de los mismos , 
// lo primero que hace es inicializar la cantidad en cero
// Luego verifica que la posicion de la jugada no este ocupada. en caso de estarlo retorna void
// En caso contrario pensamos las verificaciones necesarias como 8 dirrecciones posibles.
// verificamos cada una
// si una direccion es valida almacenamos los cambios en la lista de cambios y aumentamos el contador
// asi con las 8 direcciones 


void obtener_cambios(char tablero[8][8] , posicion jugada , char color_jugador , lista_de_cambios *cambios) {
    cambios->cantidad = 0; // ponemos el contador de cambios en cero
    
    if (tablero[jugada.fila][jugada.col] != 'X') return ; // Si la casilla no esta vacia retorna void , como el contador es cero la jugada no realizo cambios y es invalida

    char oponente = (color_jugador == 'B') ? 'N' : 'B'; // almacenamos el color del oponente para hacer las verificaciones de direcciones. 

    int direcciones[8][2] = {{-1, -1}, {-1,  0}, {-1,  1},{ 0, -1}, { 0,  1},{ 1, -1}, { 1,  0}, { 1,  1}};
    // las 8 direcciones posibles son las siguientes : 

    // {-1, -1} : diagonal arriba - izquierda 
    // {-1,  0} : vertical arriba 
    // {-1,  1} : diagonal arriba - derecha 
    // { 0, -1} : horizontal izquierda 
    // { 0,  1} : horizontal derecha 
    // { 1, -1} : diagonal abajo - izquierda 
    // { 1,  0} : vertical abajo 
    // { 1,  1} : diagonal abajo - derecha 


    for (int i = 0; i < 8; i++) 
    {   // por cada direccion guardamos hacia donde nos "moveremos"
        int movimiento_fila = direcciones[i][0];
        int movimiento_columna = direcciones[i][1];
        // hacemos el primer movimiento en X direccion 
        int fila_actual = jugada.fila + movimiento_fila;
        int col_actual = jugada.col + movimiento_columna;
        posicion lista_de_fichas[8]; // usamos un array de posiciones de largo 8 para guardar temporalmente los cambios realizados en una direccion 
        int contador_temporal = 0; // usamos un int temporal para contar cuantos cambios se realizaron en esa direccion y poder acceder al mismo

        while (coordenada_en_rango(fila_actual, col_actual) && 
               tablero[fila_actual][col_actual] == oponente) { 
            // nos preguntamos si la posicion luego del movimiento esta dentro del tablero y si la misma esta ocupada por una ficha del oponente

            // En caso de cumplir guardamos la posicion en la lista temporal y aumentamos el contador en 1 
            lista_de_fichas[contador_temporal].fila = fila_actual;
            lista_de_fichas[contador_temporal].col = col_actual;
            contador_temporal++;

            // volvemos a movernos 
            fila_actual = fila_actual + movimiento_fila;
            col_actual = col_actual + movimiento_columna;
        }
        // Una vez salimos del bucle  , debemos verificar si no nos salimos del tablero , encontramos una ficha de nuestro color y si se realizo al menos un cambio
        if (coordenada_en_rango(fila_actual, col_actual) && 
            tablero[fila_actual][col_actual] == color_jugador && 
            contador_temporal > 0){

                // En caso de ser asi entonces la direccion realizo cambios validos y podemos pasar los mismos a la lista de cambios .
                for (int k = 0; k < contador_temporal; k++) {
                cambios->cambios[cambios->cantidad] = lista_de_fichas[k];
                cambios->cantidad++; // aumentamos el contador de cambios de la estructura segun cuantos cambios realizo esta direccion
            }
        }           // repetimos esto para todas las direcciones .
    }
}

//validar_cambios(lista_de_cambios,char,jugador,jugador) -> int (0/1)
// validar_cambios verifica que la jugada haya realizado al menos un cambio , en caso de no ser asi la misma retorna cero y printea el jugador que se equivoco.

int validar_cambios(lista_de_cambios cambios, char turno_actual , jugador j1 , jugador j2 ){

    if (cambios.cantidad == 0) {
            char *nombre = (turno_actual == j1.color) ? j1.nombre : j2.nombre;
            
            printf("la jugada de %s  , es incorrecta \n",  nombre); 
            
            return 0; 
        }
        return 1;


}

//aplicar_jugada(char* , posicion , lista_de_cambios , char) -> void

// la funcion aplicar_cambios recibe el talbero , la jugada actual , la lista de cambios de la misma , y el color del jugador 
// esta reemplazada todas las posiciones guardadas en cambios por el color del jugador y tambien agrega la ficha de la jugada misma.  

void aplicar_jugada(char tablero[8][8], posicion jugada, lista_de_cambios cambios, char color) {
    
    tablero[jugada.fila][jugada.col] = color;

    for (int i = 0; i < cambios.cantidad; i++) {
        int f = cambios.cambios[i].fila;
        int c = cambios.cambios[i].col;
        tablero[f][c] = color;
    }
}

// mostrartablero(char*) -> void

// recorre el tablero y imprime el mismo

void mostrartablero(char tablero[8][8]){
    printf("\n");
    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            printf("%c ", tablero[f][c]); 
        }
        printf("\n");
    }
    printf("\n");
}


// tiene_movimientos_validos (char* , color) -> int(0/1)

// la funcion tiene_movimientos_validos verifica que un color no posee movimientos
// en caso de encontrar al menos una casilla con movimientos posibles retorna 1 , en caso contrario retorna 0

int tiene_movimientos_validos(char tablero[8][8], char color) {
    lista_de_cambios cambios_simulados;
    posicion pos_simulada;

    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            // recorre todo el tablero
            if (tablero[f][c] == 'X') { // si la casilla esta vacia 
                pos_simulada.fila = f;
                pos_simulada.col = c;

                //verifica que la misma realice cambios 
                obtener_cambios(tablero, pos_simulada, color, &cambios_simulados);

                // en caso de ser una casilla valida  el jugador tiene movimientos posibles 
                if (cambios_simulados.cantidad > 0) {
                    return 1; 
                }
            }
        }
    }
    return 0; // recorre todo el tablero y no encuentra movimeintos posibles. 
}

//buffer_a_mayusculas(char*) -> void

// recibe la direccion de un str y pasa todas sus letras a mayusculas 

void buffer_a_mayusculas(char *buffer) {
    int i = 0;
    while (buffer[i] != '\0') {
 
        if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            buffer[i] = buffer[i] - 32; // aritmética de caracteres
        }

        i++;
    }
}

//procesar_movimientos(file* , char* , char, jugador,jugador , char*)->int(0/1)

// procesar_movimientos recibe el archivo (la parte de las jugadas) y verifica que todas sean validas usando gran parte de las funciones anteriores.
// en caso de encontrar una jugada invalida retorna cero
// si todas las jugadas son validas retorna 1 

int procesar_movimientos(FILE *archivo ,char tablero[8][8] , char turno_inicial, jugador j1 ,jugador j2 ,char *turno_final){
    char buffer[10]; //veriable para almacenar los renglones 
    char turno_actual = turno_inicial; // guardamos el turno actual para estar cambiandolo 

    while (fgets(buffer, 10, archivo) != NULL) { // bucle para recorrer el archivo 
        
    buffer_a_mayusculas(buffer); // Pasamos la variable usada para almacenar las jugadas a mayusculas en caso de no estarlo

    if (buffer[0] == '\n') { // Si el la variable es una salto de lineal entonces verificamos que el jugador no posea movimientos validos 
        if (tiene_movimientos_validos(tablero,turno_actual) == 1)
        {  //Si el jugador salto de turno pero posee movimientos es una jugada invalida  
            char *nombre = (turno_actual == j1.color) ? j1.nombre : j2.nombre;
            printf("El jugador : %s , hizo un salto de turno incorrecto. \n" , nombre);
            return 0; // retornamos cero 
        }
        
        turno_actual = (turno_actual == 'B') ? 'N' : 'B'; // cambiamos de turno 
        continue; 
    }
    posicion pos = tomar_jugada(buffer); // pasamos la jugada de char a int int 
    if (validar_jugada(pos) == 0){ // verificamos si la tomar_jugada no retorno -1 -1 
        printf("La jugada de %s es incorrecta\n",
           (turno_actual == j1.color) ? j1.nombre : j2.nombre);
        mostrartablero(tablero); // mostramos el tablero
        return 0; // retornamos cero 
    }
    
    lista_de_cambios cambios ; // variable para almacenar los cambios de cada jugada 
    obtener_cambios(tablero, pos, turno_actual, &cambios); // buscamos que cambios hace la jugada actua; 

    if (validar_cambios(cambios , turno_actual, j1 , j2 ) == 0) { // si la misma no es valida 
            printf("La jugada erronea es %s \n" , buffer  );
            mostrartablero(tablero); // mostramos el tablero
            return 0;  // retornamos cero 
    }else {// En caso contrario aplicamos los cambios y cambiamos de jugador 
        aplicar_jugada(tablero , pos , cambios , turno_actual);
        turno_actual = (turno_actual == 'B') ? 'N' : 'B';
    };
    
    

}
*turno_final = turno_actual; // Si ninguna jugada es invalida guardamos el color del turno actual 
return 1; // retornamos 1 
}

//guardar_tablero(char* , char)->void 

//la funcion guardar_tablero abre un archivo en modo escritura 
// y pega el tablero seguido del color del turno que le toca jugar 


void guardar_tablero(char tablero[8][8], char proximo_turno) {
    FILE *archivo = fopen("partida_guardada.txt", "w"); // crea el archivo 
    if (archivo == NULL) {
        printf("Error al crear el archivo de salida.\n"); // si no puede crearlo imprime  y retorna cero 
        return;
    }
    //imprime el talbero
    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
           
            fprintf(archivo, "%c", tablero[f][c]);
        }
        fprintf(archivo, "\n"); 
    }
    
 
    fprintf(archivo, "%c", proximo_turno); //imprime el color 

    fclose(archivo); //cierra el archivo 
}


//partida_terminada(char*)->int(0/1)
// partida_terminada verifica si una partida termino o no 
// en caso de terminar imprime el ganador y retorna 1 
// en caso contrario retorna cero 

int partida_terminada(char tablero[8][8]) {
    int contador_blancas = 0, contador_negras = 0; // contador de fichas para saber el ganador 

    posicion pos_simulada; // variable para guardar los intentos de jugada en caracteres vacios 
    lista_de_cambios cambios_simulados; // lista para guardar cambios de las jugadas 

    for (int f = 0; f < 8; f++) { 
        for (int c = 0; c < 8; c++) {  // recorremos el tablero 
            if (tablero[f][c] == 'B') contador_blancas++; // si encontramos una ficha blanca aumentamos el contador 
            if (tablero[f][c] == 'N') contador_negras++; // si encontramos una ficha negra aumentamos el contador 
            if (tablero[f][c] == 'X') { 
// si encontramos una posicion vacia verificamos que no haya movimientos validos para ninguno de los 2 colores 
                pos_simulada.fila = f;
                pos_simulada.col = c;
                // si al menos uno de los 2 colores tiene un solo movimiento valido la partida aun no a terminado y retornamos cero 
                obtener_cambios(tablero, pos_simulada, 'B', &cambios_simulados);
                if (cambios_simulados.cantidad > 0) {
                    return 0; 
                }
                obtener_cambios(tablero, pos_simulada, 'N', &cambios_simulados);
                if (cambios_simulados.cantidad > 0) {
                    return 0; 
                }

            }

        }
    } // mostramos  quien es el ganador y el total de fichas 
    printf("Fin del juego. Blancas: %d - Negras: %d\n", contador_blancas, contador_negras);
    if (contador_blancas > contador_negras) printf("Ganan las Blancas!\n");
    else if (contador_negras > contador_blancas) printf("Ganan las Negras!\n");
    else printf("Empate!\n");

return 1; // la partida termino 
}

//validarYprocesar_archivo(file*)->int(0/1)

// la funcion toma el archivo de entrada y verifica que :
// el formato de jugador 1 y jugador 2 sea valido 
// el formato del color inicial sea valido 
// inicializar el talbero 
// los movimientos sean validos 
// en caso de que que la partida no haya terminado guarda el tablero.


int validarYprocesar_archivo (FILE *archivo) {
    jugador j1, j2;
    char turno_actual;
    char turno_final;
    // definimos  las variables necesarias para jugar y leer el archivo
    // y ademas turno_final , que nos servira para guardar cual fue el ultimo turno que realizo una jugada 
    
    if (cargar_encabezado(archivo, &j1, &j2, &turno_actual) == 0){ // leemos los primeros 3 renglones 
        printf("Error en la lectura  del encabezado\n");
        return 0;
    }

    if (validar_encabezado( j1, j2, turno_actual) == 0) { // verificamos que los mismos cumplan el formato 
        printf("Error en formato de encabezado\n");
        return 0;
    }

    char tablero[8][8] ;
    inicializar_tablero(tablero); // inicializamos el tablero 

    if (procesar_movimientos(archivo,tablero,turno_actual,j1,j2, &turno_final) == 0) // procesamos jugada a jugada , en caso de encontrar una erronea retornamos cero 
    // tambien pasamos como argumento la direccion de turno final para que la funcion sea capaz de modificarlo
    {
        return 0;
    }else{
        // si ninguna jugada es erronea verificamos si la partida termino 
        if (partida_terminada(tablero) == 1)
        {
            return 1 ;// si es asi retornamos 1 
        } else {
            guardar_tablero(tablero,turno_final); // caso contraria guardarmos el tablero y el turno final y retornamos  1
            return 1;
        }
        

    }
    

}

