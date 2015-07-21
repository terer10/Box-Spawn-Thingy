#ifndef DYNAMICBODY_H
#define DYNAMICBODY_H
#include "Body.h"
#include <Box2D/Box2D.h>
class Body;
namespace SF2D{
    class DynamicBody : public SF2D::Body{
        public:
            DynamicBody(b2World *_world,b2Vec2 _position,b2Vec2 _size,bool _kinematic = false);
            DynamicBody(b2World *_world,b2Vec2 _position,b2Vec2 _size,std::string _path,bool _kinematic = false);
            void setFixtureProperties(b2FixtureDef _properties);
            void setBodyProperties(b2BodyDef _properties);
            void setBox2D();
            virtual ~DynamicBody();
        protected:
            //Fixture properties since the body is dynamic
            b2FixtureDef _fixtureDef;
            bool _isKinematic = false;
            float _meter = 32.0f;
    };
}
#endif // DYNAMICBODY_H
