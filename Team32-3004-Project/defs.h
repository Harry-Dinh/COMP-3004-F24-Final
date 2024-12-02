#ifndef DEFS_H
#define DEFS_H

/*
This file contains all of the constants that are used throughout the project.
*/

#define STARTING_BATTERY_LEVEL 100          // The starting battery level of the simulator (at 100%, but can dynamically adjust)
#define MEASUREMENT_COUNT 12                // The maximum number of measurements that each scan can take
#define RYODORAKU_MIN_BOUND 5               // The lowest electrical current that can flow through the human body
#define RYODORAKU_MAX_BOUND 160             // The highest electrical current that can flow through the human body
#define HEALTH_CAT_COUNT 5                  // The number of health categories displayed on the summary screen
#define HEALTHY_UPPER_BOUND 70              // The upper bound for comparing health meridian values
#define HEALTHY_LOWER_BOUND 47              // The lower bound for comparing health meridian values

#endif // DEFS_H
