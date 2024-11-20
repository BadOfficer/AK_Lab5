#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("IO-24 Bondarenko Taras");
MODULE_DESCRIPTION("Hello2 module");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "The number of times to call print_hello()");

static int __init hello2_init(void)
{
	int i;

	if (count == 0) {
		pr_warn("Count is 0, nothing to print\n");
	} else if (count > 5 && count <= 10) {
		pr_warn("Count is between 5 and 10");
	} else if (count > 10) {
		pr_err("Count is greater than 10, aborting\n");
		return -EINVAL;
	}

	for (i = 0; i < count; i++) {
		print_hello();
	}
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2 module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

