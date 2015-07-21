#ifndef WALL_H
#define WALL_H
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../SOFIE/Math/Conversion.h"
namespace SF2D{
    class Wall{
        public:
            Wall(b2World *_world,b2Vec2 _position,b2Vec2 _size);
            Wall(b2World *_world,b2Vec2 _position,b2Vec2 _size,std::string _path);
            void load(std::string _path,sf::IntRect _portion = sf::IntRect(0,0,0,0));
            void setBox2D();
            void setSFML();
            void updateSFML();
            void updateBox2D();
            void update();
            void render(sf::RenderWindow *_window);
            virtual ~Wall();
        protected:
            b2BodyDef _bodyDef;
            b2Body *_body;
            b2PolygonShape _shape;
            b2Vec2 _size;
            b2Vec2 _initialPosition;
            b2Vec2 _position;
            b2World *_world;
            sf::RectangleShape *_box = new sf::RectangleShape;
            sf::Texture *_texture;
            SOFIE::Conversion *_convert = new SOFIE::Conversion;
    };
}
#endif // WALL_H
