#ifndef DEFS_H
#define DEFS_H

#include <iostream>

using namespace std;

#define STARTING_BATTERY_LEVEL 100          // The starting battery level of the simulator (at 100%, but can dynamically adjust)

typedef enum {
    ENERGY_LVL,
    IMMUNE_SYS,
    METABOLISM,
    PSYC_EMO_STATE,
    MUSCULOSKELE_SYS,
    UNKNOWN             // This one is for the default case
} DataType;

/**
 * @brief Convert a `DataType` enum into its string form
 */
string dataTypeToStr(DataType dataType);

/**
 * @brief Convert a string into its associated `DataType` value (if applicable.)
 */
DataType strToDataType(string& dtStr);

#endif // DEFS_H