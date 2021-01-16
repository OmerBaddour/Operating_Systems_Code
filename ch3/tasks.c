/**
 * tasks.c
 *
 * A kernel module to view tasks. 
 * 
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

/* This function is called when the module is loaded. */
int tasks_init(void)
{
	struct task_struct *task;

	printk(KERN_INFO "Loading Module\n");
	
	/* iterate over tasks */
	for_each_process(task) {
		printk(KERN_INFO "Task name: %s, state: %ld, PID: %ld\n", 
		       task->comm, task->state, (long)task->pid);
	}

	return 0;
}

/* This function is called when the module is removed. */
void tasks_exit(void) {
	
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( tasks_init );
module_exit( tasks_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Chapter 3 Module");
MODULE_AUTHOR("Omer");

