/*
 * graph.cpp
 *
 * Eraldo Luis Rezende Fernandes
 *
 * Outubro de 2003.
 *
 * Implementacao de estruturas para representar um grafo.
 *
 */

#include "graph.h"

//
// tGraph implementation
//
tGraph::tGraph():
	N(0),
	M(0),
	Adjacency(NULL)
{}

tGraph::tGraph(int n):
	N(n),
	M(0),
	Adjacency(new tAdjacency*[n])
{
	int i;
	for (i = 0; i < N; ++i)
		Adjacency[i] = NULL;
}

tGraph::~tGraph()
{
	Free();
}

void
tGraph::Free()
{
	int i;
	tAdjacency* v;
	tAdjacency* aux;

	if (Adjacency != NULL) {

		for (i = 0; i < N; ++i) {
			v = Adjacency[i];
			while (v) {
				aux = v->Next;
				delete v;
				v = aux;
			}
		}

	}

	delete [] Adjacency;

	N = 0;
	M = 0;
	Adjacency = NULL;
}

void 
tGraph::CreateEdge(int i, int j, int w)
{
	tAdjacency* ai = new tAdjacency;
	tAdjacency* aj = new tAdjacency;

	ai->Weight = aj->Weight = w;
	ai->Vertex = j;
	aj->Vertex = i;

	ai->Next = Adjacency[i];
	Adjacency[i] = ai;

	aj->Next = Adjacency[j];
	Adjacency[j] = aj;

	++M;
}

void
tGraph::DoForEachEdge(FDoForEdge f, void* data) const
{
	int i;
	tAdjacency* a;

	for (i = 0; i < N; ++i) {
		a = Adjacency[i];
		while (a) {
			if (a->Vertex > i)
				f(i, a->Vertex, a->Weight, data);
			a = a->Next;
		}
	}
}

void
PrintEdge(int i, int j, int w, void* data)
{
	FILE* f = (FILE*) data;
	fprintf(f, "(%d,%d,%d) ", i, j, w);
}

void 
tGraph::Write(FILE* f) const
{
	fprintf(f, "%d\n", N);
	DoForEachEdge(PrintEdge, f);
	fprintf(f, "\n");
}

void
tGraph::Read(FILE* f)
{
	int v1, v2, w;

	Free();

	// le numero de vertices
	fscanf(f, "%d", &N);
	Adjacency = new tAdjacency*[N];

	// le arestas
	while (fscanf(f, " ( %d , %d , %d ) ", &v1, &v2, &w) != EOF)
		CreateEdge(v1, v2, w);
}
