set -e
mkdir -p cmake-build-release
cd cmake-build-release
conan install .. --install-folder .
cmake -DCMAKE_BUILD_TYPE=Release ..
make
