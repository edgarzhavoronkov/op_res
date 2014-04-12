main: bin/main.o
	g++ main.o -o main
main.o: src/main.cpp
	mkdir -p bin
	g++ -c main.cpp -o main.o
clean:
	rm -r bin
	rm main