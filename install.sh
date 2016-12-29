
set -ex

git submodule update --init --recursive
scripts/installDependencies.sh
mkdir build
cd build
cmake ..
make all
