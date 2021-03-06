/*
 * Серег, впиши сюда себя. Этот класс за тобой.
 */

#include "Game.h"
#include "Constants.h"
#include "SimpleAudioEngine.h"

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
    auto menu_item_2 = MenuItemFont::create("Exit", CC_CALLBACK_1(Game::Exit, this));

    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4)*3));
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4)*2));

    auto *menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/menu.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/menu.mp3");
    
    return true;
}

void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            if (!player->isAlive()) return;
            anusKnight->runToTheLeft();
            break;
        case EventKeyboard::KeyCode::KEY_A:
            if (!player->isAlive()) return;
            player->runToTheLeft();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            if (!player->isAlive()) return;
            anusKnight->runToTheRight();
            break;
        case EventKeyboard::KeyCode::KEY_D:
            if (!player->isAlive()) return;
            player->runToTheRight();
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            if (!player->isAlive()) return;
            anusKnight->jump();
            break;
        case EventKeyboard::KeyCode::KEY_W:
            if (!player->isAlive()) return;
            player->jump();
            break;
        case EventKeyboard::KeyCode::KEY_CTRL:
            if (!player->isAlive()) return;
            player->attack();
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
            if (!player->isAlive()) return;
            player->shoot();
            break;
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            exit(0);
            break;

    }
}

void Game::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            if (!player->isAlive()) return;
            anusKnight->stop();
            break;
        case EventKeyboard::KeyCode::KEY_A:
            if (!player->isAlive()) return;
            player->stop();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            if (!player->isAlive()) return;
            anusKnight->stop();
            break;
        case EventKeyboard::KeyCode::KEY_D:
            if (!player->isAlive()) return;
            player->stop();
            break;
    } 
}

void Game::update(float dt){
    int i = 0, j = 0;
    Point ptPlayer = player->getPosition();
    Size szPlayer = player->getContentSize();
    Point ptEnemy = anusKnight->getPosition();
    Size szEnemy = anusKnight->getContentSize();
    Size sz = getContentSize();
    Size szHeart = heartEnemy[0]->getContentSize();
    for (i = 0; i < player->getLives(); i++){
        heartPlayer[i]->setPosition(Point(ptPlayer.x - szPlayer.width/2.5 + i*szHeart.width, ptPlayer.y + szPlayer.height/2 + szHeart.height));
    }
    for (;i < PLAYER_LIVES_COUNT; i++){
        heartPlayer[i]->setVisible(false);
    }
    for (j = 0; j < anusKnight->getLives(); j++){
        heartEnemy[j]->setPosition(Point(ptEnemy.x - szEnemy.width/2.5 + j*szHeart.width, ptEnemy.y + szEnemy.height/2 + szHeart.height));
    }
    for (;j < PLAYER_LIVES_COUNT; j++){
        heartEnemy[j]->setVisible(false);
    }
}

/*void Game::GameOver(){
    if (!wasHere){
        exitSprite = Sprite::create("man.jpg");
        exitSprite->setPosition(Point(player->getPosition().x, player->getPosition().y));
        addChild(exitSprite);
    }
}*/

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    
    isTouching = true;
    touchPosition = Point(touch->getLocation().x, touch->getLocation().y);
    if (touchPosition == exitSprite->getPosition())
        exit(0);
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
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/general.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/general.mp3");
    
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
    //Exit *exit = new Exit(this, Vec2(650, 70));
    
    ground->eGround(ObjectList::getInstance()->getList());
    
    heartPlayer = (Sprite**) malloc (PLAYER_LIVES_COUNT*sizeof(Sprite*));
    heartEnemy = (Sprite**) malloc (PLAYER_LIVES_COUNT*sizeof(Sprite*));
    
    for (int i = 0; i < PLAYER_LIVES_COUNT; i++){
        heartPlayer[i] = Sprite::create("heart.png");
        heartEnemy[i] = Sprite::create("heart.png");
        addChild(heartPlayer[i]);
        addChild(heartEnemy[i]);
    }
    Size sizeOfMap = ground->getMap()->getContentSize();
    camera = Follow::create(player, Rect(0,0, sizeOfMap.width, sizeOfMap.height));
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

void Game::Exit(cocos2d::Ref *pSender){
    exit(0);
}

void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}





