#pragma once

#define CRC_LEN_BYTES (2)
#define HEADER_LEN_BYTES (2)
#define PTY_PAYLOAD_BYTES (512)
#define SPI_PAYLOAD_BYTES (250)
#define PTY_BUF_SIZE_BYTES                                                     \
  (HEADER_LEN_BYTES + PTY_PAYLOAD_BYTES + CRC_LEN_BYTES)
#define SPI_BUF_SIZE_BYTES (SPI_PAYLOAD_BYTES + CRC_LEN_BYTES)
#define NAME_SIZE_BYTES (256)
#define SPI_CAN_PUT_BYTES_FLAG_OFFSET_END (1)
#define SPI_CAN_GET_BYTES_FLAG_OFFSET_END (2)
#define SPI_CAN_PUT_BYTES_FLAG                                                 \
  (SPI_PAYLOAD_BYTES - SPI_CAN_PUT_BYTES_FLAG_OFFSET_END)
#define SPI_CAN_GET_BYTES_FLAG                                                 \
  (SPI_PAYLOAD_BYTES - SPI_CAN_GET_BYTES_FLAG_OFFSET_END)

struct ptyDevice {
    int master_desc;
    int slave_desc;
    int spi_channel;
    unsigned char name[NAME_SIZE_BYTES];
    unsigned char pty_rx[PTY_BUF_SIZE_BYTES];
    unsigned char pty_tx[PTY_BUF_SIZE_BYTES];
    unsigned char spi_rx[SPI_BUF_SIZE_BYTES];
    unsigned char spi_tx[SPI_BUF_SIZE_BYTES];
    unsigned char pty_decoded[SPI_BUF_SIZE_BYTES];
};

int create_new_pty_device(int *master_desc, int *slave_desc,
                          unsigned char *name);
void close_pty_device(const int *master_desc, const int *slave_desc);
int write_to_pty(const int *device_desc, const unsigned char *buf,
                 unsigned int data_len);
int read_from_pty(const int *device_desc, unsigned char *buf,
                  unsigned int buf_len);
