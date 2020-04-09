##Files and their purpose:

-c2w.c -> main program file
-db.py -> python database functions
-fileUtils.c -> handles all the writing of logs to text files
-pyinterop.c -> handles the connectivity between c and python.
-results.txt -> contains values inserted into the database
-status.txt -> log file


##Run this command to compile the program:

gcc -I/usr/include/python3.6 c2w.c fileUtils.c pyinterop.c -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -L/usr/lib -lpython3.6m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

finally, run ./a.out to run the program.


###What it does:

It specifies the all the header files in the local directory and the location of python library files. The command is generated
from python-config.


##Setting up database

The schema.sql can be used to create a database for the program to send/recieve data into.


##Known Issues

There are errors that do occur when sending data to python, however the functionallity of the program is not affected.
The random numbers generated from C are inside the database and they get cleared based on the signal (alarm or ctrl-z).