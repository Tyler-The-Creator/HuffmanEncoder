/*
 * HuffmanTree.h
 *
 *  Created on: Apr 22, 2017
 *      Author: Tyler Pillay
 */

#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

#include <unordered_map>
#include <memory>
#include <vector>

#include "HuffmanNode.h"

namespace plltyl003 {

    // HuffmanTree class has methods to compress data, build tree etc.
	class HuffmanTree {
		private:
			std::unordered_map<char, int> uMap;

			std::unordered_map<char, std::string> codeMap;

			std::string in, out, buffStr, bitStr, uPack;

			int nBits;

			std::shared_ptr<plltyl003::HuffmanNode> rNode;

			std::vector<char> vLine;
		public:
		    // default constructor
			HuffmanTree();

			// destructor
			~HuffmanTree();

			// copy constructor
            HuffmanTree(const HuffmanTree& rhs);

            // copy assignment operator
            HuffmanTree& operator=(const HuffmanTree& rhs);

            // move constructor
            HuffmanTree(HuffmanTree&& rhs);

            // move assignment operator
            HuffmanTree& operator=(HuffmanTree&& rhs);

            // return root node of tree
			std::shared_ptr<plltyl003::HuffmanNode> getRoot() const;

			// return unordered map with letter frequencies
			std::unordered_map<char, int> getMap() const;

			// return code table
			std::unordered_map<char, std::string> getCodeTable() const;

            // return encoded string
            std::string getEncoding() const;

            // return compressed data
            std::string getPacked() const;

            // return decompressed data
            std::string getUnpacked() const;

			// read in string from textfile
			void readTextfile(std::string inFile);

			 // fill unordered_map
			void fillMap(std::string s);

			// build the tree using unordered_map
			void buildHuffTree(std::unordered_map<char, int> m);

			// build code table
            void buildHuffCodeTable(std::shared_ptr<plltyl003::HuffmanNode>, std::string s);

            // encode data into string of bits
            void encode();

            // pack encoding into bitstream
            void compress();

            // write code table to .hdr file
			void outputTable(std::string o);

			// write encoded string to .dat file
			void outputEncoding(std::string o);

			// write compressed string to .bin file
			void outputPacked(std::string o);

			// read in compressed file
			void readPacked();

			// decode packed bitstream
			void unpack(std::string s, int n);

			// print method to test map filling after file extraction
			void printMap();

			// print method to test map filling after pq manipulation
			void printMap(std::unordered_map<char, std::string> cMap);
	};

}

#endif /* HUFFMANTREE_H_ */
