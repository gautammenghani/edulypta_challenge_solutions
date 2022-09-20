#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/init.h>
MODULE_LICENSE("GPL v2");

char *myid = "testId";
char foo_buffer[4096];

static struct kobject *eudyptula_kobj;
static int id, foo, jiff;

DEFINE_MUTEX(foo_lock);

//ID - read and write
static ssize_t id_show(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf)
{
	strncpy(buf, myid, strlen(myid));
	return strlen(myid);
}

static ssize_t id_store(struct kobject *kobj, struct kobj_attribute *attr,
                            const char *buf, size_t len)
{
	char buffer[10];
	sscanf(buf, "%s", buffer);
	pr_debug("got data: %s, %ld\n",	buf, strlen(buf));
	if (len-1 == strlen(myid) && !strncmp(buffer, myid, strlen(myid))) 
		return len;	
	return -EINVAL;
}

static struct kobj_attribute id_attribute = __ATTR(id, 0664, id_show, id_store);

//jiffies - read and write
static ssize_t jiffies_show(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf)
{
	return sprintf(buf, "%lu\n", jiffies);
}

static ssize_t jiffies_store(struct kobject *kobj, struct kobj_attribute *attr,
                            const char *buf, size_t len)
{
	return -EINVAL;
}

static struct kobj_attribute jiffies_attribute = __ATTR(jiffy, 0444, jiffies_show, jiffies_store);

//FOO - read and write
static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf)
{
	mutex_lock(&foo_lock);
	strncpy(buf, foo_buffer, strlen(foo_buffer));
	mutex_unlock(&foo_lock);
	return strlen(foo_buffer);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
                            const char *buf, size_t len)
{
	if (len > 4096) {
		pr_warn("Foo: Data size exceeded 4KB");
		return -EINVAL;
	}
	mutex_lock(&foo_lock);
	strncpy(foo_buffer, buf, len);
	mutex_unlock(&foo_lock);
	return len;	
}

static struct kobj_attribute foo_attribute = __ATTR(foo, 0644, foo_show, foo_store);

static struct attribute *attrs[] = {
	&id_attribute.attr,
	&jiffies_attribute.attr,
	&foo_attribute.attr,
	NULL,
};

static struct attribute_group attr_group = {
        .attrs = attrs,
};

static int __init hello_init(void){
	int ret;
	
	eudyptula_kobj = kobject_create_and_add("eudyptula", kernel_kobj);	
	if (!eudyptula_kobj)
		return -ENOMEM;

	ret = sysfs_create_group(eudyptula_kobj, &attr_group);
	if (ret)
		kobject_put(eudyptula_kobj);
	pr_debug("INIT called");
	return ret;
}

static void __exit hello_exit(void) {
	kobject_put(eudyptula_kobj);
	pr_debug("Exiting ...\n");
}	

module_init(hello_init);
module_exit(hello_exit);
