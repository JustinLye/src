import sys
import numpy as np
import math

def load_model(infile):
    model = np.load(infile)
    w = model['W']
    unique_tags = model['uniquetags']
    return w,unique_tags