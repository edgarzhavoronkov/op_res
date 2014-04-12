main: bin/main.o
	g++ bin/main.o -o main
bin/main.o: src/main.cpp
	mkdir -p bin
	g++ -c src/main.cpp -o bin/main.o
clean:
	rm -r bin
	rm main
