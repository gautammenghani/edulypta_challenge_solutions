#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/kthread.h>

char *myid = "testId";

MODULE_LICENSE("GPL v2");

DECLARE_WAIT_QUEUE_HEAD(wee_wait);
static struct task_struct *my_thread;

int thread_fn(void *data)
{
	while (1) {
		if (wait_event_interruptible (wee_wait, kthread_should_stop())) 
			return -ERESTARTSYS;
		if (kthread_should_stop())
			break;
	}
	return 0;
}

static ssize_t device_write(struct file *filp, const char __user *buff,
                            size_t len, loff_t *off)
{
	char buffer[10];
	if(copy_from_user(buffer, buff, len))
		pr_warn("error in copy_from_user\n");
	if (len == strlen(myid) && !strncmp(buffer, myid, strlen(myid))) 
		return 0;	
	return -EINVAL;
}

struct file_operations fops = {
       .write = device_write,
};

struct miscdevice md = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "edulypta",
	.fops = &fops,
};

static int __init hello_init(void){
	misc_register(&md);
	my_thread = kthread_run(thread_fn, NULL, "eudyptula");
	pr_debug("Hello world!\n");
	return 0;
}

static void __exit hello_exit(void) {
	misc_deregister(&md);
	if (!kthread_stop(my_thread))
		pr_debug("eudyptula kthread stopped\n");
	pr_debug("Exiting ...\n");
}	


module_init(hello_init);
module_exit(hello_exit);
