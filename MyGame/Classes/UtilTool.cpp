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
	auto scene = Director::getInstance()->getRunningScene();
	if (scene->getTag() == TAG_SCENE)
	{
		return dynamic_cast<Layer*>(scene->getChildByTag(t));
	}
	return nullptr;
}
bool UtilTool::pauseLayerByTag(NodeTag t)
{
	auto scene = Director::getInstance()->getRunningScene();
	if (scene->getTag() == TAG_SCENE)
	{
		auto layer = dynamic_cast<Layer*>(scene->getChildByTag(t));
		auto vec = layer->getChildren();
		for (int i = 0; i < vec.size(); i++)
		{
			auto child = vec.at(i);
			child->pause();
		}
		layer->pause();
		scene->pause();
		Director::getInstance()->pause();
		log("---Pause---");
	}
	else
	{
		return false;
	}
	return true;
}
bool UtilTool::resumeLayerByTag(NodeTag t)
{
	Director::getInstance()->resume();
	auto scene = Director::getInstance()->getRunningScene();
	if (scene->getTag() == TAG_SCENE)
	{
		scene->resume();
		auto layer = dynamic_cast<Layer*>(scene->getChildByTag(t));
		layer->resume();
		auto vec = layer->getChildren();
		for (int i = 0; i < vec.size(); i++)
		{
			auto child = vec.at(i);
			child->resume();
		}
		log("---Resume---");
		
	}
	else
	{
		return false;
	}
	return true;
}
