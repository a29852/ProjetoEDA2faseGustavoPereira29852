/**
	@file      Main.c
	@brief     
	@author    Gustavo Pereira 29852
	@date      22.05.2024
**/

#include "Header.h"
#pragma comment(lib, "ProjetoLib.lib")

int main()
{
	bool resultado;
	Grafo* grafo = CarregarGrafo("matriz.txt");

	if (grafo != NULL)
	{
		printf("\nGrafo\n");
		ImprimirGrafoLA(grafo);

		printf("\nTodos Caminhos possiveis entre dois vertices\n");
		DFS(grafo, 0, 2);

		printf("\nCaminho mais curto de vertice de origem ate destino\n");
		CaminhoCurtoVerticeOrigemDestino(grafo, 0, 2);

		resultado = SalvarGrafo(grafo, "matriz3.txt");
		resultado = SalvarGrafoBinario(grafo, "matriz.bin");

		printf("\nCaminho mais longo\n");
		CaminhoMaxSoma(grafo, 0, 2);

		grafo = EliminaAdjGraph(grafo, 1, 2);
		printf("\nGrafo com adj eliminada\n");
		ImprimirGrafoLA(grafo);

		grafo = EliminaVerticeGraph(grafo, 2);
		printf("\ngrafo com vertice eliminado\n");
		ImprimirGrafoLA(grafo);

	}
	else
	{
		return 1;
	}

	return 0;
}
