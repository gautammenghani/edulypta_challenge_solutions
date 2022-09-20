## Edulypta challenge solutions
The Eudyptula Challenge was a series of programming exercises for the Linux kernel. They have been archived on github. This repo is my attempt at solving the challenges:
### Task 1
Write a Linux kernel module, and stand-alone Makefile, that when loaded
prints to the kernel debug log level, "Hello World!"  Be sure to make
the module be able to be unloaded as well.

### Task 2
Download Linus's latest git and build it, install it, and boot it.

### Task 3
Take the kernel git tree from Task 02 and modify the Makefile to and modify the EXTRAVERSION field.  Do this in a way that the running kernel (after modifying the Makefile, rebuilding, and rebooting) has the characters "-eudyptula" in the version string.

### Task 4
The tasks for this round all deal with the Linux kernel coding style. Attached to this message are two kernel modules that do not follow the proper Linux kernel coding style rules.  Please fix both of them up, and send it back to me in such a way that does follow the rules.

### Task 5
Take the kernel module you wrote for task 0and modify it so that when a USB keyboard is plugged in, the module will be automatically loaded by the correct userspace hotplug tools (which are implemented by depmod / kmod / udev / mdev / systemd, depending on what distro you are using.)

### Task 6
Take the kernel module you wrote for task 01, and modify it to be a misc char device driver.  The misc interface is a very simple way to be able to create a character device, without having to worry about all of the sysfs and character device registration mess.

### Task 7
Download the linux-next kernel for today.  Or tomorrow, just use the latest one.  It changes every day so there is no specific one you need to pick.  Build it.  Boot it.

### Task 8
Take the kernel module you wrote for task 01, and modify it to be create a debugfs subdirectory called "eudyptula".  In that directory, create 3 virtual files called "id", "jiffies", and "foo".
  - The file "id" operates just like it did for example 06, use the same
    logic there, the file must be readable and writable by any user.
  - The file "jiffies" is to be read only by any user, and when read,
    should return the current value of the jiffies kernel timer.
  - The file "foo" needs to be writable only by root, but readable by
    anyone.  When writing to it, the value must be stored, up to one
    page of data.  When read, which can be done by any user, the value
    must be returned that is stored it it.  Properly handle the fact
    that someone could be reading from the file while someone else is
    writing to it (oh, a locking hint!)
  - When the module is unloaded, all of the debugfs files are cleaned
    up, and any memory allocated is freed.

### Task 9
Use sysfs to implement the same features as task8

## Task 10
Create a patch that fixes one coding style problem in any of the files in drivers/staging/

## Task 11
- Write a patch against any driver that you are currently using on
    your machine.  So first you have to figure out which drivers you are
    using, and where the source code in the kernel tree is for that
    driver.
- In that driver, add a sysfs file to show up in the /sys/devices/
  tree for the device that is called "id".  As you might expect, this
  file follows the same rules as task 09 as for what you can read and
  write to it.

