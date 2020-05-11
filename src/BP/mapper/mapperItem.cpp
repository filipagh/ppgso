//
// Created by filipagh on 5. 5. 2020.
//



#include <string>
#include <sstream>
#include "mapperItem.h"

MapperItem::MapperItem(const std::string& string) {
    std::stringstream head(string);
    head >> modelBoneId >> mocapBoneId >>
         modelXAxisMapping >> mocapMaxXAxisRotation >> mocapMinXAxisRotation >> modelMaxXAxisRotation >> modelMinXAxisRotation >>
         modelYAxisMapping >> mocapMaxYAxisRotation >> mocapMinYAxisRotation >> modelMaxYAxisRotation >> modelMinYAxisRotation >>
         modelZAxisMapping >> mocapMaxZAxisRotation >> mocapMinZAxisRotation >> modelMaxZAxisRotation >> modelMinZAxisRotation;
}
