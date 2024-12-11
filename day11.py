from collections import Counter

def split_number(num):
    num_str = str(num)
    mid = len(num_str) // 2
    left = int(num_str[:mid]) if mid > 0 else 0
    right = int(num_str[mid:]) if mid < len(num_str) else 0
    return [left, right]

def process_stones(initial_stones, blinks):
    stones = Counter(initial_stones)

    for _ in range(blinks):
        new_stones = Counter()
        for stone, count in stones.items():
            if stone == 0:
                new_stones[1] += count
            elif len(str(stone)) % 2 == 0:
                left, right = split_number(stone)
                new_stones[left] += count
                new_stones[right] += count
            else:
                new_stones[stone * 2024] += count
        stones = new_stones
    return sum(stones.values())

def main():
    with open("input.txt", "r") as file:
        initial_stones = list(map(int, file.readline().split()))

    print(process_stones(initial_stones, 25))
    print(process_stones(initial_stones, 75))

if __name__ == "__main__":
    main()