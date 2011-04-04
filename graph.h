#ifndef __GRAPH_H
#define __GRAPH_H

/*
 * graph.h
 *
 * Eraldo Luis Rezende Fernandes
 *
 * Outubro de 2003.
 *
 * Declaracao de estruturas para representar um grafo.
 *
 */


#include <stdio.h>


//////////////////////////////////////////////////////////////////////
//
// tAdjacency
// ==========
//
// Objeto que representa a adjacencia de uma arestra em um
// vertice. Participa de uma lista de adjacencia de outro vertice
//
struct tAdjacency
{
	int Weight;
	int Vertex;
	tAdjacency* Next;
};


typedef void (*FDoForEdge)(int i, int j, int w, void* data);

//////////////////////////////////////////////////////////////////////
//
// tGraph
// ======
//
// Um grafo representado por listas de adjacencia
//
struct tGraph
{
	// cria um grafo vazio
	tGraph();

	// cria um grafo com 'n' vertices
	tGraph(int n);

	// destrutor
	~tGraph();

	// cria aresta ligando os vertices 'i' e 'j' com peso 'w'
	void CreateEdge(int i, int j, int w);

	// imprime grafo (adjacencias)
	void Write(FILE* f) const;

	// le grafo
	void Read(FILE* f);

	// chama funcao 'f' para cada aresta do grafo passando os vertices
	// adjacentes e 'data'
	void DoForEachEdge(FDoForEdge f, void* data) const;

	void Free();

	// quantidade de vertices
	int N;

	// quantidade de arestas
	int M;

	// vetor das listas de adjacencias
	tAdjacency** Adjacency;
};


#endif //__GRAPH_H
