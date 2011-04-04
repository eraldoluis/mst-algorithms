OBJS = \
	prim.o \
	kruskal.o \
	graph.o \
	disjointset.o

CCOPTS = -Wall -g
GCOMP = g++ $(CCOPTS)

all : test kruskal bprim fprim

test : $(OBJS) test.o *.h
	$(GCOMP) -o test $(OBJS) test.o

kruskal : $(OBJS) test_kruskal.o *.h
	$(GCOMP) -o kruskal $(OBJS) test_kruskal.o

bprim : $(OBJS) test_bprim.o *.h
	$(GCOMP) -o bprim $(OBJS) test_bprim.o

fprim : $(OBJS) test_fprim.o *.h
	$(GCOMP) -o fprim $(OBJS) test_fprim.o

%.o : %.cpp %.h
	$(GCOMP) -c $<

%.o : %.cpp
	$(GCOMP) -c $<

clean :
	rm -f $(OBJS) *~ \
	test.o test \
	test_kruskal.o kruskal \
	test_bprim.o bprim \
	test_fprim.o fprim
