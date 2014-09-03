//
//  Main.cpp
//  aStar
//
//  Created by Yawnsan on 14-8-21.
//
//

#include "Main.h"
USING_NS_CC;


cocos2d::Scene *Main::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = Main::create();
    scene -> addChild( layer );
    return scene;
}

bool Main::init()
{
    if ( Layer::init() )
    {
        return true;
    }
    
    return false;
}
//long Main::getCurrentTime()
//{
//    struct timeval tv;
//    gettimeofday(&tv,NULL);
//    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
//}
void Main::onEnter()
{
    Layer::onEnter();
//    long s1 = this->getCurrentTime();
//    log("+++++%li", this->getCurrentTime());
    Main::createGround();
    Main::createRobot();
    this->run(begin, -1);
    this->back();
//    log("=====%i====", j);
//    long s2 = this->getCurrentTime();
//    log("+++++%li", (s2 - s1));
}

void Main::createGround()
{
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 48; x++)
        {
            auto floor = Floor::create( Color4B::WHITE);
            floor -> setPosition(x * (floor -> getContentSize().width), y * (floor -> getContentSize().height));
            floor -> setX(x);
            floor -> setY(y);
            floor -> setFoorState( StateTrue );
            this -> addChild( floor );
            if ( (x == 15 && y < 7) || (x == 3 && y < 10) || (y == 12 && x < 20 && x>1) || (x == 5 &&y>2 && y<30) || (x == 13 && y < 25) ||              (x == 21 && y < 20) || (x == 26 && y > 5) || (x == 8 && y < 5) || (x == 30 && y < 25) || (x >30 && x < 40 && y == 20) || (x >33 && x <= 47 && y == 17)  || (x ==36 && y > 5 && y < 17) || (x ==38  && y < 10)|| (x==43 && y > 3 && y < 17)){
                    floor -> setColor( Color3B::GRAY );
                    floor -> setFoorState( StateFalse );
                }
            ground.pushBack( floor );
        }
    }
}

void Main::createRobot()
{
    end = Floor::create( Color4B::BLUE );
    end -> setPosition( (ground.at( Floor::at(44, 12) )) -> getPosition() );
    end -> setX(44);
    end -> setY(12);
    this -> addChild( end );
    
    begin = Floor::create( Color4B::BLUE );
    begin -> setPosition( (ground.at( Floor::at(12, 1) )) -> getPosition() );
    begin -> setX(12);
    begin -> setY(1);
    begin -> setH( fabs((end -> getX() - begin -> getX())) + fabs( end -> getY() - begin -> getY() ) );
    begin -> setG(0);
    this -> addChild( begin );
    open.pushBack( begin );
}

void Main::run(Floor * floor, int index){
    this->handleFloor(floor, index);
}

void Main::handleFloor(Floor *floor, int index){
    
    Vector<Floor *> otherFloor;
    Vector<Floor *> minList;
//    int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int direct[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    for (int i = 0; i < 8; i++) {
        this->createOtherFloor(floor, direct[i], &otherFloor);
    }
    
    open.pushBack(otherFloor);
    sort(open.begin(), open.end(), [](Floor * f1, Floor * f2){
        return f1->getF() > f2->getF() ? true : false;
    });
    Floor * floorLast ;
    for (int i = 0; i < open.size()-1; i++) {
        if (open.at(i+1)->getF()<open.at(i)->getF()) {
            floorLast = open.at(i+1);
        }
    }
    
    
    if (fabs(floor->getX() - end->getX()) > 1 || fabs(floor->getY() - end->getY()) > 1 ) {
//        auto floorLast = open.at(open.size() - 1);
        open.eraseObject(floorLast);
        this->handleFloor(floorLast, 0);
    }
}

void Main::createOtherFloor(Floor* source, int direct[], Vector<Floor *> * otherFloor){
    
    int x = source->getX() + direct[0];
    int y = source->getY() + direct[1];
    if ( x < 0 || x >= 48 || y < 0 || y >= 32){
        return;
    }
    auto floor = ground.at( Floor::at(x, y) );
    if (floor->getFoorState() == StateTrue && !close.contains(floor) && !open.contains(floor)) {
        floor->setG(source->getG() + 1);
        floor->setH(fabs(end->getX() - floor->getX()) + fabs(end->getY() - floor->getY()));
        floor->setLastFloor(source);
        floor->setColor(Color3B::BLUE);
        
        {
            std::ostringstream oss;
            oss<<floor->getF();
            floor->setString(oss.str());
        }
        
        close.pushBack(floor);
        otherFloor->pushBack(floor);
    }
    
}


void Main::back()
{
    if (open.size() != 0) {
        Floor *index = open.at( open.size() - 1 );
        while ( index -> getLastFloor() != NULL )
        {
            index -> setColor( Color3B::RED );
            move.pushBack(index);                               //移动路径数组
            index = index -> getLastFloor();
        }
    }
    
}
