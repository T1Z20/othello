import pytest
from programa.othello import aplicar_jugada, cambios_de_jugada, contar_fichas, obtener_movimientos_validos, elegir_movimiento

def tablero_inicio() : 
    tablero = []
    for i in range(8):
        fila = []

        for j in range(8):
            fila.append("X") 
        
        tablero.append(fila) 

    tablero[3][3] = "B"
    tablero[3][4] = "N"
    tablero[4][3] = "N"
    tablero[4][4] = "B"

    return tablero

def test_contar_fichas(tablero_inicio):
    tablero = tablero_inicio()
    negras, blancas = contar_fichas(tablero)
    assert negras == 2
    assert blancas == 2

def test_cambios_de_jugada_valido():
    tablero = tablero_inicio()
    cambios = cambios_de_jugada(tablero, "N", 2, 3)
    assert (3, 3) in cambios
    assert (2, 3) in cambios

def test_cambios_de_jugada_invalido():
    tablero = tablero_inicio()
    cambios = cambios_de_jugada(tablero, "N", 0, 0)
    assert cambios == []

def test_obtener_movimientos_validos():
    tablero = tablero_inicio()
    movimientos = obtener_movimientos_validos(tablero, "N")

    assert len(movimientos) == 4

def test_elegir_movimiento_nivel_1():
    movimientos = [(1, 1, [(1, 1)]),(2, 2, [(2, 2), (3, 3)])
    ]
    elegido = elegir_movimiento(movimientos, 1)
    assert elegido == movimientos[1]

def test_aplicar_jugada():
    tablero = tablero_inicio()
    cambios = [(3, 3), (2, 3)]
    aplicar_jugada(tablero, cambios, "N")

    assert tablero[3][3] == "N"
    assert tablero[2][3] == "N"

def test_contar_fichas():
    tablero = tablero_inicio()
    negras, blancas = contar_fichas(tablero)

    assert negras == 2
    assert blancas == 2

