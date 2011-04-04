#ifndef __BINOMIAL_H
#define __BINOMIAL_H

/*
 * binomial.h
 *
 * Outubro de 2003.
 *
 * Eraldo Luis Rezende Fernandes
 *
 * Declaracao de um Heap Binomial
 *
 */

#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////
//
// tBinomialHeapNode
// =================
//
template <class T>
struct tBinomialHeapNode : public tHeapNode<T>
{
	tBinomialHeapNode(T* key);
	virtual ~tBinomialHeapNode();

	void Link(tBinomialHeapNode<T>* node);

	tBinomialHeapNode<T>* Child;
	tBinomialHeapNode<T>* Parent;
	tBinomialHeapNode<T>* Sibling;

	int Degree;
};

//
// tBinomialHeapNode inline implementation
//
template <class T>
inline
tBinomialHeapNode<T>::tBinomialHeapNode(T* key)
	:  tHeapNode<T>(key),
		 Child(NULL),
		 Parent(NULL),
		 Sibling(NULL),
		 Degree(0)
{}

template <class T>
inline
tBinomialHeapNode<T>::~tBinomialHeapNode()
{
	tBinomialHeapNode<T>* n = Child;
	tBinomialHeapNode<T>* aux;
	while (n) {
		aux = n;
		n = n->Sibling;
		delete aux;
	}
}

template <class T>
inline void
tBinomialHeapNode<T>::Link(tBinomialHeapNode<T>* node)
{
	node->Parent = this;
	node->Sibling = this->Child;
	this->Child = node;
	this->Degree = this->Degree + 1;
}


//////////////////////////////////////////////////////////////////////
//
// tBinomialHeap
// =============
//
template <class T>
class tBinomialHeap : public tHeap<T>
{
 public:
	tBinomialHeap();
	virtual ~tBinomialHeap();

	// Operacoes de um heap
	virtual tStub* Insert(T* e);
	virtual T* Minimum() const;
	virtual T* ExtractMin();
	virtual void Union(tHeap<T>* heap);
	virtual void DecreaseKey(tStub* n);

 protected:
	void Merge(tBinomialHeap<T>* heap);

	tBinomialHeapNode<T>* Head;
};

//
// tBinomialHeap inline implementation
//
template <class T>
inline
tBinomialHeap<T>::tBinomialHeap()
	:	Head(NULL)
{}

template <class T>
inline
tBinomialHeap<T>::~tBinomialHeap()
{
	tBinomialHeapNode<T>* n = Head;
	tBinomialHeapNode<T>* aux;
	while (n) {
		aux = n;
		n = n->Sibling;
		delete aux;
	}
}

template <class T>
inline T*
tBinomialHeap<T>::Minimum() const
{
	if (Head == NULL)
		return NULL;

	tBinomialHeapNode<T>* min = Head;
	tBinomialHeapNode<T>* aux = Head->Sibling;

	while (aux != NULL) {
		if (aux->GetKey() < min->GetKey())
			min = aux;

		aux = aux->Sibling;
	}

	return min->Key;
}

template <class T>
inline void
tBinomialHeap<T>::Merge(tBinomialHeap<T>* heap)
{
	tBinomialHeapNode<T>* n1 = this->Head;
	tBinomialHeapNode<T>* n2 = heap->Head;
	tBinomialHeapNode<T>* n;

	heap->Head = NULL;
	delete heap;

	// 2o. heap eh vazio
	if (n2 == NULL)
		return;

	// 1o. heap eh vazio
	if (n1 == NULL) {
		this->Head = n2;
		return;
	}

	// se o grau da raiz 'n2' eh menor do que o grau de 'n1' entao ela
	// serah a nova cabeca de 'this'
	if (n2->Degree < n1->Degree) {
		n = n2;
		this->Head = n2;
		n2 = n2->Sibling;
	}
	else {
		n = n1;
		n1 = n1->Sibling;
	}

	while (n1 && n2) {
		while (n1 && n1->Degree <= n2->Degree) {
			n->Sibling = n1;
			n = n1;
			n1 = n1->Sibling;
		}

		if (n1) {
			while (n2 && n2->Degree <= n1->Degree) {
				n->Sibling = n2;
				n = n2;
				n2 = n2->Sibling;
			}
		}
	}

	if (n1)
		n->Sibling = n1;
	else if (n2)
		n->Sibling = n2;
}

template <class T>
inline void 
tBinomialHeap<T>::Union(tHeap<T>* heap)
{
	Merge((tBinomialHeap<T>*) heap);

	if (Head == NULL)
		return;

	tBinomialHeapNode<T>* nodePrev = NULL;
	tBinomialHeapNode<T>* node     = Head;
	tBinomialHeapNode<T>* nodeNext = node->Sibling;

	while (nodeNext) {
		if (node->Degree != nodeNext->Degree ||
				(nodeNext->Sibling && 
				 nodeNext->Sibling->Degree == node->Degree)) {
			nodePrev = node;
			node = nodeNext;
		}
		else if (node->GetKey() <= nodeNext->GetKey()) {
			node->Sibling = nodeNext->Sibling;

			// pendura 'nodeNext' em 'node'
			node->Link(nodeNext);
		}
		else {
			if (nodePrev == NULL)
				Head = nodeNext;
			else
				nodePrev->Sibling = nodeNext;

			// pendura 'node' em 'nodeNext'
			nodeNext->Link(node);

			node = nodeNext;
		}

		nodeNext = node->Sibling;
	}
}

template <class T>
inline tStub*
tBinomialHeap<T>::Insert(T* e)
{
	tBinomialHeap<T>* h = new tBinomialHeap<T>;
	tBinomialHeapNode<T>* n = new tBinomialHeapNode<T>(e);
	h->Head = n;
	Union(h);

	return n->Stub;
}

template <class T>
inline T* 
tBinomialHeap<T>::ExtractMin()
{
	tBinomialHeapNode<T>* n;
	tBinomialHeapNode<T>* minPrev = NULL;
	tBinomialHeapNode<T>* min = Head;

	if (min == NULL)
		return NULL;

	// encontra a raiz com menor chave
	n = min;
	while (n->Sibling) {
		if (n->Sibling->GetKey() < min->GetKey()) {
			minPrev = n;
			min = n->Sibling;
		}

		n = n->Sibling;
	}

	// retira a menor chave da lista de arvores desse heap
	if (minPrev == NULL)
		Head = min->Sibling;
	else
		minPrev->Sibling = min->Sibling;

	if (min->Child) {
		// cria um novo heap para incluir os filhos da menor raiz
		tBinomialHeap<T>* heap = new tBinomialHeap<T>;

		tBinomialHeapNode<T>* aux;

		// preenche a lista de arvores do novo heap com os filhos da menor
		// raiz (invertendo a ordem dos filhos)
		heap->Head = min->Child;
		min->Child = NULL;
		n = heap->Head->Sibling;
		heap->Head->Sibling = NULL;
		heap->Head->Parent = NULL;

		while (n) {
			aux = n;
			n = n->Sibling;
			aux->Sibling = heap->Head;
			heap->Head = aux;
			aux->Parent = NULL;
		}

		// Insere (une) o novo heap
		Union(heap);
	}

	// desaloca o noh da menor raiz e retorna sua chave
	T* ret = min->Key;
	delete min;
	return ret;
}

template <class T>
void
swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <class T>
inline void 
tBinomialHeap<T>::DecreaseKey(tStub* st)
{
	tBinomialHeapNode<T>* pnode;
	tBinomialHeapNode<T>* node = (tBinomialHeapNode<T>*) st->Node;

	pnode = node->Parent;

	while (pnode && pnode->GetKey() > node->GetKey()) {
		swap(node->Key, pnode->Key);
		swap(node->Stub, pnode->Stub);
		swap(node->Stub->Node, pnode->Stub->Node);

		node = pnode;
		pnode = pnode->Parent;
	}
}


#endif //__BINOMIAL_H
