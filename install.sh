
set -ex

submodule update --init --recursive
scipts/installDependencies.sh
mkdir build
cd build
cmake ..
make all
