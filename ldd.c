/*
 Description : Regarding creating proc file,upload & read. 
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paras");
MODULE_DESCRIPTION("First Loadable Kernel Module");

/*
    static limits visibility of the function to the current source file only, 
    so the compiler no longer expects an external prototype.
*/
static ssize_t	ProcRead_FSKernel(struct file *, 
    char __user *, 
    size_t, loff_t *){           

        printk(KERN_ALERT "Read_FSKernel: Inside File Read\n");    
        return 0;            //Important as there is EOF 
    }
static const struct proc_ops proc_fops = {
  .proc_read = ProcRead_FSKernel
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