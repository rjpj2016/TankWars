//
//  playerManager.cpp
//  Tank Wars
//
//  Created by Rajat Parajuli on 2/11/18.
//  Copyright © 2018 Rajat Parajuli. All rights reserved.
//

#define PI 3.14159265

#include "playerManager.hpp"
#include <iostream>

PlayerManager::PlayerManager(MissileManager& misM){
    missileManager = &misM;
}
PlayerManager::~PlayerManager(){}

float dot (sf::Vector2f vec1, sf::Vector2f vec2){
    return vec1.x * vec2.x + vec1.y * vec2.y ;
}

bool PlayerManager::addPlayer(Player player){
    for(int i=0;i<players.size();i++){
        if ( players[i].getHash() == player.getHash() ){
            return false;
        }
    }
    players.push_back(player);
    Player* temp = getPlayerByHash(player.getHash());
    temp->playerTank.setPlayerRef(temp);
    temp->playerTank.bodyDef.type = b2_dynamicBody;
    temp->playerTank.bodyDef.position.Set(temp->playerTank.getPosition().x, temp->playerTank.getPosition().y);
    temp->playerTank.cBody = world->CreateBody(&(temp->playerTank.bodyDef));
    temp->playerTank.shape.SetAsBox(temp->playerTank.getSize().x / 2, temp->playerTank.getSize().y/2);
    temp->playerTank.fixtureDef.shape = &temp->playerTank.shape;
    temp->playerTank.fixtureDef.friction = 0.0f;
    temp->playerTank.fixtureDef.density = 1.0f;
    temp->playerTank.fixtureDef.restitution = 0.1f;
    temp->playerTank.cBody->CreateFixture(&(temp->playerTank.fixtureDef));
    temp->playerTank.cBody->SetLinearDamping(1.0f);
    temp->playerTank.cBody->SetAngularDamping(1.0f);
    //temp->playerTank.cBody->SetAngularVelocity(1000.0f);
    
    return true;
}

bool PlayerManager::removePlayersByIP(sf::IpAddress ip){
    for (int i=0;i<players.size();i++){
        if (players[i].getIP() == ip){
            players.erase(players.begin() + i);
            return true;
        }
    }
    return false;
}
void PlayerManager::updatePlayers(float deltaTime){
    std::cout<<checkCollisions()<<" Collisions\n"<<std::flush;
    for(int i=0;i<players.size();i++){
        players[i].playerTank.update(deltaTime);
    }
}

void PlayerManager::drawPlayers(sf::RenderWindow& window){
    for(int i=0;i<players.size();i++){
        players[i].playerTank.draw(window);
    }
}

Player& PlayerManager::getPlayer(int id){
    return players[id];
}

bool PlayerManager::removePlayer(uint64_t hash){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash){
            players.erase(players.begin() + i);
            return true;
        }
    }
    return false;
}

void PlayerManager::setPlayerButtons(uint64_t hash, bool *buttons){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash){
            players[i].setPressedButtons(buttons);
            return;
        }
    }
    std::cout<<"Not found player\n";
}

Player* PlayerManager::getPlayerByHash(uint64_t hash){
    for (int i=0;i<players.size();i++){
        if (players[i].getHash() == hash ){
            return &players[i];
        }
    }
    return NULL;
}


int PlayerManager::checkCollisions(){
    int counter = 0;
    int pSize = players.size();
    for (int i=0;i<pSize-1;i++){
        std::cout<<i<<"\t"<<pSize-1<<"\n";
        for (int j=i+1;j<pSize;j++){
            std::cout<<dot(players[i].playerTank.getPosition() - players[j].playerTank.getPosition(),
                           players[j].playerTank.getVelocityVector() - players[i].playerTank.getVelocityVector())<<"\n";
            if( players[i].playerTank.getFloatRect().intersects
                            (players[j].playerTank.getFloatRect()) &&
                                        dot(players[i].playerTank.getPosition() - players[j].playerTank.getPosition(),
                                      players[j].playerTank.getVelocityVector() - players[i].playerTank.getVelocityVector()) > 0){
                //players[i].playerTank.revertMovement();
                //players[j].playerTank.revertMovement();
            }
            
        }
    }
    return counter;
}


void PlayerManager::setWorld(b2World * worl){
    world = worl;
}

