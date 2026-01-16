/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
#include <asm/param.h>

/* Store the jiffies value when the module is loaded. */
static unsigned long start_jiffies;

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");

       /* Print the value of GOLDEN_RATIO_PRIME, jiffies and HZ.*/
       printk(KERN_INFO "GOLDEN_RATIO_PRIME: %lu\n", GOLDEN_RATIO_PRIME);
       printk(KERN_INFO "jiffies: %lu\n", jiffies);
       printk(KERN_INFO "HZ: %d\n", HZ);

       /* Record the jiffies value when the module is loaded. */
       start_jiffies = jiffies;

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

       /* Store the elapsed time in jiffies when the module is removed. */
       unsigned long elapsed_jiffies;

       printk(KERN_INFO "Removing Module\n");

       /* Print the greatest common divisor of 3300 and 24. */
       printk(KERN_INFO "GCD of 3300 and 24: %lu\n", gcd(3300, 24));

       /* Print the current jiffies value. */
       printk(KERN_INFO "jiffies at exit: %lu\n", jiffies);

       /* Calculate and print the runtime. */
       elapsed_jiffies = jiffies - start_jiffies;
       printk(KERN_INFO "Module ran for %lu jiffies (%lu seconds)\n", elapsed_jiffies, elapsed_jiffies / HZ);
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

