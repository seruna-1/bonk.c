// For exchanging data between client and server

#include <stdint.h>
#include <stdbool.h>
#include "box2d/box2d.h"

struct ExchangeblePlayer
{
	uint32_t id;
	b2BodyId body_id;
	bool active;
};