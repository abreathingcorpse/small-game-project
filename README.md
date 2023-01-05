# small-game-project
This is a repo for a small game project, which is intended to be made using SFML &amp; C++

To build the main.cpp on Linux one will need to follow the "SFML and Linux" Tutorial:
https://www.sfml-dev.org/tutorials/2.5/start-linux.php

If one already understands it, then the following couple of commands are the ones that
one should actually use:

$ g++ -c main.cpp
$ g++ main.o -o Small_Game -lsfml-graphics -lsfml-window -lsfml-system

One may then run it like so:

$ ./Small_Game
