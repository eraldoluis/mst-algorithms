#include "prim.h"

#include <stdlib.h>

void
Usage()
{
	printf("\nUsage: bprim graph_file [root_node]\n\n");
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

	int root;

	if (argc >= 3)
		root = atoi(argv[2]);
	else
		root = 0;

	tGraph* tree = BinomialPrimSpanningTree(g, root);

	tree->Write(stdout);

	delete tree;
	delete g;

	return 0;
}
