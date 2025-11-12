def solveNQueens(n):
    board = [["."]* n for _ in range(n)] 
    solutions = []

    def solve(row):
        if row == n:
            solution = ["".join(r) for r in board]
            solutions.append(solution)
            return

        for col in range(n):
            if isSafe(row, col):
                board[row][col] = 'Q'
                solve(row+1)
                board[row][col] = "."
    
    def isSafe(row, col):
        for i in range(0, row):
            if board[i][col] == 'Q':
                return False
            
        i = row - 1
        j = col - 1
        while i >= 0 and j >= 0:
            if board[i][j] == 'Q':
                return False
            i -= 1
            j -= 1
        
        i = row - 1
        j = col + 1
        while i >= 0 and j < n:
            if board[i][j] == 'Q':
                return False
            
            i -= 1
            j += 1
        
        return True

    solve(0)
    return solutions


def main():
    n = 5
    solutions = solveNQueens(n)
    print(f"Total Number of solutions: {len(solutions)}")

    for sol in solutions:
        for row in sol:
            print(row)
        print("\n")


if __name__ ==  '__main__':
    main()
