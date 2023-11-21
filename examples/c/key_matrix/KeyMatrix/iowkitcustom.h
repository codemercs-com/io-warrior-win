//
// IO-Warrior kit library V1.5 custom chip include file
//

#ifndef _IOW_KIT_CUSTOM_H_
#define _IOW_KIT_CUSTOM_H_

// Values for IOWARRIOR_CUSTOM_LEVEL
#define IOWARRIOR_ORIGINAL_ONLY 0
#define IOWARRIOR_PLUS_CUSTOM   1
#define IOWARRIOR_CUSTOM_ONLY   2

// Value for unused custom ProductID
#define IOWKIT_CUSTOM_PRODUCT_ID_UNUSED 0x0000

// Values for IOWKIT_CUSTOM_PID_x_KIND
#define IOWARRIOR_KIND_24     24
#define IOWARRIOR_KIND_40     40
#define IOWARRIOR_KIND_56     56
#define IOWARRIOR_KIND_UNUSED 0

//===== customize area ====================================

// central switch to handle IO-Warriors with custom VendorID
#define IOWARRIOR_CUSTOM_LEVEL IOWARRIOR_PLUS_CUSTOM

// Number of ProductIDs for custom IO-Warriors
// Please insert the number of ProductIDs for your VendorID you have
// The allowed range is 1 to 6
#define IOWARRIOR_NUM_CUSTOM_PIDS 3

// Custom IO-Warrior vendor & product IDs
// Please insert your VendorID here
#define IOWKIT_CUSTOM_VENDOR_ID    0x12CB

// ProductIDs of your custom IOWarriors
// Please add your ProductIDs
// Unused elements should get the value IOWKIT_CUSTOM_PRODUCT_ID_UNUSED
#define IOWKIT_CUSTOM_PRODUCT_ID_1 0x000B
#define IOWKIT_CUSTOM_PRODUCT_ID_2 0x000C
#define IOWKIT_CUSTOM_PRODUCT_ID_3 0x1589
#define IOWKIT_CUSTOM_PRODUCT_ID_4 IOWKIT_CUSTOM_PRODUCT_ID_UNUSED
#define IOWKIT_CUSTOM_PRODUCT_ID_5 IOWKIT_CUSTOM_PRODUCT_ID_UNUSED
#define IOWKIT_CUSTOM_PRODUCT_ID_6 IOWKIT_CUSTOM_PRODUCT_ID_UNUSED

// Identifies the kind of IOWarrior for the custom ProductIDs
// Please insert the correct value from the IOWARRIOR_KIND_* defines above
#define IOWKIT_CUSTOM_PRODUCT_ID_1_KIND IOWARRIOR_KIND_24
#define IOWKIT_CUSTOM_PRODUCT_ID_2_KIND IOWARRIOR_KIND_40
#define IOWKIT_CUSTOM_PRODUCT_ID_3_KIND IOWARRIOR_KIND_40
#define IOWKIT_CUSTOM_PRODUCT_ID_4_KIND IOWARRIOR_KIND_UNUSED
#define IOWKIT_CUSTOM_PRODUCT_ID_5_KIND IOWARRIOR_KIND_UNUSED
#define IOWKIT_CUSTOM_PRODUCT_ID_6_KIND IOWARRIOR_KIND_UNUSED

//===== end of customize area =============================

// mapping to shorter names
#define IOWKIT_CUSTOM_VID   IOWKIT_CUSTOM_VENDOR_ID
#define IOWKIT_CUSTOM_PID_1 IOWKIT_CUSTOM_PRODUCT_ID_1
#define IOWKIT_CUSTOM_PID_2 IOWKIT_CUSTOM_PRODUCT_ID_2
#define IOWKIT_CUSTOM_PID_3 IOWKIT_CUSTOM_PRODUCT_ID_3
#define IOWKIT_CUSTOM_PID_4 IOWKIT_CUSTOM_PRODUCT_ID_4
#define IOWKIT_CUSTOM_PID_5 IOWKIT_CUSTOM_PRODUCT_ID_5
#define IOWKIT_CUSTOM_PID_6 IOWKIT_CUSTOM_PRODUCT_ID_6

#endif // _IOW_KIT_CUSTOM_H_