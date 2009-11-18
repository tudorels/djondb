#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#include "processdefinition.h"

class ProcessDefinition;

class Property {
private:
    long id;
    string* propertyName;
    PropertyType* propertyType;
    ProcessDefinition* processDefinition;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getPropertyName() {
        return propertyName;
    }

    void setPropertyName(string* _propertyName) {
        propertyName = _propertyName;
    }

    PropertyType* getPropertyType() {
        return propertyType;
    }

    void setPropertyType(PropertyType* _propertyType) {
        propertyType = _propertyType;
    }
};



#endif // PROPERTY_H_INCLUDED
