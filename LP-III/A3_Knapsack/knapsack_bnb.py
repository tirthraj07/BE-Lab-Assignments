'''
Problem Statement:
Knapsack problem using dynamic programming or branch and bound strategy. 
Refer: https://youtu.be/CwM-Mv0Bm4Y?si=79kxGD_HC-P6jm0_
Refer: https://youtu.be/yV1d-b_NeK8?si=UmVproHYOuSnauo-

(This is an implementation with Branch and Bound)
'''


'''
This approach is completely different in spirit:
instead of systematically filling a DP table, 
it explores possible item combinations as a search tree, 
but prunes unpromising branches using upper bounds — that's the “bound” part of branch & bound.

Branch: make a choice → include or exclude an item.
Bound: estimate the best possible value achievable from that point onward.

If that bound is less than the current best known solution, we skip exploring that branch.
'''

from queue import PriorityQueue

class Item:
    def __init__(self, value, weight):
        self.value = value
        self.weight = weight
        self.ratio = value / weight

# Node class for the state tree
class Node:
    def __init__(self, level, profit, weight, bound):
        self.level = level      # current index in items
        self.profit = profit    # total value so far
        self.weight = weight    # total weight so far
        self.bound = bound      # optimistic upper bound

    # For priority queue (max-heap by bound)
    def __lt__(self, other):
        return self.bound > other.bound

def bound(node, n, W, items):
    '''
        Calculate upper bound on profit in subtree rooted with 'node'
        1. If weight exceeds capacity, return 0
        2. Else, add items while possible
        3. If an item can't be fully added, add fractional part
        4. Return the computed bound
    '''
    if node.weight >= W:
        return 0

    profit_bound = node.profit
    j = node.level + 1
    total_weight = node.weight

    # take items greedily until capacity full
    while j < n and total_weight + items[j].weight <= W:
        total_weight += items[j].weight
        profit_bound += items[j].value
        j += 1

    # take fraction of next item (if any)
    if j < n:
        profit_bound += (W - total_weight) * items[j].ratio

    return profit_bound


def knapsack_branch_bound(values, weights, W):
    n = len(values)
    items = [Item(values[i], weights[i]) for i in range(n)]
    # Sort by decreasing value/weight ratio
    items.sort(key=lambda x: x.ratio, reverse=True)

    # Priority queue for live nodes
    Q = PriorityQueue()
    max_profit = 0

    # Start with root node
    root = Node(-1, 0, 0, 0)
    root.bound = bound(root, n, W, items)
    Q.put(root)

    # BFS with bounding
    while not Q.empty():
        node = Q.get()

        if node.bound > max_profit:
            # Next item
            next_level = node.level + 1

            # Case 1: include next item
            include = Node(next_level,
                           node.profit + items[next_level].value,
                           node.weight + items[next_level].weight,
                           0)

            if include.weight <= W and include.profit > max_profit:
                max_profit = include.profit

            include.bound = bound(include, n, W, items)
            if include.bound > max_profit:
                Q.put(include)

            # Case 2: exclude next item
            exclude = Node(next_level, node.profit, node.weight, 0)
            exclude.bound = bound(exclude, n, W, items)
            if exclude.bound > max_profit:
                Q.put(exclude)

    return max_profit


def main():
    values = [1, 4, 5, 7]
    weights = [1, 3, 4, 5]
    W = 7
    max_value = knapsack_branch_bound(values, weights, W)
    print(f'Maximum value in Knapsack = {max_value}')   # Maximum value in Knapsack = 9

if __name__ == "__main__":
    main()