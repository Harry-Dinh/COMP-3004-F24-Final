#ifndef DEFS_H
#define DEFS_H

#include <iostream>

using namespace std;

#define STARTING_BATTERY_LEVEL 100          // The starting battery level of the simulator (at 100%, but can dynamically adjust)
#define MEASUREMENT_COUNT 12                // The maximum number of measurements that each scan can take
#define RYODORAKU_MIN_BOUND 5               // The lowest electrical current that can flow through the human body
#define RYODORAKU_MAX_BOUND 160             // The highest electrical current that can flow through the human body
#define HEALTH_CAT_COUNT 5                  // The number of health categories displayed on the summary screen
#define HEALTHY_UPPER_BOUND 70              // The upper bound for comparing health meridian values
#define HEALTHY_LOWER_BOUND 47              // The lower bound for comparing health meridian values

// MARK: HEALTH CATEGORY

typedef enum {
    ENERGY_LVL,
    IMMUNE_SYS,
    METABOLISM,
    PSYC_EMO_STATE,
    MUSCULOSKELE_SYS,
    UNKNOWN_C             // This one is for the default case
} HealthCategory;

/**
 * @brief Convert a `DataType` enum into its string form
 */
string dataTypeToStr(HealthCategory dataType);

/**
 * @brief Convert a string into its associated `HealthCategory` value (if applicable.)
 */
HealthCategory strToDataType(string& dtStr);

// MARK: MERIDIAN TYPES

/**
 * @brief The 12 meridian points on a human body, data is associated with the the recorded Scan data.
 * Source: https://journals.sagepub.com/doi/10.1177/1420326X11409448?icid=int.sj-full-text.similar-articles.2
 */
typedef enum {
    LUNG,
    HEART_CONSTRICTOR,  // aka Pericardium
    HEART,
    SMALL_INTESTINE,
    TRIPLE_HEATER,      // aka Triple warmer
    LARGE_INTESTINE,
    SPLEEN,
    LIVER,
    KIDNEY,
    BLADDER,
    GALLBLADDER,
    STOMACH,
    UNKNOWN_T         // Not a meridian but for the default case in the switch statement
} Meridian;

/**
 * @brief Convert a Meridian enum to its associated string. This is converting to `std::string`, not `QString`.
 */
string meridianToStr(Meridian meridian);

/**
 * @brief Convert a valid Meridian string back to its enum form.
 */
Meridian strToMeridian(string& mStr);
Meridian intToMeridian(int);
#endif // DEFS_H
