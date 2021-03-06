# -*- coding: utf-8 -*-
import os
import sys

filename1 = sys.argv[1]
filename2 = sys.argv[2]

def prep(filename):
    ans = []
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip().split()
            ans.append(sorted([int(_) for _ in line]))
    ans = sorted(ans)
    return ans

f1 = prep(filename1)
f2 = prep(filename2)

if len(f1) != len(f2):
    print('Not the same.')
    sf1 = set([' '.join([str(x) for x in _]) for _ in f1])
    sf2 = set([' '.join([str(x) for x in _]) for _ in f2])
    print(len(sf2), len(sf1))
    print('In f1 / f2: ', end=' ')
    print(sf1.difference(sf2))
    print('In f2 / f1: ', end=' ')
    print(sf2.difference(sf1))
else:
    flag = True
    for i in range(len(f1)):
        if f1[i] != f2[i]:
            print(f1[i], f2[i])
            flag = False
    if flag:
        print('Same.')
    else:
        print('Not the same.')
