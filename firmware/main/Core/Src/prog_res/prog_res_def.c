/*
 * prog_res_def.c
 *
 *  Created on: 19.10.2022
 *      Author: sebas
 */

#include "prog_res/prog_res_def.h"
#include "hardware/relay_def.h"

PRES_TypeDef progres =
{
		._requestRelayControl = NULL,
		.max_voltage = 150000000,					// -> µV
		.max_short_circuit_current = 1000000,		// -> µA
		.decades = {
				// Decade 1 .. 9 Ohm
				{
						.order = 0,
						.i_0 = 223606, 				// floor(sqrt(P_0 / R_0)) with P_0 = 0.1W (derated), R_0 = 2Ohm -> uA
						.resistances =
						{
								{ .number = 0, .nominal =    0, .calibrated_2w =    0, .calibrated_4w =    0, .i_factor = 0, .relay_tap = &relays[RLY_0_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1_OHM] },
								{ .number = 1, .nominal = 1000, .calibrated_2w = 1000, .calibrated_4w = 1000, .i_factor = 2, .relay_tap = &relays[RLY_0_OHM], .relay_not_plus_one = NULL },
								{ .number = 2, .nominal = 2000, .calibrated_2w = 2000, .calibrated_4w = 2000, .i_factor = 2, .relay_tap = &relays[RLY_2_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1_OHM] },
								{ .number = 3, .nominal = 3000, .calibrated_2w = 3000, .calibrated_4w = 3000, .i_factor = 2, .relay_tap = &relays[RLY_2_OHM], .relay_not_plus_one = NULL },
								{ .number = 4, .nominal = 4000, .calibrated_2w = 4000, .calibrated_4w = 4000, .i_factor = 1, .relay_tap = &relays[RLY_4_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1_OHM] },
								{ .number = 5, .nominal = 5000, .calibrated_2w = 5000, .calibrated_4w = 5000, .i_factor = 1, .relay_tap = &relays[RLY_4_OHM], .relay_not_plus_one = NULL },
								{ .number = 6, .nominal = 6000, .calibrated_2w = 6000, .calibrated_4w = 6000, .i_factor = 1, .relay_tap = &relays[RLY_6_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1_OHM] },
								{ .number = 7, .nominal = 7000, .calibrated_2w = 7000, .calibrated_4w = 7000, .i_factor = 1, .relay_tap = &relays[RLY_6_OHM], .relay_not_plus_one = NULL },
								{ .number = 8, .nominal = 8000, .calibrated_2w = 8000, .calibrated_4w = 8000, .i_factor = 1, .relay_tap = &relays[RLY_8_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1_OHM] },
								{ .number = 9, .nominal = 9000, .calibrated_2w = 9000, .calibrated_4w = 9000, .i_factor = 1, .relay_tap = &relays[RLY_8_OHM], .relay_not_plus_one = NULL },
						},
						.relay_bypass = &relays[RLY_BYPASS_GTE_10],
				},

				// Decade 10 .. 90 Ohm
				{
						.order = 1,
						.i_0 = 111803,				// P_0 = 0.25W (derated), R_0 = 20Ohm -> uA
						.resistances =
						{
								{ .number = 0, .nominal =     0, .calibrated_2w =     0, .calibrated_4w =     0, .i_factor = 0, .relay_tap = &relays[RLY_00_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10_OHM] },
								{ .number = 1, .nominal = 10000, .calibrated_2w = 10000, .calibrated_4w = 10000, .i_factor = 2, .relay_tap = &relays[RLY_00_OHM], .relay_not_plus_one = NULL },
								{ .number = 2, .nominal = 20000, .calibrated_2w = 20000, .calibrated_4w = 20000, .i_factor = 2, .relay_tap = &relays[RLY_20_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10_OHM] },
								{ .number = 3, .nominal = 30000, .calibrated_2w = 30000, .calibrated_4w = 30000, .i_factor = 2, .relay_tap = &relays[RLY_20_OHM], .relay_not_plus_one = NULL },
								{ .number = 4, .nominal = 40000, .calibrated_2w = 40000, .calibrated_4w = 40000, .i_factor = 1, .relay_tap = &relays[RLY_40_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10_OHM] },
								{ .number = 5, .nominal = 50000, .calibrated_2w = 50000, .calibrated_4w = 50000, .i_factor = 1, .relay_tap = &relays[RLY_40_OHM], .relay_not_plus_one = NULL },
								{ .number = 6, .nominal = 60000, .calibrated_2w = 60000, .calibrated_4w = 60000, .i_factor = 1, .relay_tap = &relays[RLY_60_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10_OHM] },
								{ .number = 7, .nominal = 70000, .calibrated_2w = 70000, .calibrated_4w = 70000, .i_factor = 1, .relay_tap = &relays[RLY_60_OHM], .relay_not_plus_one = NULL },
								{ .number = 8, .nominal = 80000, .calibrated_2w = 80000, .calibrated_4w = 80000, .i_factor = 1, .relay_tap = &relays[RLY_80_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10_OHM] },
								{ .number = 9, .nominal = 90000, .calibrated_2w = 90000, .calibrated_4w = 90000, .i_factor = 1, .relay_tap = &relays[RLY_80_OHM], .relay_not_plus_one = NULL },
						},
						.relay_bypass = &relays[RLY_BYPASS_GTE_100],
				},

				// Decade 100 .. 900 Ohm
				{
						.order = 2,
						.i_0 = 35355,				// P_0 = 0.25W (derated), R_0 = 200Ohm -> uA
						.resistances =
						{
								{ .number = 0, .nominal =      0, .calibrated_2w =      0, .calibrated_4w =      0, .i_factor = 0, .relay_tap = &relays[RLY_000_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100_OHM] },
								{ .number = 1, .nominal = 100000, .calibrated_2w = 100000, .calibrated_4w = 100000, .i_factor = 2, .relay_tap = &relays[RLY_000_OHM], .relay_not_plus_one = NULL },
								{ .number = 2, .nominal = 200000, .calibrated_2w = 200000, .calibrated_4w = 200000, .i_factor = 2, .relay_tap = &relays[RLY_200_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100_OHM] },
								{ .number = 3, .nominal = 300000, .calibrated_2w = 300000, .calibrated_4w = 300000, .i_factor = 2, .relay_tap = &relays[RLY_200_OHM], .relay_not_plus_one = NULL },
								{ .number = 4, .nominal = 400000, .calibrated_2w = 400000, .calibrated_4w = 400000, .i_factor = 1, .relay_tap = &relays[RLY_400_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100_OHM] },
								{ .number = 5, .nominal = 500000, .calibrated_2w = 500000, .calibrated_4w = 500000, .i_factor = 1, .relay_tap = &relays[RLY_400_OHM], .relay_not_plus_one = NULL },
								{ .number = 6, .nominal = 600000, .calibrated_2w = 600000, .calibrated_4w = 600000, .i_factor = 1, .relay_tap = &relays[RLY_600_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100_OHM] },
								{ .number = 7, .nominal = 700000, .calibrated_2w = 700000, .calibrated_4w = 700000, .i_factor = 1, .relay_tap = &relays[RLY_600_OHM], .relay_not_plus_one = NULL },
								{ .number = 8, .nominal = 800000, .calibrated_2w = 800000, .calibrated_4w = 800000, .i_factor = 1, .relay_tap = &relays[RLY_800_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100_OHM] },
								{ .number = 9, .nominal = 900000, .calibrated_2w = 900000, .calibrated_4w = 900000, .i_factor = 1, .relay_tap = &relays[RLY_800_OHM], .relay_not_plus_one = NULL },
						},
						.relay_bypass = &relays[RLY_BYPASS_GTE_1K],
				},

				// Decade 1k .. 9k Ohm
				{
						.order = 3,
						.i_0 = 11180,				// P_0 = 0.25W (derated), R_0 = 2kOhm -> uA
						.resistances =
						{
								{ .number = 0, .nominal =       0, .calibrated_2w =       0, .calibrated_4w =       0, .i_factor = 0, .relay_tap = &relays[RLY_0K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1K_OHM] },
								{ .number = 1, .nominal = 1000000, .calibrated_2w = 1000000, .calibrated_4w = 1000000, .i_factor = 2, .relay_tap = &relays[RLY_0K_OHM], .relay_not_plus_one = NULL },
								{ .number = 2, .nominal = 2000000, .calibrated_2w = 2000000, .calibrated_4w = 2000000, .i_factor = 2, .relay_tap = &relays[RLY_2K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1K_OHM] },
								{ .number = 3, .nominal = 3000000, .calibrated_2w = 3000000, .calibrated_4w = 3000000, .i_factor = 2, .relay_tap = &relays[RLY_2K_OHM], .relay_not_plus_one = NULL },
								{ .number = 4, .nominal = 4000000, .calibrated_2w = 4000000, .calibrated_4w = 4000000, .i_factor = 1, .relay_tap = &relays[RLY_4K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1K_OHM] },
								{ .number = 5, .nominal = 5000000, .calibrated_2w = 5000000, .calibrated_4w = 5000000, .i_factor = 1, .relay_tap = &relays[RLY_4K_OHM], .relay_not_plus_one = NULL },
								{ .number = 6, .nominal = 6000000, .calibrated_2w = 6000000, .calibrated_4w = 6000000, .i_factor = 1, .relay_tap = &relays[RLY_6K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1K_OHM] },
								{ .number = 7, .nominal = 7000000, .calibrated_2w = 7000000, .calibrated_4w = 7000000, .i_factor = 1, .relay_tap = &relays[RLY_6K_OHM], .relay_not_plus_one = NULL },
								{ .number = 8, .nominal = 8000000, .calibrated_2w = 8000000, .calibrated_4w = 8000000, .i_factor = 1, .relay_tap = &relays[RLY_8K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_1K_OHM] },
								{ .number = 9, .nominal = 9000000, .calibrated_2w = 9000000, .calibrated_4w = 9000000, .i_factor = 1, .relay_tap = &relays[RLY_8K_OHM], .relay_not_plus_one = NULL },
						},
						.relay_bypass = NULL,
				},

				// Decade 10k .. 90k Ohm
				{
						.order = 4,
						.i_0 = 3535,				// P_0 = 0.25W (derated), R_0 = 20kOhm -> uA
						.resistances =
						{
								{ .number = 0, .nominal =        0, .calibrated_2w =        0, .calibrated_4w =        0, .i_factor = 0, .relay_tap = &relays[RLY_00K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10K_OHM] },
								{ .number = 1, .nominal = 10000000, .calibrated_2w = 10000000, .calibrated_4w = 10000000, .i_factor = 2, .relay_tap = &relays[RLY_00K_OHM], .relay_not_plus_one = NULL },
								{ .number = 2, .nominal = 20000000, .calibrated_2w = 20000000, .calibrated_4w = 20000000, .i_factor = 2, .relay_tap = &relays[RLY_20K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10K_OHM] },
								{ .number = 3, .nominal = 30000000, .calibrated_2w = 30000000, .calibrated_4w = 30000000, .i_factor = 2, .relay_tap = &relays[RLY_20K_OHM], .relay_not_plus_one = NULL },
								{ .number = 4, .nominal = 40000000, .calibrated_2w = 40000000, .calibrated_4w = 40000000, .i_factor = 1, .relay_tap = &relays[RLY_40K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10K_OHM] },
								{ .number = 5, .nominal = 50000000, .calibrated_2w = 50000000, .calibrated_4w = 50000000, .i_factor = 1, .relay_tap = &relays[RLY_40K_OHM], .relay_not_plus_one = NULL },
								{ .number = 6, .nominal = 60000000, .calibrated_2w = 60000000, .calibrated_4w = 60000000, .i_factor = 1, .relay_tap = &relays[RLY_60K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10K_OHM] },
								{ .number = 7, .nominal = 70000000, .calibrated_2w = 70000000, .calibrated_4w = 70000000, .i_factor = 1, .relay_tap = &relays[RLY_60K_OHM], .relay_not_plus_one = NULL },
								{ .number = 8, .nominal = 80000000, .calibrated_2w = 80000000, .calibrated_4w = 80000000, .i_factor = 1, .relay_tap = &relays[RLY_80K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_10K_OHM] },
								{ .number = 9, .nominal = 90000000, .calibrated_2w = 90000000, .calibrated_4w = 90000000, .i_factor = 1, .relay_tap = &relays[RLY_80K_OHM], .relay_not_plus_one = NULL },
						},
						.relay_bypass = NULL,
				},

				// Decade 100k .. 900k Ohm
				{
						.order = 5,
						.i_0 = 1118,				// P_0 = 0.25W (derated), R_0 = 200kOhm -> uA
						.resistances =
						{
								{ .number = 0, .nominal =         0, .calibrated_2w =         0, .calibrated_4w =         0, .i_factor = 0, .relay_tap = &relays[RLY_000K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100K_OHM] },
								{ .number = 1, .nominal = 100000000, .calibrated_2w = 100000000, .calibrated_4w = 100000000, .i_factor = 2, .relay_tap = &relays[RLY_000K_OHM], .relay_not_plus_one = NULL },
								{ .number = 2, .nominal = 200000000, .calibrated_2w = 200000000, .calibrated_4w = 200000000, .i_factor = 2, .relay_tap = &relays[RLY_200K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100K_OHM] },
								{ .number = 3, .nominal = 300000000, .calibrated_2w = 300000000, .calibrated_4w = 300000000, .i_factor = 2, .relay_tap = &relays[RLY_200K_OHM], .relay_not_plus_one = NULL },
								{ .number = 4, .nominal = 400000000, .calibrated_2w = 400000000, .calibrated_4w = 400000000, .i_factor = 1, .relay_tap = &relays[RLY_400K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100K_OHM] },
								{ .number = 5, .nominal = 500000000, .calibrated_2w = 500000000, .calibrated_4w = 500000000, .i_factor = 1, .relay_tap = &relays[RLY_400K_OHM], .relay_not_plus_one = NULL },
								{ .number = 6, .nominal = 600000000, .calibrated_2w = 600000000, .calibrated_4w = 600000000, .i_factor = 1, .relay_tap = &relays[RLY_600K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100K_OHM] },
								{ .number = 7, .nominal = 700000000, .calibrated_2w = 700000000, .calibrated_4w = 700000000, .i_factor = 1, .relay_tap = &relays[RLY_600K_OHM], .relay_not_plus_one = NULL },
								{ .number = 8, .nominal = 800000000, .calibrated_2w = 800000000, .calibrated_4w = 800000000, .i_factor = 1, .relay_tap = &relays[RLY_800K_OHM], .relay_not_plus_one = &relays[RLY_NPLUS_100K_OHM] },
								{ .number = 9, .nominal = 900000000, .calibrated_2w = 900000000, .calibrated_4w = 900000000, .i_factor = 1, .relay_tap = &relays[RLY_800K_OHM], .relay_not_plus_one = NULL },
						},
						.relay_bypass = NULL,
				}
		}
};
