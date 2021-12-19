
default:
	cd build && make

clean:
	@rm -f build/*.o test mandelbrot
	@echo "Clean!"

