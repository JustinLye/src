#!/usr/bin/env python3

import sys
import numpy as np
import math

def predict(w,x):
    return (1/(1+np.exp(-np.matmul(x,w))))

def update(y,fa,x,alpha):
    u = np.zeros((x.shape[1],y.shape[1])).astype(np.float32)
    for i in range(u.shape[1]):
        u[:,i] = (alpha * np.sum(((y-fa)*fa*(1-fa))[:,i][:,np.newaxis]*x,axis=0))
    return u
    
def save_model(outfile,w,uniquetags):
    np.savez(outfile,w=w,uniquetags=uniquetags)

class trainer:
    input_file = 0
    validate_file = 0
    feature_data = 0
    label_data = 0
    unique_labels = 0
    label_count = 0
    feature_count = 0
    example_count = 0
    target_values = 0
    targets = 0
    initial_weight_bound = 0
    batch_size = 0
    max_epoch = 0
    seed = 4788
    weights = 0
    learning_rate = 0
    sample_indices = 0
    batch_features = 0
    batch_targets = 0
    batch_prediction = 0
    validation_features = 0
    validation_targets = 0
    epoch = 0
    validation_errors = 0
    last_five_errors = 0
    def __init__(self, train_file, validate_file):
        self.input_file = np.loadtxt(train_file).astype(np.float32)
        self.feature_data = self.input_file[:,1:]
        self.label_data = self.input_file[:,0]
        self.unique_labels = np.unique(self.label_data)
        self.label_count = len(self.unique_labels)
        self.feature_count = self.feature_data.shape[1]
        self.example_count = self.feature_data.shape[0]
        self.target_values = [0.1,0.9]
        self.targets = np.zeros((self.example_count, self.label_count)).astype(np.float32)
        self.targets[:,:] = self.target_values[0]
        self.batch_size = 32
        self.max_epoch = 1000
        self.epoch = 0
        self.seed = 478848
        np.random.seed(self.seed)
        self.sample_indices = np.arange(self.example_count).astype(int)
        
        for i in range(self.label_count):
            self.targets[self.label_data==self.unique_labels[i],i] = self.target_values[1]
        self.init_weights()

        self.validate_file = np.loadtxt(validate_file)
        self.validation_features = self.validate_file[:,1:]
        self.validation_targets = self.validate_file[:,0].astype(int)

        self.validation_errors = np.zeros(0).astype(np.float32)
        self.last_five_errors = np.zeros(10).astype(np.float32)

    def init_weights(self):
        self.initial_weight_bound = 1/(1+math.sqrt(self.feature_count))
        self.weights = np.random.uniform(-self.initial_weight_bound,self.initial_weight_bound,self.feature_count*self.label_count).reshape((self.feature_count,self.label_count)).astype(np.float32)
    def increment_lr(self):
        self.learning_rate = (0.05/(1+math.pow(self.epoch,2))) # changed given learning rate formula from (2/(1+t^2)) to (0.05/(1+t^2)).
        
    def batch_step(self):
        step_count = 0
        np.random.shuffle(self.sample_indices)
        while step_count < self.example_count:
            self.batch_features = self.feature_data[self.sample_indices[step_count:step_count+self.batch_size]]
            self.batch_targets = self.targets[self.sample_indices[step_count:step_count+self.batch_size]]
            self.batch_prediction = predict(self.weights,self.batch_features)
            self.weights = self.weights + update(self.batch_targets, self.batch_prediction, self.batch_features, self.learning_rate)
            step_count = step_count + self.batch_size

    def validate(self):
        v = predict(self.weights,self.validation_features)
        p = np.argmax(v,axis=1).astype(int)
        valerr = (p == self.validation_targets)
        return sum(valerr)/len(valerr)
    def train(self):
        self.epoch = 1
        self.increment_lr()
        acc = 0
        max_acc = 0
        for i in range(self.max_epoch):
            self.batch_step()
            acc = self.validate()
            max_acc = self.last_five_errors[np.argmax(self.last_five_errors)]
            if acc < max_acc:
                if self.epoch > self.example_count/self.batch_size:
                    break
            self.validation_errors = np.append(self.validation_errors,acc)
            self.last_five_errors = np.roll(self.last_five_errors,-1)
            self.last_five_errors[len(self.last_five_errors)-1] = acc
            self.epoch = self.epoch + 1
            self.increment_lr()


if __name__ == '__main__':
    t = trainer(sys.argv[1],sys.argv[2])
    t.train()
    save_model(sys.argv[3],t.weights,t.unique_labels)
    



