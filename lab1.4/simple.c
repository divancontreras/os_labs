#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/ktime.h>

//#include <sys/sysinfo.h>
/* This function is called when the module is loaded. */
struct Student {
   int   id;
   char *name;
   int   age;
};  

int lastwritten = 0;
struct Student students[10];

void addStudent(int id, char *name, int age)
{
    struct Student student;
    student.id = id;
    student.name = name;
    student.age = age;
    students[lastwritten] = student;
    lastwritten++;
}

void listStudents(void)
{
    int i, id, age;
    char *name;
    for (i = 0; i < lastwritten; i++)
    {
        id = students[i].id;
        name = students[i].name;
        age = students[i].age;
        printk("%d .- id: %d name: %s age: %i\n",i , id, name, age);
    }
}

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
    addStudent(11, "Diego", 21);
    addStudent(1231, "Ivan", 23);
    listStudents();
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

