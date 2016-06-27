/*
 * Серег, впиши сюда себя. Этот класс за тобой.
 */

#include "Game.h"
#include "Constants.h"

USING_NS_CC;

Scene* Game::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = Game::create();
    //layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool Game::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    this->visibleSize = Director::getInstance()->getVisibleSize();
    //visibleSize = Size(1000, 1000);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ground = new Ground();
    ground->loadMap("level1.tmx");
    addChild(ground->getMap());

    //loading textures into cache
    cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("ninja.plist", "ninja.png");
    cache->addSpriteFramesWithFile("knight.plist", "knight.png");
    cache->addSpriteFramesWithFile("objects.plist", "objects.png");

    //just a test delete when you want to {
    player = new Player(this, "ninja");
    
    anusKnight = new Enemy(this, "knight");
    

    /*for (int i = 0; i < 5; i++) {
        Enemy *anusKnight = new Enemy(this, "knight");
        ObjectList::getInstance()->addObject(anusKnight);
        anusKnight->setPosition(400+i*70, 200);
    }*/

    Exit *exit = new Exit(this, Vec2(650, 70));
    
    ground->eGround(ObjectList::getInstance()->getList());

    camera = Follow::create(player, Rect::ZERO);
    camera->retain();
    runAction(camera);
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        auto eventListener = EventListenerKeyboard::create();
        Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
        eventListener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);
        eventListener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
    #else
        auto eventListener = EventListenerTouchOneByOne::create();
        eventListener->setSwallowTouches(true);
        eventListener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
        eventListener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
        eventListener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
        eventListener->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled, this);
        isTouching = false;
    #endif

    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    scheduleUpdate();
    
    return true;
}

void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            anusKnight->runToTheLeft();
            break;
        case EventKeyboard::KeyCode::KEY_A:
            player->runToTheLeft();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            anusKnight->runToTheRight();
            break;
        case EventKeyboard::KeyCode::KEY_D:
            player->runToTheRight();
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            anusKnight->jump();
            break;
        case EventKeyboard::KeyCode::KEY_W:
            player->jump();
            break;
        case EventKeyboard::KeyCode::KEY_CTRL:
            player->attack();
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
            player->shoot();
            break;
    }
}

void Game::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            anusKnight->stop();
            break;
        case EventKeyboard::KeyCode::KEY_A:
            player->stop();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            anusKnight->stop();
            break;
        case EventKeyboard::KeyCode::KEY_D:
            player->stop();
            break;
    } 
}

void Game::update(float dt){
    //Vec2 locSprite = player->getSkin()->getPosition();
    //this->setPosition(Point(-locSprite.x + visibleSize.width/2, -locSprite.y + visibleSize.height/2));

    //rough example of how to use collisions
    //makes player run into a death sequence if he collided with something
    /*if(player->getCollidedObjects(objects).size() != 0) {
        player->stop();
        player->setSpeedX(0.0f);
        player->setSpeedY(-0.1f);
        player->dead();
    }*/
}

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    
    isTouching = true;
    touchPosition = Point(touch->getLocation().x, touch->getLocation().y);
    if ((touchPosition.x > getContentSize().width/4*3) && (touchPosition.y <= getContentSize().height/2))
        player->runToTheRight();
    if ((touchPosition.x < getContentSize().width/4) && (touchPosition.y <= getContentSize().height/2))
        player->runToTheLeft();
    if ((touchPosition.x <= getContentSize().width/4) && (touchPosition.y > getContentSize().height/2)){
        player->runToTheLeft();
        player->jump();
    }
    if ((touchPosition.x >= getContentSize().width/4*3) && (touchPosition.y > getContentSize().height/2)){
        player->runToTheRight();
        player->jump();
    }
    if ((touchPosition.x > getContentSize().width/4) && (touchPosition.x < getContentSize().width/4*3) && (touchPosition.y > getContentSize().height/2)){
        player->jump();
    }
    if ((touchPosition.x > getContentSize().width/4) && (touchPosition.x < getContentSize().width/4*3) && (touchPosition.y <= getContentSize().height/2)){
        player->attack();
    }
    return true;
}

void Game::onTouchMove(cocos2d::Touch *touch, cocos2d::Event *event) {
    
}

void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
    isTouching = false;
    player->stop();
}

void Game::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event) {
    onTouchEnded(touch, event);
}






