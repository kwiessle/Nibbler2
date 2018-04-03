#!/bin/sh

git submodule init;
git submodule update;

cmake --version;

if [[ $? == 127 ]]; then
	echo "Plz, install cmake" ;
	exit ;
fi

(cd lib/glfw/glfw && cmake . && make);
(cd lib/sfml/sfml && cmake . && make);

brew install sdl2
brew install sdl2_mixer
brew install sdl2_ttf
