import random


def console_out():
    for i in range(2):
        if random.randint(1, 100) > 35:
            print(random.randint(1, 50))
        else:
            print(random.randint(1, 100))

    pirates_number = random.randint(1, 300)
    print(pirates_number)
    while pirates_number > 0:
        next_group = random.randint(1, pirates_number)
        print(next_group)
        pirates_number -= next_group


def file_out(path):
    with open(path, 'w') as file:
        for i in range(2):
            if random.randint(1, 100) > 35:
                print(random.randint(1, 50), file=file)
            else:
                print(random.randint(1, 100), file=file)

        pirates_number = random.randint(1, 300)
        print(pirates_number, file=file)
        while pirates_number > 0:
            next_group = random.randint(1, pirates_number)
            print(next_group, file=file)
            pirates_number -= next_group


if __name__ == '__main__':
    for i in range(1, int(input('Enter number of tests: ')) + 1):
        file_out(
            'SOME_PATH\\AoCS-threads\\Task5\\tests\\test{}.txt'
                .format(i))
