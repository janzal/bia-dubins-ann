from __future__ import print_function
from __future__ import division

__author__ = 'drchajan'

from ctypes import cdll, c_double, c_int
import numpy as np
import cPickle as pickle
import time


def generate_dataset_2dof(n):
    x = np.zeros((n, 2))
    t = np.zeros(n)
    xrng = 2.0
    yrng = 2.0
    for i in xrange(n):
        p1x, p1y, p1a = -1.0, rnd.uniform(-yrng, yrng), 0.0
        p2x, p2y = 0.0, 0.0
        p3x, p3y, p3a = rnd.uniform(-xrng, xrng), p1y, 0.0
        x[i] = (p1y, p3x)
        t[i] = getCenterHeading(p1x, p1y, p1a, p2x, p2y, p3x, p3y, p3a)
    return x, t


def generate_dataset_3dof(n, resolution=1024):
    x = np.zeros((n, 3))
    t = np.zeros(n)
    xrng = 2.0
    yrng = 2.0
    for i in xrange(n):
        if i % 100 == 0:
            print('\rgenerated {}%\t{}/{}'.format((i/n) * 100, i, n), end="")
        p1x, p1y, p1a = -1.0, rnd.uniform(-yrng, yrng), rnd.uniform(0.0, 2.0 * np.pi)
        p2x, p2y = 0.0, 0.0
        p3x, p3y, p3a = rnd.uniform(-xrng, xrng), p1y, 0.0
        x[i] = (p1y, p1a, p3x)
        t[i] = getCenterHeading(p1x, p1y, p1a, p2x, p2y, p3x, p3y, p3a)
    return x, t


def generate_dataset_5dof(n, resolution=1024):
    x = np.zeros((n, 5))
    t = np.zeros(n)
    xrng = 2.0
    yrng = 2.0
    start_time = time.time()
    prev_time = start_time
    for i in xrange(n):
        if i % 1000 == 0:
            curr_time = time.time()
            print('\rgenerated {}%\t{}/{} in {} seconds'.format((i/n) * 100, i, n, curr_time - prev_time), end="")
            prev_time = curr_time
        p1x, p1y, p1a = rnd.uniform(-xrng, xrng), rnd.uniform(-yrng, yrng), rnd.uniform(0.0, 2.0 * np.pi)
        p2x, p2y = 0.0, 0.0
        p3x, p3y, p3a = rnd.uniform(-xrng, xrng), p1y, rnd.uniform(0.0, 2.0 * np.pi)
        x[i] = (p1x, p1y, p1a, p3x, p3a)
        t[i] = getCenterHeadingWithResolution(resolution, p1x, p1y, p1a, p2x, p2y, p3x, p3y, p3a)
    print('dataset generated in {}'.format(time.time() - start_time))
    return x, t


if __name__ == '__main__':
    lib = cdll.LoadLibrary('/Users/janzaloudek/Development/Skola/BIA/dubin/assignment/data/C/nn_dubins/libpythonapi.so')
    getCenterHeading = lib.getCenterHeading
    getCenterHeading.argtypes = [c_double, c_double, c_double, c_double, c_double, c_double, c_double, c_double]
    getCenterHeading.restype = c_double

    getCenterHeadingWithResolution = lib.getCenterHeadingWithResolution
    getCenterHeadingWithResolution.argtypes = [c_int, c_double, c_double, c_double, c_double, c_double, c_double,
                                               c_double, c_double]
    getCenterHeadingWithResolution.restype = c_double

    rnd = np.random.RandomState(1234)

    n_patterns = 1000000
    path = '/Users/janzaloudek/Development/Skola/BIA/dubin/assignment/'

    # x_trn, t_trn = generate_dataset_2dof(n_patterns)
    # x_val, t_val = generate_dataset_2dof(n_patterns)
    # pickle.dump((x_trn, t_trn, x_val, t_val), open(path + 'datasets/datasets_midpoint_2DOF_500.p', 'w'))

    # x_trn, t_trn = generate_dataset_3dof(n_patterns)
    # x_val, t_val = generate_dataset_3dof(n_patterns)
    # pickle.dump((x_trn, t_trn, x_val, t_val), open(path + 'datasets/datasets_midpoint_3DOF_1M.p', 'w'))

    # resolution = 2
    # x_trn, t_trn = generate_dataset_5dof(n_patterns, resolution=resolution)
    # x_val, t_val = generate_dataset_5dof(n_patterns, resolution=resolution)
    # pickle.dump((x_trn, t_trn, x_val, t_val), open(path + 'datasets/datasets_midpoint_5DOF_resolution2_1M.p', 'w'))

    # resolution = 4
    # x_trn, t_trn = generate_dataset_5dof(n_patterns, resolution=resolution)
    # x_val, t_val = generate_dataset_5dof(n_patterns, resolution=resolution)
    # pickle.dump((x_trn, t_trn, x_val, t_val), open(path + 'datasets/datasets_midpoint_5DOF_resolution4_1M.p', 'w'))

    resolution = 16
    x_trn, t_trn = generate_dataset_5dof(n_patterns, resolution=resolution)
    x_val, t_val = generate_dataset_5dof(n_patterns, resolution=resolution)
    pickle.dump((x_trn, t_trn, x_val, t_val), open(path + 'datasets/datasets_midpoint_5DOF_resolution16_10M.p', 'w'))

    # resolution = 8
    # x_trn, t_trn = generate_dataset_5dof(n_patterns, resolution=resolution)
    # x_val, t_val = generate_dataset_5dof(n_patterns, resolution=resolution)
    # pickle.dump((x_trn, t_trn, x_val, t_val), open(path + 'datasets/datasets_midpoint_5DOF_resolution8_1K.p', 'w'))

    # resolution = 8
    # x_trn, t_trn = generate_dataset_3dof(n_patterns, resolution=resolution)
    # x_val, t_val = generate_dataset_3dof(n_patterns, resolution=resolution)
    # pickle.dump((x_trn, t_trn, x_val, t_val), open(path + 'datasets/datasets_midpoint_3DOF_1K.p', 'w'))

    # resolution = 3
    # x_trn, t_trn = generate_dataset_5dof(n_patterns, resolution=resolution)
    # x_val, t_val = generate_dataset_5dof(n_patterns, resolution=resolution)
    # pickle.dump((x_trn, t_trn, x_val, t_val), open(path + 'datasets/datasets_midpoint_5DO_resolution3F_1K.p', 'w'))
