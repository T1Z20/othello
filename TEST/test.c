#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "othello.h"








void test_tomar_jugador() {

    jugador j1 = tomar_jugador("Lucas,B");
    assert(strcmp(j1.nombre, "Lucas") == 0);
    assert(j1.color == 'B');

    jugador j2 = tomar_jugador("juan pablo,N");
    assert(strcmp(j2.nombre, "juan pablo") == 0);
    assert(j2.color == 'N');


    jugador j3 = tomar_jugador("fede");
    assert(j3.color == 'X');
    assert(j3.nombre[0] == '\0');

    jugador j4 = tomar_jugador(",B");
    assert(j4.nombre[0] == '\0');
    assert(j4.color == 'B');
}

void test_validar_jugador() {
    

    jugador j1 = {"Lucas", 'B'};
    assert(validar_jugador(j1) == 1);

    jugador j2 = {"Ana", 'N'};
    assert(validar_jugador(j2) == 1);

    jugador j3 = {"", 'B'};
    assert(validar_jugador(j3) == 0);

    jugador j4 = {"Pedro", 'X'};
    assert(validar_jugador(j4) == 0);
}

void test_tomar_jugada() {

    posicion p1 = tomar_jugada("A1");
    assert(p1.col == 0);
    assert(p1.fila == 0);

    posicion p2 = tomar_jugada("H8");
    assert(p2.col == 7);
    assert(p2.fila == 7);

    posicion p3 = tomar_jugada("Z1");
    assert(p3.col == -1);
    assert(p3.fila == 0);

    posicion p4 = tomar_jugada("A9");
    assert(p4.col == 0);
    assert(p4.fila == -1);
}

void test_validar_jugada() {
    

    posicion p1 = {3, 3};
    assert(validar_jugada(p1) == 1);

    posicion p2 = {3, -1};
    assert(validar_jugada(p2) == 0);

    posicion p3 = {-1, 3};
    assert(validar_jugada(p3) == 0);

    posicion p4 = {-1, -1};
    assert(validar_jugada(p4) == 0);
}

void test_tomar_color_inicial() {
    

    assert(tomar_color_inicial("B") == 'B');

    assert(tomar_color_inicial("N") == 'N');

    assert(tomar_color_inicial("X") == 'X');

    assert(tomar_color_inicial("") == '\0');
}

void test_valdiar_color_inicial() {
    
    assert(valdiar_color_inicial('B') == 1);

    assert(valdiar_color_inicial('N') == 1);

    assert(valdiar_color_inicial('X') == 0);

}

void test_coordenada_en_rango() {

    assert(coordenada_en_rango(3, 3) == 1);

    assert(coordenada_en_rango(0, 7) == 1);

    assert(coordenada_en_rango(-1, 0) == 0);

    assert(coordenada_en_rango(8, 8) == 0);
}

void test_validar_cambios() {


    jugador j1 = {"Lucas", 'B'};
    jugador j2 = {"Ana", 'N'};
    // dejo las listas vacias ,porque no importan para valdiar cambios.
    lista_de_cambios c1 = {0};
    c1.cantidad = 3;
    assert(validar_cambios(c1, 'B', j1, j2) == 1);

    lista_de_cambios c2 = {0};
    c2.cantidad = 0;
    assert(validar_cambios(c2, 'B', j1, j2) == 0);

    lista_de_cambios c3 = {0};
    c3.cantidad = 5;
    assert(validar_cambios(c3, 'N', j1, j2) == 1);

    lista_de_cambios c4 = {0};
    c4.cantidad = 0;
    assert(validar_cambios(c4, 'N', j1, j2) == 0);
}

void test_tiene_movimientos_validos() {
    
    char tablero[8][8];
    int f, c;

    
    inicializar_tablero(tablero);
    assert(tiene_movimientos_validos(tablero, 'N') == 1);

    
    inicializar_tablero(tablero);
    assert(tiene_movimientos_validos(tablero, 'B') == 1);

    
    inicializar_tablero(tablero);
    for(f=0; f<8; f++) for(c=0; c<8; c++) tablero[f][c] = 'B';
    //tablero lleno de fichas blancas 
    assert(tiene_movimientos_validos(tablero, 'N') == 0);

}

void test_partida_terminada() {
    
    char tablero[8][8];
    int f, c;

  
    inicializar_tablero(tablero);
    assert(partida_terminada(tablero) == 0);

    
    for(f=0; f<8; f++) for(c=0; c<8; c++) tablero[f][c] = 'B';
    assert(partida_terminada(tablero) == 1);

    //  casi lleno sin movimientos 
   
    for(f=0; f<8; f++) for(c=0; c<8; c++) tablero[f][c] = 'B';
    tablero[0][0] = 'X'; 
    assert(partida_terminada(tablero) == 1);

   
    // un tablero vacio con  una B y una N juntas
    for(f=0; f<8; f++) for(c=0; c<8; c++) tablero[f][c] = 'X';
    tablero[0][0] = 'B';
    tablero[0][1] = 'N';
    //  B en 0 2 
    assert(partida_terminada(tablero) == 0);
}


//algunas funciones tienen prints asi que al ejecutarlo es probable que se vea algo asi :
// la jugada de Lucas  , es incorrecta 
// la jugada de Ana  , es incorrecta 
// Fin del juego. Blancas: 64 - Negras: 0
// Ganan las Blancas!
// Fin del juego. Blancas: 63 - Negras: 0
// Ganan las Blancas!

int main() {

    test_tomar_jugador();
    test_validar_jugador();
    test_tomar_jugada();
    test_validar_jugada();
    test_tomar_color_inicial();
    test_valdiar_color_inicial();
    test_coordenada_en_rango();
    test_validar_cambios();
    test_tiene_movimientos_validos();
    test_partida_terminada();
    printf("\n\n\n\n");
    printf("los tests pasaron correctamente \n");
    printf("\n\n\n\n");
    return 0;
}

