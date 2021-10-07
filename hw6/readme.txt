Homework 6 - Austin Krause

I ran the savedset_demo program and followed the steps used to make the program
function properly. In the first root execution, the Effective User ID changes, but
the Real User ID does not. This is expected as the EUID changes for each process
change. When the mail user is the owner of the program, the program does not finish
because it is not root.

This goes for the setreuid API as well. The results stayed the same after changing 
each seteuid() check to setreuid().