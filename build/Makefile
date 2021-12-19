
CFLAGS=-Wall -O3

default:
	g++ -o test test.cxx $(CFLAGS)
	g++ -c write_bmp.cxx $(CFLAGS)
	g++ -o mandelbrot mandelbrot.cxx write_bmp.o $(CFLAGS)

clean:
	@rm -f test mandelbrot *.o out.bmp
	@echo "Clean!"

