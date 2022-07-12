#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
static LIST_HEAD(birthday_list);

struct birthday
{
       char *name;
       int day;
       int month;
       int year;
       struct list_head list;
};

void set_birthday(struct birthday *person, char *name, int day, int month, int year);

/* This function is called when the module is loaded. */
int simple_init(void)
{
       struct birthday *Facebook, *Apple, *Amazon, *Netflix, *Google;
       struct birthday *ptr;
       printk(KERN_INFO "Loading Module\n");

       Facebook = kmalloc(sizeof(*Facebook), GFP_KERNEL);
       Apple = kmalloc(sizeof(*Apple), GFP_KERNEL);
       Amazon = kmalloc(sizeof(*Amazon), GFP_KERNEL);
       Netflix = kmalloc(sizeof(*Netflix), GFP_KERNEL);
       Google = kmalloc(sizeof(*Google), GFP_KERNEL);

       set_birthday(Facebook, "Facebook", 4, 2, 2004);
       set_birthday(Apple, "Apple", 1, 4, 1976);
       set_birthday(Amazon, "Amazon", 5, 7, 1994);
       set_birthday(Netflix, "Netflix", 29, 8, 1997);
       set_birthday(Google, "Google", 4, 9, 1998);

       list_for_each_entry(ptr, &birthday_list, list)
       {
              printk(KERN_INFO "name: %s, day: %d, month: %d, year: %d \n", ptr->name, ptr->day, ptr->month, ptr->year);
       }

       return 0;
}

void set_birthday(struct birthday *person, char *name, int day, int month, int year)
{      
       person->name = name;
       person->day = day;
       person->month = month;
       person->year = year;
       INIT_LIST_HEAD(&person->list);
       list_add_tail(&person->list, &birthday_list);
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
       struct birthday *ptr, *next;
       printk(KERN_INFO "Removing Module\n");

       list_for_each_entry_safe(ptr, next, &birthday_list, list)
       {
              printk(KERN_INFO "Removing name: %s, day: %d, month: %d, year: %d \n", ptr->name, ptr->day, ptr->month, ptr->year);
              list_del(&ptr->list);
              kfree(ptr);
       }
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
