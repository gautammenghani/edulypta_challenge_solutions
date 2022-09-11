#include <linux/module.h>
#include <linux/usb.h>
#include <linux/hid.h>
MODULE_LICENSE("GPL v2");
#define USB_KB_VENDOR_ID 0x4d9
#define USB_KB_PRODUCT_ID 0x1702

static const struct usb_device_id usb_test_table[] = {
	{ USB_DEVICE(USB_KB_VENDOR_ID, USB_KB_PRODUCT_ID) },
        { }
};
MODULE_DEVICE_TABLE (usb, usb_test_table);

static int usb_test_probe (struct usb_interface *interface, const struct usb_device_id *id)
{
	pr_err("USB KEYBOARD INSERTED .....\n");
	return 0;
}

static void usb_test_disconnect (struct usb_interface *interface) {
	pr_err("USB KEYBOARD disconnected");
}

static struct usb_driver usb_test_driver = {
        .name        = "load_test",
        .probe       = usb_test_probe,
        .id_table    = usb_test_table,
        .disconnect    = usb_test_disconnect
};

static int __init hello_init(void){
	int result;
	result = usb_register(&usb_test_driver);
	if (result < 0) {
		pr_err("custom usb driver not loaded, error : %d\n", result);
		return result;
	}
	pr_warn("Custom module load success!\n");
	return 0;
}

static void __exit hello_exit(void) {
	usb_deregister(&usb_test_driver);
	pr_warn("Exiting ...\n");
}	

module_init(hello_init);
module_exit(hello_exit);
