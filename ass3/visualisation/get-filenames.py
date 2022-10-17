''' Tool to get filenames of the puzzles folder. This file
    should be run from the parent folder of the puzzles folder.
'''

from os.path import join, dirname, realpath
import os

# get the file names of puzzles folder
def get_filenames():
    files = []
    

    # get the path of the current file
    path = dirname(realpath(__file__))

    # get the path of the puzzles folder
    path = join(path, 'puzzles')

    # get the file names of the puzzles folder
    for file in os.listdir(path):
        if file.endswith(".txt"):
            files.append(file)
        
    return files

def main():
    
    list = get_filenames()

    # sort the file names
    list.sort()

    # print the file names
    for file in list:
        print(file)


if __name__ == '__main__':
    main()