FROM ubuntu:19.10

WORKDIR /usr/src/app/

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install g++ valgrind cmake less -y

COPY . .
