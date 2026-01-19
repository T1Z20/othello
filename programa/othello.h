#ifndef OTHELLO_H
#define OTHELLO_H

#include <stdio.h>

#define MAX_NOMBRE 255


typedef struct {
    int fila;
    int col;
} posicion;

typedef struct {
    char nombre[MAX_NOMBRE];
    char color;      
} jugador;

typedef struct {
    posicion cambios[20];
    int cantidad;   
} lista_de_cambios;




jugador tomar_jugador(char *renglon);
int validar_jugador(jugador j);
char tomar_color_inicial(char *renglon);
int valdiar_color_inicial(char color); 
int cargar_encabezado(FILE *archivo, jugador *j1, jugador *j2, char *turno_inicial);
int validar_encabezado(jugador j1, jugador j2, char turno_inicial);


posicion tomar_jugada(char *renglon);
int validar_jugada(posicion jugada);
void inicializar_tablero(char tablero[8][8]);
int coordenada_en_rango(int fila, int col);
void obtener_cambios(char tablero[8][8], posicion jugada, char color_jugador, lista_de_cambios *cambios);
int validar_cambios(lista_de_cambios cambios, char turno_actual, jugador j1, jugador j2);
void aplicar_jugada(char tablero[8][8], posicion jugada, lista_de_cambios cambios, char color);
void mostrartablero(char tablero[8][8]);
int tiene_movimientos_validos(char tablero[8][8], char color);
void buffer_a_mayusculas(char *buffer);


int procesar_movimientos(FILE *archivo, char tablero[8][8], char turno_inicial, jugador j1, jugador j2, char *turno_final);
void guardar_tablero(char tablero[8][8], char proximo_turno);
int partida_terminada(char tablero[8][8]);
int validarYprocesar_archivo(FILE *archivo);

#endif 