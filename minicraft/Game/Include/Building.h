#ifndef BUILDING_H
#define BUILDING_H



namespace Ogre
{
	class Entity;
}


/************************************************************************/
/*								������	                                */
/************************************************************************/

class Building
{
public:
	Building() {}
	~Building() {}

private:
	Ogre::Entity*	m_pEntity;
};


#endif