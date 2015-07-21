#ifndef Body_H
#define Body_H
#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../SOFIE/Math.h"
namespace SF2D{
class Body{
    public:
        //Constructor that sets a size and position of the box
        Body(b2World *_world,b2Vec2 _position,b2Vec2 _size);

        //Constructor that sets a size, position and texture path to the box
        Body(b2World *_world,b2Vec2 _position,b2Vec2 _size,std::string _path);

        //Sets up the bodyDef
        void setBodyProperties(b2BodyDef _bodyDef);

        //Sets up all Box2D things
        virtual void setBox2D();

        //Sets up all SFML things
        virtual void setSFML();

        //Updates all Box2D things
        void updateBox2D();

        //Updates all SFML things
        void updateSFML();

        //Updates EVERYTHING
        void update();

        //Renders EVERYTHING
        void render(sf::RenderWindow *_window);

        //Loads texture from a path
        void load(std::string _path,sf::IntRect _portion = sf::IntRect(0,0,0,0));

        //Sets texture from a sf::Texture
        void setTexture(sf::Texture *_texture,sf::IntRect _portion = sf::IntRect(0,0,0,0));

        //Returns the rectangle
        sf::RectangleShape *getBox();

        b2Vec2 getSize();
        //Destructor
        virtual ~Body();
    protected:
        //Position to load the box at initially
        b2Vec2 _initalPosition;

        //Position of the box during the whole program
        b2Vec2 _position;

        //Size of the box
        b2Vec2 _size;

        //Pointer to a preset world to create the body in
        b2World *_world;

        //Body properties
        b2BodyDef _bodyDef;

        //Fixture properties
        b2FixtureDef _fixtureDef;

        //Body
        b2Body *_body;

        //Physical Box2D shape
        b2PolygonShape _shape;

        //Visual shape
        sf::RectangleShape *_box = new sf::RectangleShape;

        //Conversion to convert radians into degrees and vice versa
        SOFIE::Conversion _convert;

        //Texture of the box
        sf::Texture *_texture;
};
typedef std::shared_ptr<Body> BodyPointer;
}

#endif // Body_H
