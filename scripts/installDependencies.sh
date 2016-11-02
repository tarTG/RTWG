#!/bin/bash
set -ex

apt-get -qq update
#install lib noise
apt-get install -y libnoise-dev
#install glfw3
add-apt-repository -y ppa:pyglfw/pyglfw && sudo apt-get update -qq && sudo apt-get install -y --no-install-recommends libglfw3-dev libxrandr-dev libxi-dev libxxf86vm-dev libxcursor1
#install glm
apt-get install -y libglm-dev

#install gl3w
mkdir gl3w
cd gl3w
wget https://github.com/skaslev/gl3w/archive/master.zip 
unzip master.zip
cd gl3w-master
python3 gl3w_gen.py
mkdir build
cd build
cmake ..
make
sudo make install
cd ..
cd ..
cd ..

#install anttweak bar
mkdir anttweakbar
cd anttweakbar
wget 'https://sourceforge.net/projects/anttweakbar/files/AntTweakBar_116.zip' 
unzip AntTweakBar_116.zip
cd AntTweakBar
cd src
make
cd ..
cd include 
cp AntTweakBar.h /usr/local/include
cd ..
cd lib
cp libAntTweakBar.so /usr/local/lib/
cd ..
cd ..
cd ..
    

#install DevIL
apt-get install libdevil-dev