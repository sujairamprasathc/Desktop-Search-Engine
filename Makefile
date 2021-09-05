CFLAGS = --std=c++17 -lstdc++fs

all: bin bin/text-crawler bin/indexer bin/interface

bin/text-crawler: Text-Crawler/main.cpp
	g++ $^ -o $@ $(CFLAGS)

bin/indexer: Indexer/main.cpp bin/DocumentIDManager.o bin/FileConstants.o bin/Indexer.o bin/hash.o
	g++ $^ -o $@ $(CFLAGS)

bin/interface: Interface/Interface.cpp bin/DocumentIDManager.o bin/FileConstants.o
	g++ $^ -o $@ $(CFLAGS) -I ./Indexer

bin/DocumentIDManager.o: Indexer/DocumentIDManager.cpp
	g++ $^ -c -o $@ $(CFLAGS)

bin/FileConstants.o: Indexer/FileConstants.cpp
	g++ $^ -c -o $@ $(CFLAGS)

bin/Indexer.o: Indexer/Indexer.cpp
	g++ $^ -c -o $@ $(CFLAGS)

bin/hash.o: Indexer/hash.cpp
	g++ $^ -c -o $@ $(CFLAGS)

bin:
	mkdir bin

clean:
	rm -rf bin
