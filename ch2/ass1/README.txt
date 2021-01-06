See page 96 of the textbook (118 of pdf)

To compile, type $ make

To trace system calls, first run the program $ ./cp_posix
Then in another window, type $ sudo dtruss -n cp_posix 
In the window running cp_posix, interact with the program, and see the triggered system calls in the dtruss window
