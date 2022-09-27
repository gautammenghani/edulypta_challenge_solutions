#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/fs.h>
MODULE_LICENSE("GPL v2");

struct identity {
        char name[20];
        int id;
        bool busy;
        struct list_head iden;
};

static LIST_HEAD(identity_list);
DEFINE_MUTEX(list_lock);

DECLARE_WAIT_QUEUE_HEAD(wee_wait);
static struct task_struct *my_thread;
static int counter = 0;


int identity_create(char *name, int id)
{
        struct identity *ident;
        if (strlen (name) > 20) {
                pr_debug ("Length of %s is more than 20", name);
                return -EINVAL;
        }
        mutex_lock_interruptible(&list_lock);
        ident = kmalloc(sizeof(*ident), GFP_KERNEL);
        strncpy(ident->name, name, 20);
        ident->name[19]='\0';
        ident->id = id;
        ident->busy = false;
        list_add(&ident->iden, &identity_list);
        mutex_unlock(&list_lock);
        return 0;
}

struct identity *identity_find(int id)
{
        struct identity *i;

        list_for_each_entry (i, &identity_list, iden)
        {
                if (i->id == id)
                        return i;
        }
        return NULL;
}

void identity_destroy (int id)
{
        struct identity *i;
        mutex_lock(&list_lock);
        list_for_each_entry (i, &identity_list, iden){
                if (i->id == id) { 
                        pr_debug("Destroying id: %d\n", id);
                        list_del(&i->iden);
                        kfree(i);
                        goto out;
                }
        }
        pr_debug("Cannot delete id: %d, not found\n", id);
out:
        mutex_unlock(&list_lock);
}

static struct identity *identity_get(void)
{
        struct identity *i;
        mutex_lock(&list_lock);
        i = list_first_entry_or_null(&identity_list, struct identity, iden);
        if (i)
                list_del(&i->iden);
        mutex_unlock(&list_lock);
        return i;
}

int thread_fn(void *data)
{
        struct identity *i;
        while (1) {
                if (wait_event_interruptible (wee_wait, 1))
                        return -ERESTARTSYS;
                if (kthread_should_stop())
                        return 0;
                i = identity_get();
                if (i) {
                        msleep_interruptible(5000);
                        pr_debug("From kernel thread - Name is %s, id is %d\n", i->name, i->id);
                        kfree(i);
                }
        }
        return 0;
}

static ssize_t device_write(struct file *filp, const char __user *buff,
                            size_t len, loff_t *off)
{
        char buffer[19];
        int res;
        if(copy_from_user(buffer, buff, len))
                pr_warn("error in copy_from_user\n");
        //if (strlen(buffer) > 19)
        //      buffer[19] = '\0';
        buffer[len] = '\0';

        res = identity_create(buffer, counter++);
        if (res) {
                pr_warn("device_write(): could not create new identity\n");
                return res;
        }
        pr_debug("New elem created : %s | %d | ", buffer, counter-1);
        wake_up(&wee_wait);
        return len;
}

struct file_operations fops = {
       .write = device_write,
};

struct miscdevice md = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = "eudyptula",
        .fops = &fops,
        .mode = 0222
};

static int __init llist_init_mod(void) 
{
        struct identity *temp;

        misc_register(&md);
        my_thread = kthread_run(thread_fn, NULL, "eudyptula");
        mutex_init(&list_lock);

        identity_create("alice", 1);
        identity_create("bob", 2);
        identity_create("dave", 3);
        identity_create("gena", 10);

        list_for_each_entry(temp, &identity_list, iden) 
                pr_debug("id: %d, name : %s\n",temp->id, temp->name);
        /*
        identity_destroy(2);
        identity_destroy(1);
        identity_destroy(10);
        identity_destroy(42);
        identity_destroy(3);
        */
        return 0;
}

static void __exit llist_exit_mod (void) 
{
        struct identity *i, *next;
        pr_debug("TASK 18: Exit method\n");
        misc_deregister(&md);
        if (!kthread_stop(my_thread))
                pr_debug("eudyptula kthread stopped\n");

        list_for_each_entry_safe(i, next, &identity_list, iden){
                pr_debug("Deleting element - name: %s, id: %d\n", i->name, i->id);
                list_del(&i->iden);
                kfree(i);
        }

}

module_init(llist_init_mod);
module_exit(llist_exit_mod);
