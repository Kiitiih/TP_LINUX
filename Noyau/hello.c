#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

#define DRIVER_AUTHOR "Christophe Barès"
#define DRIVER_DESC "Hello world Module"
#define DRIVER_LICENSE "GPL"

#define TAILLE 256
#define FILENAME "nom_de_mon_fichier"

char message[TAILLE];

int param = 3;
module_param(param, int, 0);

ssize_t fops_read(struct file *file, char __user * buffer,
	size_t count, loff_t * ppos) {
	int errno=0;
	int copy;
	if (count > TAILLE) count=TAILLE;
	if ((copy=copy_to_user(buffer, message, strlen(message)+1)))
		errno = -EFAULT;
	printk(KERN_INFO "message read, %d, %p\n", copy, buffer);
	return count-copy;
}

ssize_t fops_write(struct file * file, const char __user * buffer, size_t count, loff_t * ppos) 
{
	int len = count;
	if (len > TAILLE) len = TAILLE;
	printk(KERN_INFO "Recieving new messag\n");
	
	if (copy_from_user(message, buffer, count)) 
	{
		return -EFAULT;
	}
	
	message[count] = '\0';

	printk(KERN_INFO "New message : %s\n", message);
	return count;
}

struct file_operations proc_fops;

int hello_init(void)
{
	printk(KERN_INFO "Hello world!\n");
	printk(KERN_DEBUG "le paramètre est=%d\n", param);
	
	proc_fops.write = fops_write;
	proc_fops.read = fops_read;
	
	proc_create(FILENAME, 0666, NULL, &proc_fops);
	return 0;
}

void hello_exit(void)
{
	remove_proc_entry(FILENAME, NULL);
	printk(KERN_ALERT "Bye bye...\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

