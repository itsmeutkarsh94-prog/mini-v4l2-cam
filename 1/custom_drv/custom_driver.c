#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int value = 10;
module_param(value, int, 0644);
MODULE_PARM_DESC(value, "iniit param");

static char *name = "world";
module_param(name, charp, 0644);
MODULE_PARM_DESC(name, "A name string");

static int __init init_custom(void){
	printk(KERN_INFO "UTK: init driver\n");
	return 0;
}

static void __exit exit_custom(void){
	printk(KERN_INFO "UTK: exit driver\n");
}


module_init(init_custom);
module_exit(exit_custom);


MODULE_AUTHOR("Utkarsh");
MODULE_DESCRIPTION("CUSTOM DRIVER TO TEST FUNCTIONALITY");
MODULE_LICENSE("GPL");
