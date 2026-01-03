#include "yelp.h" 
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


static int __init main_init(void) {
    
    show_ancestry();

    show_all_tasks(); 
    
    return 0;
}

static void __exit main_exit(void) {
    pr_info("Yelp is done.\n");
}

module_init(main_init);
module_exit(main_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("YELP");
MODULE_AUTHOR("ME");
