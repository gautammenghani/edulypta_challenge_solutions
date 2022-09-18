#include <linux/module.h>
#include <linux/debugfs.h>
MODULE_LICENSE("GPL v2");

struct dentry *debug_dir = NULL;
struct dentry *debug_file = NULL;
char *myid = "testId";
char foo_buffer[4096];

DEFINE_MUTEX(foo_lock);

//ID - read and write
static ssize_t id_read(struct file *filp,  char __user *buffer,
                           size_t length, loff_t *offset)
{
	if (copy_to_user(buffer, myid, strlen(myid)))
		return -EFAULT;
	return 0;
}

static ssize_t id_write(struct file *filp, const char __user *buff,
                            size_t len, loff_t *off)
{
	char buffer[10];
	if(copy_from_user(buffer, buff, len))
		pr_warn("error in copy_from_user\n");
	if (len == strlen(myid) && !strncmp(buffer, myid, strlen(myid))) 
		return 0;	
	return -EINVAL;
}

struct file_operations id_fops = {
       .read = id_read,
       .write = id_write,
};

//FOO - read and write
static ssize_t foo_read(struct file *filp,  char __user *buffer,
                           size_t length, loff_t *offset)
{
	mutex_lock(&foo_lock);
	if (copy_to_user(buffer, foo_buffer, strlen(foo_buffer)))
		return -EFAULT;
	mutex_unlock(&foo_lock);
	return 0;
}

static ssize_t foo_write(struct file *filp, const char __user *buff,
                            size_t len, loff_t *off)
{
	if (len > 4096) {
		pr_warn("Foo: Data size exceeded 4KB");
		return -EINVAL;
	}
	mutex_lock(&foo_lock);
	if(copy_from_user(foo_buffer, buff, len)){
		pr_warn("error in copy_from_user\n");
		return -EINVAL;
	}
	mutex_unlock(&foo_lock);
	return 0;	
}

struct file_operations foo_fops = {
       .read = foo_read,
       .write = foo_write,
};


static int __init hello_init(void){
	debug_dir = debugfs_create_dir("edulypta", NULL);
	if (!debug_dir) {
		pr_err("debugfs directory creation failed");
		return -1;
	}
	debugfs_create_file("id", 0666, debug_dir, NULL, &id_fops);
	debugfs_create_u32("jiffies", 0444, debug_dir, (u32*)&jiffies);
	debugfs_create_file("foo", 0644, debug_dir, NULL, &foo_fops);
	pr_debug("Debugfs dir and files created!\n");
	mutex_init(&foo_lock);
	return 0;
}

static void __exit hello_exit(void) {
	debugfs_remove_recursive(debug_dir);
	pr_debug("Exiting ...\n");
}	

module_init(hello_init);
module_exit(hello_exit);
