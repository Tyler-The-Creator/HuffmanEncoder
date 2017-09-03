/*
 * Driver.cpp
 *
 *  Created on: Apr 18, 2017
 *      Author: Tyler Pillay
 */

#include "HuffmanTree.h"
#include "HuffmanNode.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <memory>

using namespace std;
/*
void clear(void) {
	system("clear");
}
*/
int main(int argc, char * argv[]) {
/*
    clear();
*/
	string in, outT, outE, outP;

	in = "input.txt";
	outT = "output.hdr";
    outE = "output.dat";
	outP = "output.bin";
/*
	stringstream ss;
	ss << "Command line args must be entered in the following format:" << "\n" << "./huffencode <input_file> <output_file>";
	string command = ss.str();

	if (argc != 3) {
		cout << "Incorrect command line arguments provided!" << endl;
		cout << command << endl;
		return 0;
	}
	else if (string(argv[1]).find('.') == true || string(argv[2]).find('.') == true) {
		cout << "Incorrect command line arguments provided!" << endl;
		cout << command << endl;
		cout << "File names must not have a file extension." << endl;
		return 0;
	}
	else {
		in = string(argv[1]) + ".txt";
		outT = string(argv[2]) + ".hdr";    // code table
		outE = string(argv[2]) + ".dat";    // encoded data
		outP = string(argv[2]) + ".bin";    // packed bitstream
	}
*/
	using namespace plltyl003;

	// create instance of HuffmanTree class
	HuffmanTree huff;

	// read in data from text file
	huff.readTextfile(in);

	// construct tree
	unordered_map<char, int> map = huff.getMap();
	huff.buildHuffTree(map);

    // construct code table
    shared_ptr<plltyl003::HuffmanNode> rootNode = huff.getRoot();
	huff.buildHuffCodeTable(rootNode, "");
	rootNode = nullptr;

	// encode data
	huff.encode();

	// compress to string of bits
	huff.compress();

	// write code table to output file
	huff.outputTable(outT);

    // write encoding to file
    huff.outputEncoding(outE);

	// write packed bitsream to file
	huff.outputPacked(outP);

	// unpack compressed data
	huff.readPacked();

	// test to check if map is filled properly
	//huff.printMap();

	return 0;
}
