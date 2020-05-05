

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

};

