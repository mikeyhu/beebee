FROM ubuntu:19.10

WORKDIR /usr/src/app/

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install sudo python3 python3-pip g++ valgrind cmake less -y
RUN update-alternatives --install /usr/bin/pip pip /usr/bin/pip3 1
RUN pip install conan
RUN conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"
COPY . .
CMD ./build-valgrind.sh