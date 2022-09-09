#include <linux/module.h>
MODULE_LICENSE("MIT");

static int __init hello_init(void){
	pr_debug("Hello world!\n");
	return 0;
}

static void __exit hello_exit(void) {
	pr_debug("Exiting ...\n");
}	

module_init(hello_init);
module_exit(hello_exit);
