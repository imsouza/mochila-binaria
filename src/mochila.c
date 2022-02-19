#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "mochila.h"

void trocar (int *a, int *b) {
  int aux = *b;
  *b = *a;
  *a = aux;
}


int pesoSolucao (int n, int *solucao, Item *vetorItem) {
  int somatorio = 0;

  for (int i = 0; i < n; i++) {
   if (solucao[i]) {
      somatorio += vetorItem[i].peso;
    }
  }
  return somatorio;
}


int beneficioSolucao (int n, int *solucao, Item *vetorItem) {
  int somatorio = 0;

  for (int i = 0; i < n; i++) {
    if (solucao[i]) {
      somatorio += vetorItem[i].beneficio;
    }
  }
  return somatorio;
}


void copiarVetor(int n, int *destino, int *origem) {
  memcpy(destino, origem, sizeof(int) * n);
}


void dec2bin (int n, int dec, int *bin) {
  int i;  
	for (i = 0; dec > 0; dec /= 2, i++) {
    bin[i] = (dec % 2) ? 1 : 0;
  }
  
	for (int j = n - 1; j < (i / 2); j--) {
    trocar(&bin[i - j - 1], &bin[j]);
  }
}


void inserirItem (Item *item, int peso, int beneficio) {
	item->beneficio = beneficio;
	item->peso = peso;
}


int imprimirVetorSolucao (int n, int *solucao) {
	printf("~ Vetor Solução: [");
  int i;
  
	for (i = 0; i < n; i++) {
    printf("%i", solucao[i]);
  }
  
	printf("]\n");
	return i;
}


void solucaoForcaBruta (int n, int capacidade, int *melhor_solucao, Item *vetorItem) {
	int *solucao = calloc(n, sizeof(int));
	int peso = 0, beneficio = 0, maiorBeneficio = 0;

 	for (int i = 1; i < pow(2, n); i++) {
		dec2bin(n, i, solucao);

		peso = pesoSolucao(n, solucao, vetorItem);
		beneficio = beneficioSolucao(n, solucao, vetorItem);

		if (peso <= capacidade) {
			if (beneficio > maiorBeneficio) {
  			maiorBeneficio = beneficio;
  			copiarVetor(n, melhor_solucao, solucao);
			} 
    }
	}

	free(solucao);
}


void calcularSolucaoAleatoria (int *bin, int n) {
	for (int i = 0; i < n; i++) {
    bin[i] = rand() % 2;
  }
}



void solucaoAleatoria (int n, int capacidade, int *melhor_solucao, Item *vetorItem) {
	int peso = 0, beneficio = 0, maiorBeneficio = 0;
	int *solucao = calloc (n, sizeof(int));

	for (int i = 0; i < NUM_ITER; i++) {
		calcularSolucaoAleatoria(solucao, n);
		peso = pesoSolucao(n, solucao, vetorItem);
		beneficio = beneficioSolucao(n, solucao, vetorItem);

		if (peso <= capacidade)
			if (beneficio > maiorBeneficio) {
				maiorBeneficio = beneficio;
				copiarVetor(n, melhor_solucao, solucao);
			}
	}
}


void solucaoMaiorLucro (int n, int capacidade, int *solucao, Item *vetorItem) {
	int i, indice;
	int peso = 0;
	int maior;
	for (i = 0; i < n; i++)
		solucao[i] = 0;

	while (true) {
		maior = vetorItem[0].beneficio;
		indice = -1;

		for (i = 0; i < n; i++)
			if (vetorItem[i].beneficio > maior)
				if ((peso + vetorItem[i].peso) <= capacidade)
					if (solucao[i] == 0) {
						maior = vetorItem[i].beneficio;
						indice = i;
					}

		if (indice != -1) {
			solucao[indice] = 1;
			peso = peso + vetorItem[indice].peso;
		} else {
			break;
		}
	}
}


void solucaoMenorPeso (int n, int capacidade, int *solucao, Item *vetorItem) {
	int indice;
	int peso = 0;
	int menor;
  
	for (int i = 0; i < n; i++)
		solucao[i] = 0;

	while (true) {
		menor = vetorItem[0].peso;
		indice = -1;

		for (int i = 0; i < n; i++)
			if (vetorItem[i].peso < menor)
				if ((peso + vetorItem[i].peso) <= capacidade)
					if (solucao[i] == 0) {
						menor = vetorItem[i].peso;
						indice = i;
					}

		if (indice != -1) {
			solucao[indice] = 1;
			peso = peso + vetorItem[indice].peso;
		} else {
			break;
		}
	}
}


void solucaoMaiorBeneficioPeso (int n, int capacidade, int *solucao, Item *vetorItem) {
	int indice;
	int peso  = 0;
	int maior = 0;
  
	for (int i = 0; i < n; i++) {
    solucao[i] = 0;
  }

	while (1) {
		maior = vetorItem[0].beneficio / vetorItem[0].peso;
		indice = -1;

		for (int i = 0; i < n; i++)
			if (vetorItem[i].beneficio/vetorItem[i].peso > maior)
				if ((peso + vetorItem[i].peso) <= capacidade)
					if (solucao[i] == 0) {
						maior = vetorItem[i].beneficio;
						indice = i;
					}

		if (indice != -1) {
			solucao[indice] = 1;
			peso = peso + vetorItem[indice].peso;
		} else {
			break;
		}
	}
}

