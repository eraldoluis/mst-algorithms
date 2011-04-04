#include "binomial.h"
#include "fibonacci.h"

#include <stdio.h>
//#include <curses.h>

void
PrintMenu(const char* name)
{
	printf("\n\n");
	printf("*** Heap %s ***\n", name);
	printf("(i) Insert\n");
	printf("(e) Extract Minimum\n");
	printf("(p) Print\n");
	printf("(x) Exit\n");
}

void
Menu(tHeap<int>* heap, const char* name)
{
	int i;
	const int* r;
	char ch[2];

	do {
		PrintMenu(name);

	  scanf("%s", ch);

		switch (ch[0]) {
		case 'i':
		case 'I':
			scanf("%d", &i);
			heap->Insert(new int(i));
			break;

		case 'e':
		case 'E':
			r = heap->ExtractMin();
			if (r) {
				printf("%d\n", *r);
				delete r;
			}
			break;

		case 'p':
		case 'P':
			heap->Write(stdout);
			break;
		}
	} while (ch[0] != 'x' && ch[0] != 'X');
}

void
Auto(tHeap<int>* heap)
{
	heap->Insert(new int(1));
	heap->Insert(new int(2));
	heap->Insert(new int(3));
	heap->Insert(new int(4));
	heap->Insert(new int(5));

	delete heap->ExtractMin();
	delete heap->ExtractMin();
	delete heap->ExtractMin();

	heap->Write(stdout);
}

int
MainTestHeap(char argc, char* argv[])
{
	tHeap<int>* heap;

	//Menu(heap = new tBinomialHeap<int>, "Binomial");
	Menu(heap = new tFibonacciHeap<int>, "Fibonacci");
	//Auto(heap = new tFibonacciHeap<int>);

	delete heap;

	return 0;
}
