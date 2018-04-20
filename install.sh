#!/bin/sh

echo "📡 \033[36;1mDownloading archive...\033[0m"
mkdir -p assets
curl -o ./assets.zip -s https://transfer.sh/oEyke/assets.zip
unzip -q ./assets.zip  -d ./assets
rm -rf  assets/__MACOSX
cp -R assets/assets/* assets
rm -rf assets/assets
rm ./assets.zip
echo "\033[38;5;82m✅ Assets downloaded\033[0m"

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
  echo "\033[38;5;82m✅ sdl2 already install\033[0m"
else
  brew install sdl2
fi

if brew ls --versions sdl2_mixer > /dev/null; then
  echo "\033[38;5;82m✅ sdl2_mixer already install\033[0m"
else
  brew install sdl2_mixer
fi

if brew ls --versions sdl2_ttf > /dev/null; then
  echo "\033[38;5;82m✅ sdl2_ttf already install\033[0m"
else
  brew install sdl2_tff
fi

if brew ls --versions glew > /dev/null; then
  echo "\033[38;5;82m✅ glew already install\033[0m"
else
  brew install glew
fi

if brew ls --versions freeglut > /dev/null; then
  echo "\033[38;5;82m✅ freeglut already install\033[0m"
else
  brew install freeglut
fi
