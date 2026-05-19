/*
 Description : Regarding creating proc file,upload & read. 
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paras");
MODULE_DESCRIPTION("First Loadable Kernel Module");

#define MAX_SIZE_RX_BUFFER  20
static char gRxBuffer[MAX_SIZE_RX_BUFFER] = {0};
/*
    static limits visibility of the function to the current source file only, 
    so the compiler no longer expects an external prototype.
*/

/* Write to the proc file*/
static ssize_t	ProcWrite_FSKernel(struct file *writeFile,
    const char __user *userbuffer,
    size_t sizer, 
    loff_t *offlit){

        if(copy_from_user(gRxBuffer
            ,userbuffer
            ,sizer)){

                return -EFAULT;
        }
        gRxBuffer[sizer] = '\0';
        printk(KERN_ALERT "Data Recived: %s\n",gRxBuffer);    
        return sizer;
    }


/*  Read from proc file*/
static ssize_t	ProcRead_FSKernel(struct file *readFile, 
    char __user * userbuffer, 
    size_t sizer, 
    loff_t * offlit){           

        char bufferData[] = "Hello From inside of the kernel\n";
        int lenOfStr = strlen(bufferData);
        if(*offlit >= lenOfStr){
            return 0;
        }
        if(copy_to_user(userbuffer,
            bufferData
        ,lenOfStr)){

                return -EFAULT;
        }
        *offlit += lenOfStr;
        printk(KERN_ALERT "Read_FSKernel: Inside File Read\n");    
        return lenOfStr;            //Important as there is EOF 
    }

static const struct proc_ops proc_fops = {
  .proc_read = ProcRead_FSKernel,
  .proc_write = ProcWrite_FSKernel
};

static struct proc_dir_entry *ptrToProcFileInit;
static int proc_module_init(void)
{
    printk(KERN_ALERT "Creation Proc: Started\n");
    ptrToProcFileInit = proc_create("proc_FSMineKernel", 
        666, 
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