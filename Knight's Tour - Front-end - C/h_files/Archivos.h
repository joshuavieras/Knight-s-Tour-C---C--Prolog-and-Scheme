/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file_header.h to edit this template
 */

/* 
 * File:   Archivos.h
 * Author: danil
 *
 * Created on November 25, 2021, 5:06 PM
 */

#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern void guardarPosicionInicio(int x, int y);

/*
Retorna -1 si el archivo esta vacio o si hubo un error al abrir el archivo;
Retorna 1 si la carga se realizo con exito
*/
extern int cargarSolucion(int **Solucion);

#endif /* ARCHIVOS_H */
