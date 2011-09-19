/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
	virtual void createCamera(void);
	virtual void createViewports(void);
    virtual void createScene(void);
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual void movePaddles(float deltaTime);
	virtual void moveBall(float deltaTime);
	virtual bool isBallWithinInnerBoundary(const Ogre::Vector3 &pos);
	virtual bool checkBatPresence(const Ogre::Vector3 &currPos);
	virtual void calculateBatRebound(const Ogre::Vector3 &currPos, const Ogre::Quaternion &currOr);
	//virtual bool checkBatHit(const Ogre::Vector3 &pos);
	//virtual void batRebound(const Ogre::Vector3 &batPos, const Ogre::Vector3 &pos);
	//virtual void wallRebound(void);

	bool p1Up;
	bool p1Down;
	bool p2Up;
	bool p2Down;
	bool pastBat;
	Ogre::SceneNode* mBall;
	Ogre::Timer mTimer;
};

#endif // #ifndef __TutorialApplication_h_
