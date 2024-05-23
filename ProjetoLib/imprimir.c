/**
	@file      imprimir.c
	@brief
	@author    Gustavo Pereira 29852
	@date      22.05.2024
**/
#include "Header.h"

/**
 * Função para imprimir o grafo
 */

void ImprimirGrafo(Vertice* grafo)
{
	Vertice* aux = grafo; // Inicializa um apontador auxiliar com o inicio do grafo
	while (aux != NULL) // Percorre a lista de vértices
	{
		printf("%d:\n", aux->id);
		Adjacent* auxAdjacent = aux->nextAdjacent;
		while (auxAdjacent != NULL)
		{
			printf("\tAdjacente: %d, Peso: %d\n", auxAdjacent->id, auxAdjacent->peso);
			auxAdjacent = auxAdjacent->next;
		}
		aux = aux->nextVertice;
	}
}

/**
 * Função para imprimir o grafo usando listas de adjacencia
 */

void ImprimirGrafoLA(Grafo* grafo)
{
	ImprimirGrafo(grafo->inicioGraph);
}


void ExibirCaminho(int* caminho, int indiceCaminho) {
	printf("Caminho encontrado: ");
	for (int i = 0; i < indiceCaminho; i++) {
		printf("%d ", caminho[i]);
	}
	printf("\n");
}

/**
 * Função para imprimir o caminho do vértice de origem até o vertice de destino
 *
 * @param depois O parâmetro "depois" é um array de inteiros que armazena o antecessor de cada vértice num caminho
 * @param destino O parâmetro `destino` representa o destino 
 */

void ImprimeCaminho(int* depois, int destino)
{
	if (depois[destino] == -1)
	{
		printf("%d ", destino);
		return;
	}

	ImprimeCaminho(depois, depois[destino]);
	printf("%d ", destino);
}

/**
 * A função imprime o caminho mais curto de um vértice de origem até um vértice de destino
 * @param origem O parâmetro "origem" representa o vértice inicial do caminho 
 * @param destino O parâmetro "destino" representa o vértice de destino 
 * @param anterior O parâmetro "anterior" representa um array que armazena o vértice anterior no caminho mais curto 
 * @param distancia O parâmetro `distancia` é um apotnador para um array de inteiros
 */
void imprimir(int origem, int destino, int anterior, int* distancia)
{
	// Imprimindo o caminho mais curto até o vértice de destino
	printf("Caminho mais curto de %d para %d: ", origem, destino);
	ImprimeCaminho(anterior, destino);
	printf("com peso %d\n", distancia[destino]);
}

/**
 * A função imprime o caminho com maior soma de pesos de um vertice de origem até um de destino
 *
 * @param origem O parâmetro "origem" representa vertice de origem 
 * @param destino O parâmetro "destino" representa o vértice de destino 
 * @param dist O parâmetro `dist` é um apotnador para um array de inteiros
 */
void imprimir2(int origem, int destino, int anterior, int* dist)
{
	printf("Maior soma de %d para %d: ", origem, destino);
	ImprimeCaminho(anterior, destino);
	printf("com peso %d\n", dist[destino]);
}