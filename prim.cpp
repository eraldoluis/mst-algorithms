#include "prim.h"
#include "binomial.h"
#include "fibonacci.h"

#include <limits.h>

struct tVertex
{
	bool operator<(const tVertex& v) const
	{
		return Weight < v.Weight;
	}

	bool operator>(const tVertex& v) const
	{
		return Weight > v.Weight;
	}

	bool operator<=(const tVertex& v) const
	{
		return Weight <= v.Weight;
	}

	bool operator>=(const tVertex& v) const
	{
		return Weight >= v.Weight;
	}

	bool InQ;
	int Vertex;
	int Weight;
	int Parent;
	tStub* HeapStub;
};

tGraph*
PrimSpanningTree(const tGraph* g, int r, tHeap<tVertex>* heap)
{
	int i;

	tVertex* v = new tVertex[g->N];

	for (i = 0; i < g->N; ++i) {
		v[i].Vertex = i;
		v[i].Weight = INT_MAX;
		v[i].InQ = true;
		v[i].Parent = -1;

		if (i == r)
			v[i].Weight = 0;

		v[i].HeapStub = heap->Insert(&(v[i]));
	}

	while (heap->Minimum()) {
		tVertex* u = heap->ExtractMin();
		tAdjacency* a = g->Adjacency[u->Vertex];
		while (a) {
			if (v[a->Vertex].InQ && a->Weight < v[a->Vertex].Weight) {
				v[a->Vertex].Weight = a->Weight;
				v[a->Vertex].Parent = u->Vertex;
				heap->DecreaseKey(v[a->Vertex].HeapStub);
			}

			a = a->Next;
		}

		u->InQ = false;
	}

	// constroi a arvore geradora minima a partir dos 'Parent's dos
	// vertices
	tGraph* tree = new tGraph(g->N);

	for (i = 0; i < g->N; ++i) {
		if (v[i].Parent >= 0)
			tree->CreateEdge(i, v[i].Parent, v[i].Weight);
	}

	return tree;
}

tGraph*
BinomialPrimSpanningTree(const tGraph* g, int r)
{
	tBinomialHeap<tVertex> heap;
	return PrimSpanningTree(g, r, &heap);
}

tGraph*
FibonacciPrimSpanningTree(const tGraph* g, int r)
{
	tFibonacciHeap<tVertex> heap;
	return PrimSpanningTree(g, r, &heap);
}
