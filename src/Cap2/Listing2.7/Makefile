Listing2.7: test.c app.c
	gcc -c test.c


	ar cr libtest.a test.o
	gcc -c app.c 

	@mkdir -p ../../../build/Cap2/Listing2.7/

	gcc -o ../../../build/Cap2/Listing2.7/app app.o -L. -ltest


	rm *.o

	rm *.a