default:
	docker build -t mandelbrot:local .
	docker image tag mandelbrot:local localhost:32000/mandelbrot:local

push:
	docker push localhost:32000/mandelbrot:local

run:
	docker run --rm -it mandelbrot:local /bin/bash

