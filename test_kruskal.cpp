#include "kruskal.h"

void
Usage()
{
	printf("\nUsage: teste2 [graph_file]\n\n");
}

int
main(int argc, char* argv[])
{
	if (argc < 2) {
		Usage();
		return 1;
	}

	FILE* f = fopen(argv[1], "rt");
	tGraph* g = new tGraph;
	g->Read(f);

	tGraph* tree = KruskalSpanningTree(g);

	tree->Write(stdout);

	delete tree;
	delete g;

	return 0;
}
