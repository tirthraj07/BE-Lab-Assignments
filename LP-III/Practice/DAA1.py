def recursive_fibo(n):
    if n == 0 or n == 1:
        return n
    return recursive_fibo(n-1) + recursive_fibo(n-2)

dp = {}
def dp_fibo(n):
    if n == 0 or n == 1:
        return n
    
    if n not in dp:
        dp[n] = dp_fibo(n-1) + dp_fibo(n-2)
    
    return dp[n] 

def iter_fibo(n):
    if n == 0 or n == 1:
        return n
    
    a = 0
    b = 1
    for i in range(2, n+1):
        a, b = b, a+b

    return b

def main():
    for i in range(0, 10):
        print(f"{i}th fibonacci number: {iter_fibo(i)}")

if __name__ == "__main__":
    main()