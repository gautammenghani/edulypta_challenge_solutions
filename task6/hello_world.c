#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

char *myid = "testId";

MODULE_LICENSE("MIT");

static int device_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t device_read(struct file *filp,  char __user *buffer,
                           size_t length, loff_t *offset)
{	
	if (copy_to_user(buffer, myid, strlen(myid)))
		return -EFAULT;
	return 0;
}

static ssize_t device_write(struct file *filp, const char __user *buff,
                            size_t len, loff_t *off)
{
	char buffer[10];
	if(copy_from_user(buffer, buff, len))
		pr_warn("error in copy_from_user\n");
	if (!strncmp(buffer, myid, strlen(buffer))) 
		return 0;	
	return -EINVAL;
}

struct file_operations fops = {
       .read = device_read,
       .write = device_write,
       .open = device_open,
       .release = device_release
};

struct miscdevice md = {
	.minor = 0,
	.name = "edulypta",
	.fops = &fops,
};

static int __init hello_init(void){
	misc_register(&md);
	pr_debug("Hello world!\n");
	return 0;
}

static void __exit hello_exit(void) {
	misc_deregister(&md);
	pr_debug("Exiting ...\n");
}	


module_init(hello_init);
module_exit(hello_exit);
