#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "utillities.h"

#include "Unit.h"
#include "Planet.h"


namespace
{

// primary collision-processing functions
void planetUnit(Object& planetObj,
                  Object& unitObj)
{
     Planet& planet = dynamic_cast<Planet&>(planetObj);
     Unit&  unit  = dynamic_cast<Unit&>(unitObj);

     if (planet.getColor() == unit.getColor())
     {
         if (planet.getHealth() != MAX_HEALTH)
         {
             planet.setHealth(INC);
             
         }
         else if (!planet.isMaxUpgrade())
         {
             planet.addToUpgrade();
             
         }
         else
         {
             unit.setInUse(false);
             return;
         }
             
     }
     else if (planet.getColor() == sf::Color::White)
     {
         planet.charge(unit.getColor());
         //need unit planet and for it make the dec...
     }
     else if (planet.getColor() != unit.getColor())
     {
         planet.underAttack();
     }

     unit.setActive(false);
      
}

void unitUnit(Object& unitObj1,
                 Object& unitObj2)
{
    Unit& unit1 = dynamic_cast<Unit&>(unitObj1);
    Unit& unit2 = dynamic_cast<Unit&>(unitObj2);

    if (unit1.getColor() != unit2.getColor())
    {
        unit1.setActive(false);
        unit2.setActive(false);
    }
    Music::instance().startCollideSound();
}

void unitPlanet(Object& unitObj,
                  Object& planetObj)
{
    planetUnit(planetObj, unitObj);
}


using HitFunctionPtr = void (*)(Object&, Object&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

HitMap initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(Planet  ), typeid(Unit   ))] = &planetUnit;
    phm[Key(typeid(Unit   ), typeid(Planet))] = &unitPlanet;
    phm[Key(typeid(Unit   ), typeid(Unit))] = &unitUnit;
    return phm;
}

HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

} // end namespace

void processCollision(Object& object1, Object& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
       throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}
