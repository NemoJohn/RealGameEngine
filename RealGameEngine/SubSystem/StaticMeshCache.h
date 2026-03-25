#pragma once
#include "TSingleton.h"
#include "../xml/tinyxml.h"
#include "../utility.hpp"


class StaticMeshCache :
    public TSingleton<StaticMeshCache>
{
public:
    void Init();
    FStaticMeshAsset FindStaticMeshAssetByID(string id);
private:
    map<string, FStaticMeshAsset> allStaticMesh;

};

