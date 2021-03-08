# function: 聚类算法，注重均衡性
# author： heany
# time：2018.11.19

import numpy as np
import random
import pandas as pd
import matplotlib.pyplot as plt


def parttion(list1,left,right):
    # 找到中间的那个数
    key = list1[left]
    while left < right:
        # 由后开始向前搜索(right--)，找到第一个小于key的值A[right]，将A[left]和A[right]互换
        while left < right and list1[right] >= key:
            right -= 1
        list1[left] = list1[right]
        # 由前开始向后搜索(left++)，找到第一个大于key的A[left]，将A[right]和A[left]互换；
        while left < right and list1[left] <= key:
            left += 1
        list1[right] = list1[left]
        list1[left] = key
    return left

def quickSort(list1, left, right):
    if left < right:
        # 先对序列排序，并找到一个元素A，这个元素的特点是：左边的元素<=A,右边的元素>=A
        p = parttion(list1,left,right)
        quickSort(list1,left,p)          # 对A的左边递归
        quickSort(list1,p+1,right)       # 对A的右边递归

def getInt(frac):

    if isinstance(frac, int):
        return frac
    s = str(frac)

    s_list = s.split('.')

    return int(s_list[0])

class KMeans_H:

    def __init__(self,  n_clusters):
        self.n_clusters = n_clusters

        pass
    sampleDist_sorted = list()
    # centroidInterval = dict()
    clusterDict = dict()
    clusterSampleDict = dict()
    labels_ = list()
    centroid_ = list()
    
    def calculateDistance(self, vecA):
        # 计算向量vecA和零向量之间的欧氏距离
        # 求出每条记录的所有的特征的平方和，作为一个特征f(x)

        int_p = []
        for it in vecA:
            int_p.append(getInt(it))

        return np.sqrt(np.sum(np.square(np.array(int_p) - 0)))
        # return np.sqrt(np.sum(np.square(vecA - 0)))

    
    def fit(self, X):
        # 将所有的记录的f(x)按照距离从小到大排序
        sampleDistance = list()
        # X = np.array(X)
        store_X = X.copy()

        for item in X.values:
            sampleDistance.append(self.calculateDistance(np.array(item)))

        self.sampleDist_sorted = sampleDistance.copy()
        quickSort(self.sampleDist_sorted,0,len(self.sampleDist_sorted)-1)

        # 初始化聚类分组，k组
        # clusterDict = dict()
        for i in range(self.n_clusters):
            self.clusterDict[i] = list()
            self.clusterSampleDict[i] = list()

        counter = int(len(sampleDistance)/self.n_clusters)
        flag = 0
        c = 0
        for sample in self.sampleDist_sorted:
            c += 1
            self.clusterDict[flag].append(sample)
            if flag == self.n_clusters-1:
                continue
            if c == counter:
                flag += 1
                c = 0
        


        # 预测所有的数据的类标
        for temp in store_X.values:
            t = self.predict(temp)
            self.labels_.append(t)
            self.clusterSampleDict[t].append(temp)

    
    def getInterval(self):
        # 计算出每个类的区间centroidInterval=>Dict()，

        # 初始化
        centroidInterval = dict()
        for i in range(self.n_clusters):
            centroidInterval[i] = list()

        for key,value in self.clusterDict.items():
            centroidInterval[key].append(value[0])
            centroidInterval[key].append(value[-1])
        
        return centroidInterval
    
    # def getlabels_(self):
    #     return self.labels_

    
    def getcentroid_(self):
        # 获得每一个分类的区间=>list()
        centroidInterval = self.getInterval()
        for value in centroidInterval.values():
            self.centroid_.append(value)
        return self.centroid_


    def predict(self, test_x):
        # 预测单条记录的label
        test_x_dist = self.calculateDistance(np.array(test_x))

        centroidInterval = self.getInterval()

        for key,value in centroidInterval.items():
            if value[0] > test_x_dist:
                return key
            if value[0] <= test_x_dist and test_x_dist <= value[1]:
                return key
        return key
        
        pass





# data = pd.read_csv("~/code/wm/data_10_attr.csv", encoding='utf-8')
# data.drop(['Unnamed: 0'], inplace=True, axis=1)

# data = data[:100]

# k = 4

# clf = KMeans_H(k)
# clf.fit(data)
# label = clf.labels_

# # 计算每一类的记录的数目

# c = list()
# for i in range(k):
#     c.append(0)
# for item in label:
#     c[item] +=1
# print(c)
# # print(label[:10])







# # centroidInterval

# # test
# #------------------

# # vecA=np.array([1,2,3])
# #
# # print(calculateDistance(vecA))

# # list1 = [random.randint(1,999) for i in range(100)]
# # list11 = list1.copy()
# # print(list1)
# # quickSort(list1,0,len(list1)-1)
# # print("aaa")
# # print(list1)