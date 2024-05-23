/**
	@file      funcoes.c
	@brief
	@author    Gustavo Pereira 29852
	@date      22.05.2024
**/
#include "Header.h"

/**
 * A função realiza a busca em profundidade (DFS) no grafo a partir de um vértice de origem até ao vertice destino
 *
 * @param grafo O parâmetro "grafo" é um apontador para a estrutura de dados do grafo no qual a busca em profundidade está sendo realizada
 * @param atual `atual` é um apontador para o vértice atual que está sendo visitado durante a primeira pesquisa em profundidade
 * @param visitado O parâmetro `visitado` é um array de booleanos que indica se um vértice foi visitado
 * @param caminho O parâmetro `caminho` representa o caminho obtido durante a pesquisa em profundidade
 * @param indiceCaminho O parâmetro `indiceCaminho` representa o índice atual no array `caminho` onde o ID do vértice atual é armazenado durante a pesquisa
 * @param destino O parâmetro `destino` representa o vértice de destino
 */
bool DFSFuncao(Grafo* grafo, Vertice* atual, bool* visitado, int* caminho, int indiceCaminho, int destino)
{
	bool result;

	// Marca o vértice atual como visitado e o adiciona ao caminho percorrido
	visitado[atual->id] = true;
	caminho[indiceCaminho] = atual->id;
	indiceCaminho++;

	// Se o vértice atual é o destino, mostra o caminho percorrido
	if (atual->id == destino)
	{
		ExibirCaminho(caminho, indiceCaminho);
	}

	// Percorre todos os vértices adjacentes ao vértice atual
	Adjacent* adj = atual->nextAdjacent;
	while (adj != NULL)
	{
		// Se o vértice adjacente ainda não foi visitado, realiza a busca em profundidade a partir dele
		if (!visitado[adj->id])
		{
			// Chama recursivamente a função DFSFuncao para o próximo vértice adjacente
			result = DFSFuncao(grafo, OndeEstaVerticeGraph(grafo, adj->id), visitado, caminho, indiceCaminho, destino);
		}
		adj = adj->next;
	}

	// Marca o vértice como não visitado para possiveis novas buscas a partir dele
	visitado[atual->id] = false;

	return true;
}


/**
 * A função DFS realiza uma pesquisa em profundidade no grafo para encontrar um caminho a partir de um determinado vértice de origem a´té um de destino
 *
 * @param grafo A variável `grafo` é um apotnador para uma estrutura de dados grafo
 * @param origem O parâmetro `origem` representa o vértice inicial a partir do qual o algoritmo começa a percorrer o grafo
 * @param destino O parâmetro `destino` representa o vértice de destino
 */
bool DFS(Grafo* grafo, int origem, int destino)
{
	bool result;


	bool* visitado = (bool*)malloc(grafo->totVertices * sizeof(bool));
	int* caminho = (int*)malloc(grafo->totVertices * sizeof(int));
	int indiceCaminho = 0; // indice para controlar o caminho percorrido

	// Inicializa todos os vértices como nao visitados
	for (int i = 0; i < grafo->totVertices; i++)
	{
		visitado[i] = false;
	}

	// Chama a função para encontrar o caminho até o destino
	result = DFSFuncao(grafo, OndeEstaVerticeGraph(grafo, origem), visitado, caminho, indiceCaminho, destino);

	// Liberta a memoria alocada para os vetores de visitados e caminho
	free(visitado);
	free(caminho);

	return true;
}

/**
 * Função para encontrar o vértice com a menor distancia
 *
 * @param distancia O parâmetro `distancia` é um array que armazena as distâncias de cada vértice
 * @param totalVertices `totalVertices` é o número total de vértices no grafo
 */

int EncontraVerticeMenorDist(int* distancia, bool* processado, int totalVertices)
{
	int min_distancia = INT_MAX, min_index; // Inicializa a menor distancia como um valor maximo e o indice do vértice de menor distancia


	for (int i = 0; i < totalVertices; i++) 	// Itera sobre todos os vértices
	{
		if (!processado[i] && distancia[i] <= min_distancia) // Verifica se o vértice ainda não foi processado e se sua distancia é menor ou igual á menor distancia atual
		{
			min_distancia = distancia[i]; // Atualiza a menor distancia e o indice do vértice de menor distancia
			min_index = i;
		}
	}

	return min_index;
}

/**
 * A função encontra o caminho mais curto de um vértice de origem para um vértice de destino atraves do algoritmo Dijkstra
 *
 * @param grafo Grafo é um apontador para uma estrutura que representa o grafo
 * @param origem O parâmetro "origem" representa o vértice inicial a partir do qual vai encontrar o caminho mais curto para o vértice de destino
 * @param destino O parâmetro "destino" representa o vértice de destino no grafo
 */

bool CaminhoCurtoVerticeOrigemDestino(Grafo* grafo, int origem, int destino)
{
	int totalVertices = grafo->totVertices; // Obtem o total de vértices no grafo

	// Aloca memória para os vetores de distancia, vértices predecessores e indicadores de processamento
	int* distancia = (int*)malloc(totalVertices * sizeof(int));
	int* anterior = (int*)malloc(totalVertices * sizeof(int));
	bool* processado = (bool*)malloc(totalVertices * sizeof(bool));

	// Inicializa todas as distancias como infinito, os predecessores como -1 e os vértices como não processados
	for (int i = 0; i < totalVertices; i++)
	{
		distancia[i] = INT_MAX;
		anterior[i] = -1;
		processado[i] = false;
	}

	// Define a distancia do vértice de origem como 0
	distancia[origem] = 0;


	for (int count = 0; count < totalVertices - 1; count++) // Encontra o caminho mais curto para o vértice de destino
	{

		int u = EncontraVerticeMenorDist(distancia, processado, totalVertices); // Encontra o vértice com a menor distancia entre aqueles que ainda não foram processados
		processado[u] = true;


		Vertice* vertice = OndeEstaVerticeGraph(grafo, u); // Obtem o vértice correspondente ao indice
		Adjacent* adjacente = vertice->nextAdjacent;


		while (adjacente != NULL) // Percorre todos os vértices adjacentes ao vértice atual
		{
			int v = adjacente->id; // indice do vértice adjacente
			int peso = adjacente->peso; // Peso da aresta entre os vértices u e v

			if (!processado[v] && distancia[u] != INT_MAX && distancia[u] + peso < distancia[v])
			{
				distancia[v] = distancia[u] + peso;
				anterior[v] = u;
			}
			adjacente = adjacente->next;
		}

		if (processado[destino])
		{
			break;
		}
	}


	if (distancia[destino] == INT_MAX) // Verifica se foi possivel encontrar um caminho para o vértice de destino
	{
		free(distancia);
		free(anterior);
		free(processado);
		return false;
	}
	else
	{
		imprimir(origem, destino, anterior, distancia);
		free(distancia);
		free(anterior);
		free(processado);
		return true;
	}
}

/**
 * A funçãoo encontra o vértice com a maior distancia entre aqueles que ainda não foram processados
 * @param dist O parâmetro `dist` é um array que armazena as distâncias dos vértices 
 * @param totalVertices Número total de vértices no gráfico
 */

int EncontraVerticeMaiorDist(int* dist, bool* processado, int totalVertices)
{
	// Inicializa a maior distancia como um valor minimo e o indice do vértice de maior distancia como -1
	int max_dist = INT_MIN, max_index = -1;

	// Itera sobre todos os vértices
	for (int i = 0; i < totalVertices; i++)
	{

		if (!processado[i] && dist[i] >= max_dist) // Verifica se o vértice ainda não foi processado e se sua distáncia é maior ou igual á maior distancia atual
		{
			max_dist = dist[i]; // Atualiza a maior distancia e o indice do vértice de maior distancia
			max_index = i;
		}
	}
	return max_index;
}


/**
 * A função encontra o caminho com a soma máxima dos pesos
 *
 * @param origem O parâmetro `origem` representa o vértice inicial a partir do qual vai encontrar o caminho com a soma máxima dos pesos
 * @param destino O parâmetro `destino` representa o destino 
 */
bool CaminhoMaxSoma(Grafo* grafo, int origem, int destino)
{

	int totalVertices = grafo->totVertices; // Obtem o total de vértices no grafo

	// Aloca memoria para os vetores de distancia, vértices predecessores e indicadores de processamento
	int* dist = (int*)malloc(totalVertices * sizeof(int));
	int* anterior = (int*)malloc(totalVertices * sizeof(int));
	bool* processado = (bool*)malloc(totalVertices * sizeof(bool));

	// Inicializa todas as distancias como o valor minimo possivel, os predecessores como -1 e os vértices como não processados
	for (int i = 0; i < totalVertices; i++)
	{
		dist[i] = INT_MIN;
		anterior[i] = -1;
		processado[i] = false;
	}

	// Define a distancia da origem como 0
	dist[origem] = 0;

	for (int count = 0; count < totalVertices - 1; count++) // Encontra o caminho com a maior soma de pesos
	{

		int u = EncontraVerticeMaiorDist(dist, processado, totalVertices); // Encontra o vértice com a maior distancia entre aqueles que ainda não foram processados

		if (u == -1) // Se nao há mais vértices a serem processados
		{
			break;
		}

		processado[u] = true; // Marca o vértice como processado


		Vertice* verticeU = OndeEstaVerticeGraph(grafo, u); // Obtem o vértice correspondente ao indice

		if (verticeU == NULL) // Se o vértice não existir, passa para o próximo
		{
			continue;
		}


		Adjacent* adj = verticeU->nextAdjacent; // Obtem a lista de adjacencia do vértice atual

		while (adj != NULL) // Percorre todos os vértices adjacentes ao vertice atual
		{
			int v = adj->id;
			int peso = adj->peso;

			// Se o vértice adjacente ainda não foi processado e a distancia atualizada á maior que a armazenada, atualiza a distancia e o predecessor
			if (!processado[v] && dist[u] != INT_MIN && dist[u] + peso > dist[v]) {
				dist[v] = dist[u] + peso;
				anterior[v] = u;
			}

			adj = adj->next;
		}
	}


	if (dist[destino] == INT_MIN) // Verifica se foi possivel encontrar um caminho para o destino
	{
		free(dist);
		free(anterior);
		free(processado);
		return false;
	}
	else
	{
		imprimir2(origem, destino, anterior, dist);
		free(dist);
		free(anterior);
		free(processado);
		return true;
	}
}