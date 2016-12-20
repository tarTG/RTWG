#!/bin/bash
set -ex


add-apt-repository -y ppa:pyglfw/pyglfw && sudo apt-get update -qq && sudo apt-get install -y --no-install-recommends g++ libmesa-dev libglfw3-dev libxrandr-dev libxi-dev libxxf86vm-dev libxcursor1 libxcursor-dev libxinerama-dev libnoise-dev libglm-dev libdevil-dev libdevil-dev

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
    
