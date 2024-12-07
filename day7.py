def evaluate1(numbers, operators):
    result = numbers[0]
    for i in range(len(operators)):
        if operators[i] == '+':
            result += numbers[i + 1]
        elif operators[i] == '*':
            result *= numbers[i + 1]
    return result

def evaluate2(numbers, operators):
    result = numbers[0]
    for i in range(len(operators)):
        if operators[i] == '+':
            result += numbers[i + 1]
        elif operators[i] == '*':
            result *= numbers[i + 1]
        elif operators[i] == '||': 
            result = int(str(result) + str(numbers[i + 1]))
    return result

def check1(test_value, numbers):
    n = len(numbers)
    if n == 1:
        return test_value == numbers[0]  
    total_valid = 0
    for i in range(1 << (n - 1)): 
        operators = []
        for j in range(n - 1):
            operators.append('*' if (i & (1 << j)) else '+')
        if evaluate1(numbers, operators) == test_value:
            return True  
    return False

def check2(test_value, numbers):
    n = len(numbers)
    if n == 1:
        return test_value == numbers[0]  
    total_valid = 0
    operators_list = ['+', '*', '||']
    for i in range(3 ** (n - 1)):  
        operators = []
        num = i
        for j in range(n - 1):
            operators.append(operators_list[num % 3])
            num //= 3
        if evaluate2(numbers, operators) == test_value:
            return True
    return False

def main():
    total1 = 0
    total2 = 0
    with open('input.txt', 'r') as file:
        for line in file:
            parts = line.split(':')
            test_value = int(parts[0].strip())
            numbers = list(map(int, parts[1].strip().split()))
            if check1(test_value, numbers):
                total1 += test_value
            if check2(test_value, numbers):
                total2 += test_value
    print(total1, total2)

if __name__ == "__main__":
    main()