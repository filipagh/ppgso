#ifndef PPGSO_MAPPERITEM_H
#define PPGSO_MAPPERITEM_H

class MapperItem {

public:
    MapperItem(const std::string& basicString);

    int modelBoneId;
    int mocapBoneId;

    char modelXAxisMapping;
    char modelYAxisMapping;
    char modelZAxisMapping;

    int mocapMaxXAxisRotation;
    int mocapMinXAxisRotation;
    int mocapMaxYAxisRotation;
    int mocapMinYAxisRotation;
    int mocapMaxZAxisRotation;
    int mocapMinZAxisRotation;

    int modelMaxXAxisRotation;
    int modelMinXAxisRotation;
    int modelMaxYAxisRotation;
    int modelMinYAxisRotation;
    int modelMaxZAxisRotation;
    int modelMinZAxisRotation;

};

#endif //PPGSO_MAPPERITEM_H
