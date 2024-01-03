# multithreaded-sorting

How to use and compile
----------------------
1. ensure IntegerList.txt exists in the same directory as main.c
2. compile the file using: gcc -o main main.c -lpthread
3. run the code using: ./main
4. vim SortedIntegerList.txt to see the output

Sources
-------
The following sources were used for referencing <stdio.h> functions:

    accessing parameters in merger and sorter methods: parameters *param = (parameters *)params;
    TA help received from Yitong Zhou

    fgets():
    https://www.tutorialspoint.com/cprogramming/c_file_io.html

The following sources were used for referencing <pthread.h> functions:

    pthread_create() and pthread_join():
    Chapter 4 lecture notes pg. 26-25

The following sources were used for referencing <string.h> functions:

    strtok():
    http://www.cplusplus.com/reference/cstring/strtok/
