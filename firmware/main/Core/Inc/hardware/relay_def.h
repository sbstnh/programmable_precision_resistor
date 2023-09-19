/*
 * relay_def.h
 *
 *  Created on: Oct 15, 2022
 *      Author: sebas
 */

#ifndef INC_HARDWARE_RELAY_DEF_H_
#define INC_HARDWARE_RELAY_DEF_H_

#include "prog_res/relay.h"

#define RLY_COUNT			39

#define RLY_NPLUS_1_OHM		0
#define RLY_0_OHM			1
#define RLY_2_OHM			2
#define RLY_4_OHM			3
#define RLY_6_OHM			4
#define RLY_8_OHM			5

#define RLY_NPLUS_10_OHM	6
#define RLY_00_OHM			7
#define RLY_20_OHM			8
#define RLY_40_OHM			9
#define RLY_60_OHM			10
#define RLY_80_OHM			11

#define RLY_NPLUS_100_OHM	12
#define RLY_000_OHM			13
#define RLY_200_OHM			14
#define RLY_400_OHM			15
#define RLY_600_OHM			16
#define RLY_800_OHM			17

#define RLY_NPLUS_1K_OHM	18
#define RLY_0K_OHM			19
#define RLY_2K_OHM			20
#define RLY_4K_OHM			21
#define RLY_6K_OHM			22
#define RLY_8K_OHM			23

#define RLY_NPLUS_10K_OHM	24
#define RLY_00K_OHM			25
#define RLY_20K_OHM			26
#define RLY_40K_OHM			27
#define RLY_60K_OHM			28
#define RLY_80K_OHM			29

#define RLY_NPLUS_100K_OHM	30
#define RLY_000K_OHM		31
#define RLY_200K_OHM		32
#define RLY_400K_OHM		33
#define RLY_600K_OHM		34
#define RLY_800K_OHM		35

#define RLY_BYPASS_GTE_10	36
#define RLY_BYPASS_GTE_100	37
#define RLY_BYPASS_GTE_1K	38

extern RLY_TypeDef relays[RLY_COUNT];

#endif /* INC_HARDWARE_RELAY_DEF_H_ */
