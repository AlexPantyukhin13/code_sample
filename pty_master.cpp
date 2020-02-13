#include "debug_print.h"
#include <cerrno>
#include <cstring>
#include <pty.h>
#include <termios.h>
#include <unistd.h>

/**
 *
 * @brief creates pseudo terminal unit
 * @param master_desc pointer for storing master descriptor
 * @param slave_desc pointer for storing master descriptor
 * @param name pointer for storing device name
 * @retval returns 0 if success else error code
 */

int create_new_pty_device(int *master_desc, int *slave_desc,
                          unsigned char *name) {
    int result = -1;
    if (NULL == master_desc) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return -1;
    }

    if (NULL == slave_desc) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return -1;
    }

    if (NULL == name) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return -1;
    }
    termios tty = {};
    tty.c_iflag = (tcflag_t)0;
    tty.c_lflag = (tcflag_t)0;
    tty.c_cflag = CS8;
    tty.c_oflag = (tcflag_t)0;

    result = openpty(master_desc, slave_desc, (char *)name, &tty, nullptr);
    if (result < 0) {
        dbg_perr("Error: create_new_pty_device -> %s\n\r", strerror(errno));
    }
    return result;
}

/**
 *
 * @brief close pty's device descriptors
 * @param master_desc master descriptor
 * @param slave_desc  slave descriptor
 * @retval void
 */

void close_pty_device(const int *master_desc, const int *slave_desc) {
    if (NULL == master_desc) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return;
    }

    if (NULL == slave_desc) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return;
    }

    close(*master_desc);
    close(*slave_desc);
}

/**
 *
 * @brief write data to PTY device
 * @param device_desc device descriptor
 * @param buf pointer to data which should be send
 * @param data_len len of data to be send
 * @return returns -1 if error else number of written bytes
 */

int write_to_pty(const int *device_desc, const unsigned char *buf,
                 unsigned int data_len) {
    int result = -1;
    if (NULL == device_desc) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return -1;
    }

    if (NULL == buf) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return -1;
    }

    result = write(*device_desc, buf, data_len);

    if (result < 0) {
        dbg_perr("Error: write_to_pty -> %s\n\r", strerror(errno));
    } else {
        dbg_pinfo("%d of %d bytes writen to descriptor %d \n\r", result, data_len,
                  *(device_desc));
    }
    return result;
}

/**
 *
 * @brief read data from PTY device
 * @param device_desc device descriptor
 * @param buf pointer to an array for storing data
 * @param data_len len of data to be read
 * @return -1 if error else number of bytes which was read
 */

int read_from_pty(const int *device_desc, unsigned char *buf,
                  unsigned int buf_len) {
    int result = -1;
    if (NULL == device_desc) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return -1;
    }

    if (NULL == buf) {
        dbg_perr("Error: null check failed -> %s, %d\n\r", __FILE__, __LINE__);
        return -1;
    }

    result = read(*device_desc, buf, data_len);

    if (result < 0) {
        dbg_perr("Error: read_from_pty -> %s\n\r", strerror(errno));
    } else {
        dbg_pinfo("%d of %d bytes were read from descriptor %d \n\r", result,
                  data_len, *(device_desc));
    }
    return result;
}
