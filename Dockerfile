FROM ubuntu:22.04@sha256:19478ce7fc2ffbce89df29fea5725a8d12e57de52eb9ea570890dc5852aac1ac

RUN apt-get update && \
    apt-get install -y gcc gdb
RUN apt-get install netcat vim python3 tmux -y
RUN apt-get update
RUN apt-get install python3-pip -y
RUN pip3 install pwntools
