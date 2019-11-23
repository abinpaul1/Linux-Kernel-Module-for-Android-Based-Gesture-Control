#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/pci.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


/* Represents the file data structure of input device */
struct input_dev *gesture_input_dev; 

/* Device structure */
static struct platform_device *gesture_dev; 

/* Sysfs method to input simulated gesture */
static ssize_t Write_gesture(struct device *dev,
                             struct device_attribute *attr,
                             const char *buffer, size_t count)
{
    int key;

    /* parsing input data */
    sscanf(buffer, "%d", &key);

    printk("gesture_event: key: %d\n", key);

    /* Report key event */
    if (key > 46)
    {
        if (key == 76) // L
            input_report_key(gesture_input_dev, KEY_SCREENLOCK, 1);
        else if (key == 90) //Z
            input_report_key(gesture_input_dev, KEY_SLEEP, 1);
        else if (key == 67) //C
            input_report_key(gesture_input_dev, KEY_CALC, 1);
        else if (key == 108) // l
            input_report_key(gesture_input_dev, KEY_LOGOFF, 1);
        else if (key == 98) //b
            input_report_key(gesture_input_dev, KEY_BRIGHTNESSDOWN, 1);
        else if (key == 66) // B
            input_report_key(gesture_input_dev, KEY_BRIGHTNESSUP, 1);
        else if (key == 86) //V
            input_report_key(gesture_input_dev, KEY_VOLUMEUP, 1);
        else if (key == 118) //v
            input_report_key(gesture_input_dev, KEY_VOLUMEDOWN, 1);
        else if (key == 109) //m
            input_report_key(gesture_input_dev, KEY_MUTE, 1);
        else if (key == 87) //W
            input_report_key(gesture_input_dev, KEY_WWW, 1);
        else if (key == 80) //P
            input_report_key(gesture_input_dev, KEY_PLAYPAUSE, 1);
        else if (key == 112) //p
            input_report_key(gesture_input_dev, KEY_PREVIOUSSONG, 1);
        else if (key == 110) //n
            input_report_key(gesture_input_dev, KEY_NEXTSONG, 1);
        else if (key == 47) //
            input_report_key(gesture_input_dev, KEY_PAGEUP, 1);
        else if (key == 92) //
            input_report_key(gesture_input_dev, KEY_PAGEDOWN, 1);
        else if (key == 115) //s
            input_report_key(gesture_input_dev, KEY_SYSRQ, 1);
        else if (key == 119) //w
            input_report_key(gesture_input_dev, KEY_WAKEUP, 1);
        else if (key == 85) //u
            input_report_key(gesture_input_dev, KEY_SPACE, 1);
        else if (key == 49) //1
            input_report_key(gesture_input_dev, KEY_1, 1);
        else if (key == 53) //5
            input_report_key(gesture_input_dev, KEY_5, 1);
        else if (key == 57) //9
            input_report_key(gesture_input_dev, KEY_9, 1);
        else if (key == 51) //3
            input_report_key(gesture_input_dev, KEY_3, 1);
        else if (key == 101)
            input_report_key(gesture_input_dev, KEY_ENTER, 1);
    }
    else
    {
        input_report_key(gesture_input_dev, KEY_SCREENLOCK, 0);
        input_report_key(gesture_input_dev, KEY_CALC, 0);
        input_report_key(gesture_input_dev, KEY_SLEEP, 0);
        input_report_key(gesture_input_dev, KEY_WWW, 0);
        input_report_key(gesture_input_dev, KEY_LOGOFF, 0);
        input_report_key(gesture_input_dev, KEY_BRIGHTNESSDOWN, 0);
        input_report_key(gesture_input_dev, KEY_BRIGHTNESSUP, 0);
        input_report_key(gesture_input_dev, KEY_VOLUMEUP, 0);
        input_report_key(gesture_input_dev, KEY_VOLUMEDOWN, 0);
        input_report_key(gesture_input_dev, KEY_MUTE, 0);
        input_report_key(gesture_input_dev, KEY_PLAYPAUSE, 0);
        input_report_key(gesture_input_dev, KEY_PREVIOUSSONG, 0);
        input_report_key(gesture_input_dev, KEY_NEXTSONG, 0);
        input_report_key(gesture_input_dev, KEY_PAGEUP, 0);
        input_report_key(gesture_input_dev, KEY_PAGEDOWN, 0);
        input_report_key(gesture_input_dev, KEY_SYSRQ, 0);
        input_report_key(gesture_input_dev, KEY_WAKEUP, 0);
        input_report_key(gesture_input_dev, KEY_SPACE, 0);
        input_report_key(gesture_input_dev, KEY_1, 0);
        input_report_key(gesture_input_dev, KEY_5, 0);
        input_report_key(gesture_input_dev, KEY_9, 0);
        input_report_key(gesture_input_dev, KEY_3, 0);
        input_report_key(gesture_input_dev, KEY_ENTER, 0);
    }

    input_sync(gesture_input_dev);

    return count;
}


/* As explained in Documentation/kobject.txt, device attributes must be
created before the kobject event(gevent) is generated. The only way to realize
that is by defining an attribute group.*/

/* Attributes are declared */

/* Sysfs write method */
DEVICE_ATTR(gevent, 0644, NULL, Write_gesture);

/* Attribute Descriptor */
static struct attribute *gesture_attrs[] = {
    &dev_attr_gevent.attr,
    NULL};

/* Attribute group */
static struct attribute_group gesture_attr_group = {
    .attrs = gesture_attrs,
};

/* Driver Initializing */
int __init gesture_init(void)
{
    /* Register a platform device */
    gesture_dev = platform_device_register_simple("gesture", -1, NULL, 0);
    if (IS_ERR(gesture_dev))
    {
        printk("gesture_init: error\n");
        return PTR_ERR(gesture_dev);
    }

    /* Create a sysfs node to read simulated gestures */
    sysfs_create_group(&gesture_dev->dev.kobj, &gesture_attr_group);

    /* Allocate an input device data structure */
    gesture_input_dev = input_allocate_device();
    if (!gesture_input_dev)
    {
        printk("Bad input_allocate_device()\n");
        return -ENOMEM; /*Out of memory error returned*/
    }

    gesture_input_dev->name = "Gesture controller"; //name of the device
    gesture_input_dev->phys = "gcd/input0"; // Physical path to the device in the system heirarchy
    gesture_input_dev->id.bustype = BUS_VIRTUAL; 
    gesture_input_dev->id.vendor = 0x0000;
    gesture_input_dev->id.product = 0x0000;
    gesture_input_dev->id.version = 0x0000;

    /* Announce key event */
    set_bit(EV_KEY, gesture_input_dev->evbit);
    set_bit(KEY_SCREENLOCK, gesture_input_dev->keybit);
    set_bit(KEY_CALC, gesture_input_dev->keybit);
    set_bit(KEY_WWW, gesture_input_dev->keybit);
    set_bit(KEY_SLEEP, gesture_input_dev->keybit);
    set_bit(KEY_LOGOFF, gesture_input_dev->keybit);
    set_bit(KEY_BRIGHTNESSDOWN, gesture_input_dev->keybit);
    set_bit(KEY_BRIGHTNESSUP, gesture_input_dev->keybit);
    set_bit(KEY_VOLUMEUP, gesture_input_dev->keybit);
    set_bit(KEY_VOLUMEDOWN, gesture_input_dev->keybit);
    set_bit(KEY_MUTE, gesture_input_dev->keybit);
    set_bit(KEY_PLAYPAUSE, gesture_input_dev->keybit);
    set_bit(KEY_PREVIOUSSONG, gesture_input_dev->keybit);
    set_bit(KEY_NEXTSONG, gesture_input_dev->keybit);
    set_bit(KEY_PAGEUP, gesture_input_dev->keybit);
    set_bit(KEY_PAGEDOWN, gesture_input_dev->keybit);
    set_bit(KEY_SYSRQ, gesture_input_dev->keybit);
    set_bit(KEY_WAKEUP, gesture_input_dev->keybit);
    set_bit(KEY_SPACE, gesture_input_dev->keybit);
    set_bit(KEY_1, gesture_input_dev->keybit);
    set_bit(KEY_5, gesture_input_dev->keybit);
    set_bit(KEY_9, gesture_input_dev->keybit);
    set_bit(KEY_3, gesture_input_dev->keybit);
    set_bit(KEY_ENTER, gesture_input_dev->keybit);

    /* Register with the input subsystem */
    input_register_device(gesture_input_dev);

    /* print messages in the dmesg */
    printk("Gesture control Driver Initialized.\n");

    return 0;
}

/* Driver Uninitializing */
void gesture_uninit(void)
{
    /* Unregister from the input subsystem */
    input_unregister_device(gesture_input_dev);

    /* Remove sysfs node */
    sysfs_remove_group(&gesture_dev->dev.kobj, &gesture_attr_group);

    /* Unregister driver */
    platform_device_unregister(gesture_dev);

    return;
}

MODULE_LICENSE("GPL");
module_init(gesture_init);
module_exit(gesture_uninit);
