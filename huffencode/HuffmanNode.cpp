/*
 * HuffmanNode.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: Tyler Pillay
 */

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

	/************************HUFFMAN_NODE CLASS***************************/

	// default constructor
	HuffmanNode::HuffmanNode(char c, int i) {
		alphabet = c;
		alphaFreq = i;
		l = nullptr;
		r = nullptr;
	}

	// destructor
	HuffmanNode::~HuffmanNode() {
		l = nullptr;
		r = nullptr;
	}

    // copy constructor
    HuffmanNode::HuffmanNode(const HuffmanNode & rhs) : alphabet(rhs.alphabet), alphaFreq(rhs.alphaFreq), l(rhs.l), r(rhs.r) {
    };

    // copy assignment operator
    HuffmanNode & HuffmanNode::operator=(const HuffmanNode & rhs) {
        if (this != &rhs) {
            alphabet = rhs.alphabet;
            alphaFreq = rhs.alphaFreq;
            l = rhs.l;
            r = rhs.r;
        }
        return *this;
    }

    // move constructor
    HuffmanNode::HuffmanNode(HuffmanNode && rhs) : alphabet(move(rhs.alphabet)), alphaFreq(move(rhs.alphaFreq)), l(move(rhs.l)), r(move(rhs.r)) {
        rhs.l = nullptr;
        rhs.r = nullptr;
    }

    // move assignment operator
    HuffmanNode & HuffmanNode::operator=(HuffmanNode && rhs) {
        if(this != &rhs){
            alphabet = move(rhs.alphabet);
            alphaFreq = move(rhs.alphaFreq);
            l = move(rhs.l);
            r = move(rhs.r);
            rhs.l = nullptr;
            rhs.r = nullptr;
        }
        return *this;
    }

	//obtain this node's left branch
	shared_ptr<HuffmanNode> HuffmanNode::getLeft() {
		return l;
	}

	//obtain this node's right branch
	shared_ptr<HuffmanNode> HuffmanNode::getRight() {
		return r;
	}

	//set this node's left branch
	void HuffmanNode::setLeft(shared_ptr<HuffmanNode> left) {
		l = left;
	}

	//set this node's right branch
	void HuffmanNode::setRight(shared_ptr<HuffmanNode> right) {
		r = right;
	}

	//return letter frequency from node
	int HuffmanNode::getValue() {
		return alphaFreq;
	}

	//set letter frequency in node
	void HuffmanNode::setValue(int f) {
		alphaFreq = f;
	}

	//return letter from node
	char HuffmanNode::getLetter() {
		return alphabet;
	}

	/************************HUFFMAN_NODE CLASS***************************/
