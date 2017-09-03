# makefile for assignment 3: Huffman Tree Encoder

# flags
CC=g++         		# the compiler
CPP=--std=c++11 	#  specify c++11

# make executable
huffencode: Driver.o HuffmanNode.o HuffmanTree.o
	$(CC) Driver.o HuffmanNode.o HuffmanTree.o -o huffencode $(CPP)

# make binary files
HuffmanNode.o: HuffmanNode.cpp HuffmanNode.h
	$(CC) -c HuffmanNode.cpp $(CPP)

HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h
	$(CC) -c HuffmanTree.cpp $(CPP)
	
Driver.o: Driver.cpp HuffmanTree.h HuffmanNode.h
	$(CC) -c Driver.cpp $(CPP)


# test rule
test: HuffmanTest.o HuffmanNode.o HuffmanTree.o
	$(CC) HuffmanTest.o HuffmanNode.o HuffmanTree.o -o test $(CPP)
	
HuffmanTest.o: HuffmanTest.cpp HuffmanTest.h
	$(CC) -c HuffmanTest.cpp $(CPP)
	
# make clean
clean:
	@rm -f *.bin *.hdr *.dat *.o huffencode test