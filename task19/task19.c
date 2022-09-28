#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/textsearch.h>
MODULE_LICENSE("MIT");

#define MY_ID "myTestId"
static  struct ts_config *conf;

static unsigned int testid_hook(void *priv, struct sk_buff *skb, const struct nf_hook_state *hook_state)
{
        int pos=-1;
        struct ts_state state;

        memset(&state, 0, sizeof(struct ts_state));

        pos = skb_find_text(skb, 0, INT_MAX, conf);
        if (pos!=-1)
                pr_debug(MY_ID " found at %d\n", pos);

        return NF_ACCEPT;
}

static struct nf_hook_ops euhooks =  {
        .hook = testid_hook,
        .hooknum = NF_INET_PRE_ROUTING,
        .pf = NFPROTO_IPV4,
        .priority = NF_IP_PRI_FIRST
};

static int __init hello_init(void)
{
        pr_debug("Registering hook\n");

        conf = textsearch_prepare("kmp", MY_ID, 8, GFP_KERNEL, TS_AUTOLOAD);
        if (IS_ERR(conf))
                return PTR_ERR(conf);

        return nf_register_net_hook(&init_net,&euhooks);
}

static void __exit hello_exit(void)
{
        pr_debug("Unregistering hook\n");
        textsearch_destroy(conf);
        nf_unregister_net_hook(&init_net,&euhooks);
}

module_init(hello_init);
module_exit(hello_exit);


