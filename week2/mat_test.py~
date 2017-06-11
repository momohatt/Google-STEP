# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import time

def main():
    elapsed_time = []
    for n in range(1000):
        a_array = np.random.rand(n*n).reshape((n,n))
        b_array = np.random.rand(n*n).reshape((n,n))
        start = time.time()
        c_array = np.dot(a_array, b_array)
        elapsed_time.append( time.time() - start )
    plt.plot(elapsed_time)
    plt.show()
    return 0

if __name__ == '__main__':
    main()
