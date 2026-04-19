all: Dockerfile
	docker images 2>&1 | grep -qe debian/aso || docker build -t debian/aso:r1 .

run-nox:
	docker run -it --rm \
		-h aso \
		-v /tmp:/tmp/tmp:rw \
		-v `pwd`/..:/root/aso --name aso debian/aso:r1

run:
	xhost +local:root
	docker run -it --rm \
		-h aso \
		-e DISPLAY=${DISPLAY} \
		--security-opt seccomp=unconfined \
		--cap-add=SYS_PTRACE \
		-v /tmp/.X11-unix:/tmp/.X11-unix:rw \
		-v /tmp:/tmp/tmp:rw \
		-v `pwd`/..:/root/aso --name aso debian/aso:r1

run-gdb:
	docker exec -it aso bash

.PHONY: all run run-nox run-gdb

clean:
	docker rmi -f debian/aso:r1 || true