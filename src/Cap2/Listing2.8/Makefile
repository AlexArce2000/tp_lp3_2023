Listing2.8: app.c test.c
	gcc -c test.c
	gcc -c app.c

	
	ar cr libtest.a test.o

	@mkdir -p ../../../build/Cap2/Listing2.8
	gcc -o ../../../build/Cap2/Listing2.8/app app.o -L. -ltest
	rm *.o
	rm *.a