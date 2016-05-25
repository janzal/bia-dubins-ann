import numpy as np

def normalize_values_5(x):
    result = np.empty(7)
    result[0] = x[0]
    result[1] = x[1]
    result[2] = np.sin(x[2])
    result[3] = np.cos(x[2])
    result[4] = x[3]
    result[5] = np.sin(x[4])
    result[6] = np.cos(x[4])
    return result