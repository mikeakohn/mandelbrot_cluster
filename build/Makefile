VPATH=../src
CFLAGS=-Wall -O3
CPP=g++

default:
	$(CPP) -c ../src/write_bmp.cxx $(CFLAGS)
	$(CPP) -o ../mandelbrot ../src/mandelbrot.cxx write_bmp.o $(CFLAGS)
	$(CPP) -o ../create_coordinates ../src/create_coordinates.cxx $(CFLAGS)

test:
	$(CPP) -o ../test ../src/test.cxx $(CFLAGS)

clean:
	@rm -f test mandelbrot *.o out.bmp
	@echo "Clean!"

