//
//  tank.hpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 1/25/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#pragma once

#ifndef tank_hpp
#define tank_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "message.hpp"
#include "unistd.h"
#include <Box2D/Box2D.h>
//#include "missileManager.hpp"

class MissileManager;
class Player;

class Tank{
public:
    Tank( sf::Texture* texture, MissileManager* mManager);
    ~Tank();
    void setOrigin(sf::Vector2f origin);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    void update(float deltaTime);
    int posOrNeg(float x);
    float sign(float temp);
    float clamp(float var, float limit);
    void setPressedButtons(bool * buttons);
    void setPlayerRef(Player * p);
    float getTurretOrientation();
    sf::FloatRect getFloatRect();
    float getVelocityScalar();
    float getOrientation();
    void move(sf::Vector2f movement);
    void setExternalVelocity(float scalar, float direction);
    void revertMovement();
    float getLastDTime();
    sf::Vector2f getSize();
    sf::Vector2f getVelocityVector();
    b2BodyDef bodyDef;
    b2Body * cBody;
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;
    
    
private:
    MissileManager * missileManager;
    Player* player;
    
    long long lastMissileTime;
    
    
    sf::Texture texture;
    sf::RectangleShape body, turret;
    sf::IntRect bodyRect, turretRect;
    float textureWidth, textureHeight;
    
    
    float linearAcc;
    float angularAcc;
    
    sf::Vector2f velocityVector;
    float maxLinearVelocity;
    float turretVelocity;
    float velocityScalar;
    
    sf::Vector2f lastMovement; // for collision, to revert it
    
    float externalVelocityScalar;
    float externalVelocityDirection;
    
    sf::Vector2f resultantVelocityVector;
    
    float lastDTime;
    
    
    float angularVelocity;
    float maxAngularVelocity;
    
    float bodyOrientation;
    float turretOrientation;
    bool  pressedButtons[9];
};

long long getMs();
#endif /* tank_hpp */
