#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/gpio.h>                       // for the GPIO functions 
#include <linux/interrupt.h>                  // for the IRQ code

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Derek Molloy"); 
MODULE_DESCRIPTION("A Button/LED test driver for the RPi"); 
MODULE_VERSION("0.1");

static unsigned int  encoder_in1 = 17;             // pin 17 (GPIO17) 
static unsigned int encoder_in2 = 22;          // pin 22 (GPIO27) 
static int encoder_counter = 0;
static bool current_input = 0;
static unsigned int irqNumber;                // share IRQ num within file 

module_param(encoder_counter, int, S_IRUGO);
MODULE_PARM_DESC(encoder_counter, "The current counter value");

static bool ledOn = 0;                // used to invert state of LED


// prototype for the custom IRQ handler function, function below 
static irq_handler_t  erpi_gpio_irq_handler(unsigned int irq, 
                                            void *dev_id, struct pt_regs *regs);

static int __init erpi_gpio_init(void) 
{
    int result = 0;
    printk(KERN_INFO "Motor encoder: Initializing the GPIO_TEST LKM\n");

    if (!gpio_is_valid(encoder_in1)) 
    {
        printk(KERN_INFO "Motor encoder: invalid GPIO\n");
        return -ENODEV;
    }   

    ledOn = true;

    // gpio_request(gpioLED, "sysfs");          // request LED GPIO
    // gpio_direction_output(gpioLED, ledOn);   // set in output mode and on 
    // // gpio_set_value(gpioLED, ledOn);       // not reqd - see line above
    // gpio_export(gpioLED, false);             // appears in /sys/class/gpio
    //                                          // false prevents in/out change  
    
    // set encoder inputs
    gpio_request(encoder_in1, "sysfs");       // set up gpioButton   
    gpio_direction_input(encoder_in1);        // set up as input   
    gpio_export(encoder_in1, false);          // appears in /sys/class/gpio
    gpio_request(encoder_in2, "sysfs");       // set up gpioButton   
    gpio_direction_input(encoder_in2);        // set up as input   
    gpio_export(encoder_in2, false);          // appears in /sys/class/gpio

    printk(KERN_INFO "Motor encoder: interrupt pin value is currently: %d\n", 
           gpio_get_value(encoder_in1));

    irqNumber = gpio_to_irq(encoder_in1);     // map GPIO to IRQ number
    printk(KERN_INFO "Motor encoder: interrupt pin mapped to IRQ: %d\n", irqNumber);

    // This next call requests an interrupt line   
    result = request_irq(irqNumber,          // interrupt number requested            
        (irq_handler_t) erpi_gpio_irq_handler,   // handler function            
        (IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING),                     // on rising edge (press, not release)            
        "erpi_gpio_handler",                     // used in /proc/interrupts
        NULL);                                   // *dev_id for shared interrupt lines
    printk(KERN_INFO "Motor encoder: IRQ request result is: %d\n", result);
    return result;
}

static void __exit erpi_gpio_exit(void) 
{   
    printk(KERN_INFO "Motor encoder: interrupt pin value is currently: %d\n", 
           gpio_get_value(encoder_in1));

    // gpio_set_value(gpioLED, 0);              // turn the LED off
    // gpio_unexport(gpioLED);                  // unexport the LED GPIO   
    free_irq(irqNumber, NULL);               // free the IRQ number, no *dev_id   
    gpio_unexport(encoder_in1);               // unexport the Button GPIO   
    gpio_unexport(encoder_in2);               // unexport the Button GPIO   
    
    gpio_free(encoder_in1);                      // free the LED GPIO
    gpio_free(encoder_in2);                   // free the Button GPIO
    printk(KERN_INFO "Motor encoder: Goodbye from the LKM!\n"); 
}

static irq_handler_t erpi_gpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) 
{   
    // ledOn = !ledOn;                          // toggle the LED state   
    // gpio_set_value(gpioLED, ledOn);          // set LED accordingly  
    
    current_input = gpio_get_value(encoder_in2);
    encoder_counter++;

    // if(current_input == 0){
    //     encoder_counter++;
    // }
    // else{
    //     encoder_counter--;
    // }
    return (irq_handler_t) IRQ_HANDLED;      // announce IRQ handled 
}

module_init(erpi_gpio_init);
module_exit(erpi_gpio_exit);