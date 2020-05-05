

#include <string>
#include <sstream>
#include "mapperItem.h"

MapperItem::MapperItem(const std::string& string) {
    std::stringstream head(string);
    head >> modelBoneId >> mocapBoneId >>
    modelXAxisMapping >> mocapMaxXAxisRotation >> mocapMinXAxisRotation >>
    modelYAxisMapping >> mocapMaxYAxisRotation >> mocapMinYAxisRotation >>
    modelZAxisMapping >> mocapMaxZAxisRotation >> mocapMinZAxisRotation;
}
