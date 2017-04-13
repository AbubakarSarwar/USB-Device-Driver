#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>

static struct usb_device *device;

//prob function
static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id){

printk(KERN_INFO " The USB device of Abubakar, Fahad and Elsa has been connected\n");
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;
 
    iface_desc = interface->cur_altsetting;
    printk(KERN_INFO "The USB probed (%04X:%04X)\n", id->idVendor, id->idProduct);
    printk(KERN_INFO "ID-> Number of Endpoints: %02X\n",
            iface_desc->desc.bNumEndpoints);
    for (i = 0; i < iface_desc->desc.bNumEndpoints; i++)
    {
        endpoint = &iface_desc->endpoint[i].desc;
 
        printk(KERN_INFO "Endpoint[%d]-> EndpointAddress: 0x%02X\n", i, endpoint->bEndpointAddress);
        printk(KERN_INFO "Endpoint[%d]-> Attribute : 0x%02X\n", i, endpoint->bmAttributes);
        printk(KERN_INFO "Endpoint[%d]-> MaxPacketSize: 0x%04X (%d)\n",
                i, endpoint->wMaxPacketSize, endpoint->wMaxPacketSize);
    }
 
    device = interface_to_usbdev(interface);
 
return 0;
}


//disconnect
static void usb_disconnect(struct usb_interface *interface){
printk(KERN_INFO "The USB device of Abubakar, Fahad and Elsa has been removed\n");
}



//usb device  id
static struct usb_device_id usb_table[] = {
//vendor / product ids
{ USB_DEVICE(0x0951, 0x1643)},
{}/*terminating entry*/
};
MODULE_DEVICE_TABLE(usb, usb_table);



static struct usb_driver usb_driver=
{
.name= "USB device driver by Abubakar,Elsa and Fahad",
.id_table= usb_table,
.probe= usb_probe,
.disconnect= usb_disconnect,
};
static int __init usb_init(void){
int ret = -1;
printk(KERN_INFO "Constructor for the USB device of Abubakar, fahad and elsa has been called\n");
printk(KERN_INFO "Registering USB device of Abubakar, fahad and elsa\n");
ret = usb_register(&usb_driver);
printk(KERN_INFO "Registeration is completed for USB device of Abubakar, fahad and elsa\n");
return ret;
}



static void __exit usb_exit(void){
//deregister
printk(KERN_INFO "Desstructor for the USB device of Abubakar, fahad and elsa has been called\n");
usb_deregister(&usb_driver);
printk(KERN_INFO "Deregisteration is completed for USB device of Abubakar, fahad and elsa\n");
}


module_init(usb_init);
module_exit(usb_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABUBAKAR");
MODULE_DESCRIPTION("USB DRIVER");
