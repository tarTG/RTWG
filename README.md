# RTWG
[![Build Status](https://travis-ci.org/tarTG/RTWG.svg?branch=master)](https://travis-ci.org/tarTG/RTWG)

The Real-Time World Generation project aims to provide a tool for world/terrain generation based on procedural algorithms and cellular automata simulation.
This is the result of my Masterthesis on the University of Applied Sciences in Rosenheim. The Thesis will be added, when its done.

## Demo Video

[![screenshots/3DMap.png](http://img.youtube.com/vi/lntbdItSFtg/0.jpg)](http://www.youtube.com/watch?v=lntbdItSFtg)

## Features

- Start world is generated thought prozedural algorithmen or imported heightmap
- Realtime simulation and manipulation of water, wind, soil, moist, ice, plate-tectonic, temperature and the resulting climate zones
- 2D and 3D representation
- PNG Export of all data

## Requirements

- OpenGL 4.+
- a C++14 compiler
- currently only tested under Debian/Ubuntu-based Linux

## Installation

- go to the RTWG folder
- sudo sh install.sh
- start the program with run.sh

If you start the program, you have to wait for a short time, until the  heightmap is generated.


## Controls

**Key** | **Description**
-----|------
Tab | toogle between 3D / 2D
w/s/a/d | camera movement in 3D
Shift + Mouse | camera movement in 3D


Simulation view can be changed on top "General" Bar (Current Display)

A detailed description of all parameters can be found in the [wiki](https://github.com/tarTG/RTWG/wiki).

## Example images

Here is an example that is generated throught this tool.

### Heigthmap

![](screenshots/heightmap.png?raw=true)

### Climate zones

![](screenshots/Climat.png?raw=true)

### 3D representation

![](screenshots/3DMap.png?raw=true)


## Further plans

- More simulations (like water temperature or global water movements)
- Direct manipulation (like adding water on a specific place)
- Faster Plate tectonic(via Shaders, faster but less accurate)
- More manipulation options
- a config file for startup parameters

## Credits
- Maxis SimEarth where i got the original idea
- original platec developer Lauri Viitanen ( http://sourceforge.net/projects/platec/ )
- water errosion is heavily inspired by https://github.com/pyalot/craftscape
- some ideas are taken from https://github.com/Mindwerks/worldengine
- a lot of world generation tools out there, where i got a lot of interessting ideas
