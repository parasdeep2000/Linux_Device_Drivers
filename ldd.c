/*
 Description : Regarding creating proc file and upload
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paras");
MODULE_DESCRIPTION("First Loadable Kernel Module");

static const struct proc_ops proc_fops = {
  
};
static struct proc_dir_entry *ptrToProcFileInit;
static int proc_module_init(void)
{
    printk(KERN_ALERT "Creation Proc: Started\n");
    ptrToProcFileInit = proc_create("proc_FSMineKernel", 
        0, 
        NULL, 
        &proc_fops);
    printk(KERN_ALERT "Creation Proc: Completed\n");
    return 0;
}

static void proc_module_exit(void)
{
    proc_remove(ptrToProcFileInit);
    printk(KERN_ALERT "Creation Proc: Ended\n");
}

module_init(proc_module_init);
module_exit(proc_module_exit);