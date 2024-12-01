def read_input(path):
    with open(path, "r") as file:
        for line in file:
            left, right = map(int, line.split())
            listLeft.append(left)
            listRight.append(right)

def sort_lists(list1, list2):
    return sorted(list1), sorted(list2)

def calculate_distance(list1, list2):
    total = sum(abs(left - right) for left, right in zip(list1, list2))
    return total

listLeft = []
listRight = []

read_input("input.txt")
listLeft, listRight = sort_lists(listLeft, listRight)
print(calculate_distance(listLeft, listRight))
