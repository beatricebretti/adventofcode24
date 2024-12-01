from collections import Counter

def read_input(path):
    with open(path, "r") as file:
        for line in file:
            left, right = map(int, line.split())
            listLeft.append(left)
            listRight.append(right)

def count_ocurrences(lista):
    return Counter(lista)

def similarity_score(counts, lista):
    score = 0
    for number in lista:
        score += number * counts[number]
    return score

listLeft = []
listRight = []

read_input("input.txt")
print(similarity_score(count_ocurrences(listRight), listLeft))