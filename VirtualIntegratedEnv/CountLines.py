import os

def getNumOfLines(file):
    NumOflines = 0
    with open(file, "r") as filing:
        for line in filing:
            NumOflines = NumOflines + 1
    return NumOflines

'Get a list of files existing in the current directory'
filelist = os.listdir()

totalNumOfLines = 0

for each_file in filelist:
    if each_file[-3:] == 'cpp':
        #print('cpp: ' + each_file)
        totalNumOfLines = totalNumOfLines + getNumOfLines(each_file)
    if each_file[-1] == 'h':
        #print('h: ' + each_file)
        totalNumOfLines = totalNumOfLines + getNumOfLines(each_file)

print('Total lines of files: ', totalNumOfLines)
