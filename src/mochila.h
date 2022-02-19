#ifndef _MOCHILA_H
#define _MOCHILA_H

#include "params.h"

typedef struct {
	int peso;
	int beneficio;
} Item;

int imprimirVetorSolucao(int, int *);
int pesoSolucao(int, int *, Item *);
int beneficioSolucao(int, int *, Item *);
void solucaoForcaBruta(int, int, int *, Item *);
void solucaoAleatoria(int, int, int *, Item *);
void solucaoMaiorLucro(int, int, int *, Item *);
void solucaoMenorPeso(int, int, int *, Item *);
void solucaoMaiorBeneficioPeso(int, int, int *, Item *);

#endif
