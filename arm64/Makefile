FLAGS=-Wall -O3 -g
#FLAGS=-Wall -g
SIMD=mandelbrot_simd.o

default: $(SIMD)
	gcc -o mandelbrot mandelbrot.c $(SIMD) $(FLAGS)

mandelbrot_simd.o: mandelbrot_simd.asm
	../../naken_asm/naken_asm -l -type elf -o mandelbrot_simd.o mandelbrot_simd.asm

clean:
	rm -f mandelbrot *.o
	@echo "Clean!"

