/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file_header.c to edit this template
 */

/* 
 * File:   Archivos.c
 * Author: danil
 * 
 * Created on November 25, 2021, 5:06 PM
 */

#include "../h_files/Archivos.h"

void guardarPosicionInicio(int x, int y)
{
    FILE *inicio = fopen("Archivos/PosInicio.txt", "w");

    if (!inicio)
    {
        return;
    }
    
    fprintf(inicio, "%d\n", x);
    fprintf(inicio, "%d", y);
    
    fclose(inicio);
}

int cargarSolucion(int **Solucion)
{
    FILE *solucion = fopen("Archivos/RespuestaCaballo.txt", "r");
    
     if (!solucion)
    {
        return -1;
    }

    fseek(solucion, 0, SEEK_END);

    if (ftell(solucion) == 0)
    {
        fclose(solucion);
        return -1;
    }

    rewind(solucion);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fscanf(solucion, "%d", &Solucion[i][j]);
        }
    }
    
    fclose(solucion);
    
    return 1;
}