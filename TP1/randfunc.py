import sys
import random

FUNCTIONS = [('exp', 1), ('sin', 1), ('cos', 1), ('+', 2), ('-', 2), ('*', 2)]

def rand_operand():
    op = random.choice(['z', 'num'])
    if op != 'z':
        op = str(random.randint(0, 10000000))
    return op

def randfunc(size):
    if size == 1:
        return rand_operand()
    f, arity = random.choice(FUNCTIONS)
    if arity == 2:
        left_size = random.randint(1, size-1)
        right_size = size - left_size
        op1 = randfunc(left_size)
        op2 = randfunc(right_size)
        return '%s%s%s' % (op1, f, op2)
    else:
        op = randfunc(size-1)
        return '%s(%s)' % (f, op)

if __name__ == '__main__':
    size = int(sys.argv[1])
    print randfunc(size)
