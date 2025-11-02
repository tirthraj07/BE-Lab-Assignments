'''
Problem Statement:
Knapsack problem using dynamic programming or branch and bound strategy. 
Refer: https://youtu.be/GqOmJHQZivw?si=NslU3sWzZh1HIgya

(This is a tabulation implementation (Bottom-Up DP))
'''

class Item:
    def __init__(self, value, weight):
        self.value = value
        self.weight = weight

'''
In tabulation, we build a 2D dp array iteratively.
dp[i][w] will represent the maximum value for items[0..i] with capacity w
Base Case:
For i = 0:
    If weight of item 0 <= w, dp[0][w] = value of item 0
    Else dp[0][w] = 0
'''


def knapsack_dp_tabulation(items, W):
    n = len(items)
    # Create a 2D dp array initialized to 0
    dp = []
    for _ in range(n):
        dp.append([0] * (W + 1))

    # Base Case initialization
    '''
        For every weight greater than or equal to items[0], we can steal it in the knapsack
        It is what we do in the base case of recursion and memoization, where we return the value of item 0 if its weight is less than or equal to W 
        This is equivalent to filling the first row of the dp table in tabulation
        If the knapsack capacity is less than the weight of item 0, we cannot include it, so the value remains 0 (which is already initialized)
    '''
    for w in range(items[0].weight, W + 1):
        dp[0][w] = items[0].value

    # Fill the dp table
    for i in range(1, n):
        for w in range(W + 1):
            # Not pick the item
            '''
                This means that, we are not including the current item i in the knapsack
                So, the maxium value will be the same as that of the previous item at the same capacity w
            '''
            not_pick = dp[i - 1][w]

            # Pick the item (if weight allows)
            pick = float('-inf')
            if items[i].weight <= w:
                pick = items[i].value + dp[i - 1][w - items[i].weight]

            dp[i][w] = max(pick, not_pick)

    return dp[n - 1][W]

def main():
    items = [Item(1,1), Item(4,3), Item(5,4), Item(7,5)]
    W = 7
    max_value = knapsack_dp_tabulation(items, W)
    print(f'Maximum value in Knapsack = {max_value}')   # Maximum value in Knapsack = 9

if __name__ == "__main__":
    main()