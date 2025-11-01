def factorial_recursive(n):
    """Calculate the factorial of a number recursively."""
    if n < 0:
        raise ValueError("Factorial is not defined for negative numbers.")
    if n == 0 or n == 1:
        return 1
    return n * factorial_recursive(n - 1)


def factorial_non_recursive(n):
    """Calculate the factorial of a number non-recursively."""
    if n < 0:
        raise ValueError("Factorial is not defined for negative numbers.")
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result

def main():
    n = 5
    print(f"Factorial Recursive of {n}: {factorial_recursive(n)}")
    print(f"Factorial Non-Recursive of {n}: {factorial_non_recursive(n)}")

if __name__ == "__main__":
    main()