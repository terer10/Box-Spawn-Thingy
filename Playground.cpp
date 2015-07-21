#include "Playground.h"

sf::RenderWindow *Playground::_window = NULL;
Playground::Playground(){
    _windowSize.x = 640;
    _windowSize.y = (_windowSize.x/16)*9;
    _window = new sf::RenderWindow(sf::VideoMode(_windowSize.x * _scale,_windowSize.y * _scale,32),"Box2d/SFML Playground");
    _skeletal = false;
    _engine->setFont("res/RPGSystem.ttf");
    run();
}
std::string Playground::randomTexture(){
    std::string _path;
    std::string _paths[3];
    _paths[0] = "res/img1.png";
    _paths[1] = "res/img2.png";
    _paths[2] = "res/img3.png";
    //Rolls a random number to choose an element from the _paths array
    _random.reroll();
    _path = _paths[(int)_random.getNumber()];
    return _path;
}

void Playground::createBox(b2Vec2 _position,b2Vec2 _size){
    //Limits the amount of boxes on the screen to 10
    if(_spawnTime == 5){
        if(_boxes.size() < 180){
            SF2D::Body *_box;
            if(_skeletal){
                _box = new SF2D::DynamicBody(&_world,_position,_size);
            }else{
                _box = new SF2D::DynamicBody(&_world,_position,_size,randomTexture());
            }
            _boxes.push_back(_box);
        }
    }
}
void Playground::drawBoxes(){
     //Renders every box in the _boxes vector
    for(_boxIterator = _boxes.begin();_boxIterator != _boxes.end();){
        //Renders the current box
        (*_boxIterator)->render(_window);
        //Deletes box if it goes out of sight
        if((*_boxIterator)->getBox()->getPosition().y > (float)_window->getSize().y){
            delete (*_boxIterator);
            _boxIterator = _boxes.erase(_boxIterator);
        }else{
            //continues if in sight of the window
            _boxIterator++;
        }
    }
}

void Playground::update(){
    _mousePos = (sf::Vector2f)sf::Mouse::getPosition(*_window);
    //Creates box at the mouse
    if(_mouseInWindow){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            createBox(b2Vec2(_mousePos.x,_mousePos.y),b2Vec2(32,32));
        }
    }
    //Updates every box in the _boxes vector
    for(_boxIterator = _boxes.begin();_boxIterator != _boxes.end();_boxIterator++){
        (*_boxIterator)->update();
    }
    //Prints out the number of boxes in the vector
    std::cout << "Number of boxes: " << _boxes.size() << std::endl;
}

void Playground::render(){
    _window->clear(sf::Color::Black);
    drawBoxes();
    _window->draw(_engine->drawString("Click anywhere in the window to spawn boxes.",sf::Vector2f(5,5),20.0f,sf::Color::White));
    _window->display();
}

void Playground::processEvents(){
    sf::Event e;
    while(_window->pollEvent(e)){
        if(e.type == sf::Event::Closed){
                    for(_boxIterator = _boxes.begin();_boxIterator != _boxes.end();_boxIterator++){
        delete (*_boxIterator);
    }
            _window->close();
        }
        if(e.type == sf::Event::MouseEntered){
            _mouseInWindow = true;
        }else if(e.type == sf::Event::MouseLeft){
            _mouseInWindow = false;
        }
    }
}

void Playground::run(){
    const sf::Time UPDATE_TIME = sf::seconds(1.0f/60.0f);
    sf::Clock _clock;
    sf::Time _delta;
    std::clog << "Welcome to the Box2D/SFML Playground!" << std::endl;
    std::clog << "Box2D Version: " << _version.minor<< std::endl;
    while(_window->isOpen()){
            processEvents();
        _delta+=_clock.restart();
        if(_delta > UPDATE_TIME){
            _world.Step(1.0f/60.0f,8,3);
            update();
            if(_spawnTime < 10)
                _spawnTime++;
            else
                _spawnTime = 0;
        }
    render();
    }
}

Playground::~Playground(){
    delete _window;
}
