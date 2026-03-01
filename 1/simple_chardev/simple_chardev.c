#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "simplechardev"
#define DEV_COUNT 1

static dev_t dev_num;
static struct cdev my_cdev;

static int my_open(struct inode *inode, struct file *file){
    printk(KERN_INFO "%s: open char device\n", DEVICE_NAME);
    return 0;
}

static int my_release(struct inode *inode, struct file *file){
    printk(KERN_INFO "%s: release char device\n", DEVICE_NAME);
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release
};

static int __init init_chardev(void){
    int ret;
    ret = alloc_chrdev_region(&dev_num, 0, DEV_COUNT, DEVICE_NAME);
    if(ret < 0) {
        printk(KERN_ERR "%s :alloc_chrdev_region failed\n", DEVICE_NAME);
        return ret;
    }
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;

    ret = cdev_add(&my_cdev, dev_num, DEV_COUNT);
    if(ret){
        printk(KERN_ERR "%s: cdev_add failed\n", DEVICE_NAME);
        unregister_chrdev_region(dev_num, DEV_COUNT);
        return ret;
    }
    printk(KERN_INFO "%s: registered major %d minor %d\n",
            DEVICE_NAME, MAJOR(dev_num), MINOR(dev_num));
    return 0;
}

static void __exit exit_chardev(void){
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, DEV_COUNT);
    printk(KERN_INFO "%s: unregistered\n", DEVICE_NAME);
}

module_init(init_chardev);
module_exit(exit_chardev);

MODULE_AUTHOR("Utkarsh");
MODULE_DESCRIPTION("CUSTOM DRIVER TO TEST FUNCTIONALITY");
MODULE_LICENSE("GPL");