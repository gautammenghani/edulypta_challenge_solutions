## Edulypta challenge solutions
The Eudyptula Challenge was a series of programming exercises for the Linux kernel. They have been archived on github. This repo is my attempt at solving the challenges:
### Task 1
1. Write a Linux kernel module, and stand-alone Makefile, that when loaded
prints to the kernel debug log level, "Hello World!"  Be sure to make
the module be able to be unloaded as well.

### Task 2
1. Download Linus's latest git and build it, install it, and boot it.

### Task 3
1. Take the kernel git tree from Task 02 and modify the Makefile to and modify the EXTRAVERSION field.  Do this in a way that the running kernel (after modifying the Makefile, rebuilding, and rebooting) has the characters "-eudyptula" in the version string.

### Task 4
1. The tasks for this round all deal with the Linux kernel coding style. Attached to this message are two kernel modules that do not follow the proper Linux kernel coding style rules.  Please fix both of them up, and send it back to me in such a way that does follow the rules.
