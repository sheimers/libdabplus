CC=gcc
CFLAGS=-O3 -fPIC -W -Wall -g
LDFLAGS=-lm -lfftw3 -lpthread -g

CFLAGS+=$(shell pkg-config --cflags librtlsdr)
LDFLAGS+=$(shell pkg-config --libs librtlsdr)

# Uncomment the following line to use the fast, but x86-only Spiral Viterbi function.
#ENABLE_SPIRAL_VITERBI=yes

ifdef ENABLE_SPIRAL_VITERBI
  CFLAGS+=-DENABLE_SPIRAL_VITERBI -msse2 -msse3 -std=gnu99 
  VITERBI_OBJS=viterbi_spiral.o viterbi_spiral_sse16.o
else
  VITERBI_OBJS=viterbi.o
endif


OBJS=wf_sync.o wf_prstables.o wf_maths.o fic.o misc.o dab_tables.o input_wf.o depuncture.o input_sdr.o sdr_fifo.o sdr_sync.o dab.o $(VITERBI_OBJS)

all: dab2eti eti2mpa libdabtoolsplusplus

dab2eti: $(OBJS) dab2eti.o
	$(CC) -o dab2eti dab2eti.o $(OBJS) $(LDFLAGS)

eti2mpa: eti2mpa.o
	$(CC) -o eti2mpa eti2mpa.o

libdabtoolsplusplus: $(OBJS)
	g++ -c -fPIC libdabtoolscplus.cpp -o libdabtoolscplus.o
	g++ -Wall -shared -fPIC -o libdabtools++.so libdabtoolscplus.o $(OBJS)

clean:
	rm -f dab2eti eti2mpa *.o *.so *~
