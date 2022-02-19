#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "mochila.h"

double MyClock () {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000) + tv.tv_usec; 
}


void processar (char *fName, int numeroItens, int capacidade, int *melhorSolucao, Item *vetorItem, void (*solucao)(int, int, int*, Item*)) {
  double time = MyClock();
  printf("==> %s <==\n", fName);
	(*solucao)(numeroItens, capacidade, melhorSolucao, vetorItem);
	imprimirVetorSolucao(numeroItens, melhorSolucao);
	printf("~ Peso:%3i\n", pesoSolucao(numeroItens, melhorSolucao, vetorItem));
	printf("~ Benefício:%3i\n", beneficioSolucao(numeroItens, melhorSolucao, vetorItem));
	printf("~ Tempo de Execução: %.10lf ms\n\n\n", (MyClock() - time) / CLOCKS_PER_SEC);
}


int main () {  
	FILE *arq = fopen(ARQUIVO, "r");

  if (arq == NULL) {
    exit(1);
  }

  int numeroItens = 0, capacidade = 0;

  fscanf(arq, "%i", &capacidade);
  fscanf(arq, "%i", &numeroItens);

	int *melhorSolucao = calloc(numeroItens, sizeof(int));
	Item *vetorItem = calloc(numeroItens, sizeof(Item));

  for (int i = 0; i < numeroItens; i++) {
    fscanf(arq, "%i", &vetorItem[i].beneficio);
  }
  
  for (int i = 0; i < numeroItens; i++) {
    fscanf(arq, "%i", &vetorItem[i].peso);
  }

  if (numeroItens > 30) {
    printf("Não foi possível encontrar a uma solução ótima \
            para essa quantidade de itens.\n");
    fclose(arq);
    exit(1);
  }

  processar("Solução Menor Peso", numeroItens, capacidade, melhorSolucao, vetorItem, solucaoMenorPeso);
  processar("Solução Maior Lucro", numeroItens, capacidade, melhorSolucao, vetorItem, solucaoMaiorLucro);
  processar("Solução Maior Benefício/Peso", numeroItens, capacidade, melhorSolucao, vetorItem, solucaoMaiorBeneficioPeso);
  processar("Solução Força Bruta", numeroItens, capacidade, melhorSolucao, vetorItem, solucaoForcaBruta);
  processar("Solução Aleatória", numeroItens, capacidade, melhorSolucao, vetorItem, solucaoAleatoria);

  free(melhorSolucao);
  free(vetorItem);
  fclose(arq);

  melhorSolucao = NULL;
  vetorItem = NULL;
  arq = NULL;

	return 0;
}