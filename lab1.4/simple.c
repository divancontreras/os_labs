#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/ktime.h>

//#include <sys/sysinfo.h>
/* This function is called when the module is loaded. */


void getSystemInfo(void)
{
    printk(KERN_INFO "Kernel sysname %s\n", utsname()->sysname);
    printk(KERN_INFO "Kernel nodename %s\n", utsname()->nodename);
    printk(KERN_INFO "Kernel release %s\n", utsname()->release);
    printk(KERN_INFO "Kernel machine %s\n", utsname()->machine);
    printk(KERN_INFO "Kernel version %s\n", utsname()->version);
}

void getUpTime(void)
{
    s64  uptime_ms;
    uptime_ms = ktime_to_ms(ktime_get_boottime());
    printk("It has been %lld miliseconds since boot\n", uptime_ms);
}

int simple_init(void)
{
    printk("e This is a initialization message");
    printk(KERN_INFO "Loading Module\n");
    getUpTime();    
    getSystemInfo();
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
    printk("This is a termination message\n");
    printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

