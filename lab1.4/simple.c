#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/utsname.h>

void uptime(void);
void getSystemInfo(void);

int simple_init(void)
{
       printk(KERN_INFO "Loading Juan Module \n");
       uptime();
       getSystemInfo();
       return 0;
}

void simple_exit(void) {
	printk(KERN_INFO "Removing Juan Module\n");
}


void uptime() {
  printk("Uptime: %i\n", jiffies_to_msecs(get_jiffies_64())/1000);
}


void getSystemInfo(){  
  struct new_utsname *buf;
  buf = utsname();

  printk("Nodename: %s\n",buf->nodename);
  printk("Machine: %s\n",buf->machine);
  printk("Sysname: %s\n",buf->sysname);
  printk("Release: %s\n",buf->release);
  printk("Version: %s\n",buf->version);
#ifdef __linux__
  printk("Domain Name: %s\n", buf->domainname); 
#endif
}


module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
