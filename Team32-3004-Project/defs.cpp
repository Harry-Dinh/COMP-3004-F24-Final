#include "defs.h"

string dataTypeToStr(HealthCategory dataType) {
    switch (dataType) {
    case ENERGY_LVL: return "Energy Level";
    case IMMUNE_SYS: return "Immune System";
    case METABOLISM: return "Metabolism";
    case PSYC_EMO_STATE: return "Psycho-emotional State";
    case MUSCULOSKELE_SYS: return "Musculoskeletal System";
    default: return "Unknown";
    }
}

HealthCategory strToDataType(string& dtStr) {
    if (dtStr == "Energy Level") return ENERGY_LVL;
    else if (dtStr == "Immune System") return IMMUNE_SYS;
    else if (dtStr == "Metabolism") return METABOLISM;
    else if (dtStr == "Psycho-emotional State") return PSYC_EMO_STATE;
    else if (dtStr == "Musculoskeletal System") return MUSCULOSKELE_SYS;
    return UNKNOWN_C;
}

string meridianToStr(Meridian meridian) {
    switch (meridian) {
    case LUNG: return "Lungs";
    case HEART_CONSTRICTOR: return "Heart Constrictor";
    case HEART: return "Heart";
    case SMALL_INTESTINE: return "Small Intestine";
    case TRIPLE_HEATER: return "Triple Heater";
    case LARGE_INTESTINE: return "Large Intestine";
    case SPLEEN: return "Spleen";
    case LIVER: return "Liver";
    case KIDNEY: return "Kidney";
    case BLADDER: return "Bladder";
    case GALLBLADDER: return "Gallbladder";
    case STOMACH: return "Stomach";
    default: return "UNKNOWN TYPE";
    }
}

Meridian intToMeridian(int i) {
    switch (i) {
    case 1: return LUNG;
    case 2: return HEART_CONSTRICTOR;
    case 3: return HEART;
    case 4: return SMALL_INTESTINE;
    case 5: return TRIPLE_HEATER;
    case 6: return LARGE_INTESTINE;
    case 7: return SPLEEN;
    case 8: return LIVER;
    case 9: return KIDNEY;
    case 10: return BLADDER;
    case 11: return GALLBLADDER;
    case 12: return STOMACH;
    default: return UNKNOWN_T;
    }
}

Meridian strToMeridian(string& mStr) {
    if (mStr == "Lungs") return LUNG;
    else if (mStr == "Heart Constrictor") return HEART_CONSTRICTOR;
    else if (mStr == "Heart") return HEART;
    else if (mStr == "Small Intestine") return SMALL_INTESTINE;
    else if (mStr == "Triple Heater") return TRIPLE_HEATER;
    else if (mStr == "Large Intestine") return LARGE_INTESTINE;
    else if (mStr == "Spleen") return SPLEEN;
    else if (mStr == "Liver") return LIVER;
    else if (mStr == "Kidney") return KIDNEY;
    else if (mStr == "Bladder") return BLADDER;
    else if (mStr == "Gallbladder") return GALLBLADDER;
    else if (mStr == "Stomach") return STOMACH;
    
    return UNKNOWN_T;
}
