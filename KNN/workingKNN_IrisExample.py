# Author: Alexander Wang
# Last Updated: 2020-01-18
# 
from random import seed
from random import randrange
from csv import reader
from math import sqrt

def euclidean_distance(vec1 = [], vec2 = []):
    if(len(vec1) != len(vec2)):
        print("cannot calculate euclidian distance between two vectors with mismatching number of elements")
        return -1
    distance = 0.0
    for i in range(0, len(vec1) - 1):
        distance += (vec1[i] - vec2[i])**2
    return sqrt(distance)

def get_k_neighbors(training_set, test_vector, num_of_neighbors):
    distance_vectors = list()
    for v in training_set:
        dist_value = euclidean_distance(v, test_vector)
        distance_vectors.append((dist_value, v))
    distance_vectors.sort(key = lambda tup: tup[0])
    neighbors = list()
    for i in range(num_of_neighbors):
        neighbors.append(distance_vectors[i][1])
    return neighbors

def classify_unknown_vector(training_set, test_vector, num_of_neighbors):
    neighbors = get_k_neighbors(training_set, test_vector, num_of_neighbors)
    class_of_neighbors = list()
    for neighbor in neighbors:
        class_of_neighbors.append(neighbor[-1])
    prediction = max(set(class_of_neighbors), key = class_of_neighbors.count)
    return prediction

def load_csv(filename):
	dataset = list()
	with open(filename, 'r') as file:
		csv_reader = reader(file)
		for row in csv_reader:
			if not row:
				continue
			dataset.append(row)
	return dataset

def str_column_to_float(dataset, column):
	for row in dataset:
		row[column] = float(row[column].strip())

def str_column_to_int(dataset, column):
	class_values = [row[column] for row in dataset]
	unique = set(class_values)
	lookup = dict()
	for i, value in enumerate(unique):
		lookup[value] = i
	for row in dataset:
		row[column] = lookup[row[column]]
	return lookup

# Find the min and max values for each column
def dataset_minmax(dataset):
	minmax = list()
	for i in range(len(dataset[0])):
		col_values = [row[i] for row in dataset]
		value_min = min(col_values)
		value_max = max(col_values)
		minmax.append([value_min, value_max])
	return minmax
 
# Rescale dataset columns to the range 0-1
def normalize_dataset(dataset, minmax):
	for row in dataset:
		for i in range(len(row)):
			row[i] = (row[i] - minmax[i][0]) / (minmax[i][1] - minmax[i][0])
 
# Split a dataset into k folds
def cross_validation_split(dataset, n_folds):
	dataset_split = list()
	dataset_copy = list(dataset)
	fold_size = int(len(dataset) / n_folds)
	for _ in range(n_folds):
		fold = list()
		while len(fold) < fold_size:
			index = randrange(len(dataset_copy))
			fold.append(dataset_copy.pop(index))
		dataset_split.append(fold)
	return dataset_split

# Calculate accuracy percentage
def accuracy_metric(actual, predicted):
	correct = 0
	for i in range(len(actual)):
		if actual[i] == predicted[i]:
			correct += 1
	return correct / float(len(actual)) * 100.0

# Evaluate an algorithm using a cross validation split
def evaluate_algorithm(dataset, algorithm, n_folds, *args):
	folds = cross_validation_split(dataset, n_folds)
	scores = list()
	for fold in folds:
		train_set = list(folds)
		train_set.remove(fold)
		train_set = sum(train_set, [])
		test_set = list()
		for row in fold:
			row_copy = list(row)
			test_set.append(row_copy)
			row_copy[-1] = None
		predicted = algorithm(train_set, test_set, *args)
		actual = [row[-1] for row in fold]
		accuracy = accuracy_metric(actual, predicted)
		scores.append(accuracy)
	return scores

# kNN Algorithm
def k_nearest_neighbors(train, test, num_neighbors):
	predictions = list()
	for row in test:
		output = classify_unknown_vector(train, row, num_neighbors)
		predictions.append(output)
	return(predictions)

# Test the kNN on the Iris Flowers dataset
#seed(1)
filename = 'datasets\iris.csv'
dataset = load_csv(filename)
for i in range(len(dataset[0])-1):
	str_column_to_float(dataset, i)
# convert class column to integers
str_column_to_int(dataset, len(dataset[0])-1)
# evaluate algorithm
n_folds = 6
num_neighbors = 7
scores = evaluate_algorithm(dataset, k_nearest_neighbors, n_folds, num_neighbors)
print('Scores: %s' % scores)
print('Mean Accuracy: %.3f%%' % (sum(scores)/float(len(scores))))

