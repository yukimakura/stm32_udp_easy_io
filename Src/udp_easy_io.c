/*
 * udp_easy_io.c
 *
 * Copyright (c) 2019 yukimakura
 * Released under the MIT license.
 * see https://opensource.org/licenses/MIT
 *
 */

#include "udp_easy_io.h"
static ip4_addr_t dst_addr_;
static unsigned short dst_port_;
static unsigned short own_port_;
struct udp_pcb *pcb_;
err_t err_;
static char udp_read_buffer_[128];
static unsigned char read_flag_;
static char *empty_str_ = "";


static void UDP_EASY_IO_recv_(void *arg, struct udp_pcb *pcb, struct pbuf *p,
		const ip_addr_t *addr, u16_t port) {
	char printbuff[64] = "";
	if (p != NULL) {
		memset(udp_read_buffer_,'\0',sizeof(udp_read_buffer_));//buffer clear
		memcpy(udp_read_buffer_,p->payload,p->len);
		read_flag_ = 0;
	}
}

static void UDP_EASY_IO_main_task_(void *arg) {
	/* init code for LWIP */
	MX_LWIP_Init();

	struct pbuf *p;

	pcb_ = udp_new();
	err_ = udp_bind(pcb_, IP_ADDR_ANY, own_port_);
	udp_recv(pcb_, UDP_EASY_IO_recv_, NULL);

	for (;;) {
		vTaskDelay( 100 );
	}

}
void UDP_EASY_IO_write(char *payload) {

	struct pbuf *p;

	p = pbuf_alloc(PBUF_TRANSPORT, strlen(payload), PBUF_RAM);
	memcpy(p->payload, payload, strlen(payload));
	udp_sendto(pcb_, p, &dst_addr_, dst_port_);
	pbuf_free(p);
}
unsigned char UDP_EASY_IO_was_read() {
	return read_flag_;
}
char *UDP_EASY_IO_read_char_prt() {
		read_flag_ = 1;
		return udp_read_buffer_;
}

char UDP_EASY_IO_read_char() {
		read_flag_ = 1;
		return udp_read_buffer_[0];
}

void UDP_EASY_IO_init(ip4_addr_t dst_addr, unsigned short dst_port,
		unsigned short own_port) {
	dst_addr_ = dst_addr;
	dst_port_ = dst_port;
	own_port_ = own_port;
	sprintf(udp_read_buffer_,"");
	xTaskCreate(&UDP_EASY_IO_main_task_ , "UDP_EASY_IO_main_task", 512, NULL, 1, NULL);
}
