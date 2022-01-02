
default:
	microk8s.kubectl apply -f mandelbrot.yaml
	sleep 5
	microk8s.kubectl get pods
	microk8s.kubectl describe jobs/mandelbrot

import:
	docker save mandelbrot > mandelbrot.tar
	microk8s.ctr --namespace k8s.io image import mandelbrot.tar
	rm mandelbrot.tar
	microk8s ctr images ls

query:
	microk8s.kubectl get pods

describe:
	microk8s.kubectl describe pod mandelbrot

delete:
	microk8s.kubectl delete -f mandelbrot.yaml

