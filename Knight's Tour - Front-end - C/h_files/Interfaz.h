/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interfaz.h
 * Author: Dani
 *
 * Created on October 23, 2021, 7:13 PM
 */

#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <ctype.h>
#include <time.h>
#include <unistd.h>  
#include "Tablero.h"
#include "Archivos.h"

extern int **solucion;

extern void iniciarPrograma();

extern void iniciarSolucion();

extern void liberarSolucion();

extern void imprimirTablero();

extern void inicioJuego(int typeChosen);

extern void doMoves();

#endif /* INTERFAZ_H */
