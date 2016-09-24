#!/usr/bin/env python3

import sys
import numpy as np
import math

def predict(w,x,b):
    return (1/(1+np.exp(-np.matmul(x,w)+b)))

def update(y,fa,x,alpha):
    u = np.zeros((x.shape[1],y.shape[1])).astype(np.float32)
    for i in range(u.shape[1]):
        u[:,i] = (alpha * np.sum(((y-fa)*fa*(1-fa))[:,i][:,np.newaxis]*x,axis=0))
    return u
    
def save_model(outfile,w,b,label_count,feature_count,uniquetags):
    np.savez(outfile,w=w,b=b,label_count=label_count,feature_count=feature_count,uniquetags=uniquetags)

class trainer:
    input_file = 0
    validate_file = 0
    bias = 0
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
    batch_bias = 0
    validation_features = 0
    validation_targets = 0
    epoch = 0
    tlu_collection_errors = 0
    tlu_individual_errors = 0
    last_five_errors = 0
    validation_bias = 0
    weight_hist = 0
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
        #self.seed = 47834
        self.seed = 342
        self.weight_hist = np.zeros((1,self.feature_count,self.label_count))

        np.random.seed(self.seed)
        self.sample_indices = np.arange(self.example_count).astype(int)
        
        for i in range(self.label_count):
            self.targets[self.label_data==self.unique_labels[i],i] = self.target_values[1]
        self.init_weights_and_bias()
        self.weight_hist[0,:]=self.weights
        self.validate_file = np.loadtxt(validate_file)
        self.validation_features = self.validate_file[:,1:]
        self.validation_targets = self.validate_file[:,0].astype(int)
        self.validation_bias = np.zeros(self.validation_features.shape[0])[:,np.newaxis]
        self.tlu_collection_errors = np.zeros(0).astype(np.float32)
        self.tlu_individual_errors = np.zeros((1,self.label_count)).astype(np.float32)
        self.last_five_errors = np.zeros(5).astype(np.float32)

    def init_weights_and_bias(self):
        self.initial_weight_bound = 1/(1+math.sqrt(self.feature_count))
        self.weights = np.random.uniform(-self.initial_weight_bound,self.initial_weight_bound,self.feature_count*self.label_count).reshape((self.feature_count,self.label_count)).astype(np.float32)
        self.bias = np.random.uniform(-self.initial_weight_bound, self.initial_weight_bound,self.example_count).reshape((self.example_count,1)).astype(np.float32)
    def increment_lr(self):
        self.learning_rate = (2/(1+math.pow(self.epoch,2))) # changed given learning rate formula from (2/(1+t^2)) to (0.05/(1+t^2)).
        
    def batch_step(self):
        step_count = 0
        np.random.shuffle(self.sample_indices)
        while step_count < self.example_count:
            self.batch_features = self.feature_data[self.sample_indices[step_count:step_count+self.batch_size]]
            self.batch_targets = self.targets[self.sample_indices[step_count:step_count+self.batch_size]]
            self.batch_bias = self.bias[self.sample_indices[step_count:step_count+self.batch_size]]
            self.batch_prediction = predict(self.weights,self.batch_features,self.batch_bias)
            self.weights = self.weights + update(self.batch_targets, self.batch_prediction, self.batch_features, self.learning_rate)
            step_count = step_count + self.batch_size
    
    def tlu_validate(self, tlu_num):
        pred = predict(self.weights[:,tlu_num][:,np.newaxis],self.validation_features,self.validation_bias)
        check = (pred >= 0.5)
        val = (self.validation_targets == self.unique_labels[tlu_num])[:,np.newaxis]
        err = (check==val).astype(int)
        return 1-sum(err)/len(err)

    def validate(self):
        batch_error = np.zeros((1,self.label_count)).astype(np.float32)
        for i in range(self.label_count):
            batch_error[:,i] = self.tlu_validate(i)
        if self.epoch == 1:
            self.tlu_individual_errors = batch_error.copy()
        else:
            self.tlu_individual_errors = np.append(self.tlu_individual_errors,batch_error,axis=0)
        v = predict(self.weights,self.validation_features,self.validation_bias)
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
            self.tlu_collection_errors = np.append(self.tlu_collection_errors,1-acc)
            self.last_five_errors = np.roll(self.last_five_errors,-1)
            self.last_five_errors[len(self.last_five_errors)-1] = acc
            self.epoch = self.epoch + 1
            self.increment_lr()
            self.weight_hist = np.insert(self.weight_hist,self.weight_hist.shape[0],self.weights,axis=0)


if __name__ == '__main__':
    t = trainer(sys.argv[1],sys.argv[2])
    t.train()
    w = t.weight_hist[np.argmax(np.sum(t.tlu_individual_errors,axis=1))]
    save_model(sys.argv[3],t.weights,t.bias,t.label_count, t.feature_count, t.unique_labels)
    if len(sys.argv) > 5:
        np.savetxt(sys.argv[4],t.tlu_collection_errors)
        np.savetxt(sys.argv[5],t.tlu_individual_errors)
    
    



