//
//  SceneManager.cpp
//  SingleEye
//
//  Created by gwsoft on 1/21/14.
//
//
#include "IncludeForCpp.h"
#include "SceneManager.h"


SceneManager* SceneManager::getInstance()
{
    static SceneManager instance;
    return &instance;
}


SceneManager::SceneManager()
{
    Node::init();
    
    m_pOldScene = NULL;
}


SceneManager::~SceneManager()
{
    m_vData.clear();
}

void SceneManager::replaceScene(SceneData &data)
{  
    Scene *pScene = NULL;
    
        //这里将记录当前的Tag
    m_eCurScene = data.aTag;
    
    switch (data.aTag) {
        case SCENE_TODAY:
        {
            pScene = TodayScene::createScene();
        }
            break;
        case SCENE_NEW:
        {
            pScene = NewScene::createScene();
        }
            break;
        case SCENE_DETAIL:
        {
            pScene = DetailScene::createScene(data.iData);
        }
            break;
        case SCENE_FREQUENCY:
        {
            pScene = FrequencyScene::createScene();
        }
            break;
        default:
            break;
    }
    
    if (m_vData.size() != 0) {
        Director::getInstance()->replaceScene(pScene);
    } else {
        //第1个场景
        Director::getInstance()->runWithScene(pScene);
    }
}

void SceneManager::back()
{    
    if (isOldScene()) {
        return;
    }        
    
    //删除当前场景记录            
    m_vData.pop_back();
    CCAssert(m_vData.size() != 0, "error");

    SceneData data = m_vData.at(m_vData.size() - 1);
    replaceScene(data);
}

void SceneManager::back(SceneTag aTag)
{
    if (isOldScene()) {
        return;
    }
    
    CCAssert(m_vData.size() != 0, "error");
    
    int index = m_vData.size();

    while (index > 0) {
        SceneData data = m_vData.at(index - 1);
        
        if (data.aTag == aTag) {
            replaceScene(data);
            break;
        }
        else
        {
            //删除该记录
            index--;
            m_vData.pop_back();
            CCAssert(index != 0, "no this scene.");
        }
    }
}

void SceneManager::forward(SceneTag aTag)
{   
    forward(aTag, 0, NULL);
}

void SceneManager::forward(SceneTag aTag, int iData, void* pData)
{
    if (isOldScene()) {
        return;
    }
    
    //记录进入的Scene
    SceneData data;
    
    data.aTag = aTag;
    data.iData = iData;
    data.pData = pData;
        
    replaceScene(data);

    m_vData.push_back(data);
}

SceneTag SceneManager::getLastSceneTag()
{
    if (m_vData.size() > 1) {
        SceneData data = m_vData.at(m_vData.size() - 2);        
        return data.aTag;
    }
    else
    {
        return SCENE_NONE;
    }
}

SceneTag SceneManager::getRunningSceneTag()
{      
    return m_eCurScene;
//    if (m_vData.size() != 0) {
//        SceneData data = m_vData.at(m_vData.size() - 1);        
//        return data.aTag;
//    }
//    else
//    {
//        return ST_None;
//    }
}

bool SceneManager::isOldScene()
{
    bool bRet = false;
    
    Scene *pRunningScene = Director::getInstance()->getRunningScene();
    
    if (pRunningScene != NULL) {
        if (m_pOldScene == pRunningScene) {
            bRet = true;
        }
        else
        {
            m_pOldScene = pRunningScene;
        }
    }
        
    return bRet;
}

void SceneManager::dumpAll()
{
    for (int i = 0; i < m_vData.size(); i++) 
    {
        CCLOG("######### %d", m_vData.at(i).aTag);
    }
}

