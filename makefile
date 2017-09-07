RT.exe : main.o objects.o utils.o scene.o camera.o renderer.o texture.o
	g++ main.o objects.o utils.o scene.o camera.o renderer.o texture.o `pkg-config opencv --cflags --libs` -o RT.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o -std=c++11

utils.o: utils.cpp
	g++ -c utils.cpp -o utils.o -std=c++11

camera.o: camera.cpp
	g++ -c camera.cpp -o camera.o -std=c++11

scene.o: scene.cpp
	g++ -c scene.cpp -o scene.o -std=c++11

texture.o: texture.cpp
	g++ -c texture.cpp -o texture.o -std=c++11

objects.o: objects.cpp
	g++ -c objects.cpp -o objects.o -std=c++11

renderer.o: renderer.cpp
	g++ -c renderer.cpp -o renderer.o -std=c++11
