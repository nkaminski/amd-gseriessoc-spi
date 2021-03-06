#ifndef SPIROM_H
#define SPIROM_H

#include <linux/types.h>

/*---------------------------------------------------------------------------*/

/* IOCTL commands */

#define SPI_IOC_MAGIC			'k'

#define TRANSMIT	1
#define RECEIVE		2

/*
 * struct spi_ioc_transfer - interface structure between application and ioctl
 *
 * @buf: Buffer to hold 1-byte command, 3-bytes address, and 64-byte data for
 *       transmit or receive. The internal FIFO of our controller can hold a
 *       maximum of 70 bytes, including the address. But here we assume the
 *       maximum data excluding address to be 64-bytes long.
 *
 * @direction: Direction of data transfer, either TRANSMIT or RECEIVE.
 *
 * @len: Length of data excluding command and address.
 *
 * @addr_present: Flag to indicate whether 'buf' above contains an address.
 */
struct spi_ioc_transfer {
	__u8		buf[64 + 1 + 3];
	__u8		direction;
	__u8		len;
	__u8		addr_present;
};

/* not all platforms use <asm-generic/ioctl.h> or _IOC_TYPECHECK() ... */
#define SPI_MSGSIZE(N) \
	((((N)*(sizeof (struct spi_ioc_transfer))) < (1 << _IOC_SIZEBITS)) \
		? ((N)*(sizeof (struct spi_ioc_transfer))) : 0)
#define SPI_IOC_MESSAGE(N) _IOW(SPI_IOC_MAGIC, 0, char[SPI_MSGSIZE(N)])


#endif /* SPIROM_H */
