#include "TestButton1.h"

bool TestButton1::OnMouseButtonDown(MouseType _type)
{
    OutputDebugString(TEXT("你点击了1号按钮\n"));
    return true;
}

bool TestButton1::OnMouseButtonUp(MouseType _type)
{
    OutputDebugString(TEXT("你点击了1号按钮并抬起了按钮\n"));
    return true;
}
