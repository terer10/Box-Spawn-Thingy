#include "Body.h"
using namespace SF2D;
Body::Body(b2World *_world,b2Vec2 _position,b2Vec2 _size){
    Body::_world = _world;
    Body::_initalPosition = _position;
    Body::_size = _size;
    setBox2D();
    setSFML();
}
Body::Body(b2World *_world,b2Vec2 _position,b2Vec2 _size,std::string _path){
    Body::_world = _world;
    Body::_initalPosition = _position;
    Body::_size = _size;
    setBox2D();
    setSFML();
    load(_path);
}
void Body::setBodyProperties(b2BodyDef _bodyDef){
    Body::_bodyDef = _bodyDef;
}
void Body::setBox2D(){
    _bodyDef.position.Set(_initalPosition.x,_initalPosition.y);
    //Creates the body in the world
    _body = _world->CreateBody(&_bodyDef);
    //Set the box to only half the size because Box2D multiplies the given size by 2 automatically
    _shape.SetAsBox(_size.x/2,_size.y/2);
    _fixtureDef.density = 1.0f;
    _fixtureDef.friction = 0.3;
    //Sets the box at the initial position
    _fixtureDef.shape = &_shape;
    //_body->CreateFixture(&_fixtureDef);
}
void Body::updateBox2D(){
    //Sets _position to the body's position
    _position = _body->GetPosition();
}
void Body::setSFML(){
    _box->setOutlineColor(sf::Color::White);
    _box->setFillColor(sf::Color::Transparent);
    _box->setOutlineThickness(1.0f);
    _box->setSize(sf::Vector2f(_size.x,_size.y));
}
void Body::updateSFML(){
    _box->setPosition(_position.x,_position.y);
    _box->setRotation(_convert.toDegrees(_body->GetAngle()));
}
void Body::render(sf::RenderWindow *_window){
        _window->draw(*_box);
}
void Body::update(){
    updateBox2D();
    updateSFML();
}
void Body::load(std::string _path,sf::IntRect _portion){
    _texture = new sf::Texture;
    _texture->loadFromFile(_path);
    _box->setTexture(_texture);
    _box->setFillColor(sf::Color::White);
    _box->setOutlineThickness(0.0f);
    if(_portion!=sf::IntRect(0,0,0,0)){
        _box->setTextureRect(_portion);
    }
}
void Body::setTexture(sf::Texture *_texture,sf::IntRect _portion){
        Body::_texture = _texture;
        _box->setTexture(_texture);
        //Removes all skeleton properties for an actual texture
        _box->setFillColor(sf::Color::White);
        _box->setOutlineThickness(0.0f);
        //Sets textureRect if given in declaration
        if(_portion!=sf::IntRect(0,0,0,0)){
            _box->setTextureRect(_portion);
        }
}
sf::RectangleShape *Body::getBox(){
    return _box;
}
b2Vec2 Body::getSize(){
    return _size;
}
Body::~Body(){
    std::cout << "Body box removed" << std::endl;
}
