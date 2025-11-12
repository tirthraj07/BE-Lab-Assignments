import heapq

class Node:    
    def __init__(self, data, freq):
        self.data = data
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


class HuffmanEncoding:
    def __init__(self, char_freq):
        self.heap = []
        self.char_freq = char_freq
        self.codes = {}

    def encode(self):
        self.build_heap()
        root = self.build_huffman_tree()
        self.generate_codes(root)
        return self.codes
    
    def build_heap(self):
        for char, freq in self.char_freq.items():
            heapq.heappush(self.heap, Node(char, freq))

    def build_huffman_tree(self):
        while len(self.heap) > 1:
            left_node = heapq.heappop(self.heap)
            right_node = heapq.heappop(self.heap)
            root_node = Node(None, left_node.freq + right_node.freq)
            root_node.left = left_node 
            root_node.right = right_node
            heapq.heappush(self.heap, root_node)

        return heapq.heappop(self.heap)
    
    def generate_codes(self, root, current_code=""):
        if root is None:
            return
        if root.data is not None:
            self.codes[root.data] = current_code
            return
        
        self.generate_codes(root.left, current_code + "0")
        self.generate_codes(root.right, current_code + "1")

def print_codes(codes):
    for char, code in codes.items():
        print(f"{char} -> {code}")
    print()


def main():
    char_freq = {'A': 7, 'B': 2, 'C': 6, 'D': 3, 'E': 9}
    huffman_encoding = HuffmanEncoding(char_freq)
    codes = huffman_encoding.encode()
    print_codes(codes)

if __name__ == '__main__':
    main()