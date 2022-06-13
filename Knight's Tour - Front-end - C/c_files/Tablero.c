/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tablero.c
 * Author: Dani
 * 
 * Created on October 23, 2021, 7:12 PM
 */

#include "../h_files/Tablero.h"
Tablero table;

void inicializarTablero()
{
    table.row_count = 8;

    table.col_count = 8;

    table.contador_movimientos = 0;

    table.tablero = (Casilla **)malloc(8 * sizeof(Casilla *)); // Allocate row pointers

    for (int i = 0; i < 8; i++)
    {
        table.tablero[i] = (Casilla *)malloc(8 * sizeof(Casilla));
    }
    
    for (int i = 0; i < table.row_count; i++)
    {
        for (int j = 0; j < table.col_count; j++)
        {
            table.tablero[i][j].numero_movimiento = 0;
        }
    }
}

int posicionarCaballo(int i, int j)
{
    if (i >= table.row_count || j >= table.col_count || i < 0 || j < 0)
    {
        return -1;
    }

    if (table.contador_movimientos != 0)
    {
        return -1;
    }

    table.tablero[i][j].caballo_aqui = 1;
    table.tablero[i][j].estado = 1;
    table.tablero[i][j].numero_movimiento = table.contador_movimientos + 1;

    table.contador_movimientos++;

    table.antI = i;

    table.antJ = j;

    return 1;
}

int reposicionarCaballo(int i, int j)
{
    if (i >= table.row_count || j >= table.col_count || i < 0 || j < 0)
    {
        return -1;
    }

    if (table.contador_movimientos == 0)
    {
        return -1;
    }

    table.tablero[table.antI][table.antJ].caballo_aqui = 0;

    table.tablero[i][j].caballo_aqui = 1;
    table.tablero[i][j].estado = 1;
    table.tablero[i][j].numero_movimiento = table.contador_movimientos + 1;

    table.contador_movimientos++;

    table.antI = i;

    table.antJ = j;

    return 1;
}

int checkIfValidRow(char row)
{
    int total = table.col_count * table.row_count;

    int tam = total / 2;

    char letras[tam];

    char inicio = 'A';

    for (int i = 0; i < tam; i++)
    {
        letras[i] = inicio;

        inicio++;
    }

    for (int i = 0; i < tam; i++)
    {
        if (letras[i] == row)
        {
            return 1;
        }
    }

    return -1;
}

int retornarPosSegunChar(char row)
{
    int total = table.col_count * table.row_count;

    int tam = total / 2;

    char inicio = 'A';

    for (int i = 0; i < tam; i++)
    {
        if (inicio == row)
        {
            return i;
        }

        inicio++;
    }

    return -1;
}

void liberarMemoria()
{
    for (int i = 0; i < table.row_count; i++)
    {
        free(table.tablero[i]);
    }

    free(table.tablero);
}