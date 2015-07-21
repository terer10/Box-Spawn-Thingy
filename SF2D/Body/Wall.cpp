#include "Wall.h"
using namespace SF2D;
Wall::Wall(b2World *_world,b2Vec2 _position,b2Vec2 _size){
    Wall::_world = _world;
    Wall::_size = _size;
    Wall::_initialPosition = _position;
    setBox2D();
    setSFML();
}

Wall::Wall(b2World *_world,b2Vec2 _position,b2Vec2 _size,std::string _path){
    Wall::_world = _world;
    Wall::_size = _size;
    Wall::_initialPosition = _position;
    setBox2D();
    setSFML();
    load(_path);
}

void Wall::setBox2D(){
      _bodyDef.type = b2_staticBody;
    _bodyDef.position.Set(_initialPosition.x,_initialPosition.y);
    _body = _world->CreateBody(&_bodyDef);
    _shape.SetAsBox(_size.x/2,_size.y/2);

    _body->CreateFixture(&_shape,0.0f);
}

void Wall::updateBox2D(){
    _position = _body->GetPosition();
}

void Wall::setSFML(){
    _box->setSize(sf::Vector2f(_size.x,_size.y));
    _box->setOutlineThickness(1.0f);
    _box->setOutlineColor(sf::Color::White);
    _box->setFillColor(sf::Color::Transparent);
}

void Wall::updateSFML(){
    _box->setPosition(_position.x,_position.y);
    _box->setRotation(_convert->toDegrees(_body->GetAngle()));
}

void Wall::update(){
    updateBox2D();
    updateSFML();
}

void Wall::render(sf::RenderWindow *_window){
    _window->draw(*_box);
}
void Wall::load(std::string _path,sf::IntRect _portion){
    _texture = new sf::Texture;
    _texture->loadFromFile(_path);
    _box->setTexture(_texture);
    _box->setFillColor(sf::Color::White);
    _box->setOutlineThickness(0.0f);
    if(_portion!=sf::IntRect(0,0,0,0)){
        _box->setTextureRect(_portion);
    }
}
Wall::~Wall(){
    _world->DestroyBody(_body);
}
