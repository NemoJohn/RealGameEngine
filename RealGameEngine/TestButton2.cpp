#include "TestButton2.h"

bool TestButton2::OnMouseButtonDown(MouseType _type)
{
    OutputDebugString(TEXT("你点击了2号按钮\n"));
    return true;
}

bool TestButton2::OnMouseButtonUp(MouseType _type)
{
    OutputDebugString(TEXT("你点击了2号按钮并抬起了按钮\n"));
    return true;
}
