/**
	@file      vertice.c
	@brief
	@author    Gustavo Pereira 29852
	@date      22.05.2024
**/
#include "Header.h"

/**
 * Função para liberar a memeria alocada
 *
 * @param ptNode é um apotnador para uma estrutura que representa um vértice no grafo
 */
void DestroiVertice(Vertice* ptNode)
{
	if (ptNode == NULL) // Verifica se o apontador para o vértice é NULL
	{
		return;
	}
	free(ptNode); // Libera a memeria alocada para o vértice
}

/**
 * Função para criar um vértice
 *
 * @param id O parâmetro `id` representa o identificador do vértice
 */
Vertice* CriaVertice(int id)
{
	Vertice* aux = (Vertice*)malloc(sizeof(Vertice)); // Aloca memeria para um novo vértice
	if (aux == NULL)
	{ // Verifica se a alocação foi bem sucedida
		return NULL;
	}
	aux->id = id; // Define o ID do vértice
	aux->nextVertice = NULL; // Inicializa o apontador para o próximo vértice como NULL
	aux->nextAdjacent = NULL; // Inicializa o apontador para a lista de adjacentes como NULL
	return aux;
}

/**
 * Função para verificar se um vértice com um determinado ID existe na lista de vértices
 *
 * @param inicio `inicio` é um apontador para o início de uma lista de vértices
 * @param id O parâmetro `id` representa o ID do vértice que
 */
bool ExisteVertice(Vertice* inicio, int id)
{
	if (inicio == NULL) // Verifica se a lista de vértices existe
	{
		return false;
	}
	Vertice* aux = inicio; // Inicializa um apontador auxiliar com o inicio da lista
	while (aux) // Percorre a lista de vértices
	{
		if (aux->id == id)
		{
			return true;
		}
		aux = aux->nextVertice;
	}
	return false;
}

/**
 * Função para inserir um novo vértice na lista de vértices
 *
 * @param novo O parâmetro `novo` representa o novo vértice que vai ser inserido
 */
Vertice* InsereVertice(Vertice* vertices, Vertice* novo)
{
	if (vertices == NULL) // Verifica se a lista de vertices está vazia
	{
		vertices = novo;
		return vertices;
	}
	if (ExisteVertice(vertices, novo->id)) // Verifica se o vértice já existe na lista
	{
		return vertices;
	}
	else
	{
		Vertice* anterior = NULL; // Inicializa um apontador para o vértice anterior como NULL
		Vertice* aux = vertices; // Inicializa um apontador auxiliar com o inicio da lista
		while (aux != NULL) { // Percorre a lista de vértices
			anterior = aux; // Atualiza o apontador anterior
			aux = aux->nextVertice; // Move para o proximo vértice
		}
		anterior->nextVertice = novo; // Insere o novo vértice no final da lista
		return vertices; // Retorna a lista atualizada
	}
}

/**
 * Função para eliminar um vértice da lista de vértices
 *
 * @param vertices é um apontador para o primeiro vértice na lista de vértices
 * @param codVertice O parâmetro `codVertice` representa o código do vértice que vai ser eliminado
 */

Vertice* EliminaVertice(Vertice* vertices, int codVertice)
{
	if (vertices == NULL) // Verifica se a lista de vértices está vazia
	{
		return NULL;
	}
	Vertice* anterior = NULL; // Inicializa um apontador para o vértice anterior como NULL
	Vertice* aux = vertices; // Inicializa um apontador auxiliar com o inicio da lista

	while (aux != NULL && aux->id != codVertice)// Percorre a lista até encontrar o vértice a ser eliminado
	{
		anterior = aux; // Atualiza o apontador anterior
		aux = aux->nextVertice;
	}
	if (aux == NULL)
	{
		return vertices;
	}
	if (anterior == NULL) // Verifica se o vértice a ser eliminado é o primeiro da lista
	{
		vertices = aux->nextVertice;
	}
	else
	{
		anterior->nextVertice = aux->nextVertice;
	}
	DestroiAdjacent(aux->nextAdjacent); // Apaga a lista de adjacencias do vértice
	DestroiVertice(aux); // Apaga o vértice
	return vertices;
}

/**
 * Função para eliminar todas as adjacencias de um vértice em todos os vértices
 *representado como uma lista vinculada.
 *
 * @param vertices é um apontador para o primeiro vértice 
 * @param codAdj O parâmetro `codAdj` representa o código da adjacência que deseja eliminar
 */

Vertice* EliminaAdjacenciaTodosVertices(Vertice* vertices, int codAdj)
{
	Vertice* aux = vertices; // Inicializa um apontador auxiliar com o inicio da lista

	while (aux != NULL) // Percorre a lista de vértices
	{
		aux->nextAdjacent = ElimiminaAdj(aux->nextAdjacent, codAdj); // Elimina a adjacencia do vértice
		aux = aux->nextVertice;
	}
	return vertices;
}