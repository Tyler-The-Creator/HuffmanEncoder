/*
 * HuffmanNode.h
 *
 *  Created on: Apr 22, 2017
 *      Author: Tyler Pillay
 */

#ifndef HUFFMANNODE_H_
#define HUFFMANNODE_H_

#include <unordered_map>
#include <memory>
#include <vector>

namespace plltyl003 {

    // HuffmanNode class represents the tree nodes in underlying Huffman tree
    class HuffmanNode {
		private:
			char alphabet ;

			int alphaFreq ;

			std::shared_ptr<HuffmanNode> l;

			std::shared_ptr<HuffmanNode> r;
		public:
		    // default constructor
			HuffmanNode(char c, int i);

            // destructor
            ~HuffmanNode();

            // copy constructor
            HuffmanNode(const HuffmanNode& rhs);

            // copy assignment operator
            HuffmanNode& operator=(const HuffmanNode& rhs);

            // move constructor
            HuffmanNode(HuffmanNode&& rhs);

            // move assignment operator
            HuffmanNode& operator=(HuffmanNode&& rhs);

            //obtain this node's left branch
			std::shared_ptr<HuffmanNode> getLeft();

			//obtain this node's right branch
			std::shared_ptr<HuffmanNode> getRight();

			//set this node's left branch
			void setLeft(std::shared_ptr<HuffmanNode> left);

			//set this node's right branch
			void setRight(std::shared_ptr<HuffmanNode> right);

			//return letter frequency from node
			int getValue();

			//set letter frequency in node
			void setValue(int f);

			//return letter from node
			char getLetter();
	};

}

#endif /* HUFFMANNODE_H_ */
