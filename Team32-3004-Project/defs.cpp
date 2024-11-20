#include "defs.h"

string dataTypeToStr(DataType dataType) {
    switch (dataType) {
        case ENERGY_LVL: return "Energy Level";
        case IMMUNE_SYS: return "Immune System";
        case METABOLISM: return "Metabolism";
        case PSYC_EMO_STATE: return "Psycho-emotional State";
        case MUSCULOSKELE_SYS: return "Musculoskeletal System";
        default: return "Unknown";
    }
}

DataType strToDataType(string& dtStr) {
    if (dtStr == "Energy Level") return ENERGY_LVL;
    else if (dtStr == "Immune System") return IMMUNE_SYS;
    else if (dtStr == "Metabolism") return METABOLISM;
    else if (dtStr == "Psycho-emotional State") return PSYC_EMO_STATE;
    else if (dtStr == "Musculoskeletal System") return MUSCULOSKELE_SYS;
    return UNKNOWN;
}