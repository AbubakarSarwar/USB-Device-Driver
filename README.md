Firstly, we should be aware of the fact that whether a driver for a USB device is there or not on a Linux system, a valid USB device will always be detected at the hardware and kernel spaces of a USB-enabled Linux system, since it is designed (and detected) as per the USB protocol specifications. At the hardware level, the Hardware-space detection is done by the USB host controller which is typically a native bus device The corresponding host controller driver would pick and translate the low-level physical layer information into higher-level USB protocol-specific information. The USB protocol formatted information about the USB device is then populated into the generic USB core layer (the usbcore driver) in kernel-space, thus enabling the detection of a USB device in kernel-space, even without having its specific driver available.
A basic listing of all detected USB devices can be obtained using the lsusb command, as root.

COMMANDS USED:<br>
⦁	lsusb (It is used to view all the usb devices connected ) <br> 
⦁	lsusb –v (Is is used to give a detailed view of the usb devices connected)<br>
⦁	cat /sys/kernel/debug/usb/devices (It also gives detail info of the connected devices including the details of interfaces and endpoints)<br>
⦁	sudo –i (in order to log in from root)<br>
⦁	make (to compile a module)<br>
⦁	insmod (inserting a module)<br>
⦁	rmmod (removing a module)<br>
⦁	modprobe (inserting back a module)<br>
⦁	mount (lists all mounted devices)<br>
⦁	fdisk –l (Gives detailed info of the mounted disks)<br>
⦁	mkdir (create new directory)<br>


The source code is very simple. The header files used are linux/module.h, linux/kernel.h and linux/usb.h. The must important structure is our usb_driver structure. It is the core of our code. It includes 4 main branches. Name, id , prob and disconnect. There are three functions defined inside the structure of usb_driver. Name is simply the name of the device driver.

First of all lets talk about our ID table which is taken in the form of an array. It is because we want to detect as many devices we want. The ID table is fully dependent upon two things. The Vendor ID and the Product ID. Whenever a device is connected this ID_Table functions just matches that whether the vendor ID and product ID matches to any of the stored ID’s. If yes, then it takes control of the device. However , if it doesn’t match then it lets go.  The vendor ID and Product ID are saved in the USB_DEVICE(vendor,product) function. At the end we have a terminating condition for a situation in which our driver receives null. 

Moving on towards the prob function. It is called whenever a device is connected to any of the serial ports in our system. In this function we have two arguments one is the interface pointer while other is for the USB ID(Yes it is same as the ID I mentioned about above).  Other than the arguments I have initialized two different structures. One of type usb_host_interface while other is of type usb_endpoint_descriptor. The host interface has all the information about the interface of the device you have connected. Meanwhile the endpoint descriptor will have the detailed information about the endpoints available in our device. These both are just used inorder to print the number of endpoints and to print out the attributes and details of the endpoints. After that we have stored the information of the usb_host into a pointer and then printed the number of endpoints. Then we had a loop from 1 to the number of endpoints available. 

Then one by one we have printed the addresses, MXPS and the type of endpoint for all the endpoints inside the device.
After that we have a function named disconnect. The name suggests it very well. Yes, the disconnect function is only called when the device is disconnected. We don’t have to do anything special in this function. Therefore, I have just printed a statement on the console instead.

Now talking about the init function. We all know that init function is the function that is called when you are installing a mod. Therefore, we have registered the module as a usb device driver in the init function. However, if the usb registration is not done properly then the return value will be -1 else than that it will be greater than 0.

To conclude, we can see 5 different lines. The first two lines of module_init(usb_init) is just telling the kernel that the init function for this module is usb_init. Same goes for our favourite exit function. After that we have taken license from GPL. Without this license I cannot call the functions such as usb_register or usb_deregister. It is because the ubuntu has a permission set not letting everyone use those special function. But when you give license of GPL then no one can stop you from taking any function from the usb.h library. Next line just shows the author and after then that the module_description is showing just a small description of your project.
