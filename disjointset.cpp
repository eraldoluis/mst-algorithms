/*
 * disjointset.cpp
 *
 * Eraldo Luis Rezende Fernandes
 *
 * Outubro de 2003.
 *
 * Implementacao de estruturas para representar conjuntos disjuntos
 * (particoes)
 *
 */

#include "disjointset.h"

//
// tDisjointSet implementation
//
tDisjointSet::tDisjointSet() :
	Rank(0),
	Parent(this)
{}

void 
tDisjointSet::Union(tDisjointSet* set)
{
	tDisjointSet* r1 = this->FindSet();
	tDisjointSet* r2 = set->FindSet();

	if (r1 == r2)
		return;

	if (r1->Rank > r2->Rank)
		r2->Parent = r1->Parent;
	else {
		r1->Parent = r2;

		if (r1->Rank == r2->Rank)
			++(r2->Rank);
	}
}

tDisjointSet* 
tDisjointSet::FindSet()
{
	if (this != Parent)
		Parent = Parent->FindSet();
	return Parent;
}
