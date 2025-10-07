# UEFI Hello World

This is a small project that I did one evening in making a first attempt at writing code that will run on a PC without an operating system. 

# Running the Code 

Jumping to the end, to run the code, compile this project with Visual Studio 2022. The output has a binary named BOOTX64.efi. Copy that to a FAT32 formatted USB drive to the path /efi/BOOT. If you boot this on a machine that doesn't have secure boot enabled, it should print "Hello World".

# Helpful Links

 https://uefi.org/specs/UEFI/2.10/04_EFI_System_Table.html
https://masm32.com/board/index.php?topic=7942.0
http://x86asm.net/articles/uefi-programming-first-steps/


# Blog Entry

This code originally appeared on my personal blog, https://blog.j2i.net. Most of the contents of that blog entry are below. 

