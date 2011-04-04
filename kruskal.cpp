/*
 * kruskal.cpp
 *
 * Eraldo Luis Rezende Fernandes
 *
 * Outubro de 2003.
 *
 * Implementacao do algoritmo de Kruskal para encontrar a floresta
 * geradora minima de um grafo (conexo ou nao)
 *
 */

#include "kruskal.h"
#include "disjointset.h"

#include <stdlib.h>

struct tEdge
{
	bool operator<(const tEdge& e) const
	{
		return Weight < e.Weight;
	}

	bool operator>(const tEdge& e) const
	{
		return Weight > e.Weight;
	}

	bool operator<=(const tEdge& e) const
	{
		return Weight <= e.Weight;
	}

	bool operator>=(const tEdge& e) const
	{
		return Weight >= e.Weight;
	}

	int V1;
	int V2;
	int Weight;
};

struct tVectorIterator
{
	int Index;
	tEdge** Vector;
};

void
FillEdgeVector(int i, int j, int w, void* data)
{
	tEdge* e = new tEdge;
	tVectorIterator* it = (tVectorIterator*) data;

	e->V1 = i;
	e->V2 = j;
	e->Weight = w;

	it->Vector[it->Index] = e;
	++(it->Index);
}

int
CompEdges(const void* d1, const void* d2)
{
	const tEdge& e1 = **((tEdge**) d1);
	const tEdge& e2 = **((tEdge**) d2);

	return ( e1 < e2 ? -1 : ( e1 > e2 ? 1 : 0  ) );
}

tGraph*
KruskalSpanningTree(const tGraph* g)
{
	// vetor de (ponteiros de) arestas
	tEdge** edges = new tEdge*[g->M];

	// preenche vetor com arestas
	tVectorIterator it;
	it.Index = 0;
	it.Vector = edges;
	g->DoForEachEdge(FillEdgeVector, &it);

	// ordena arestas
	qsort(edges, g->M, sizeof(edges[0]), CompEdges);

	// cria uma particao dos vertices de 'g' onde cada conjunto possui
	// apenas um vertice
	int i;
	tDisjointSet** set = new tDisjointSet*[g->N];
	for (i = 0; i < g->N; ++i)
		set[i] = new tDisjointSet;

	// cria o grafo que representarah a arvore geradora minima
	tGraph* tree = new tGraph(g->N);

	// gera a arvore geradora minima
	const tEdge* e;
	tDisjointSet* s1;
	tDisjointSet* s2;
	for (i = 0; i < g->M; ++i) {
		e = edges[i];
		s1 = set[e->V1]->FindSet();
		s2 = set[e->V2]->FindSet();
		if (s1 != s2) {
			tree->CreateEdge(e->V1, e->V2, e->Weight);
			s1->Union(s2);
		}
	}

	// desaloca memoria da estrutura de conjuntos disjuntos
	for (i = 0; i < g->N; ++i)
		delete set[i];
	delete [] set;

	return tree;
}
