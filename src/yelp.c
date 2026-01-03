#include "yelp.h"
#include<linux/sched.h>
#include<linux/kernel.h>

void freenot(Handler hand)
{
	rcu_read_lock();

	/* contains a macro whom I hate, and love */
	hand(current);

	rcu_read_unlock();
}

void freenot_kids(Handler hand, struct task_struct *tsk)
{		
		struct task_struct *chld;
		
		rcu_read_lock();

		list_for_each_entry(chld, &tsk->children, sibling) {
			hand(chld);

			freenot_kids(hand, chld);
		}

		rcu_read_unlock();
}

void check_ancestry(struct task_struct *tsk) {
	if (!tsk) return;
	
	pid_t p = tsk->pid;
	pr_info("Task PID:\t\n%d\t\n", p);

	if (is_child(p)) { 
        	pr_info("\t\nThis is the current process.\n\n");
    	} else if (is_parent(p)) {
        	pr_info("\t\nThis is the parent process.\n\n");
    	} else {
        	pr_info("\t\nThis is the sibling process.\n\n");
    	}
}

void show_desc_info(struct task_struct *tsk)
{
	pr_info("PROCESS NAME:\t\n%s\t\n", tsk->comm); 
	pr_info("PID:\t\n%d\t\n", tsk->pid); 
	pr_info("STATE:\t\n%d\t\n", (int)tsk->__state); 
	pr_info("PRIORITY:\t\n%d\t\n", tsk->prio); 
	pr_info("STATIC-PRIORITY:\t\n%d\t\n", tsk->static_prio); 
	pr_info("NORMAL-PRIORITY:\t\n%d\t\n", tsk->normal_prio);	
}
