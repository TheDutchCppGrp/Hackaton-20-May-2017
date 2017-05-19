from multiprocessing import Pool, cpu_count
import sys


def expensive_function(i):
    print "Calling expensive function 1000 times, i = %d" % i
    sys.stdout.flush()
    counter = 0
    for i in range(0, 1000):
        for j in range(0, 10000):
            counter = counter + 1

if __name__ == '__main__':
    # single threaded version
    #for i in range(0, 1000):
    #    expensive_function(i)

    # parallel version
    pool = Pool(processes=cpu_count())
    pool.map(expensive_function, range(1000))

