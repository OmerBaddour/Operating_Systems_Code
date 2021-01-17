cp_posix:

To compile, type $ make cp_posix

MAC OS
To trace system calls, first run the program $ ./cp_posix
Then in another window, type $ sudo dtruss -n cp_posix 
In the window running cp_posix, interact with the program, and see the 
triggered system calls in the dtruss window

Linux
One window $ ./cp_posix
Another window: find PID using $ top
Then $ sudo strace -c -p <PID>
Then go back to window running ./cp_posix, and run until termination
Then back to strace window to see system calls 
See pages 96-101 of the textbook (118-123 of pdf)

Clean with $ make clean

-------------------------------------------------------------------------------

birthday:

To compile, type $ make birthday

To load kernel module, type $ sudo insmod birthday.ko
See kernel buffer with $ dmesg
Unload kernel module with $ sudo rmmod birthday
Clear kernel buffer with $ sudo dmesg -c

Clean with $ make kclean
