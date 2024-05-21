FLAGS=-Wall -O3 -g
#FLAGS=-Wall -g
SIMD_O=mandelbrot_simd.o
SIMD=-DSIMD $(SIMD_O)


default: $(SIMD_O)
	gcc -o mandelbrot mandelbrot.c $(SIMD) $(FLAGS)

mandelbrot_simd.o: mandelbrot_simd.asm
	../../naken_asm/naken_asm -l -type elf -o mandelbrot_simd.o mandelbrot_simd.asm

clean:
	rm -f mandelbrot *.o
	@echo "Clean!"

