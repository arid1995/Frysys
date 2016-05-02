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
    
    //this->visibleSize = Director::getInstance()->getVisibleSize();
    this->visibleSize = Size(1000, 1000);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
////////////////////////////
    ground = new Ground();
    ground->loadMap("level1.tmx");
    this->addChild(ground->getMap());
    
    
    
////////////////////////////////////
    /*auto edgeBody = PhysicsBody::createEdgeBox(this->visibleSize, PhysicsMaterial(0, 0, 0));
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(this->visibleSize.width / 2 + origin.x, this->visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);*/
    //float t;
    //this->eGround(t);

    this->player = new Player(this);
    
    ground->eGround(player);
    
    auto eventListener = EventListenerKeyboard::create();
    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    eventListener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);
    eventListener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    this->scheduleUpdate();
    
    return true;
}

/*void Game::eGround(float dt){
    
    ground.eGround( this );
    
}*/

void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            player->runToTheLeft();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            player->runToTheRight();
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            player->jump();
            break;
        case EventKeyboard::KeyCode::KEY_CTRL:
            player->attack();
            break;
    }
}

void Game::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            player->stop();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            player->stop();
            break;
    } 
}

void Game::update(float dt){
    //Vec2 locSprite = player->getSkin()->getPosition();
    //this->setPosition(Point(-locSprite.x + visibleSize.width/2, -locSprite.y + visibleSize.height/2));
    //CCLOG("x=%f, y=%f\n",locSprite.x, locSprite.y);
}






