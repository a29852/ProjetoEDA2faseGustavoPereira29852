/**
	@file      ficheiros.c
	@brief
	@author    Gustavo Pereira 29852
	@date      22.05.2024
**/
#include "Header.h"

/**
 * A função lê um ficheiro para carregar o grafo
 *
 * @param nome O parâmetro `nome` é um apontador para um array de caracteres constante que representa o nome do ficheiro
 *
 */
Grafo* CarregarGrafo(char* nome)
{
	FILE* ficheiro = fopen(nome, "r");
	if (ficheiro == NULL)
	{
		return NULL;
	}

	Grafo* grafo = NULL;
	int totalVertices = 0;

	// Le o ficheiro para determinar o numero total de vértices
	char buffer[100];
	while (fgets(buffer, sizeof(buffer), ficheiro) != NULL)
	{
		totalVertices++;
	}

	// Reinicia o ponteiro do ficheiro para o inicio
	rewind(ficheiro);

	// Cria o grafo com o numero total de vertices determinado
	grafo = CriaGrafo(totalVertices);

	// Leitura dos pesos do ficheiro e construção do grafo
	int idOrigem = 0;
	while (fgets(buffer, sizeof(buffer), ficheiro) != NULL)
	{
		Vertice* origemNode = CriaVertice(idOrigem);
		grafo = InsereVerticeGrafo(grafo, origemNode);

		// Dividi a linha em tokens
		char* token = strtok(buffer, ";");
		int idDestino = 0;
		while (token != NULL)
		{
			// Ignorar os valores 0, que representam vertices sem arestas
			if (atoi(token) != 0)
			{
				// Inserir a adjacencia com o peso correspondente
				origemNode->nextAdjacent = InsereAdj(origemNode->nextAdjacent, idDestino, atoi(token));
			}
			idDestino++;
			token = strtok(NULL, ";");
		}

		idOrigem++;
	}

	fclose(ficheiro);
	return grafo;
}

/**
 * Função para salvar o grafo num ficheiro .txt
 *
 * @param grafo O parâmetro `grafo` é um apontador para a estrutura do gráfico que contém informações sobre os vértices e os seus vértices adjacentes
 *
 */

bool SalvarGrafo(Grafo* grafo,  char* nome)
{

	if (grafo == NULL || grafo->inicioGraph == NULL)
	{
		return false;
	}


	FILE* ficheiro = fopen(nome, "w"); // Abre o ficheiro

	if (ficheiro == NULL)  // Verifica se o ficheiro foi aberto com sucesso
	{
		return false;
	}


	Vertice* aux = grafo->inicioGraph; // Apontador auxiliar para percorrer os vertices do grafo

	while (aux != NULL) // Itera sobre todos os vertices do grafo
	{

		Adjacent* auxAdjacent = aux->nextAdjacent; // Apontador auxiliar para percorrer os adjacentes do vertice atual


		while (auxAdjacent != NULL) // Itera sobre todos os adjacentes do vertice atual
		{

			fprintf(ficheiro, "%d", auxAdjacent->peso); // Escreve o peso da aresta no ficheiro

			auxAdjacent = auxAdjacent->next;

			if (auxAdjacent != NULL) // Verifica se há mais adjacentes
			{
				fprintf(ficheiro, ";");
			}
		}
		fprintf(ficheiro, "\n");
		aux = aux->nextVertice;
	}

	fclose(ficheiro);
	return true;
}



/**
 * Função para salvar o grafo num ficheiro .bin
 *
 * @param grafo O parâmetro `grafo` é um apontador para uma estrutura que representa o grafo
 * @param nome O parâmetro `nome` representa o nome do ficheiro onde serão guardados os dados
 *
 */

bool SalvarGrafoBinario(Grafo* grafo,  char* nome)
{
	if (grafo == NULL || grafo->inicioGraph == NULL)
	{
		return false;
	}

	FILE* ficheiro = fopen(nome, "wb"); // Abre o ficheiro binário 
	if (ficheiro == NULL)
	{
		return false;
	}


	Vertice* aux = grafo->inicioGraph; // Apontador auxiliar para percorrer os vértices do grafo

	while (aux != NULL) // Itera sobre todos os vértices do grafo
	{

		Adjacent* auxAdjacent = aux->nextAdjacent; // Apontador auxiliar para percorrer os adjacentes do vértice atual

		while (auxAdjacent != NULL) // Itera sobre todos os adjacentes do vertice atual
		{

			fwrite(&(auxAdjacent->peso), sizeof(int), 1, ficheiro); // Escreve o peso da aresta no ficheiro binário
			auxAdjacent = auxAdjacent->next;

			if (auxAdjacent != NULL) // Verifica se há mais adjacentes
			{

				int marcacao = -1; // Se sim, escreve um marcador (-1) para representar um ; no ficheiro binrio
				fwrite(&marcacao, sizeof(int), 1, ficheiro);
			}
		}

		int fimLinha = -2; // Escreve um marcador (-2) para representar o \n
		fwrite(&fimLinha, sizeof(int), 1, ficheiro);
		aux = aux->nextVertice;
	}

	fclose(ficheiro);
	return true;
}