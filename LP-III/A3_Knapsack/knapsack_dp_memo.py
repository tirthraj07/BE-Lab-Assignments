'''
Problem Statement:
Knapsack problem using dynamic programming or branch and bound strategy. 
Refer: https://youtu.be/GqOmJHQZivw?si=NslU3sWzZh1HIgya

(This is an implementation with memoization (Top-Down DP))
'''

class Item:
    def __init__(self, value, weight):
        self.value = value
        self.weight = weight

'''
Memoization is just recursion with caching
In recursion, we had two changing parameters: i (item index) and W (remaining capacity)
We create a 2D array dp[n][W+1] where dp[i][w] stores the maximum value for items[0..i] with capacity w
'''

def knapsack_memo(items, W):
    n = len(items)
    # Create a 2D dp array initialized to -1
    dp = []
    for _ in range(n):
        dp.append([-1] * (W + 1))

    def f(i, W):
        # Base Case
        if i == 0:
            if items[0].weight <= W:
                return items[0].value
            else:
                return 0
        
        # If already computed, return the stored value
        if dp[i][W] != -1:
            return dp[i][W]
        
        # Not pick
        not_pick = f(i - 1, W)

        # Pick (if weight allows)
        pick = float('-inf')
        if items[i].weight <= W:
            pick = items[i].value + f(i - 1, W - items[i].weight)
        
        # Store the result in dp array
        dp[i][W] = max(pick, not_pick)
        return dp[i][W]
    
    return f(n - 1, W)

def main():
    items = [Item(1,1), Item(4,3), Item(5,4), Item(7,5)]
    W = 7
    max_value = knapsack_memo(items, W)
    print(f'Maximum value in Knapsack = {max_value}')   # Maximum value in Knapsack = 9

if __name__ == "__main__":
    main()