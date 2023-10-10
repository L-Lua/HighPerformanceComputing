NEW1  := MMult_naive
NEW2  := MMult_openblas
NEW3  := MMult_pthread
NEW4  := MMult_openmp

CC         := gcc
LINKER     := $(CC)
CFLAGS     := -Wall -g
LDFLAGS    := -Wall -lm -fopenmp -pthread -lopenblas

UTILS      := copy_matrix.o \
              compare_matrices.o \
              random_matrix.o \
              dclock.o \
              REF_MMult.o \
              print_matrix.o \
	          parameters.h
	          
REFTEST    := test_ref_MMult.o
TEST       := test_MMult.o
TEST_OBJS   := MMult_naive.o MMult_openblas.o MMult_pthread.o MMult_openmp.o
TARGET     := MMult_1.x MMult_2.x MMult_3.x MMult_4.x


all:
	make $(UTILS)
	make $(TEST_OBJS)
	rm -f *.x
	make $(TARGET)

MMult_naive.o: MMult_naive.c
	$(CC) $(CFLAGS) -c $< -o $@
	
MMult_openblas.o: MMult_openblas.c
	$(CC) $(CFLAGS) -lopenblas -c $< -o $@
	
MMult_pthread.o: MMult_pthread.c
	$(CC) $(CFLAGS) -pthread -c $< -o $@

MMult_openmp.o: MMult_openmp.c
	$(CC) $(CFLAGS) -fopenmp -c $< -o $@

test_ref_MMult.o: test_ref_MMult.c parameters.h

MMult_1.x: $(TEST) $(NEW1).o $(UTILS)
	$(LINKER) $(TEST) $(NEW1).o $(UTILS) $(LDFLAGS) -o $@
	
MMult_2.x: $(TEST) $(NEW2).o $(UTILS)
	$(LINKER) $(TEST) $(NEW2).o $(UTILS) $(LDFLAGS) -o $@
	
MMult_3.x: $(TEST) $(NEW3).o $(UTILS)
	$(LINKER) $(TEST) $(NEW3).o $(UTILS) $(LDFLAGS) -o $@

MMult_4.x: $(TEST) $(NEW4).o $(UTILS)
	$(LINKER) $(TEST) $(NEW4).o $(UTILS) $(LDFLAGS) -o $@

export OMP_NUM_THREADS=12
export GOTO_NUM_THREADS=1

run:
	make all
	
	echo "version = '$(NEW1)';" > output_$(NEW1).m
	./MMult_1.x >> output_$(NEW1).m
	cp output_$(NEW1).m output_new1.m
	
	echo "version = '$(NEW2)';" > output_$(NEW2).m
	./MMult_2.x >> output_$(NEW2).m
	cp output_$(NEW2).m output_new2.m
	
	echo "version = '$(NEW3)';" > output_$(NEW3).m
	echo $$OMP_NUM_THREADS
	./MMult_3.x >> output_$(NEW3).m
	cp output_$(NEW3).m output_new3.m

	echo "version = '$(NEW4)';" > output_$(NEW4).m
	echo $$OMP_NUM_THREADS
	./MMult_4.x >> output_$(NEW4).m
	cp output_$(NEW4).m output_new4.m

clean:
	rm -f *.o *~ core *.x

cleanall:
	rm -f *.o *~ core *.x output*.m *.eps *.png *.jpg

