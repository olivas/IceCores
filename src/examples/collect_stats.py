#!/usr/bin/env python3

import subprocess
import collections
import pylab
import math

exponents = range(2,7)
results = collections.defaultdict(list)
for exponent in exponents:
    expectation = 10**exponent
    for i in range(1000):
        output = subprocess.check_output(['./a.out', str(0.5*10**exponent)]).decode('utf-8')
        result = int(output.split(' ')[2])
        print('%d: %d' % (expectation, result))
        results[expectation].append(math.log(result, 10))
print(results)

print(len(results.values()))
print(len(exponents))
pylab.violinplot(results.values(), exponents)
pylab.show()


