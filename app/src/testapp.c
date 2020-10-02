#include <lwip/raw.h>
#include <lwip/pbuf.h>
#include <lwip/udp.h>
#include <lwip/timeouts.h>
#include "sapi.h"

/** Demo application that will listen to UDP port 1234, respond to everything
 * sent there, and flash a LED when accessed. */

static const char message_text[] = "Received a package, flashed LED.\n";

static void led2_off_timeout(void __attribute__((unused)) *payload)
{
	gpioWrite(LED2, OFF);
}

static void
recv(void __attribute__((unused)) *arg, struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *addr, uint16_t port)
{
	struct pbuf *response;
	struct pbuf *message;

	gpioWrite(LED1, ON);
	gpioWrite(LED2, ON);

	response = pbuf_alloc(PBUF_TRANSPORT, 0, PBUF_RAM);
	message = pbuf_alloc(PBUF_RAW, sizeof(message_text), PBUF_ROM);
	/* by casting from const char* to char*, we acknowledge to the compiler
	 * that we rely on lwIP never to write to the payload of a PBUF_ROM
	 * type buffer. (it can't know that by itself, so we'd get a
	 * "assignment discards `const' qualifier from pointer target type"
	 * warning). */
	message->payload = (char*)message_text;
	pbuf_cat(response, message);

	udp_sendto(pcb, response, addr, port);

	pbuf_free(response);

	pbuf_free(p);

	gpioWrite(LED1, OFF);
	sys_untimeout(led2_off_timeout, NULL);
	sys_timeout(2000, led2_off_timeout, NULL);
}

void testapp_init(void)
{
	struct udp_pcb *my_pcb;

	my_pcb = udp_new();
	LWIP_ASSERT("my_pcb != NULL", my_pcb != NULL);

	udp_recv(my_pcb, (udp_recv_fn)recv, NULL);
	udp_bind(my_pcb, IP_ADDR_ANY, 1234);
}
