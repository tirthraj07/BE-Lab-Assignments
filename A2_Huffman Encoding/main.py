'''
Problem Statement:
Write a program to implement Huffman Encoding using a greedy strategy.
(With implementation of Min-Heap)
'''

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq
    
class MinHeap:
    def __init__(self):
        self.heap = []

    def insert(self, node):
        self.heap.append(node)
        self._heapify_up(len(self.heap) - 1)

    def extract_min(self):
        if len(self.heap) == 0:
            return None
        if len(self.heap) == 1:
            return self.heap.pop()
        
        root = self.heap[0]
        self.heap[0] = self.heap.pop()
        self._heapify_down(0)
        return root

    def _heapify_up(self, index):
        parent_index = (index - 1) // 2
        if index > 0 and self.heap[index] < self.heap[parent_index]:
            self.heap[index], self.heap[parent_index] = self.heap[parent_index], self.heap[index]
            self._heapify_up(parent_index)

    def _heapify_down(self, index):
        smallest = index
        left_child = 2 * index + 1
        right_child = 2 * index + 2

        if left_child < len(self.heap) and self.heap[left_child] < self.heap[smallest]:
            smallest = left_child
        if right_child < len(self.heap) and self.heap[right_child] < self.heap[smallest]:
            smallest = right_child
        if smallest != index:
            self.heap[index], self.heap[smallest] = self.heap[smallest], self.heap[index]
            self._heapify_down(smallest)

class HuffmanCoding:
    def __init__(self, char_freq):
        self.char_freq = char_freq
        self.heap = MinHeap()
        self.codes = {}

    def build_heap(self):
        for char, freq in self.char_freq.items():
            node = Node(char, freq)
            self.heap.insert(node)

    def build_huffman_tree(self):
        while len(self.heap.heap) > 1:
            left = self.heap.extract_min()
            right = self.heap.extract_min()
            merged = Node(None, left.freq + right.freq)
            merged.left = left
            merged.right = right
            self.heap.insert(merged)
        return self.heap.extract_min()

    def generate_codes(self, node, current_code=""):
        if node is None:
            return
        if node.char is not None:
            self.codes[node.char] = current_code
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
        if char in char_freq:
            char_freq[char] += 1
        else:
            char_freq[char] = 1
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

