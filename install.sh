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

if brew ls --versions sdl2 > /dev/null; then
  echo "\033[38;5;82m✅ sdl_2 already install\033[0m"
else
  brew install sdl2
fi

if brew ls --versions sdl2_mixer > /dev/null; then
  echo "\033[38;5;82m✅ sdl_2_mixer already install\033[0m"
else
  brew install sdl2_mixer
fi

if brew ls --versions sdl2_ttf > /dev/null; then
  echo "\033[38;5;82m✅ sdl_2_ttf already install\033[0m"
else
  brew install sdl2_tff
fi
