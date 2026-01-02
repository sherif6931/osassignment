#ifndef _YELP_H_
#define _YELP_H_

#include<linux/compiler.h>
#include<linux/types.h>
#include<linux/sched.h>

// I, henceforth, declare to you, forward-ly.
struct task_struct;

typedef void (*Handler)(struct task_struct*);

static __always_inline bool is_child(pid_t p)
{
	/* current is a macro whom I hate, and love */
	return (p != 0) && (p == task_tgid_vnr(current));
}

static __always_inline bool is_parent(pid_t p)
{
	return (p == task_pid_nr(current));
}

void show_desc_info(struct task_struct*);

void check_ancestry(struct task_struct*);

/* not forever though, Sisyphus */
void freenot(Handler);

void freenot_kids(Handler, struct task_struct*);

#define show_task() freenot(show_desc_info)
#define show_ancestry() check_ancestry(current)

#endif /* _YELP_H_ */
