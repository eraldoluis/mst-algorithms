#ifndef __DISJOINTSET_H
#define __DISJOINTSET_H

/*
 * disjointset.h
 *
 * Eraldo Luis Rezende Fernandes
 *
 * Outubro de 2003.
 *
 * Declaracao de estruturas para representar conjuntos disjuntos
 * (particoes)
 *
 */


//////////////////////////////////////////////////////////////////////
//
// tDisjointSet
// ============
//
// Conjunto disjunto (representa um elemento de um conjunto ao mesmo
// tempo)
//
class tDisjointSet
{
 public:
	tDisjointSet();

	// une o conjunto desse elemento com o conjunto de 'set'
	void Union(tDisjointSet* set);

	// retorna o representante do conjunto desse elemento
	tDisjointSet* FindSet();

 protected:
	int Rank;
	tDisjointSet* Parent;
};


#endif //__DISJOINTSET_H
