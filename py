import sys
import os
import re
import glob

print('Hi, I can count the occurrences of each word in a document.')

#задать путь к файлу, закинув его в переменную
print('Please, enter the path to the file.')
path = (input())
#path = '/Users/daniiltrenkin/PycharmProjects/untitled/work_file.c'
#path = '/Users/daniiltrenkin/PycharmProjects/untitled/'



#for top, dirs, files in os.walk('/Users/daniiltrenkin/PycharmProjects/untitled/'):
#    for nm in files:
#        print (os.path.join(top, nm))

#directory = '/Users/daniiltrenkin/PycharmProjects/untitled/'
#files = os.listdir(directory)
#texts = filter(lambda x: x.endwith('.txt'), files)
#print(files)

# for files in glob.glob(os.path.join(path, '*.txt')):
#     print(files)
#     filelist = glob.glob(os.path.join(path, '*.txt'))
#     print('asd')
#     file = open('1.txt', 'w')
#     file.write(str(filelist))

file = open(path, 'r')
try:
    text = file.read()
finally:
    file.close()

# регулярка для слов
pattern = re.compile("((?:[a-zA-Z]+[-']?)*[a-zA-Z]+)")
result = pattern.findall(text)

# pattern = re.compile("((?:[a-zA-Z]+[-']?)*[a-zA-Z]+)")
# for file in glob.glob('*.txt'):
#     with open(file) as fp:
#         for result in pattern.findall(text):
#             print(result)

# создание частотного словарь
frequency = {}
for word in result:
    word = word.lower()
    if word in frequency:
        value = frequency[word]
        frequency[word] = value + 1
    else:
        frequency[word] = 1



# создание сортировщика слов и вывод в файл
sorter = sorted(frequency, key=lambda x: int(frequency[x]), reverse=True)
file = open('result.txt', 'w')
try:
    for word in sorter:
        s = "{1} {0}\n".format(word, frequency[word])
        file.write(s)
    print('Done! You can now view the result in the same directory in the ' +  '"result.txt"')
finally:
    file.close()