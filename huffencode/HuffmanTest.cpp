/*
 * HuffmanTest.cpp
 *
 *  Created on: May 03, 2017
 *      Author: Tyler Pillay
 */

#define CATCH_CONFIG_MAIN
#include "HuffmanTest.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

namespace plltyl003 {

    TEST_CASE("Build Tree", "HuffmanTree") {
        SECTION("Priority Queue creation") {
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
            shared_ptr<HuffmanNode> nodeA = make_shared<HuffmanNode>('a', 5);
            shared_ptr<HuffmanNode> nodeB = make_shared<HuffmanNode>('b', 9);
            shared_ptr<HuffmanNode> nodeC = make_shared<HuffmanNode>('c', 12);
            shared_ptr<HuffmanNode> nodeD = make_shared<HuffmanNode>('d', 13);
            shared_ptr<HuffmanNode> nodeE = make_shared<HuffmanNode>('e', 16);
            shared_ptr<HuffmanNode> nodeF = make_shared<HuffmanNode>('f', 45);
            myQueue.push(nodeA);
            myQueue.push(nodeB);
            myQueue.push(nodeC);
            myQueue.push(nodeD);
            myQueue.push(nodeE);
            myQueue.push(nodeF);

            shared_ptr<HuffmanNode> tNode = myQueue.top();
            REQUIRE((*tNode).getValue() == 5);
            REQUIRE((*tNode).getLetter() == 'a');
        }

        SECTION("Priority Queue insertion") {
            unordered_map<char, int> tMap;
            unordered_map<char, int>::iterator it;
            tMap.insert(make_pair('f', 45));
            tMap.insert(make_pair('a', 2));
            tMap.insert(make_pair('c', 14));
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

            for (it = tMap.begin(); it != tMap.end(); it++) {
                shared_ptr<HuffmanNode> node = make_shared<HuffmanNode>(it->first, it->second);
                myQueue.push(node);
            }
            shared_ptr<HuffmanNode> tNode = myQueue.top();
            REQUIRE((*tNode).getLetter() == 'a');
            REQUIRE((*tNode).getValue() == 2);
        }

        SECTION("Create Tree") {
            unordered_map<char, int> tMap;
            tMap.insert(make_pair('f', 45));
            tMap.insert(make_pair('a', 2));
            tMap.insert(make_pair('c', 14));
            HuffmanTree huffTree;
            huffTree.buildHuffTree(tMap);
            shared_ptr<HuffmanNode> rNode = huffTree.getRoot();
            REQUIRE((*rNode).getValue() == 61);
            REQUIRE((*((*rNode).getRight())).getValue() == 45);
            REQUIRE((*((*rNode).getLeft())).getValue() == 16);
            REQUIRE((*(*((*rNode).getLeft())).getRight()).getValue() == 14);
            REQUIRE((*(*((*rNode).getLeft())).getLeft()).getValue() == 2);
        }
    }

    TEST_CASE("Creating Huffman Code Table", "HuffmanTree") {
 		unordered_map<char, int> tMap;
		tMap.insert(std::make_pair('f', 45));
		tMap.insert(std::make_pair('b', 9));
		tMap.insert(std::make_pair('e', 16));
        tMap.insert(std::make_pair('a', 5));
		tMap.insert(std::make_pair('c', 12));
		tMap.insert(std::make_pair('d', 13));
		HuffmanTree huffTree;
        huffTree.buildHuffTree(tMap);
        shared_ptr<HuffmanNode> rNode = huffTree.getRoot();
        huffTree.buildHuffCodeTable(rNode, "");
        unordered_map<char, string> cMap = huffTree.getCodeTable();
		REQUIRE(cMap.at('a') == "1100");
		REQUIRE(cMap.at('b') == "1101");
        REQUIRE(cMap.at('c') == "100");
        REQUIRE(cMap.at('d') == "101");
		REQUIRE(cMap.at('e') == "111");
        REQUIRE(cMap.at('f') == "0");
    }

    TEST_CASE("Encode data", "HuffmanTree") {
        HuffmanTree huffTree;
        unordered_map<char, int> tMap;
        string input = "ADA ATE APPLE";
        vector<char> vLine;
        huffTree.fillMap(input);
		tMap.insert(make_pair('A', 4));
		tMap.insert(make_pair('D', 1));
		tMap.insert(make_pair('T', 1));
        tMap.insert(make_pair('P', 2));
		tMap.insert(make_pair('L', 1));
		tMap.insert(make_pair('E', 2));
		tMap.insert(make_pair(' ', 2));
		huffTree.buildHuffTree(tMap);
        shared_ptr<HuffmanNode> rNode = huffTree.getRoot();
        huffTree.buildHuffCodeTable(rNode, "");
        unordered_map<char, string> codeMap = huffTree.getCodeTable();
        huffTree.encode();
        string encoded = huffTree.getEncoding();
        REQUIRE(encoded == "11010111011110000111011100001001011");
    }

    TEST_CASE("Compress data", "HuffmanTree") {
        HuffmanTree huffTree;
        unordered_map<char, int> tMap;
        string input = "ADA ATE APPLE";
        vector<char> vLine;
        huffTree.fillMap(input);
		tMap.insert(make_pair('A', 4));
		tMap.insert(make_pair('D', 1));
		tMap.insert(make_pair('T', 1));
        tMap.insert(make_pair('P', 2));
		tMap.insert(make_pair('L', 1));
		tMap.insert(make_pair('E', 2));
		tMap.insert(make_pair(' ', 2));
		huffTree.buildHuffTree(tMap);
        shared_ptr<HuffmanNode> rNode = huffTree.getRoot();
        huffTree.buildHuffCodeTable(rNode, "");
        unordered_map<char, string> codeMap = huffTree.getCodeTable();
        huffTree.encode();
        string encoded = huffTree.getEncoding();
        int nBits = encoded.size();
        huffTree.compress();
        string compStr = huffTree.getPacked();
        int compSize = compStr.size();
        int realCompSize = (nBits/8) + (nBits%8 ? 1 : 0);
        REQUIRE(compSize == realCompSize);
    }

    TEST_CASE("Decompress data", "HuffmanTree") {
        HuffmanTree huffTree;
        unordered_map<char, int> tMap;
        string input = "ADA ATE APPLE";
        vector<char> vLine;
        huffTree.fillMap(input);
		tMap.insert(make_pair('A', 4));
		tMap.insert(make_pair('D', 1));
		tMap.insert(make_pair('T', 1));
        tMap.insert(make_pair('P', 2));
		tMap.insert(make_pair('L', 1));
		tMap.insert(make_pair('E', 2));
		tMap.insert(make_pair(' ', 2));
		huffTree.buildHuffTree(tMap);
        shared_ptr<HuffmanNode> rNode = huffTree.getRoot();
        huffTree.buildHuffCodeTable(rNode, "");
        unordered_map<char, string> codeMap = huffTree.getCodeTable();
        huffTree.encode();
        string encoded = huffTree.getEncoding();
        int n = 35;
        huffTree.compress();
        string compStr = huffTree.getPacked();
        huffTree.unpack(compStr, n);
        string u = huffTree.getUnpacked();
        REQUIRE(u == encoded);
    }

    TEST_CASE("Creating a new node", "HuffmanNode") {
        shared_ptr<HuffmanNode> tNode = make_shared<HuffmanNode>('f', 45);
        REQUIRE((*tNode).getLetter() == 'f');
        REQUIRE((*tNode).getValue() == 45);
    }

    TEST_CASE("Frequency handling", "HuffmanNode") {
        shared_ptr<HuffmanNode> tNode = make_shared<HuffmanNode>('x', 12);
        REQUIRE((*tNode).getLetter() == 'x');
        REQUIRE((*tNode).getValue() == 12);
        (*tNode).setValue(7);
        REQUIRE((*tNode).getValue() == 7);
    }

    TEST_CASE("Left node handling", "HuffmanNode") {
      	shared_ptr<HuffmanNode> tNodeA = make_shared<HuffmanNode>('a', 4);
        shared_ptr<HuffmanNode> tNodeB = make_shared<HuffmanNode>('b', 2);
        (*tNodeA).setLeft(tNodeB);
        REQUIRE((*((*tNodeA).getLeft())).getLetter() == 'b');
        REQUIRE((*((*tNodeA).getLeft())).getValue() == 2);
    }

    TEST_CASE("Right node handling", "HuffmanNode") {
        shared_ptr<HuffmanNode> tNodeA = make_shared<HuffmanNode>('a', 4);
        shared_ptr<HuffmanNode> tNodeB = make_shared<HuffmanNode>('b', 2);
        (*tNodeA).setRight(tNodeB);
        REQUIRE((*((*tNodeA).getRight())).getLetter() == 'b');
        REQUIRE((*((*tNodeA).getRight())).getValue() == 2);
    }

}
