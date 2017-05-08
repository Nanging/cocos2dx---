#include "UtilTool.h"


UtilTool::UtilTool()
{
}


UtilTool::~UtilTool()
{
}
Size UtilTool::getSize()
{
	return Director::getInstance()->getVisibleSize();
}
Layer* UtilTool::getLayerByTag(NodeTag t)
{
	auto s = Director::getInstance()->getRunningScene();
	if (s->getTag() == TAG_SCENE)
	{
		return dynamic_cast<Layer*>(s->getChildByTag(t));
	}
	return nullptr;
}
