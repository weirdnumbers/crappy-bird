all:
	g++ main.cpp Game.cpp Bird.cpp Wall.cpp Texture_manager.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
