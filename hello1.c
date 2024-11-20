#include <linux/module.h>
#include <linux/slab.h>
#include <linux/printk.h>
#include "hello1.h"


MODULE_AUTHOR("Bondarenko Taras");
MODULE_DESCRIPTION("Hello1 module for kernel training");
MODULE_LICENSE("Dual BSD/GPL");


static LIST_HEAD(list_head);
void print_hello(void)
{
	struct list_item *item;

    item = kmalloc(sizeof(*item), GFP_KERNEL);
    if (!item) {
	pr_err("Memory allocation failed for list_item\n");
	return;
    }
    item->start = ktime_get();
    pr_info("Hello, world!\n");
    item->end = ktime_get();
    list_add_tail(&item->list, &list_head);
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct list_item *item, *tmp;
	list_for_each_entry_safe(item, tmp, &list_head, list) {
		pr_info("Print took: %lld ns\n", ktime_to_ns(item->end) - ktime_to_ns(item->start));
		list_del(&item->list);
		kfree(item);
    }
}

module_exit(hello1_exit);
