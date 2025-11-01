'''
Problem Statement:
Write a program to implement Huffman Encoding using a greedy strategy.
(Without implementation of Min-Heap)
'''

import heapq

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq

class HuffmanCoding:
    def __init__(self, char_freq):
        self.char_freq = char_freq
        self.heap = []
        self.codes = {}

    def build_heap(self):
        # Push all nodes into the heap
        for char, freq in self.char_freq.items():
            heapq.heappush(self.heap, Node(char, freq))

    def build_huffman_tree(self):
        # Keep combining until only one node remains (the root)
        while len(self.heap) > 1:
            left = heapq.heappop(self.heap)
            right = heapq.heappop(self.heap)
            merged = Node(None, left.freq + right.freq)
            merged.left = left
            merged.right = right
            heapq.heappush(self.heap, merged)
        # Root node
        return heapq.heappop(self.heap)

    def generate_codes(self, node, current_code=""):
        if node is None:
            return
        if node.char is not None:
            self.codes[node.char] = current_code
            return
        self.generate_codes(node.left, current_code + "0")
        self.generate_codes(node.right, current_code + "1")

    def huffman_encoding(self):
        self.build_heap()
        root = self.build_huffman_tree()
        self.generate_codes(root)
        return self.codes

def build_char_freq(input_string):
    char_freq = {}
    for char in input_string:
        char_freq[char] = char_freq.get(char, 0) + 1
    return char_freq

def main():
    input_string = input("Enter a string to encode using Huffman Coding: ")

    char_freq = build_char_freq(input_string)
    print("Character Frequencies:", char_freq)

    huffman_coding = HuffmanCoding(char_freq)
    codes = huffman_coding.huffman_encoding()

    print("Character Codes:")
    for char, code in codes.items():
        print(f"{char}: {code}")

if __name__ == "__main__":
    main()

'''
Enter a string to encode using Huffman Coding: AAAAAAABBCCCCCCDDDEEEEEEEEE
Character Frequencies: {'A': 7, 'B': 2, 'C': 6, 'D': 3, 'E': 9}
Character Codes:
B: 000
D: 001
C: 01
A: 10
E: 11
'''