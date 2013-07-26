# Cocoa2dx - LPP:

Przepisanie gry z XNA (C#), które robiło problemy w przypadku urządzeń mobilnych na
Cocos2DX (C++).

## Linux - Kompilacja:

```
$ wget http://cocos2d-x.googlecode.com/files/cocos2d-x-2.1.4.zip
$ unzip cocos2d-x-2.1.4.zip
$ cd cocos2d-x-2.1.4
$ make PLATFORM=linux DEBUG=1 all
$ make PLATFORM=linux DEBUG=0 all
# Pewnie będą potrzebne zależności. U mnie udało się instalując jedynie glew (Chakra Linux),
# w przypadku debianowatych wystarczy zainstalować paczki:
# libx11-dev libxmu-dev libglu1-mesa-dev libgl2ps-dev libxi-dev libglfw-dev
# g++ libzip-dev libcurl4-gnutls-dev libfontconfig1-dev libsqlite3-dev
# libglew*-dev


# Ustawić w Project.Linux/Makefile COCOA_ROOT na odpowiedni katalog.
# cd <katalog_z_projektem>
# make project_mkf
# make
```

## Linux - Uruchamianie gry:

```
cd <katalog_z_projektem>
./run.sh
```
