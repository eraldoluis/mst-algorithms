#include "kruskal.h"
#include "prim.h"
#include "fibonacci.h"

#include <stdlib.h>
#include <string.h>

void Usage() {
	printf("\nUsage: mst <algorithm> <graph_file> [<root_node>]\n");
	printf("\t<algorithm> := ( kruskal | bprim | fprim )\n\n");
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		Usage();
		return 1;
	}

	// Load the graph file.
	FILE* f = fopen(argv[2], "rt");
	if (f == NULL) {
		printf("\nError reading file %s\n\n", argv[2]);
		return 1;
	}

	tGraph* g = new tGraph();
	g->Read(f);
	fclose(f);

	// Parse the given tree root.
	int root;
	if (argc >= 3)
		root = atoi(argv[2]);
	else
		root = 0;

	tGraph* tree = NULL;
	if (strcmp(argv[1], "kruskal") == 0)
		tree = KruskalSpanningTree(g);
	else if (strcmp(argv[1], "bprim") == 0)
		tree = BinomialPrimSpanningTree(g, root);
	else if (strcmp(argv[1], "fprim") == 0)
		tree = FibonacciPrimSpanningTree(g, root);
	else {
		delete g;
		Usage();
		return 1;
	}

	tree->Write(stdout);

	delete tree;
	delete g;

	return 0;
}
