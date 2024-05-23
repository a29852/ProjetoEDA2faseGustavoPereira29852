
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 100
#define MAX_VERTICES 100

typedef struct Adjacent {
	int id;
	int peso;
	struct Adjacent* next;
} Adjacent;

typedef struct Vertice {
	int id;
	struct Vertice* nextVertice;
	struct Adjacent* nextAdjacent;
} Vertice;

typedef struct Grafo {
	struct Vertice* inicioGraph;
	int numeroVertices;
	int totVertices;
} Grafo;



//Vertices
void DestroiVertice(Vertice* ptNode);
Vertice* CriaVertice(int id);
bool ExisteVertice(Vertice* inicio, int id);
Vertice* InsereVertice(Vertice* vertices, Vertice* novo);
Vertice* EliminaVertice(Vertice* vertices, int codVertice);
Vertice* EliminaAdjacenciaTodosVertices(Vertice* vertices, int codAdj);
Vertice* OndeEstaVerticeGraph(Grafo* grafo, int idVertice);
bool ExisteVerticeGraph(Grafo* grafo, int idVertice);

//Grafo
Grafo* CriaGrafo(int total);
Grafo* InsereVerticeGrafo(Grafo* grafo, Vertice* novo);
Grafo* InsereAdjaGrafo(Grafo* grafo, int idOrigem, int idDestino, int peso);
Grafo* EliminaAdjGraph(Grafo* grafo, int origem, int destino);
Grafo* EliminaVerticeGraph(Grafo* grafo, int idVertice);

//Adjacentes
Adjacent* NovaAdjacent(int id, int peso);
void DestroiAdjacent(Adjacent* ptAdjacent);
Adjacent* ElimiminaAdj(Adjacent* listAdj, int codAdj);
Adjacent* ElimiminaTodasAdj(Adjacent* listAdj);
Adjacent* InsereAdj(Adjacent* listaAdja, int idDestino, int peso);

//Fun��es
bool DFSFuncao(Grafo* grafo, Vertice* atual, bool* visitado, int* caminho, int indiceCaminho, int destino);
bool DFS(Grafo* grafo, int origem, int destino);
int EncontraVerticeMenorDist(int* distancia, bool* processado, int V);
bool CaminhoCurtoVerticeOrigemDestino(Grafo* grafo, int origem, int destino);
int EncontraVerticeMaiorDist(int* distancia, bool* processado, int totalVertices);
bool CaminhoMaxSoma(Grafo* grafo, int origem, int destino);

//Imprimir Ecr�
void ImprimirGrafo(Vertice* grafo);
void ImprimirGrafoLA(Grafo* grafo);
void ExibirCaminho(int* caminho, int indiceCaminho);
void ImprimeCaminho(int* predecessor, int destino);
void imprimir(int origem, int destino, int depois, int* distancia);
void imprimir2(int origem, int destino, int anterior, int* dist);

//Ficheiros
Grafo* CarregarGrafo(const char* filename);
bool SalvarGrafo(Grafo* grafo, const char* filename);
bool SalvarGrafoBinario(Grafo* grafo, const char* filename);