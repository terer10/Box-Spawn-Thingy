#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include "../SOFIE/Math.h"
#include "../SOFIE/Engine/Engine.h"
#include "SF2D/Body/DynamicBody.h"
#include "SF2D/Body/Wall.h"

class Playground{
    public:
        Playground();
        virtual ~Playground();
    private:
        void processEvents();

        void update();

        void render();

        void run();

        //Sets up all Box2D things
        void setBox2D();

        //Updates all Box2D things
        void updateBox2D();

        //Sets up all SFML things
        void setSFML();

        //Updates all SFML things
        void updateSFML();

        //Draws all the boxes in the _boxes vector
        void drawBoxes();

        //Method to create a box with a set position and size
        void createBox(b2Vec2 _position, b2Vec2 _size);

        //Loads a random texture based on
        std::string randomTexture();

        //Window
        static sf::RenderWindow *_window;

        //Size of the window
        sf::Vector2u _windowSize;

        //Scale of the window
        unsigned int _scale = 1;

        //Gravity goes 10m down
        b2Vec2 _gravity = b2Vec2(0.0f,10.0f);

        //World to draw everything in
        b2World _world = b2World(_gravity);

        ///Floor box
        //SF2D::Body *_floor = new SF2D::Body(&_world,b2Vec2(0,300),b2Vec2(640,30));
        //Vector of boxes
        std::vector<SF2D::Body*> _boxes;

        //Iterator for the boxes vector
        std::vector<SF2D::Body*>::iterator _boxIterator;

        //Version of Box2D installed on the user's system
        b2Version _version;

        //Mouse position
        sf::Vector2f _mousePos;

        //Random number generator for choosing random textures for the boxes
        SOFIE::Random<float> _random = SOFIE::Random<float>(0,3);

        //All the possible image paths for the random images
        std::string _paths[3];

        //Check whether to render the blocks' bare skeletons or texture
        bool _skeletal = true;

        bool _mouseInWindow = false;

        SOFIE::Engine *_engine = new SOFIE::Engine;
        SOFIE::Conversion *_convert = new SOFIE::Conversion;

        b2FixtureDef _newDef;

        //When this integer = 5,
        int _spawnTime = 0;
};

#endif // PLAYGROUND_H
