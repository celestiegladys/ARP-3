#!/bin/bash

# In order to install the program you have to run the "install.sh".
# If there isn't any first argument, which is <pathname>, there will be an echo containing the information to how install the program
# <pathname> is the folder you have to create in which you insert all processes' folders.

if [ $# -eq 0 ]

then
    echo "To install correctly enter this line: source ./install.sh <pathname> ";
    exit;
fi

# If there isn't any folder inside the path, we have to create it. We can check if there is a 
# folder and this if statement ($1 is the folder we have to create).

if [ ! -d $1 ]

then
 echo "There is an ERROR: $1 directory does NOT exist!";
 while true; do
  read -p "Do you want to create $1 directory? [y/n] " yn
  case $yn in
   [y]* ) mkdir $1; break;;
   [n]* ) exit;;
   * ) "y = yes & n = no";;
  esac
 done
fi

# The following lines we will unzip the sources.script. 
# We export the path of the folder in order to use it in a file bash.

echo "Program installation on $1 ... ";
export X=$1;
unzip sources.zip -d $1;

# Compile of all the .c files and we put the executables and moved the executables inside a new folder.

echo "Compiling files on sources ...";
cd $1

cd sources
gcc f.c -o f -lpthread -lrt
cd ..

mkdir executables

mv sources/f executables
cd ..

echo "Run the program with ./run.sh ";


Philosophers.txt