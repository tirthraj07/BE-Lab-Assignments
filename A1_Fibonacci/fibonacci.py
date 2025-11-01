'''
Problem Statement
Write a non-recursive and recursive program to calculate Fibonacci numbers and analyze their time and space complexity. 

Time and Space Complexity Analysis:
1. Recursive Approach:
    - Time Complexity: O(2^n) - Exponential time complexity due to the repeated calculations of the same Fibonacci numbers.
    - Space Complexity: O(n) - Due to the call stack used by recursion.
2. Non-Recursive Approach:
    - Time Complexity: O(n) - Linear time complexity as it calculates each Fibonacci number once
    - Space Complexity: O(1) - Constant space complexity as it uses a fixed amount of space.
3. Dynamic Programming Approach:
    - Time Complexity: O(n) - Linear time complexity as it calculates each Fibonacci number once
    - Space Complexity: O(n) - Linear space complexity due to the storage of computed Fibonacci numbers in a memoization table.
    
'''

def fibonacci_recursive(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)
    
def fibonacci_non_recursive(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        a, b = 0, 1
        for _ in range(2, n + 1):
            a, b = b, a + b
        return b

def fibonacci_dp(n, memo={}):
    if n in memo:
        return memo[n]
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        memo[n] = fibonacci_dp(n - 1, memo) + fibonacci_dp(n - 2, memo)
        return memo[n]


def main():
    n = 10
    print(f"Fibonacci Recursive of {n}: {fibonacci_recursive(n)}")
    print(f"Fibonacci Non-Recursive of {n}: {fibonacci_non_recursive(n)}")
    print(f"Fibonacci DP of {n}: {fibonacci_dp(n)}")

if __name__ == "__main__":
    main()