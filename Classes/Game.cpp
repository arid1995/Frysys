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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(Game::Play, this));
    auto menu_item_2 = MenuItemFont::create("Highscores", CC_CALLBACK_1(Game::Highscores, this));
    auto menu_item_3 = MenuItemFont::create("Settings", CC_CALLBACK_1(Game::Settings, this));

    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4)*3));
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4)*2));
    menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4)*1));
    
    auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    
    
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
    int i = 0;
    Point ptPlayer = player->getPosition();
    Size sz = getContentSize();
    for (i = 0; i < anusKnight->getLives(); i++){
        heart[i]->setPosition(Point(ptPlayer.x - sz.width/2.5 + i*20, ptPlayer.y + sz.height/2.5));
    }
    for (;i < PLAYER_LIVES_COUNT; i++){
        heart[i]->setVisible(false);
    }
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

void Game::Play(cocos2d::Ref *pSender){
    ground = new Ground();
    ground->loadMap("level1.tmx");
    addChild(ground->getMap());
    
    cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("ninja.plist", "ninja.png");
    cache->addSpriteFramesWithFile("knight.plist", "knight.png");
    cache->addSpriteFramesWithFile("objects.plist", "objects.png");
    
    player = new Player(this, "knight");
    
    anusKnight = new Enemy(this, "ninja");

    //FIXME::Hardcode!
    Exit *exit = new Exit(this, Vec2(650, 70));
    
    ground->eGround(ObjectList::getInstance()->getList());
    
    heart = (Sprite**) malloc (PLAYER_LIVES_COUNT*sizeof(Sprite*));
    
    for (int i = 0; i < 3; i++){
        heart[i] = Sprite::create("heart.png");
        addChild(heart[i]);
    }
    
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
}

void Game::Highscores(cocos2d::Ref *pSender){
    CCLOG("Highscores");
}

void Game::Settings(cocos2d::Ref *pSender){
    CCLOG("Settings");
}

void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}





