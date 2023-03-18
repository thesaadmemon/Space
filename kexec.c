#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/kexec.h>

int main(int argc, char *argv[]) {
    int ret;
    char *filename = "/boot/kernel.img";
    char *cmdline = "root=/dev/mmcblk0p2 rw console=ttyAMA0,115200 console=tty1";

    // Set up the kexec_segment structure
    struct kexec_segment seg = {
        .buf = (void *)0x8000,    // Load kernel image at address 0x8000
        .bufsz = 1024*1024*8,     // Allocate 8 MB for the kernel image
        .mem = 0,                 // Don't specify physical memory location
        .memsz = 0                // Use buf and bufsz to determine memory allocation
    };

    // Set up the kexec_info structure
    struct kexec_info ki = {
        .entry = 0x8000,          // Entry point for the new kernel
        .nr_segments = 1,         // Load a single kernel image
        .segments = &seg,         // Pointer to the kexec_segment structure
        .cmdline = cmdline        // Command line arguments for the new kernel
    };

    // Load the new kernel image
    ret = kexec_file_load(filename, &ki, 0);
    if (ret < 0) {
        perror("kexec_file_load");
        exit(EXIT_FAILURE);
    }

    return 0;
}
