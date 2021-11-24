# README

To compile just run the **make** command in the shell since the makefile compiles both at the same time, thus producing two excutable files called **simplethread1** and **simplethread2**  

To execute a program just run the **./simplethread1** < natural number > commad with a single number as argument representing the numeber of threads the program uses. For example, to execute first program with 3 threads type the following commad ** ./simplethread1 3 **. The same thing can be done with the second program, ** ./simplethread2 3 ** will run the second program with 3 threads.

To remove the executables just run the following command ** make clean ** since we remove both executables at the same time

In Part 1, we don't have any synchronization between the threads so we see multiple writes happening to the shared variable,making the system insecure. Also, race conditions occurred as multiple threads are trying to read the value of the shared variable. They then compete to try to be the last to write the result of their operation to the variable. The value of the last one is preserved since it has overwritten the result of the others, making the final value different for each thread.