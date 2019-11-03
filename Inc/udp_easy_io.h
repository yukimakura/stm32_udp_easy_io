/*
 * udp_easy_io.h
 *
 * Copyright (c) 2019 yukimakura
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef UDP_EASY_IO_H_
#define UDP_EASY_IO_H_
#include "main.h"
#include "cmsis_os.h"
#include "lwip.h"
#define true 1
#define false 0

#define FORCE 1
#define ONCE 0
#define UDP_READ_BUFFER_SIZE 256//読み込み時のバッファサイズ


void UDP_EASY_IO_init(ip4_addr_t dst_addr,unsigned short dst_port,unsigned short own_port);
void UDP_EASY_IO_write(char *payload);
unsigned char UDP_EASY_IO_was_read();
char *UDP_EASY_IO_read_char_prt();
char UDP_EASY_IO_read_char();

#ifdef __cplusplus
}
#endif

#endif /* UDP_EASY_IO_H_ */
