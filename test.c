#include "vc_mem.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEVICE_PREFIX "/dev"
#define DRIVER_NAME "vc-mem"

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	unsigned long phys_addr;
	unsigned int size, base, load;

	fd = open(DEVICE_PREFIX "/" DRIVER_NAME, O_NONBLOCK);
	if (fd == -1) {
		fprintf(stderr, "%s: %s:%d: open: %s\n", argv[0], __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd, VC_MEM_IOC_MEM_PHYS_ADDR, &phys_addr);
	if (ret == -1) {
		fprintf(stderr, "%s: %s:%d: ioctl: %s\n", argv[0], __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd, VC_MEM_IOC_MEM_SIZE, &size);
	if (ret == -1) {
		fprintf(stderr, "%s: %s:%d: ioctl: %s\n", argv[0], __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd, VC_MEM_IOC_MEM_BASE, &base);
	if (ret == -1) {
		fprintf(stderr, "%s: %s:%d: ioctl: %s\n", argv[0], __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd, VC_MEM_IOC_MEM_LOAD, &load);
	if (ret == -1) {
		fprintf(stderr, "%s: %s:%d: ioctl: %s\n", argv[0], __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = close(fd);
	if (ret == -1) {
		fprintf(stderr, "%s: %s:%d: close: %s\n", argv[0], __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("phys_addr: 0x%08lx\n", phys_addr);
	printf("size: 0x%08x\n", size);
	printf("base: 0x%08x\n", base);
	printf("load: 0x%08x\n", load);

	return 0;
}
