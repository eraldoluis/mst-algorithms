#ifndef __FIBONACCI_H
#define __FIBONACCI_H

/*
 * fibonacci.h
 *
 * Outubro de 2003.
 *
 * Eraldo Luis Rezende Fernandes
 *
 * Declaracao de um Heap de Fibonacci
 *
 */

#include "heap.h"

#include <math.h>
#include <stdio.h>


//////////////////////////////////////////////////////////////////////
//
// tFibonacciHeapNode
// ==================
//
template <class T>
struct tFibonacciHeapNode : public tHeapNode<T>
{
	tFibonacciHeapNode(T* key);
	virtual ~tFibonacciHeapNode();

	void Link(tFibonacciHeapNode<T>* node);

	tFibonacciHeapNode<T>* Child;
	tFibonacciHeapNode<T>* Parent;
	tFibonacciHeapNode<T>* Prev;
	tFibonacciHeapNode<T>* Next;

	int Degree;
	bool Mark;
};

//
// tFibonacciHeapNode inline implementation
//
template <class T>
inline
tFibonacciHeapNode<T>::tFibonacciHeapNode(T* key)
	:  tHeapNode<T>(key),
		 Child(NULL),
		 Parent(NULL),
		 Prev(NULL),
		 Next(NULL),
		 Degree(0),
		 Mark(false)
{}

template <class T>
inline
tFibonacciHeapNode<T>::~tFibonacciHeapNode()
{
	if (!Child)
		return;

	tFibonacciHeapNode<T>* n = Child->Next;
	tFibonacciHeapNode<T>* aux;

	while (n != Child) {
		aux = n;
		n = n->Next;
		delete aux;
	}

	delete Child;
}

template <class T>
inline void
tFibonacciHeapNode<T>::Link(tFibonacciHeapNode<T>* node)
{
	node->Parent = this;

	if (this->Child) {
		node->Next = this->Child;
		node->Prev = this->Child->Prev;
		node->Next->Prev = node;
		node->Prev->Next = node;
	}
	else {
		this->Child = node;
		node->Next = node;
		node->Prev = node;
	}

	this->Degree = this->Degree + 1;

	node->Mark = false;
}


//////////////////////////////////////////////////////////////////////
//
// tFibonacciHeap
// =============
//
template <class T>
class tFibonacciHeap : public tHeap<T>
{
 public:
	tFibonacciHeap();
	virtual ~tFibonacciHeap();

	// Operacoes de um heap
	virtual tStub* Insert(T* e);
	virtual T* Minimum() const;
	virtual T* ExtractMin();
	virtual void Union(tHeap<T>* heap);
	virtual void DecreaseKey(tStub* n);

 protected:
	void Consolidate();
	void Concatenate(tFibonacciHeapNode<T>* n1, tFibonacciHeapNode<T>* n2);
	void InsertInBucket(tFibonacciHeapNode<T>*& b, tFibonacciHeapNode<T>* n);

	void Cut(tFibonacciHeapNode<T>* node);
	void CascadingCut(tFibonacciHeapNode<T>* node);

	tFibonacciHeapNode<T>* Min;
	int N;
};

//
// tFibonacciHeap inline implementation
//
template <class T>
inline
tFibonacciHeap<T>::tFibonacciHeap()
	:	 Min(NULL),
		 N(0)
{}

template <class T>
inline
tFibonacciHeap<T>::~tFibonacciHeap()
{
	if (!Min)
		return;

	tFibonacciHeapNode<T>* n = Min->Next;
	tFibonacciHeapNode<T>* aux;

	while (n != Min) {
		aux = n;
		n = n->Next;
		delete aux;
	}

	delete Min;
}

template <class T>
inline T*
tFibonacciHeap<T>::Minimum() const
{
	if (!Min)
		return NULL;

	return Min->Key;
}

template <class T>
inline void 
tFibonacciHeap<T>::Concatenate(tFibonacciHeapNode<T>* n1, 
															 tFibonacciHeapNode<T>* n2)
{
	tFibonacciHeapNode<T>* n1n = n1->Next;
	tFibonacciHeapNode<T>* n2n = n2->Next;

	n1->Next = n2n;
	n2n->Prev = n1;
	n2->Next = n1n;
	n1n->Prev = n2;
}

template <class T>
inline void 
tFibonacciHeap<T>::Union(tHeap<T>* h)
{
	tFibonacciHeap<T>* heap = dynamic_cast<tFibonacciHeap<T>*>(h);
	if (!heap)
		return;

	if (heap->Min == NULL)
		return;

	this->N += heap->N;

	if (this->Min == NULL)
		this->Min = heap->Min;
	else {
		Concatenate(this->Min, heap->Min);
		if (heap->Min->GetKey() < this->Min->GetKey())
			this->Min = heap->Min;
	}

	heap->Min = NULL;
	delete heap;
}

template <class T>
inline tStub*
tFibonacciHeap<T>::Insert(T* e)
{
	tFibonacciHeapNode<T>* n = new tFibonacciHeapNode<T>(e);
	n->Next = n->Prev = n;

	N += 1;

	if (Min == NULL) {
		Min = n;
		return n->Stub;
	}

	Concatenate(Min, n);

	if (n->GetKey() < Min->GetKey())
		Min = n;

	return n->Stub;
}

template <class T>
inline T* 
tFibonacciHeap<T>::ExtractMin()
{
	tFibonacciHeapNode<T>* n;

	if (Min == NULL)
		return NULL;

	--N;

	n = Min;

	tFibonacciHeapNode<T>* nc = n->Child;
	if (nc) {
		nc->Parent = NULL;
		nc = nc->Next;
		while (nc != n->Child) {
			nc->Parent = NULL;
			nc = nc->Next;
		}

		Concatenate(n, n->Child);
	}

	n->Prev->Next = n->Next;
	n->Next->Prev = n->Prev;

	if (n->Next == n)
		Min = NULL;
	else {
		Min = n->Next;
		Consolidate();
	}

	T* e = n->Key;
	n->Child = NULL;
	delete n;

	return e;
}

//
// insere noh 'n' no bucket 'b'
//
template <class T>
inline void
tFibonacciHeap<T>::InsertInBucket(tFibonacciHeapNode<T>*& b, 
																	tFibonacciHeapNode<T>* n)
{
	if (b == NULL) {
		b = n;

		n->Next = n;
		n->Prev = n;
	}
	else {
		n->Next = b->Next;
		n->Prev = b;

		n->Next->Prev = n;
		n->Prev->Next = n;
	}
}

template <class T>
inline void
tFibonacciHeap<T>::Consolidate()
{
	int i, nb;
	tFibonacciHeapNode<T>** buckets;
	tFibonacciHeapNode<T>* p;
	tFibonacciHeapNode<T>* aux;

	// numero de buckets
	nb = 1 + (int)log2(N);

	// cria um vetor de tamanho log2(N) de buckets
	buckets = new tFibonacciHeapNode<T>*[nb];
	for (i = 0; i < nb; ++i)
		buckets[i] = NULL;

	// insere todas as raizes do heap nos respectivos buckets
	p = Min->Next;
	InsertInBucket(buckets[Min->Degree], Min);
	while (p != Min) {
		aux = p;
		p = p->Next;
		InsertInBucket(buckets[aux->Degree], aux);
	}

	// linka as raizes de mesmo grau deixando, em cada bucket, no maximo
	// uma raiz
	for (i = 0; i < nb; ++i) {
		p = buckets[i];
		while (p && p->Next != p) {
			// 'aux' eh a primeira das duas raizes a serem linkadas
			aux = p;

			// 'p' eh a proxima raiz do bucket a ser analisada
			p = p->Next->Next;

			// retira 'aux' e 'aux->Next' da lista desse bucket
			if (aux != p) {
				p->Prev = aux->Prev;
				aux->Prev->Next = p;
			}
			else
				p = NULL;

			// atualiza ponteiro desse bucket
			buckets[i] = p;

			// pendura uma raiz na outra (mantendo a ordem parcial)
			if (aux->GetKey() <= aux->Next->GetKey())
				aux->Link(aux->Next);
			else {
				aux = aux->Next;
				aux->Link(aux->Prev);
			}

			// insere a menor raiz no proximo bucket (pois agora possui grau
			// maior)
			InsertInBucket(buckets[i+1], aux);
		}
	}

	// varre os buckets reinserindo as raizes no heap e atribui a 'Min'
	// a raiz com menor chave
	for (i = 0; buckets[i] == NULL && i < nb; ++i)
		;

	if (i < nb)
		Min = buckets[i];
	else
		Min = NULL;

	for (++i; i < nb; ++i) {
		if (buckets[i]) {
			Concatenate(Min, buckets[i]);
			if (buckets[i]->GetKey() < Min->GetKey())
				Min = buckets[i];
		}
	}
}

template <class T>
inline void 
tFibonacciHeap<T>::DecreaseKey(tStub* st)
{
	tFibonacciHeapNode<T>* node = (tFibonacciHeapNode<T>*) st->Node;

	if (node->Parent && node->Parent->GetKey() > node->GetKey()) {
		Cut(node);
		CascadingCut(node->Parent);
	}

	if (node->GetKey() < Min->GetKey())
		Min = node;
}

template <class T>
inline void
tFibonacciHeap<T>::Cut(tFibonacciHeapNode<T>* node)
{
	if (node->Next == node)
		node->Parent->Child = NULL;
	else {
		node->Prev->Next = node->Next;
		node->Next->Prev = node->Prev;
	}

	--(node->Parent->Degree);

	node->Parent = NULL;
	node->Next = node->Prev = node;

	node->Mark = false;

	Concatenate(Min, node);
}

template <class T>
inline void
tFibonacciHeap<T>::CascadingCut(tFibonacciHeapNode<T>* node)
{
	if (node->Parent) {
		if (node->Mark) {
			Cut(node);
			CascadingCut(node->Parent);
		}
		else
			node->Mark = true;
	}
}


#endif //__FIBONACCI_H
