import cPickle as pickle

import math
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import mappings

# dataset = pickle.load(open('./datasets/datasets_midpoint_3DOF_1M.p', 'rb'))
# dataset = pickle.load(open('./datasets/datasets_midpoint_3DOF_1K.p', 'rb'))
# dataset = pickle.load(open('./datasets/datasets_midpoint_3DOF_500.p', 'rb'))
# dataset = pickle.load(open('./datasets/datasets_midpoint_5DOF_resolution16_10M.p', 'rb'))
dataset = pickle.load(open('./datasets/datasets_midpoint_5DOF_resolution8_1M.p', 'rb'))
x_trn, t_trn, x_val, t_val = dataset

# def discretize(x):
#     if (x > 4):
#         return True
#     return False

# print("Discretizing...")
# t_trn = np.array(map(discretize, t_trn))
# t_val = np.array(map(discretize, t_val))
# print("Done!")

nr_classes = 8


def create_classes(x):
    result = np.zeros(nr_classes)
    result_class = np.floor((nr_classes / (2.0 * np.pi)) * x) % nr_classes
    result[result_class] = 1
    return result


def split_angle(x, preserve_original=False):
    result = None

    if preserve_original:
        result = np.empty(3)
    else:
        result = np.empty(2)

    result[0] = np.sin(x)
    result[1] = np.cos(x)
    if preserve_original:
        result[2] = x

    return result


def split_angle_without_original(x):
    return split_angle(x, False)


def split_angle_with_original(x):
    return split_angle(x, True)


print("Preparing datasets...")

# print("Preparing outputs")
# tri_t_trn = np.array(map(split_angle_without_original, t_trn))
# tri_t_val = np.array(map(split_angle_without_original, t_val))

print("Discretizing outputs...")
tri_t_trn = np.array(map(create_classes, t_trn))
tri_t_val = np.array(map(create_classes, t_val))

print("Preparing inputs")
tri_x_trn = np.array(map(mappings.normalize_values_5, x_trn))
tri_x_val = np.array(map(mappings.normalize_values_5, x_val))

print("Done!")

# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')
#
# x_trnF = x_trn[t_trn]
# xsF = x_trnF[:, [0]]
# ysF = x_trnF[:, [1]]
# zsF = x_trnF[:, [2]]
# ax.scatter(xsF, ysF, zsF, c='r', marker='o')
#
# x_trnT = x_trn[np.logical_not(t_trn)]
# xsT = x_trnT[:, [0]]
# ysT = x_trnT[:, [1]]
# zsT = x_trnT[:, [2]]
# ax.scatter(xsT, ysT, zsT, c='b', marker='^')
#
# plt.show()
#
# exit()

# print('Input', x_trn[0])
# print('Output', t_trn[0])
#
# result = np.empty((1000, 6))
# for i in range(0, 999):
#     result[i] = np.append(x_trn[i], [t_trn[i]])
#
# print(result)
# PCAresult = PCA(result)
# print(PCAresult)

import time

from keras.models import Sequential
from keras.layers import Dense, Activation, Dropout, MaxoutDense
from keras.utils.visualize_util import plot
from keras.models import model_from_json
from keras.optimizers import RMSprop


def maxout_model(input_size, output_size):
    model = Sequential()
    model.add(Dense(12, input_dim=input_size))
    model.add(Activation('tanh'))
    model.add(MaxoutDense(20))
    # model.add(Dense(20))
    model.add(Dropout(0.5))
    model.add(Activation('tanh'))
    model.add(Dense(output_size))

    model.compile(loss='mean_squared_error', optimizer='sgd', metrics=['accuracy'])

    return model


def dense_dropout_model(input_size, output_size):
    model = Sequential()
    model.add(Dense(12, input_dim=input_size))
    model.add(Activation('tanh'))
    model.add(Dropout(0.2))
    model.add(Dense(20))
    model.add(Activation('tanh'))
    model.add(Dropout(0.4))
    model.add(Dense(output_size))

    model.compile(loss='mean_squared_error', optimizer='sgd', metrics=['accuracy'])

    return model


def dense_model(input_size, output_size):
    model = Sequential()
    model.add(Dense(15, input_dim=input_size))
    model.add(Activation('tanh'))
    model.add(Dense(20))
    model.add(Activation('tanh'))
    model.add(Dense(output_size))
    model.add(Activation('relu'))

    model.compile(loss='mean_squared_error', optimizer='sgd', metrics=['accuracy'])

    return model


def dense_model_small(input_size, output_size):
    model = Sequential()
    model.add(Dense(15, input_dim=input_size))
    model.add(Activation('tanh'))
    model.add(Dense(13))
    model.add(Activation('tanh'))
    model.add(Dense(output_size))
    model.add(Activation('tanh'))

    model.compile(loss='mean_squared_error', optimizer='sgd', metrics=['accuracy'])

    return model


# experiment with all tanh was not good
def dense_model_classif(input_size, output_size):
    model = Sequential()
    model.add(Dense(32, input_dim=input_size))
    model.add(Activation('relu'))
    model.add(Dense(64))
    model.add(Activation('tanh'))
    model.add(Dense(output_size))
    model.add(Activation('relu'))

    model.compile(loss='mean_squared_error', optimizer='sgd', metrics=['accuracy'])

    return model


def dense_model_classif2(input_size, output_size):
    model = Sequential()
    model.add(Dense(20, input_dim=input_size))
    model.add(Activation('tanh'))
    model.add(Dense(30))
    model.add(Activation('relu'))
    model.add(Dense(output_size))
    model.add(Activation('relu'))

    model.compile(loss='mse', optimizer='sgd', metrics=['accuracy'])

    return model


# nope
def dense_mae_model(input_size, output_size):
    model = Sequential()
    model.add(Dense(12, input_dim=input_size))
    model.add(Activation('tanh'))
    model.add(Dense(30))
    model.add(Activation('tanh'))
    model.add(Dense(output_size))

    model.compile(loss='mae', optimizer='sgd', metrics=['accuracy'])

    return model


experiment_description = ''
load_from_file = False
save_learned_model = True
input_size = 7
output_size = nr_classes

model = None
if load_from_file:
    ts = '1464167032'
    model = model_from_json(open('models/model_arch_{}.json'.format(ts)).read())
    model.load_weights('models/model_weights_{}.h5'.format(ts))
    model.compile(loss='mean_squared_error', optimizer='sgd')
else:
    model = dense_model_small(input_size, output_size)
    history_cb = model.fit(tri_x_trn, tri_t_trn, batch_size=32, nb_epoch=50, verbose=1)
    # history_cb = model.fit(x_trn, tri_t_trn, batch_size=128, nb_epoch=500, verbose=1)

    if save_learned_model:
        ts = int(time.mktime(time.localtime(time.time())))

        print('Timestamp: {}'.format(ts))
        model_json = model.to_json()
        open('models/model_arch_{}.json'.format(ts), 'w').write(model_json)
        model.save_weights('models/model_weights_{}.h5'.format(ts))
        pickle.dump(history_cb.history, open('models/history_{}.p'.format(ts), 'w'))
        plot(model, to_file='models/model_{}.png'.format(ts), show_shapes=True)

score = model.evaluate(tri_x_trn, tri_t_trn)
print(score)

score = model.evaluate(tri_x_val, tri_t_val)
print(score)

# print(model.predict(x_trn), tri_t_trn)
prediction = model.predict_classes(tri_x_trn)

for i in range(0, 100):
    # print(prediction[i], tri_t_trn[i],
    #       np.arctan(np.arcsin(prediction[i][0]) / np.arccos(prediction[i][1])),
    #       np.arctan(np.arcsin(tri_t_trn[i][0]) / np.arccos(tri_t_trn[i][1])))

    print(prediction[i], tri_t_trn[i])
