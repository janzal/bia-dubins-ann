import cPickle as pickle
import matplotlib.pyplot as plt

plt.style.use('ggplot')

history = pickle.load(open('models/history_1464164122.p', 'rb'))

plt.figure()
plt.plot(history['acc'])
plt.ylabel('acc')
plt.xlabel('epoch')
plt.title('training accuracy')
plt.show()