#include "UContentWidget.h"

void UContentWidget::AddChild(UWidget* _child)
{
	uniqueChild = _child;
	_child->SetZOrder(GetZOrder());
	_child->SetParent(this);
}
