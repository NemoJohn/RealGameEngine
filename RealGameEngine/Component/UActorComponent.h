#pragma once
#include "../UObject.h"


class UActorComponent :
    public UObject
{
public:
    virtual void SetupAttachment(UObject* _parent);
    UObject* GetOwning()const
    {
        return parent;
    }

protected:
    UObject* parent = nullptr;

private:

};

