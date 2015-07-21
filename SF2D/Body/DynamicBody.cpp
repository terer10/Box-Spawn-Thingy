#include "DynamicBody.h"
using namespace SF2D;
DynamicBody::DynamicBody(b2World *_world,b2Vec2 _position,b2Vec2 _size,bool _kinematic):Body(_world,_position,_size){
    _isKinematic = _kinematic;
    setBox2D();
}
DynamicBody::DynamicBody(b2World *_world,b2Vec2 _position,b2Vec2 _size,std::string _path,bool _kinematic):Body(_world,_position,_size,_path){
    _isKinematic = _kinematic;
    setBox2D();
    load(_path);
}
void DynamicBody::setBox2D(){
        if(!_isKinematic){
            _bodyDef.type = b2_dynamicBody;
        }else{
            _bodyDef.type = b2_kinematicBody;
        }
        _bodyDef.position.Set(_initalPosition.x,_initalPosition.y);
        _body = _world->CreateBody(&_bodyDef);
        _shape.SetAsBox(2,2);
        //_fixtureDef.density = 1.0f;
        _fixtureDef.shape = &_shape;
        _body->CreateFixture(&_fixtureDef);
}

void DynamicBody::setBodyProperties(b2BodyDef _properties){
    _bodyDef = _properties;
    _bodyDef.type = b2_dynamicBody;
    _body = _world->CreateBody(&_bodyDef);
}
void DynamicBody::setFixtureProperties(b2FixtureDef _properties){
    _world->DestroyBody(_body);
    _fixtureDef = _properties;
    setBox2D();
}

DynamicBody::~DynamicBody(){
    _world->DestroyBody(_body);
}
