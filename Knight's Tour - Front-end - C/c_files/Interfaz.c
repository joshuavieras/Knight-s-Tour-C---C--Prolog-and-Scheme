/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interfaz.c
 * Author: Dani
 * 
 * Created on October 23, 2021, 7:13 PM
 */

#include "../h_files/Interfaz.h"

int **solucion;

/*
int solucion[8][8] = { 
                { 1, 48, 31, 50, 33, 16, 63, 18 },
                { 30, 51, 46, 3, 62, 19, 14, 35 },
                { 47, 2, 49, 32, 15, 34, 17, 64 },
                { 52, 29, 4, 45, 20, 61, 36, 13 },
                { 5, 44, 25, 56, 9, 40, 21, 60 },
                { 28, 53, 8, 41, 24, 57, 12, 37 },
                { 43, 6, 55, 26, 39, 10, 59, 22 },
                { 54, 27, 42, 7, 58, 23, 38, 11 }
            };
*/

void iniciarPrograma()
{
    inicializarTablero();

    iniciarSolucion();
    
    inicioJuego(0);

    liberarMemoria();
    
    liberarSolucion();
}

void iniciarSolucion()
{
    solucion = (int **)malloc(8 * sizeof(int *)); // Allocate row pointers

    for (int i = 0; i < 8; i++)
    {
        solucion[i] = (int *)malloc(8 * sizeof(int));
    }
}

void liberarSolucion()
{
    for (int i = 0; i < table.row_count; i++)
    {
        free(solucion[i]);
    }

    free(solucion);
}

void imprimirTablero()
{
    int tam = table.col_count * table.row_count;

    char row = 'A';

    for (int j = 0; j < table.col_count; j++)
    {
        printf("\t %c", row);

        row++;
    }

    printf("\n \n \t");

    for (int j = 0; j < tam; j++)
    {
        printf("*");
    }

    printf("\n \n");

    for (int i = 0; i < table.row_count; i++)
    {
        printf(" %i", i + 1);

        for (int j = 0; j < table.col_count; j++)
        {
            if (table.tablero[i][j].caballo_aqui == 1)
            {
                printf("\t[%2s]", "🐎");
            }
            else if(table.tablero[i][j].numero_movimiento != 0)
            {
                if(table.tablero[i][j].numero_movimiento < 10)
                {
                    printf("\t[0%d]", table.tablero[i][j].numero_movimiento);
    
                }
                else
                {
                    printf("\t[%2d]", table.tablero[i][j].numero_movimiento);
                }
            }
            else
            {
                printf("\t[  ]");
            }
        }

        printf("\n \n");
    }
}

void inicioJuego(int typeChosen)
{
    int i = 0;
    char j = 'x';
    int resultado = 0;
    
    if(typeChosen != 1)
    {
        printf("Digite el tipo de recorrido que desea visualizar.\n");
    
        printf("[1] - Recorrido abierto.\n");
        printf("[2] - Recorrido cerrado.\n");
        printf("[3] - Salir.\n\n");

        printf("Digite la opcion\n-> ");

        resultado = scanf("%d", &i);

        if (resultado != 1)
        {
            return;
        }

        if(i != 1 && i != 2)
        {
            return;
        }  
    }
    
    printf("\e[1;1H\e[2J");

    imprimirTablero();

    printf("Digite la fila de la posicion inicial del caballo.\n");

    printf("Rango valido: ");

    for (int i = 0; i < table.col_count; i++)
    {
        if (i == 0)
        {
            printf("( %i,", i + 1);
        }
        else if (i == table.col_count - 1)
        {
            printf(" %i ) \n", i + 1);
        }
        else
        {
            printf(" %i,", i + 1);
        }
    }
    
    printf("-> ");

    resultado = scanf("%d", &i);

    if (resultado != 1)
    {
        inicioJuego(1);
        return;
    }

    printf("\nDigite la columna de la posicion inicial del caballo.\n");

    printf("Rango valido: ");

    int row_name = 'A';

    for (int i = 0; i < table.row_count; i++)
    {
        if (i == 0)
        {
            printf("( %c,", row_name);
        }
        else if (i == table.row_count - 1)
        {
            printf(" %c ) \n", row_name);
        }
        else
        {
            printf(" %c,", row_name);
        }

        row_name++;
    }

    printf("-> ");

    resultado = scanf(" %c", &j);

    if (resultado != 1)
    {
        inicioJuego(1);
        return;
    }

    j = toupper(j);

    if (checkIfValidRow(j) == -1)
    {
        inicioJuego(1);
        return;
    }

    int posJ = retornarPosSegunChar(j);

    posicionarCaballo(i - 1, posJ);

    if(i == 1) 
    {
        //Hacer recorrido abierto
    }
    else 
    {
        //Hacer recorrido cerrado
    }
    
    //Metodo para pintar despues de cada movimiento

    guardarPosicionInicio(i - 1, posJ);
    system("../Knights-Tour-Back-end-Scheme/KnightsTour.exe");
    printf("\n\nDigite un caracter cualquiera para empezar el recorrido.\n");    

    printf("-> ");

    resultado = scanf(" %c", &j);
    
    cargarSolucion(solucion);
    
    printf("\e[1;1H\e[2J");

    imprimirTablero();
    
    fflush(stdout);
    sleep(1.5);
    
    printf("\e[1;1H\e[2J");
    
    doMoves();
    
    imprimirTablero();
}

void doMoves()
{
    if(table.contador_movimientos != 64)
    {
        for (int i = 0; i < table.row_count; i++)
        {
            for (int j = 0; j < table.col_count; j++)
            {
                if(solucion[i][j] == (table.contador_movimientos + 1))
                {
                    reposicionarCaballo(i, j);
                    imprimirTablero();
                    fflush(stdout);
                    sleep(1.5);
                    printf("\e[1;1H\e[2J");
                    doMoves();
                    return;
                }
            }
        } 
    }
}