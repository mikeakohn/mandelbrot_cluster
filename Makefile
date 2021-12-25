
default:
	cd build && make

clean:
	@rm -f build/*.o test mandelbrot create_coordinates
	@echo "Clean!"

