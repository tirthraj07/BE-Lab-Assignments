"""
Problem Statement:
Design n-Queens matrix having first Queen placed. Use 
backtracking to place remaining Queens to generate the final n- 
queen
"""

def solveNQueens(n):
    board = [["."] * n for _ in range(n)]
    results = []

    def is_safe(row, col):
        # Check column
        for i in range(row):
            if board[i][col] == "Q":
                return False

        # Check upper-left diagonal
        i, j = row - 1, col - 1
        while i >= 0 and j >= 0:
            if board[i][j] == "Q":
                return False
            i -= 1
            j -= 1

        # Check upper-right diagonal
        i, j = row - 1, col + 1
        while i >= 0 and j < n:
            if board[i][j] == "Q":
                return False
            i -= 1
            j += 1

        return True

    def backtrack(row):
        # Base case: all queens placed
        if row == n:
            solution = ["".join(r) for r in board]
            results.append(solution)
            return

        # Try placing queen in each column
        for col in range(n):
            if is_safe(row, col):
                board[row][col] = "Q"   # place queen
                backtrack(row + 1)      # move to next row
                board[row][col] = "."   # backtrack

    backtrack(0)
    return results

def main():
    n = 4                                                       # Example for 4-Queens
    solutions = solveNQueens(n)                                 # Two valid solutions for N = 4
    print(f"Total solutions for {n}-Queens: {len(solutions)}")
    for solution in solutions:
        for row in solution:
            print(row)
        print()

if __name__ == "__main__":
    main()
