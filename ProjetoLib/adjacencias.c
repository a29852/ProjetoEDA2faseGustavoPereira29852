/**
	@file      adjacencias.c
	@brief
	@author    Gustavo Pereira 29852
	@date      22.05.2024
**/
#include "Header.h"

/**
 * Função para criar uma nova adjacencia
 *
 * @param id O parâmetro `id` na função `NovaAdjacent` representa o identificador do vertice adjacente. É usado para identificar exclusivamente o vertice adjacente no grafo
 * @param peso O parâmetro "peso" na função "NovaAdjacent" representa o peso da adjacência. É usado para armazenar o peso entre dois vertices
 *
 * @return A função `NovaAdjacent` retorna um apontador para uma estrutura `Adjacent`
 */
Adjacent* NovaAdjacent(int id, int peso)
{
	Adjacent* aux = (Adjacent*)malloc(sizeof(Adjacent)); // Aloca memeria para uma nova adjacancia
	if (aux == NULL)  // Verifica se foi bem sucedida
	{
		return NULL;
	}
	aux->id = id;
	aux->peso = peso;
	aux->next = NULL;
	return aux;
}

/**
 * Função para liberar a memória alocada
 *
 * @param ptAdjacent é um apontador para uma estrutura de dados que representa informações de adjacência no grafo
 */

void DestroiAdjacent(Adjacent* ptAdjacent)
{
	if (ptAdjacent == NULL) // Verifica se o apontador para a adjacencia é NULL
	{
		return;
	}
	free(ptAdjacent); // Libera a memeria alocada para a adjacencia
}

/**
 * Função para eliminar uma adjacencia de uma lista de adjacencias
 *
 * @param listAdj Apontador para o início da lista de adjacências
 * @param codAdj O parâmetro `codAdj` representa o código da adjacência que vai ser eliminada 
 *
 * @return A função `ElimiminaAdj` retorna a lista atualizada de adjacências
 */
Adjacent* ElimiminaAdj(Adjacent* listAdj, int codAdj)
{
	if (listAdj == NULL) // Verifica se a lista de adjacencias está vazia
	{
		return NULL;
	}
	Adjacent* anterior = NULL; // Inicializa um apontador para a adjacencia anterior como NULL
	Adjacent* aux = listAdj; // Inicializa um apontador auxiliar com o inicio da lista
	while (aux != NULL && aux->id != codAdj) // Percorre a lista até encontrar a adjacencia a ser eliminada
	{
		anterior = aux;
		aux = aux->next;
	}
	if (aux == NULL)
	{
		return listAdj;
	}
	if (anterior == NULL)  // Verifica se a adjacencia a ser eliminada é a primeira da lista
	{
		listAdj = aux->next;
	}
	else
	{
		anterior->next = aux->next;
	}
	DestroiAdjacent(aux); // Apaga a adjacencia
	return listAdj;
}

/**
 * Função para eliminar todas as adjacencias de uma lista de adjacencias
 */
Adjacent* ElimiminaTodasAdj(Adjacent* listAdj)
{
	Adjacent* aux; // Declaração um apontador auxiliar
	while (listAdj != NULL) // Percorre a lista de adjacencias
	{
		aux = listAdj; // Atualiza o apontador auxiliar
		listAdj = listAdj->next;
		DestroiAdjacent(aux); // Apaga a adjacencia atual
	}
	return NULL;
}

/**
 * Função para inserir uma nova adjacencia na lista de adjacencias
 *
 * @param idDestino O parâmetro `idDestino` representa o identificador do vertice de destino da adjacência que vai ser inserido
 * @param peso O parâmetro "peso" representa o peso da adjacencia que liga o vertice atual ao vertice de destino
 */
Adjacent* InsereAdj(Adjacent* listaAdja, int idDestino, int peso)
{
	Adjacent* nova = NovaAdjacent(idDestino, peso); // Cria uma nova adjacencia
	if (nova == NULL) // Verifica se a criaçao foi bem sucedida
	{
		return listaAdja;
	}
	if (listaAdja == NULL) // Verifica se a lista de adjacencias está vazia
	{
		return nova;
	}
	Adjacent* aux = listaAdja; // Inicializa um apontador auxiliar com o inecio da lista
	while (aux->next != NULL) // Percorre a lista até a ultima adjacencia
	{
		aux = aux->next;
	}
	aux->next = nova; // Insere a nova adjacencia no final da lista
	return listaAdja;
}