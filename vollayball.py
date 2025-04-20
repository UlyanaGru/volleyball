import math

def main():
    import sys
    line = sys.stdin.readline().strip()
    parts = line.split()
    N = int(parts[0])
    games = parts[1:N+1]
    total = 1
    for i in range(N):
        game = games[i]
        a, b = map(int, game.split(':'))
        is_fifth = (i == 4) and (N == 5)
        if a > b:
            win = a
            lose = b
        else:
            win = b
            lose = a
        if is_fifth:
            if win == 15 and lose <= 13:
                ways = math.comb(14 + lose, lose)
            else:
                total_after = win + lose - 28
                m = total_after // 2
                ways = math.comb(28, 14) * (2 ** (m - 1))
        else:
            if win == 25 and lose <= 23:
                ways = math.comb(24 + lose, lose)
            else:
                total_after = win + lose - 48
                m = total_after // 2
                ways = math.comb(48, 24) * (2 ** (m - 1))
        total *= ways
    print(total)

if __name__ == "__main__":
    main()