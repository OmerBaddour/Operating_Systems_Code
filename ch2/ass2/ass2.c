/**
 * ass2.c
 *
 * Kernel module for assignment 2. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Note: compiler version requires declaration of variables to be first in code blocks
 * Note: compiler version requires no declaration of variables in for loop header
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

// declare and initialize list_head birthday_list
static LIST_HEAD(birthday_list);

struct birthday {
       int day;
       int month;
       int year;
       struct list_head list;
};

/* This function is called when the module is loaded. */
int ass2_init(void)
{
       int i;	
       struct birthday *ptr;

       printk(KERN_INFO "Loading Module\n");
       
       for (i = 1; i < 6; i++) {
               // create and initialize birthday instance
               struct birthday *person;
               person = kmalloc(sizeof(*person), GFP_KERNEL);
               person->day = i;
               person->month = i;
               person->year = 2000 + i;
               INIT_LIST_HEAD(&person->list);

               // add birthday instance to end of birthday_list
               list_add_tail(&person->list, &birthday_list);
       } 

       printk(KERN_INFO "Traversing birthday list and outputting contents\n");

       list_for_each_entry(ptr, &birthday_list, list) {
              printk(KERN_INFO "%d/%d/%d\n", ptr->day, ptr->month, ptr->year);
       }

       return 0;
}

/* This function is called when the module is removed. */
void ass2_exit(void) {
        struct birthday *ptr, *next;

	printk(KERN_INFO "Removing Module\n");
	printk(KERN_INFO "Freeing memory for birthday list\n");
       

       list_for_each_entry_safe(ptr, next, &birthday_list, list) {
              list_del(&ptr->list);
              printk(KERN_INFO "Removing: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
              kfree(ptr);
       }
       
}

/* Macros for registering module entry and exit points. */
module_init( ass2_init );
module_exit( ass2_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Assignment 2 Module");
MODULE_AUTHOR("Omer");

