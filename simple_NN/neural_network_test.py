import numpy as np


def sigmoid(x):
    return 1/(1 + np.exp(-x))


def initialize_parameters(n_x, n_h, n_y): pass


def act_func(x): pass


def forward_prop_test_activation_func(X, parameters): pass


def calculate_cost(A2, Y): pass


def backward_prop(X, Y, cache, parameters): pass


def update_parameters(parameters, grads, learning_rate): pass


def model(X, Y, n_x, n_h, n_y, num_of_iters, learning_rate): pass


def predict_test_activation_func(X, parameters): pass


np.random.seed(2)

# The 4 training examples by columns
X = np.array([[0, 0, 1, 1], [0, 1, 0, 1]])

# The outputs of the XOR for every example in X
Y = np.array([[0, 1, 1, 0]])

# No. of training examples
m = X.shape[1]
# Set the hyperparameters
n_x = 2  # No. of neurons in first layer
n_h = 2  # No. of neurons in hidden layer
n_y = 1  # No. of neurons in output layer
num_of_iters = 1000
learning_rate = 0.3

trained_parameters = model(
    X, Y, n_x, n_h, n_y, num_of_iters, learning_rate)

# for i in range(0, 10):
#     for j in range(0, 10):
#         # Test 2X1 vector to calculate the XOR of its elements.
#         # You can try any of those: (0, 0), (0, 1), (1, 0), (1, 1)
#         X_test = np.array([[i/10.0], [j/10.0]])
#         y_predict = predict_test_activation_func(X_test, trained_parameters)
#         # Print the result
#         print('Neural Network prediction for example ({:f}, {:f}) is {:d}'.format(
#             X_test[0][0], X_test[1][0], y_predict))
