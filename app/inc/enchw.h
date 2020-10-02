#include <stdint.h>
#include "sapi.h"

typedef struct {
} enchw_device_t;

void enc_hw_setup(enchw_device_t *dev);
void enc_hw_select(enchw_device_t *dev);
void enc_hw_unselect(enchw_device_t *dev);
uint8_t enc_hw_exchangebyte(enchw_device_t *dev, uint8_t byte);
