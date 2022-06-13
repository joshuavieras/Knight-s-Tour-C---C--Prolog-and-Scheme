/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tablero.h
 * Author: Dani
 *
 * Created on October 23, 2021, 7:12 PM
 */

#ifndef TABLERO_H
#define TABLERO_H
#include "Casilla.h"

typedef struct Tablero
{
    Casilla **tablero;
    int row_count; //n
    int col_count; //m
    int contador_movimientos;
    int antI;
    int antJ;

} Tablero;

extern Tablero table;

extern void inicializarTablero();

extern int posicionarCaballo(int i, int j);

extern int reposicionarCaballo(int i, int j);

extern int checkIfValidRow(char row);

extern int retornarPosSegunChar(char row);

extern void liberarMemoria();

#endif /* TABLERO_H */
