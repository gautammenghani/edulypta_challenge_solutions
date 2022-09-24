#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
MODULE_LICENSE("GPL v2");

struct identity {
	char name[20];
	int id;
	bool busy;
	struct list_head iden;
};

static LIST_HEAD(identity_list);

int identity_create(char *name, int id)
{
	struct identity *ident;
	if (strlen (name) > 20) {
		pr_debug ("Length of %s is more than 20", name);
		return -EINVAL;
	}

	ident = kmalloc(sizeof(*ident), GFP_KERNEL);
	strncpy(ident->name, name, 20);
	ident->name[19]='\0';
	ident->id = id;
	ident->busy = false;
	list_add_tail(&ident->iden, &identity_list);

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
	list_for_each_entry (i, &identity_list, iden){
		if (i->id == id) { 
			pr_debug("Destroying id: %d\n", id);
			list_del(&i->iden);
			return;
		}	
	}	
	pr_debug("Cannot delete id: %d, not found\n", id);
}

static int __init llist_init_mod(void) 
{
	struct identity *temp;

	identity_create("alice", 1);
	identity_create("bob", 2);
	identity_create("dave", 3);
	identity_create("gena", 10);
	
	list_for_each_entry(temp, &identity_list, iden) {
		pr_debug("id: %d\n",temp->id);	
		pr_debug("name: %s\n",temp->name);	
	}
	
	temp = identity_find(3);
	pr_debug("id 3 = %s\n", temp->name);

        temp = identity_find(42);
        if (temp == NULL)
                pr_debug("id 42 not found\n");

        identity_destroy(2);
        identity_destroy(1);
        identity_destroy(10);
        identity_destroy(42);
        identity_destroy(3);
	
	return 0;
}

static void __exit llist_exit_mod (void) 
{
	pr_debug("TASK 12: Exit method\n");
}

module_init(llist_init_mod);
module_exit(llist_exit_mod);
