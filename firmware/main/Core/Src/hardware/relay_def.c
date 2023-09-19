/*
 * relay_def.c
 *
 *  Created on: Oct 15, 2022
 *      Author: sebas
 */


#include "hardware/relay_def.h"


RLY_TypeDef relays[RLY_COUNT] =
{
		// RELAYS FOR DECADE 1 .. 9 Ohm
		{ .device = 0, .channel = 13, .cycles = 0 },	// RLY_PLUS_1_OHM
		{ .device = 0, .channel = 12, .cycles = 0 },	// RLY_0_1_OHM
		{ .device = 0, .channel = 11, .cycles = 0 },	// RLY_2_OHM
		{ .device = 0, .channel = 10, .cycles = 0 },	// RLY_4_OHM
		{ .device = 0, .channel = 9, .cycles = 0 },		// RLY_6_OHM
		{ .device = 0, .channel = 8, .cycles = 0 },		// RLY_8_OHM

		// RELAYS FOR DECADE 10 .. 90 Ohm
		{ .device = 0, .channel = 1, .cycles = 0 },		// RLY_PLUS_10_OHM
		{ .device = 0, .channel = 2, .cycles = 0 },		// RLY_0_10_OHM
		{ .device = 0, .channel = 3, .cycles = 0 },		// RLY_20_OHM
		{ .device = 0, .channel = 4, .cycles = 0 },		// RLY_40_OHM
		{ .device = 0, .channel = 5, .cycles = 0 },		// RLY_60_OHM
		{ .device = 0, .channel = 6, .cycles = 0 },		// RLY_80_OHM

		// RELAYS FOR DECADE 100 .. 900 Ohm
		{ .device = 1, .channel = 8, .cycles = 0 },		// RLY_PLUS_100_OHM
		{ .device = 1, .channel = 9, .cycles = 0 },		// RLY_0_100_OHM
		{ .device = 1, .channel = 10, .cycles = 0 },	// RLY_200_OHM
		{ .device = 1, .channel = 11, .cycles = 0 },	// RLY_400_OHM
		{ .device = 1, .channel = 12, .cycles = 0 },	// RLY_600_OHM
		{ .device = 1, .channel = 13, .cycles = 0 },	// RLY_800_OHM

		// RELAYS FOR DECADE 1K .. 9K Ohm
		{ .device = 1, .channel = 15, .cycles = 0 },	// RLY_PLUS_1K_OHM
		{ .device = 1, .channel = 7, .cycles = 0 },		// RLY_0K_1K_OHM
		{ .device = 1, .channel = 6, .cycles = 0 },		// RLY_2K_OHM
		{ .device = 1, .channel = 5, .cycles = 0 },		// RLY_4K_OHM
		{ .device = 1, .channel = 4, .cycles = 0 },		// RLY_6K_OHM
		{ .device = 1, .channel = 3, .cycles = 0 },		// RLY_8K_OHM

		// RELAYS FOR DECADE 10K .. 90K Ohm
		{ .device = 2, .channel = 11, .cycles = 0 },	// RLY_PLUS_10K_OHM
		{ .device = 2, .channel = 10, .cycles = 0 },	// RLY_0K_10K_OHM
		{ .device = 2, .channel = 9, .cycles = 0 },		// RLY_20K_OHM
		{ .device = 2, .channel = 8, .cycles = 0 },		// RLY_40K_OHM
		{ .device = 2, .channel = 0, .cycles = 0 },		// RLY_60K_OHM
		{ .device = 2, .channel = 1, .cycles = 0 },		// RLY_80K_OHM

		// RELAYS FOR DECADE 100K .. 900K Ohm
		{ .device = 2, .channel = 2, .cycles = 0 },		// RLY_PLUS_100K_OHM
		{ .device = 2, .channel = 3, .cycles = 0 },		// RLY_0K_100K_OHM
		{ .device = 2, .channel = 4, .cycles = 0 },		// RLY_200K_OHM
		{ .device = 2, .channel = 5, .cycles = 0 },		// RLY_400K_OHM
		{ .device = 2, .channel = 6, .cycles = 0 },		// RLY_600K_OHM
		{ .device = 2, .channel = 7, .cycles = 0 },		// RLY_800K_OHM

		// RELAYS FOR BYPASSING HIGHER RANGES
		{ .device = 0, .channel = 0, .cycles = 0 },		// RLY_BYPASS_GTE_10
		{ .device = 0, .channel = 7, .cycles = 0 },		// RLY_BYPASS_GTE_100
		{ .device = 1, .channel = 14, .cycles = 0 },	// RLY_BYPASS_GTE_1K
};
