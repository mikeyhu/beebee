set -e
docker build -t beebee-valgrind .
docker run -it beebee-valgrind