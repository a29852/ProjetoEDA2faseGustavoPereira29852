/**
	@file      grafo.c
	@brief
	@author    Gustavo Pereira 29852
	@date      22.05.2024
**/
#include "Header.h"

/**
 * Função para criar um grafo
 *
 * @param total o parâmetro `total` representa o número total de vértices 
 */

Grafo* CriaGrafo(int total)
{
	Grafo* novo = (Grafo*)malloc(sizeof(Grafo)); // Aloca memeria para um novo grafo
	if (novo == NULL) // Verifica se foi bem sucedida
	{
		return NULL;
	}
	novo->inicioGraph = NULL; // Inicializa o apontador para o inicio do grafo como NULL
	novo->numeroVertices = 0; // Inicializa o numero de vértices como 0
	novo->totVertices = total; // Define o total de vértices do grafo
	return novo;
}

/**
 * Função para inserir um novo vértice no grafo
 *
 * @param grafo `grafo` é um apontador para uma estrutura de dados
 * @param novo O parâmetro "novo" representa um novo vértice que é inserir no grafo
 */

Grafo* InsereVerticeGrafo(Grafo* grafo, Vertice* novo)
{
	if (novo == NULL)
	{
		return grafo;
	}
	if (grafo == NULL)
	{
		return NULL;
	}
	if (ExisteVertice(grafo->inicioGraph, novo->id))
	{
		return grafo;
	}

	grafo->inicioGraph = InsereVertice(grafo->inicioGraph, novo);
	grafo->numeroVertices++;
	return grafo;
}

/**
 * Função para inserir uma nova adjacencia no grafo
 *
 * @param grafo O parâmetro "grafo" representa o grafo
 * @param idDestino O parâmetro `idDestino` representa o ID do vértice de destino onde a nova adjacência é adicionada
 * @param peso O parâmetro "peso" representa o peso
 */

Grafo* InsereAdjaGrafo(Grafo* grafo, int idOrigem, int idDestino, int peso)
{
	if (grafo == NULL)
	{
		return grafo;
	}
	Vertice* verticeOrigem = OndeEstaVerticeGraph(grafo, idOrigem); // Vai buscar o vértice de origem no grafo

	if (verticeOrigem == NULL) // Verifica se o vértice de origem foi encontrado
	{
		return grafo;
	}
	verticeOrigem->nextAdjacent = InsereAdj(verticeOrigem->nextAdjacent, idDestino, peso); // Insere a adjacencia no vértice de origem
	return grafo;
}



/**
 * Função para eliminar uma adjacencia do grafo
 *
 * @param origem 
 * @param destino O parâmetro "destino" representa o destino
 *
 */

Grafo* EliminaAdjGraph(Grafo* grafo, int origem, int destino)
{
	if (grafo == NULL) // Verifica se o grafo é NULL
	{
		return grafo;
	}
	Vertice* verticeOrigem = OndeEstaVerticeGraph(grafo, origem); // Vai buscar o vértice de origem no grafo

	if (verticeOrigem == NULL) // Verifica se o vértice de origem foi encontrado
	{
		return grafo;
	}
	verticeOrigem->nextAdjacent = ElimiminaAdj(verticeOrigem->nextAdjacent, destino); // Elimina a adjacencia do vértice de origem
	return grafo;
}

/**
 * Função para encontrar um vértice no grafo
 * @param grafo O parâmetro `grafo` é um apontador para a estrutura do grafo
 * @param idVertice O parâmetro `idVertice` representa o ID do vértice que é procurando no grafo
 */

Vertice* OndeEstaVerticeGraph(Grafo* grafo, int idVertice)
{
	if (grafo == NULL)
	{
		return NULL;
	}
	Vertice* aux = grafo->inicioGraph; // Inicializa um apontador auxiliar com o inicio do grafo

	while (aux != NULL) // Percorre a lista de vértices
	{
		if (aux->id == idVertice) // Verifica se o ID do vértice é igual ao ID procurado
		{
			return aux;
		}
		aux = aux->nextVertice;
	}
	return NULL;
}

/**
 * A função verifica se existe um vértice na estrutura de dados grafo.
 *
 * @param idVertice O parâmetro `idVertice` representa o ID do vértice que está a ser verificado
 */
bool ExisteVerticeGraph(Grafo* grafo, int idVertice)
{
	if (grafo == NULL)
	{
		return false;
	}
	return (ExisteVertice(grafo->inicioGraph, idVertice));
}

/**
 * Função para eliminar um vértice do grafo
 *
 * @param grafo `grafo` é um apontador para uma estrutura de dados grafo
 * @param idVertice O parâmetro `idVertice` representa o identificador do vértice que vai ser eliminado
 */

Grafo* EliminaVerticeGraph(Grafo* grafo, int idVertice)
{
	if (grafo == NULL)
	{
		return NULL;
	}

	grafo->inicioGraph = EliminaVertice(grafo->inicioGraph, idVertice);
	grafo->inicioGraph = EliminaAdjacenciaTodosVertices(grafo->inicioGraph, idVertice);
	grafo->numeroVertices--;
	return grafo;
}