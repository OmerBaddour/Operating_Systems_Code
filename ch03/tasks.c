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
#include <linux/list.h>

/* recursive DFS */
void dfs(struct task_struct *base_task) {

	struct task_struct *task;
	struct list_head *list;

	printk(KERN_INFO "Task name: %s, state: %ld, PID: %ld\n", 
	       base_task->comm, base_task->state, (long)base_task->pid);

	list_for_each(list, &base_task->children) {
		task = list_entry(list, struct task_struct, sibling);
		dfs(task); /* call for all children */
	}
}

/* This function is called when the module is loaded. */
int tasks_init(void)
{
	dfs(&init_task);

	return 0;
}

/* This function is called when the module is removed. */
void tasks_exit(void) {
	
	printk(KERN_INFO "Removing Module tasks\n");
}

/* Macros for registering module entry and exit points. */
module_init( tasks_init );
module_exit( tasks_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Chapter 3 Module");
MODULE_AUTHOR("Omer");

