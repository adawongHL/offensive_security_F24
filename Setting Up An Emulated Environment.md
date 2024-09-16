The following instructions set up a Dockerized solution for emulating the exact Linux OS running on the remote challenge servers locally on your machine. The Docker container will let us run the challenges and develop our solver locally while also connecting to the remote server (assuming it is run on your host machine with the NYU VPN running). _This solution works for ARM macOS as well, thanks to [Rosetta](https://en.wikipedia.org/wiki/Rosetta_(software))!_

## Instructions

1. Install [Docker](https://docs.docker.com/get-started/get-docker/). For ARM Macs, install Docker Desktop for the Apple Silicon chip.
2. Start Docker: [start the daemon on the command line](https://docs.docker.com/engine/daemon/start/) or open the Docker Desktop app
3. Add to the [[Dockerfile]] provided in this repo if you would like to install any additional Linux utilities within your Docker image. Some core utilities like `pwntools` are already included.
4. Navigate to this directory in your terminal
5. Run `docker build -t offsec . --platform linux/amd64`. This builds the Docker image locally and names it `offsec`. _Note that you must include `--platform linux/amd64` for ARM machines_.
6. Run the container with `docker run --rm -it --platform linux/amd64 offsec bash`
	1. `--rm` removes the container once we exit. This is nice to prevent overloading our system with a bunch of dangling containers. Feel free to remove it if you want to keep the container and attach to it later
	2. `-it` provides an interactive terminal so we can interact with the container
	3. `--platform linux/amd64` is again necessary when translating architectures, for those of us on an ARM machine
	4. `offsec` is the image name, which we defined in the previous command
	5. `bash` spawns `/bin/bash` for us upon entry to the container
7. Feel free to experiment with `-v $(pwd):/root`, which mounts the current directory of your host machine to `~/` in the container. This is really helpful for loading binaries that we download from the class site into the container so we can run and operate on them.
	1. Which turns your  complete build command to:
		1. `docker run --rm -it --platform linux/amd64 -v $(pwd):/root offsec bash`

With this setup, we can easily spin up a container and start writing solver scripts. We can also run the binaries, which is extremely helpful. _If you get a `Permission denied` error, try adjusting the file permissions with `chmod +x <filename>`_.

## Benefits

The benefits of this strategy include:
1. Being able to connect to the challenge servers using our host machine (with NYU VPN)
2. Being able to mount and run local files, including solver scripts and the binaries, even on an ARM machine
3. Not having to rely on cloud services
4. Having the exact same glibc version as the challenge server (the `libc.so.6` files on the challenge site should have identical hashes to the `/lib/x86_64-linux-gnu/libc.so.6` file in the container). This is nice for the `glibc` challenges in week0 and for later challenges in the exploitation unit.