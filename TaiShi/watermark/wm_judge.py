# function: 水印算法：水印嵌入、提取
# author： heany
# time：2019.1.10

import numpy as np
import pandas as pd
import hashlib
import random

import matplotlib.pyplot as plt
import matplotlib.colors

#k-means model
from sklearn.cluster import KMeans
from sklearn.cluster import DBSCAN

from sklearn.externals import joblib
from collections import Counter

# 载入文件
from wm_kmeans import *
import reedsolomon as RS

KEY = '1111100000'
# k = 5  # the number of datasets classes
a = 4  # the length of fractional part of numeric candidate attribute
p = 5  # the quantity of the attributes
# N = 32 # the length of the hash  function
c = 3  # the bits number of the sub_watermarking
m = 5 # the length of redundant check code
# clusters
# clusters = 9
i_set = set()
j_set = set()
x_set = set()
xx_set = set()

def watermark_encoding(rs, msg):
    '''
    :param msg: the string of watermark
    :param m: the length of redundant check code
    :return: the encoded watermarks 
    '''
    return  rs.encode(msg)

def watermark_regeneration(rs, wm_ext):
    '''
    :return: the recovered watermarks
    '''
    return rs.decode(wm_ext)


def Preprocess(msg,c):
    '''
    :function: conver the information into the numeric data and devide the wm into sub_wms
    :param msg: the information fo the copyright (words)
    :param c: the bits number of the sub_watermarking
    :return: the number of the clusters and the numeric wm segment (list)
    '''
    ch = []
    w_to_n = ''
    wm = [] # save the number of wm after teh split k clusters
    msg_list = msg.split(' ')
    # convert the word to the alphabet
    for word in msg_list:
        for e in word:
            ch.append(e)
    # convert the alphabet to the decimal number
    for item in ch:
        o = ord(item)
        w_to_n += str(o)

    k = len(w_to_n) / c  # the number of datasets classes
    # print("k=%f" % k)

    if k == int(k):
        # k is a integer
        # print("hhhhh")
        for it in range(k):
            wm.append(w_to_n[it*c:it*c+c])
    else:
        # k is a float
        k = int(k) + 1
        reminder = len(w_to_n) % c
        # print("re=%d" % reminder)
        for i in range(c-reminder):
            w_to_n += str(0)

        for it in range(k):
            wm.append(w_to_n[it*c:it*c+c])

    return wm
    pass


def Hash(src):
    m = hashlib.md5()
    m.update(src.encode('UTF-8'))
    md5 = m.hexdigest()
    return md5


def getHexStrMode(hex_str, mode_num):
    str_len = len(hex_str)
    result_mod = 0
    for idx, ch in enumerate(hex_str):
        result_mod = (result_mod * 16 + int(ch, 16)) % mode_num

    return result_mod


def wmMod(label,k):
    return (label+len(KEY)) % k


def float_split(num):
    '''
    :param num: num is a float
    :return: the integer and the fractional parts of the floating number
    '''
    s = str(num)
    s_list = s.split('.')
    # print(s_list)
    return [s_list[0],s_list[1]]
    pass


def Embeding(w,tuple,label,k):
    '''
    :param tuple: the tuple of the datasets
    :param label: the tuple's class-label
    :return: float // watermarked the tuple
    '''
    # k = len(w)
    H = Hash(KEY+str(label))
    H_t = int(H,16)
    # x = H_t % a     # select the position of the embeding watermarking
    i = H_t % p     # select the i-th attribute
    i_set.add(i)

    count = 0
    i_true = 0
    for it in range(len(KEY)): # list(KEY)
        if KEY[it] == '1':
            count = count + 1
        if count == i:
            i_true = it
            break

    # index = H_t % k
    index = wmMod(label,k)
    # start embeding the watermarking
    int_float = float_split(tuple[i_true])
    # x = H_t % len(str(int_float[1]))
    x = H_t % a
    x_set.add(x)

    sub_wm = w[index]

    # if x == 2 and sub_wm[-1] == '0':
    #     sub_wm += '1'


    # embeding the w[index] at the positions x and x+1 in the fractional part of A[i]
    if len(str(w[index])) == 2:
        float_get_str = int_float[1][:x] + str(0)+str(w[index]) + int_float[1][x:]
    else:
        float_get_str = int_float[1][:x] + str(w[index]) + int_float[1][x:]
    # return the watermarked tuple
    res = float(int_float[0] + '.' + float_get_str)
    tuple[i_true] = res

    return tuple,res

def Extracting(tuple,label,k):
    '''
    :param tuple: the tuple contained the watermarking
    :param label: the tuple's class-label
    :return: the watermarking of the class-label and the origin tuple
    '''
    H = Hash(KEY + str(label))
    H_t = int(H, 16)
    # x = H_t % a  # select the position of the embeding watermarking
    i = H_t % p  # select the i-th attribute
    # index = H_t % k
    j_set.add(i)

    # 将有用属性的索引映射到所有属性索引上
    count = 0
    i_true = 0
    for it in range(len(KEY)): # list(KEY)
        if KEY[it] == '1':
            count = count + 1
        if count == i:
            i_true = it
            break

    index = wmMod(label,k)
    # start extracting the watermarking
    int_float = float_split(tuple[i_true])
    # x = H_t % len(str(int_float[1]))
    x = H_t % a
    # x = x + 1
    xx_set.add(x)


    # extracting the w[index] at the positions x and x+1 in the fractional part of A[i]
    t = x + c
    float_get_str = int_float[1][:x] + int_float[1][t:]
    w = str(int_float[1])[x:t]
    res = float(int_float[0] + '.' + float_get_str)
    tuple[i_true] = res
    return w,index,tuple
    pass

def load_data():
    data = pd.read_csv("~/code/RS_wm/data/covtype_10000.csv", encoding='utf-8')
    # print(data.columns.size)
    # print(data.iloc[:,0].size)
    print(data.shape)
    return data[:1000]

def select_attrs(data):
    '''
    function: select the useful attribution according to the key
    :param data:
    :return: the useful attributes list
    '''
    attrs = list(data.columns)
    attrs_select = []
    for i in range(len(KEY)):
        if KEY[i] == '1':
            attrs_select.append(attrs[i])
    return attrs_select

def model_fit(data,attrs_select,clusters):
    # print(df.size)
    # print(df.columns)
    # select the attritutes according to the key
    # attrs_select = select_attrs(data)

    # DBSCAN
    # df = data.loc[:, attrs_select]
    # clf = DBSCAN(eps=0.5, min_samples=2).fit(df.values)
    # print(clf.labels_)
    #
    # res = pd.DataFrame()
    # res['score'] = clf.labels_
    # res.to_csv("./data_10_attr_dbscanpre.csv",encoding='utf-8')

    '''kmeans
    # train model
    clf = KMeans(n_clusters=clusters,random_state=28)
    df = data.loc[:,attrs_select]
    clf.fit(df.values)

    # save model
    joblib.dump(clf,"train_model.m")

    label_pred = clf.labels_
    c = [0,0,0,0,0]
    for x in label_pred:
        c[x] = c[x] + 1
    # the quantity of each clusters
    print(c)
    '''

    # the cluster algorithm by heany
    clf = KMeans_H(clusters)
    df = data.loc[:,attrs_select]
    clf.fit(df)
    label_pred = clf.labels_

    # 计算每一类的记录的数目

    c = list()
    for i in range(clusters):
        c.append(0)
    for item in label_pred:
        c[item] +=1
    print(c)

    return clf

def tuple_prediction(clf,tuple_list):
    num = []
    # convert the two dim list to the one dim list
    # tup = list(np.hstack(tuple_list))

    for i in range(len(KEY)):
        if KEY[i] == '1':
            num.append(tuple_list[i])
    label_list = clf.predict(num)
    return label_list
    pass

def recover_wm(dict_wm):
    extract_wm = []
    for key,value in dict_wm.items():
        if len(value) == 0:
            extract_wm.append("**")
            continue
        z = Counter(value).most_common(1)[0][0]
        if len(z) == c-1:
            # z = Counter(value).most_common(2)[1][0]
            z += '0'
        extract_wm.append(z)

    return extract_wm

def alter_tuple(tup):
    '''
    :param tup: the record of dataset
    :return: new tuple after alternation the value
    :description: 随机选择元组的一个属性r，将r插入到属性r的小数部分
    '''
    tt = tup.copy()
    r = random.sample(range(0,10),1)[0]
    t = float_split(tup[r])
    newValue = float(str(t[0]+'.'+str(r)+t[1]))
    tt[r] = newValue
    return tt

    pass

def test():
    t = [2596.021,51.021,3.021,258.021,0.021,510.021,221.021,232.021,148.021,6279.021]
    n ,r= alter_tuple(t)
    print(t)
    print(n)
    print(r)

def main():

    msg = 'HITSZ'

    rs = RS.RSCodec(m)
    wm_num = watermark_encoding(rs,msg)
    # wm_num = Preprocess(msg, c)
    print("the original wm !!!")
    print(wm_num)
    k = len(wm_num)

    data = load_data()
    size = data.iloc[:,0].size
    # print("size:"+str(size))
    attrs_select = select_attrs(data)
    clf = model_fit(data,attrs_select,k)

    # 使用kmeas时使用
    # clf = joblib.load("train_model.m")

    # print(data.shape)

    '''
    # save the data after embedding the wm
    data_wm = pd.DataFrame(columns=list(data.columns))

    #逐条嵌入水印
    for i in range(size):
        tup = list(data.loc[i].values)
        # print(tup)
        label = tuple_prediction(clf,tup)
        # print(label)
        tup_w,res = Embeding(wm_num,tup,label,k)
        data_wm.loc[i] = tup_w

    # save the watermarked data
    data_wm.to_csv("~/code/RS_wm/data/data_wm_1000_em_wm.csv",encoding='utf-8',index=False)
    '''

    # initial the wm array
    dict_wm = {}
    for i in range(k):
        dict_wm[str(i)] = []

    # save the data after extract the wm
    data_ext_wm = pd.DataFrame(columns=list(data.columns))

    # 读取已嵌入水印的数据
    data_wm = pd.read_csv("./data/data_wm_1000_em_wm.csv",encoding='utf-8')
    # print(data_wm[:2])

    # for ccount,row in data_wm.iterrows():
    #     if ccount == 1000:
    #         break
    #     data_wm.loc[ccount] = alter_tuple(list(row.values))
    #     pass
    # print(data_wm[:2])

    # Addition attack
    # data_wm = pd.concat([data_wm,data[:900]],axis=0, ignore_index=True)
    # print(data_wm.shape)

    # subset deletion attack
    # Delete consecutive tuples
    # data_wm = data_wm[:100]

    # Deletion Randomly
    l = random.sample(range(0,1000),100)

    # Alteration attacks

    l = data_wm.iloc[:,0].size

    for i in range(l):
        tup = list(data_wm.loc[i].values)
        # print(tup)
        label = tuple_prediction(clf, tup)
        wm, index, t_origin = Extracting(tup,label,k)
        dict_wm[str(index)].append(wm)
        data_ext_wm.loc[i] = t_origin

        # print(wm)
        # print(index)
        # print(t_origin)
        # break
    
    # save the data after extracting watermarking 
    # data_ext_wm.to_csv("~/code/RS_wm/data/data_1000_ext_wm_20190215.csv",encoding='utf-8')
    # print(dict_wm)

    # recover the wm
    print("the extract the wm!!")
    wm_ext = recover_wm(dict_wm)
    print(wm_ext)

    print("the recovered watermarks!!")
    wm_rec = watermark_regeneration(rs, [int(ch) for ch in wm_ext])
    print(wm_rec)
    print([ch for ch in wm_rec])

    # print(i_set)
    # print(x_set)
    # print("extract")
    # print(j_set)
    # print(xx_set)


    pass

if __name__ == '__main__':
    main()
    # test()



# test = [[5.959,0.572,3.06,2.93,0.47,1.135,0.072,0.353,35.1,0.13,0.4]]
# # clf = model_fit(clusters)
# clf = joblib.load("train_model.m")
# x = tuple_prediction(clf,test)[0]
# print(x)

# test = [[6.78,3.47,2.81,2.28,1.31],
#         [5.78,3.62,1.99,2.3,1.27],
#         [5.82,4.96,1.99,2.35,1.63],
#         [2.69,3.09,0.91,1.68,1.17]]
# # embedding the watermarking
# test_wm = [[6.78001101,3.47,2.81,2.28,1.31001101],
#             [5.78001101,3.62,1.99,2.3,1.27001101],
#             [5.82001101,4.96,1.99,2.35,1.63001101],
#             [2.69001101,3.09,0.91,1.68,1.17001101]]
#
#
# label_test = clf.predict(test)
# label_test_wm = clf.predict(test_wm)
#

# # centeroids = km.cluster_centers_
# # inertia = km.inertia_
# print("Before embedding the watermarking")
# print(label_test)
# print("After embeding the watermaking")
# print(label_test_wm)

# label_pred = clf.labels_
# c = [0,0,0,0,0,0,0,0,0]
# for x in label_pred:
#     c[x] = c[x] + 1
# # the quantity of each clusters
# print(c)


# res = pd.DataFrame()
# res['score'] = label_pred
# res.to_csv(r"/home/heany/code/wm/data_5_attr_pre.csv",encoding='utf-8')
#
# print(label_pred)
