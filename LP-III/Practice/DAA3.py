class Item:
    def __init__(self, value, weight):
        self.value = value
        self.weight = weight
        


def recursive_knapsack(items, W, i):
    if i == 0:
        if items[0].weight <= W:
            return items[0].value
        return 0
    
    not_pick = recursive_knapsack(items, W, i-1)

    pick = float('-inf')
    if items[i].weight <= W:
        pick = items[i].value + recursive_knapsack(items, W - items[i].weight, i-1)
    
    return max(pick, not_pick)

def dp_knapsack(items, W):
    dp = []
    for i in range(len(items)):
        dp.append([-1]*(W+1))

    def f(i, W):
        if i == 0:
            if items[0].weight <= W:
                return items[0].value
            return 0
        
        if dp[i][W] == -1:

            not_pick = f(i-1, W)

            pick = float('-inf')
            if items[i].weight <= W:
                pick = items[i].value + f(i-1, W - items[i].weight)
        
            dp[i][W] = max(pick, not_pick)

        return dp[i][W] 


    return f(len(items) - 1, W)

def main():
    items = [Item(1,1), Item(4,3), Item(5,4), Item(7,5)]
    max_value = dp_knapsack(items, 7)
    print(f"Max Value: {max_value}")


if __name__ == '__main__':
    main()