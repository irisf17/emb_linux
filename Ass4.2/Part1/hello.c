#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Iris");
MODULE_DESCRIPTION("A simple Linux LKM that accepts a single parameter.");
MODULE_VERSION("0.1");

static char *name = "Iris";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");
static int __init hello_init(void) {
printk(KERN_INFO "hello: Hello %s from the RPi LKM!\n", name);
return 0;
}
static void __exit hello_exit(void) {
printk(KERN_INFO "hello: Goodbye %s from the RPi LKM!\n", name);
}
module_init(hello_init);
module_exit(hello_exit);