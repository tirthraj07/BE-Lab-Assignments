'''
Problem Statement:
Knapsack problem using dynamic programming or branch and bound strategy. 

(This is a recursive implementation without memoization for educational purposes.)
Refer: https://youtu.be/GqOmJHQZivw?si=NslU3sWzZh1HIgya
'''


class Item:
    def __init__(self, value, weight):
        self.value = value
        self.weight = weight
    
'''
We have been given items with certain weights and values, and a knapsack with a maximum weight capacity W
We must maximize total value of Knapsack without exceeding the weight limit.

The Recursive thinking:
At every item i, we have two choices:
1. Not pick item i: move to next item (i-1), with same capacity W
2. Pick item i (if weight allows): add its value to total, reduce capacity by item's weight, move to next item (i-1)
We explore both choices and take the maximum.


Base Case:
If i == 0:
    If weight of item 0 <= W, return its value
    Else return 0
'''



def knapsack_recursive(items, W, i):
    # Base Case
    if i == 0:
        if items[0].weight <= W:
            return items[0].value
        else:
            return 0

    # Not pick the item
    not_pick = knapsack_recursive(items, W, i - 1)

    # Pick the item (if weight allows)
    pick = float('-inf')
    if items[i].weight <= W:
        pick = items[i].value + knapsack_recursive(items, W - items[i].weight, i - 1)

    return max(pick, not_pick)

def main():
    items = [Item(1,1), Item(4,3), Item(5,4), Item(7,5)]
    W = 7
    n = len(items)
    max_value = knapsack_recursive(items, W, n - 1)
    print(f'Maximum value in Knapsack = {max_value}')   # Maximum value in Knapsack = 9

if __name__ == "__main__":
    main()