//
//  MainMenuScene.cpp
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#include "MainMenuScene.h"
#include "LoadingScene.h"
#include "PublicApi.h"
#include "Plane.h"
#include "GameLayer.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Star_Chaser.mp3");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //************ adds Plane ****************
    plane = Plane::create();
    //plane->setPosition(visible_size_macro.width/2+100,visible_size_macro.height/2);
    this->addChild(plane, 10);
    this->scheduleUpdate();
    
    //************ adds emission flare ****************
    auto flare = ParticleSystemQuad::create("missileFlare.plist");
    flare->setScale(5);
    float originX = -9.0f;
    float originY = 159.0f;
    float originZ = 9.0f;
    flare->setTotalParticles(50);
    flare->setRotation3D(Vertex3F(-originX,-originY,-originZ));
    flare->setPosition(-39,-2);
    flare->setPositionType(tPositionType::GROUPED);
    flare->setStartColor(Color4F(0,0.99,1,1));
    plane->addChild(flare, -1);
    
    auto emis = ParticleSystemQuad::create("menuEmission.plist");
    emis->setScale(3);
    //emis->setTotalParticles(50);
    emis->setRotation3D(Vertex3F(-originX,-originY,-originZ));
    emis->setPosition(-45,-2);
    emis->setPositionType(tPositionType::FREE);
    emis->setRotation(180);
    //emis->setStartColor(Color4F(0,0.99,1,1));
    plane->addChild(emis, -2);

    
    //************ adds stars ****************
    auto fileUtil = FileUtils::getInstance();
    auto plistData = fileUtil->getValueMapFromFile("vanishingPoint.plist");
    auto stars = ParticleSystemQuad::create(plistData);
    stars->setAnchorPoint(Point(0.5f,0.5f));
    stars->setPosition(visible_size_macro.width-50,visible_size_macro.height/2 +40);
//    stars->setTotalParticles(8);
//    stars->setEmissionRate(9999999999);
//    stars->setScale(0.7);
//    stars->setTotalParticles(5);
//    stars->setEmissionRate(9999999999);
    this->addChild(stars,1,1);
    
    //************* adds background ***********
    auto background = Sprite::create("mainmenu_BG.png");
    background->setAnchorPoint(Point(0,0));
    this->addChild(background,-1,-1);
    
    //************* adds logo *****************
    auto logo = Sprite::create("LOGO.png");
    logo->setAnchorPoint(Point(0.5,0.5));
    logo->setPosition(visibleSize.width/2,visibleSize.height-200);
    this->addChild(logo,3,3);
    
    //************* adds start game ***********
    startgame_item = MenuItemImage::create("start_game.png", "start_game.png", CC_CALLBACK_1(MainMenuScene::startgame, this));
    startgame_item->setPosition(visibleSize.width/2,200);
    startgame_item->setScale(1.3);
    
    //************* license *******************
    license_item = MenuItemImage::create("license.png", "license.png", CC_CALLBACK_1(MainMenuScene::license, this));
    license_item->setPosition(visibleSize.width/2-200,100);
    license_item->setScale(0.7);

    //************* credits ******************
    auto credits = MenuItemImage::create("credits.png", "credits.png", CC_CALLBACK_1(MainMenuScene::credits, this));
    credits->setPosition(visibleSize.width/2+200,100);

    //************* quitgame ******************
    credits_item = MenuItemImage::create("credits.png", "credits.png", CC_CALLBACK_1(MainMenuScene::credits, this));
    credits_item->setPosition(visibleSize.width/2+200,100);
    credits_item->setScale(0.7);
    auto menu = Menu::create(startgame_item,license_item,credits_item, NULL);
    menu->setPosition(origin);
    this->addChild(menu,3);
    
    return true;
}

void MainMenuScene::update(float dt){
    pRate+=0.01;
    plane->setPosition3D(Vertex3F(visible_size_macro.width/2+100,480-20*sin(1.05*pRate),0));
}

void MainMenuScene::startgame(Ref* sender){
    startgame_item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                                ScaleTo::create(0.1f, 0.9f),
                                                ScaleTo::create(0.1f, 1.0f),
                                               CallFunc::create(CC_CALLBACK_0(MainMenuScene::startgame_callback,this)),NULL));
}

void MainMenuScene::startgame_callback()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    GameLayer::isDie=false;
    Director::getInstance()->replaceScene(LoadingScene::createScene());
}

void MainMenuScene::credits(Ref* sender){
    credits_item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                               ScaleTo::create(0.1f, 0.9f),
                                               ScaleTo::create(0.1f, 1.0f),
                                             CallFunc::create(CC_CALLBACK_0(MainMenuScene::credits_callback, this)),NULL));
}

void MainMenuScene::credits_callback()
{
    
}

void MainMenuScene::license(Ref* sender){
    license_item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                               ScaleTo::create(0.1f, 0.9f),
                                               ScaleTo::create(0.1f, 1.0f),
                                             CallFunc::create(CC_CALLBACK_0(MainMenuScene::license_callback, this)),NULL));
}

void MainMenuScene::license_callback()
{
    
}