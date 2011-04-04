#ifndef __HEAP_H
#define __HEAP_H

/*
 * heap.h
 *
 * Outubro de 2003.
 *
 * Eraldo Luis Rezende Fernandes
 *
 * Declaracao do tipo abstrato de dados 'heap'
 *
 */

#include <stdio.h>


//////////////////////////////////////////////////////////////////////
//
// tStub
// =====
//
// Objeto de referencia para um noh
//
struct tStub
{
	void* Node;
};


//////////////////////////////////////////////////////////////////////
//
// tHeapNode
// =========
//
template <class T>
struct tHeapNode
{
	tHeapNode(T* key);
	virtual ~tHeapNode();

	const T& GetKey() const;

	T* Key;
	tStub* Stub;
};


//
// tHeapNode inline implementation
//
template <class T>
inline
tHeapNode<T>::tHeapNode(T* key)
	:  Key(key),
		 Stub(new tStub)
{
	Stub->Node = this;
}

template <class T>
inline
tHeapNode<T>::~tHeapNode()
{
	delete Stub;
}

template <class T>
inline const T&
tHeapNode<T>::GetKey() const
{
	return *Key;
}


//////////////////////////////////////////////////////////////////////
//
// tHeap
// =====
//
template <class T>
class tHeap
{
 public:
	virtual ~tHeap() {}

	// Operacoes de um heap
	virtual tStub* Insert(T* e) =0;
	virtual T* Minimum() const =0;
	virtual T* ExtractMin() =0;
	virtual void Union(tHeap<T>* heap) =0;
	virtual void DecreaseKey(tStub* st) =0;
};


#endif //__HEAP_H
