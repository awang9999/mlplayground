from sklearn.datasets import load_iris
import random as rd
import math
import numpy as np

iris = load_iris()

#load the data
full_data = iris.data
full_targets = iris.target
names = iris.target_names

print(full_targets)
print(names)

# Feature scaling
# Standardization (Z-score Normalization)
feature_means = [0, 0, 0, 0]
feature_stds = [0, 0, 0, 0]
# Calculate sample means and sample stds
for i in range (0, full_data[0].size):
    feature_i = full_data[: , i]
    #calculate mean
    sum = 0
    for j in range(0, len(feature_i)):
        sum += feature_i[j]
    feature_means[i] = sum / len(feature_i)
    #Calculate std
    sum_of_differences_squared = 0
    for j in range(0, feature_i.size):
        sum_of_differences_squared += (feature_i[j] - feature_means[i])**2
    svariance = (1/feature_i.size) * sum_of_differences_squared
    feature_stds[i] = math.sqrt(svariance)
    #standardize feature
    for j in range(0, feature_i.size):
        full_data[j][i] = (full_data[j][i] - feature_means[i]) / feature_stds[i]

print('means: ')
print(feature_means)
print('stds: ')
print(feature_stds)

#shuffle the data
for x in range(0, full_targets.size):
    randomind = int(rd.random() * full_targets.size)
    #switch around in data
    temp = full_data[x]
    full_data[x] = full_data[randomind]
    full_data[randomind] = temp
    #switch around in targets
    temp2 = full_targets[x]
    full_targets[x] = full_targets[randomind]
    full_targets[randomind] = temp2

print(full_targets)

#separate the data into training and testing data
training_data = full_data[0:int((full_data.size / 4) * 0.8)]
training_targets = full_targets[0:int(full_targets.size*0.8)]
testing_data = full_data[int((full_data.size / 4) * 0.8):]
testing_targets = full_targets[int(full_targets.size*0.8):]
if(training_data.size != 4*training_targets.size):
    print('inconsistent training datasets!')
elif(testing_data.size != 4*testing_targets.size):
    print('inconsistent testing datasets!')

#Requires v1 to have the same amount of features as v2
def calculate_euclidian_distance(v1 = [0], v2 = [0]):
    if(len(v1) != len(v2)):
        print("length mismatch")
        return 0
    else:
        sum_of_differences_squared = 0
        for x in range (0, len(v1)):
            sum_of_differences_squared += (v2[x] - v1[x])**2
        
        return math.sqrt(sum_of_differences_squared)

def classify_using_KNN(data, targets, unknown_v = [0], k = 3):

    if(len(unknown_v) != len(data[0])):
        print('vector mismatch')
        return 0

    distances = [0] * len(data)
    for i in range(0, len(data)):
        distances[i] = calculate_euclidian_distance(data[i], unknown_v)
    
    for i in range(1, len(distances)):
        j = i
        while(j > 0 and distances[j-1] > distances[j]):
            #swap distances[j] with distances[j-1]
            temp = distances[j]
            distances[j] = distances[j-1]
            distances[j-1] = temp

            temp2 = targets[j]
            targets[j] = targets[j-1]
            targets[j-1] = temp2 
            j = j-1
    
    print(distances)
    print(targets)

    votes = [0] * len(names)
    for i in range(0, k):
        votes[targets[i]] += 1

    max_ind = 0
    for i in range(0, len(names)):
        if(votes[i] > votes[max_ind]):
            max_ind = i
    
    return max_ind

correct_predictions = 0
for i in range(0, 1):
    prediction = classify_using_KNN(training_data, training_targets, testing_data[i], 5)
    if(prediction == testing_targets[i]):
        correct_predictions += 1;
    s = '{}, {}'.format(names[prediction], names[testing_targets[i]])
    print(s)

accuracy = correct_predictions / (len(testing_data))
print('accuracy: {}'.format(accuracy))
# print(training_data[0])
# print(training_targets[0])
# print(names)

# print(calculate_euclidian_distance(np.array([0,0,0]), np.array([1,1,1])))

print('made it to the end')