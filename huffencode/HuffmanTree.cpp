/*
 * HuffmanTree.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: Tyler Pillay
 */

#include "HuffmanTree.h"
#include "HuffmanNode.h"

#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
using namespace plltyl003;

    /************************HUFFMAN_TREE_CLASS***************************/

    // default constructor
	HuffmanTree::HuffmanTree() {
        uMap.clear();
        codeMap.clear();
        in = "";
        out = "";
        buffStr = "";
        bitStr = "";
        uPack = "";
        nBits = 0;
		rNode = nullptr;
		vLine.clear();
	}

	// destructor
	HuffmanTree::~HuffmanTree() {
		rNode = nullptr;
	}

    // copy constructor
    HuffmanTree::HuffmanTree(const HuffmanTree & rhs) : uMap(rhs.uMap), codeMap(rhs.codeMap), in(rhs.in), out(rhs.out), buffStr(rhs.buffStr), bitStr(rhs.bitStr), uPack(rhs.uPack), nBits(rhs.nBits), rNode(rhs.rNode), vLine(rhs.vLine) {
    };

    // copy assignment operator
    HuffmanTree & HuffmanTree::operator=(const HuffmanTree & rhs) {
        if(this != &rhs){
            uMap = rhs.uMap;
            codeMap = rhs.codeMap;
            in = rhs.in;
			out = rhs.out;
			buffStr = rhs.buffStr;
			bitStr = rhs.bitStr;
			uPack = rhs.uPack;
			nBits = rhs.nBits;
			rNode = rhs.rNode;
			vLine = rhs.vLine;
        }
		return *this;
    }

    // move constructor
    HuffmanTree::HuffmanTree(HuffmanTree && rhs) : uMap(move(rhs.uMap)), codeMap(move(rhs.codeMap)), in(move(rhs.in)), out(move(rhs.out)), buffStr(move(rhs.buffStr)), bitStr(move(rhs.bitStr)), uPack(move(rhs.uPack)), nBits(move(rhs.nBits)), rNode(move(rhs.rNode)), vLine(move(rhs.vLine)) {
        rhs.rNode = nullptr;
    }

    // move assignment operator
    HuffmanTree & HuffmanTree::operator=(HuffmanTree && rhs) {
        if(this != &rhs){
            uMap = move(rhs.uMap);
            codeMap = move(rhs.codeMap);
			in = move(rhs.in);
			out = move(rhs.out);
			buffStr = move(rhs.buffStr);
			bitStr = move(rhs.bitStr);
			uPack = move(rhs.uPack);
			nBits = move(rhs.nBits);
			rNode = move(rhs.rNode);
            vLine = move(rhs.vLine);
			rhs.rNode = nullptr;
		}
		return *this;
    }

	// return the root node
	shared_ptr<HuffmanNode> HuffmanTree::getRoot() const {
		return rNode;
	}

	// return map
	unordered_map<char, int> HuffmanTree::getMap() const {
        return uMap;
	}

	// return code table
	unordered_map<char, string> HuffmanTree::getCodeTable() const {
        return codeMap;
	}

	// return encoded string
    string HuffmanTree::getEncoding() const {
        return buffStr;
    }

    // return compressed data
    string HuffmanTree::getPacked() const {
        return bitStr;
    }

    // return decompressed data
    string HuffmanTree::getUnpacked() const {
        return uPack;
    }

	// read in string from textfile
	void HuffmanTree::readTextfile(string inFile) {
		string line;
		in = inFile;
		stringstream ss;
		ifstream file(in.c_str());
		if (file.is_open()) {
			while (getline(file, line)) {
				ss << line;
			}
			file.close();
		}
		else {
			cout << "Unable to open file. Please ensure file " << in << " exists." << endl;
			exit(0);
		}
		string temp = ss.str();
		fillMap(temp);
	}

	// fill unordered_map
	void HuffmanTree::fillMap(string s) {
		unordered_map<char, int>::iterator it;
		for (unsigned int x = 0; x < s.size(); x++) {
			vLine.push_back(s[x]); // add letters to vector to use when writing out to file later
			it = uMap.find(s[x]);
			if (it == uMap.end()) {
				uMap.insert(make_pair(s[x], 1));
			}
			else {
				it->second++;
			}
		}
	}

	// build the tree using unordered_map
	void HuffmanTree::buildHuffTree(unordered_map<char, int> m) {
		unordered_map<char, int>::iterator it;
        uMap = m;
		// compare 2 nodes
		struct compare {
			bool operator()(const shared_ptr<HuffmanNode> & a, const shared_ptr<HuffmanNode> & b) {
				if ((*a).getValue() > (*b).getValue()) {
					return true;
				}
				else {
					return false;
				}
			}
		};

		priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, compare> myQueue;
		for (it = uMap.begin(); it != uMap.end(); it++) {
			shared_ptr<HuffmanNode> node = make_shared<HuffmanNode>(it->first, it->second);
			myQueue.push(node);
        }

		while (!myQueue.empty()) {
			if (myQueue.size() == 1) {
				rNode = myQueue.top();
				myQueue.pop();
			}
			else {
				shared_ptr<HuffmanNode> pNode = make_shared<HuffmanNode>('\0', 0);
                (*pNode).setLeft(myQueue.top());
				myQueue.pop();
                (*pNode).setRight(myQueue.top());
				myQueue.pop();
                int freq = (*(*pNode).getLeft()).getValue() + (*(*pNode).getRight()).getValue();
                (*pNode).setValue(freq);
				myQueue.push(pNode);
            }
		}
	}

	// build the huffman code
	void HuffmanTree::buildHuffCodeTable(shared_ptr<HuffmanNode> node, string s) {
		if ((*node).getLeft() != nullptr) {
            HuffmanTree::buildHuffCodeTable(node->getLeft(), s + "0");
		}
		if ((*node).getLetter() != '\0') {
			codeMap.insert(make_pair((*node).getLetter(), s));
			s = "";
		}
		if ((*node).getRight() != nullptr) {
			HuffmanTree::buildHuffCodeTable(node->getRight(), s + "1");
		}
	}

	// encode data into string of bits
    void HuffmanTree::encode() {
   		unordered_map<char, string>::iterator it;
		for (unsigned int x = 0; x < vLine.size(); x++) {
            it = codeMap.find(vLine[x]);
            buffStr += it->second;
        }
   	}

	// pack encoding into bitstream
	void HuffmanTree::compress() {
        unsigned char temp = '\0';
        string s = "";
        bitStr = "";
        for (unsigned int i = 0; i < buffStr.length(); i+=8) {
            s = buffStr.substr(i, 8);
            if (s.length() < 8) {
                s = buffStr.substr(i, s.length() - i);
            }
            for (unsigned int j = 0; j < s.length(); j++) {
                if (s[j] == '1') {
                    temp |= 1 << j;
                }
                else {
                    temp |= 0 << j;
                }
            }
            bitStr += temp;;
            temp = '\0';
        }
    }

    // write compressed string to .hdr file
    void HuffmanTree::outputTable(string o) {
        out = o;
        int size = codeMap.size();
        unordered_map<char, string>::iterator it;
        ofstream file(out.c_str());
		if (file.is_open()) {
			file << "Number of fields: " << size << endl;
			file << "_____________________" << endl;
			file << "__Char__|__Encoding__" << endl;
			for (it = codeMap.begin(); it != codeMap.end(); it++) {
                file << "   " << it->first << "    |    " << it->second << endl;
            }
            file << "________|____________";
		}
		file.close();
    }

    // write encoded string to .dat file
	void HuffmanTree::outputEncoding(string o) {
        out = o;
   		nBits = buffStr.size();
		int comp = (nBits/8) + (nBits%8 ? 1 : 0);
        const char * byte = buffStr.c_str();
        ofstream file(out.c_str());
		if (file.is_open()) {
            file << "Compression ratio = " << nBits << ":" << comp << endl;
            file << byte;
		}
        file.close();
	}

	// write compressed string to .bin file
	void HuffmanTree::outputPacked(string o) {
		out = o;
		nBits = buffStr.size();
		const char * buffer = bitStr.c_str();
		ofstream file(out.c_str());
		if (file.is_open()) {
		    file << nBits << '\n';
            file << buffer;
		}
		file.close();
	}

	// read in compressed file
	void HuffmanTree::readPacked() {
	    string line;
        string fName = "output.bin";
        string bit;
        ifstream file(fName.c_str());
        getline(file, bit);
        stringstream convert(bit);
        convert >> nBits;
        stringstream allData;
        if (file.is_open()) {
            while (getline(file, line)) {
                allData << line;
            }
            file.close();
        }
        string temp = allData.str();
        unpack(temp, nBits);
	}

	// decode packed bitstream
	void HuffmanTree::unpack(string s, int n) {
	    nBits = n;
	    int comp = (nBits/8) + (nBits%8 ? 1 : 0);
		vector<unsigned char> v;
        for (int x = 0; x < comp; x++) {
            v.push_back(s[x]);
        }
        stringstream sOut;
        int realSize = 0;
        for (unsigned int i = 0; i < v.size(); i++) {
            unsigned char temp = v[i];
            int a = 0;
            while (a < 8 && realSize < nBits) {
                if (temp & 0x01) {
                    sOut << '1';
                    realSize++;
                }
                else {
                    sOut << '0';
                    realSize++;
                }
                a++;
                temp = temp >> 1;
            }
        }
        uPack = sOut.str();
        if (uPack == buffStr) {
            cout << "Unpacking of compressed data successful!!!" << endl;
        }
        else {
            cout << "Unpacking of compressed data unsuccessful!!!" << endl;
        }
    }

	// print method to test map filling
	void HuffmanTree::printMap() {
		cout << "___________________________________________________" << endl;
		cout << "Map contents:" << endl;
		if (!uMap.empty()) {
			unordered_map<char, int>::iterator it;
			unordered_map<char, int> temp = uMap;
			for (it = temp.begin(); it != temp.end(); it++) {
				cout << it->first << ":" << it->second << endl;
			}
		}
		else {
			cout << "Map is empty." << endl;
		}
		printMap(codeMap);
	}

	// print codeMap
	void HuffmanTree::printMap(unordered_map<char, string> cMap) {
		cout << "___________________________________________________" << endl;
		cout << "Map contents:" << endl;
		unordered_map<char, string>::iterator it;
		for (it = cMap.begin(); it != cMap.end(); it++) {
			cout << it->first << ":" << it->second << endl;
		}
	}

	/************************HUFFMAN_TREE_CLASS***************************/
