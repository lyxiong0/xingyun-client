import sys
import argparse
import json

#  传入变量，字符串格式

filename = sys.argv[0]
string = sys.argv[1]

print(filename)
print(string)
# print(sys.argv[2])

# 传入json格式的字符分串
# parser = argparse.ArgumentParser(description='json load and watermarking Embedding') 
# parser.add_argument('-f','--filename', help='Input String as filename',required=True) 
# parser.add_argument('-w','--watermark', help='Input String as watermarking',required=True)
# parser.add_argument('-r','--record', help='Input String in JSON format as record',required=True) 
# args = parser.parse_args() 

# inp = parser.parse_args() 
# inp = args.inputstring 
# data = json.loads(inp) 
# print(data['Employees']) 
# print(data['boy'])

# print(args.filename)