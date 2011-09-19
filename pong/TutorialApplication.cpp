/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void): p1Up(false), p1Down(false), p2Up(false), p2Down(false), pastBat(false)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

void TutorialApplication::createCamera(void) {
	// Create the camera
    mCamera = mSceneMgr->createCamera("Cam");
	mCamera->setPosition(Ogre::Vector3(0, 500, 10));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	//mCamera->setNearClipDistance(5);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

void TutorialApplication::createViewports(void) {
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
		// Alter the camera aspect ratio to match the viewport
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));    
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
	//'Ball' entity
    Ogre::Entity* head = mSceneMgr->createEntity("Head", "ogrehead.mesh");
		head->setCastShadows(true);
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ball", Ogre::Vector3(0, 30, 0));
		headNode->attachObject(head);
		headNode->yaw(Ogre::Angle(250));
		mBall = headNode;

	//Paddle entities
	Ogre::Entity* paddle1 = mSceneMgr->createEntity("paddle1", "Prefab_Cube");
		paddle1->setCastShadows(true);
		Ogre::SceneNode* paddle1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("paddle1Node", Ogre::Vector3(-240, 20, 0));
			paddle1Node->attachObject(paddle1);
			paddle1Node->scale(Ogre::Vector3(0.1, 0.3, 0.9));

	Ogre::Entity* paddle2 = mSceneMgr->createEntity("paddle2", "Prefab_Cube");
		paddle2->setCastShadows(true);
		Ogre::SceneNode* paddle2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("paddle2Node", Ogre::Vector3(240, 20, 0));
			paddle2Node->attachObject(paddle2);
			paddle2Node->scale(Ogre::Vector3(0.1, 0.3, 0.9));

	//Create plane
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	   Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 500, 400, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
		Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	    entGround->setMaterialName("Examples/Rockwall");
		entGround->setCastShadows(false);
 
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
		pointLight->setType(Ogre::Light::LT_POINT);
		pointLight->setPosition(Ogre::Vector3(0, 150, 250));
		pointLight->setDiffuseColour(0.0, 0.5, 0.0);
		pointLight->setSpecularColour(0.0, 0.5, 0.0);
 
    /*Ogre::Light* directionalLight = mSceneMgr->createLight("directionalLight");
		directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
		directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
		directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
		directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 )); */
 
    Ogre::Light* spotLight = mSceneMgr->createLight("spotLight");
		spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
		spotLight->setDiffuseColour(0, 0, 1.0);
		spotLight->setSpecularColour(0, 0, 1.0);
		spotLight->setDirection(-1, -1, 0);
		spotLight->setPosition(Ogre::Vector3(300, 300, 0));
		spotLight->setSpotlightRange(Ogre::Degree(25), Ogre::Degree(40));
	Ogre::Light* spotLight2 = mSceneMgr->createLight("spotLight2");
		spotLight2->setType(Ogre::Light::LT_SPOTLIGHT);
		spotLight2->setDiffuseColour(1, 0, 0);
		spotLight2->setSpecularColour(0, 0, 1.0);
		spotLight2->setDirection(-1, -1, 0);
		spotLight2->setPosition(Ogre::Vector3(-300, 300, 0));
		spotLight2->setSpotlightRange(Ogre::Degree(25), Ogre::Degree(40));
}

bool TutorialApplication::keyPressed( const OIS::KeyEvent &arg ){
	if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up
	
	if(arg.key == OIS::KC_UP){
		p2Up = true;
	}
	else if(arg.key == OIS::KC_DOWN){
		p2Down = true;
	}

	if(arg.key == OIS::KC_W){
		p1Up = true;
	}
	else if(arg.key == OIS::KC_S){
		p1Down = true;
	}

	else if (arg.key == OIS::KC_ESCAPE)
    {
		mShutDown = true;
    }
    return true;
}

bool TutorialApplication::keyReleased( const OIS::KeyEvent &arg ){
	if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up
	
	if(arg.key == OIS::KC_UP){
		p2Up = false;
	}
	else if(arg.key == OIS::KC_DOWN){
		p2Down = false;
	}

	if(arg.key == OIS::KC_W){
		p1Up = false;
	}
	else if(arg.key == OIS::KC_S){
		p1Down = false;
	}

	else if (arg.key == OIS::KC_ESCAPE)
    {
		mShutDown = true;
    }

    return true;
}

void TutorialApplication::movePaddles(float deltaTime) {
	Ogre::Vector3 p1 = mSceneMgr->getSceneNode("paddle1Node")->getPosition();
	Ogre::Vector3 p2 = mSceneMgr->getSceneNode("paddle2Node")->getPosition();

	if(p1Up) {
		if(p1.z >= -150){
			p1.z -= 2 * deltaTime;
		}
	} 
	else if(p1Down) {
		if(p1.z <= 150){
			p1.z += 2 * deltaTime;
		}
	}
	if(p2Up){
		if(p2.z >= -150){
			p2.z -= 2 * deltaTime;
		}
	}
	else if(p2Down) {
		if(p2.z <= 150){
			p2.z += 2 * deltaTime;
		}
	}
	mSceneMgr->getSceneNode("paddle1Node")->setPosition(p1);
	mSceneMgr->getSceneNode("paddle2Node")->setPosition(p2);
}


void TutorialApplication::moveBall(float deltaTime) {
	Ogre::Vector3 currPos = mBall->getPosition();
	Ogre::Vector3 zPos = mBall->getLocalAxes().GetColumn(2) * deltaTime;
	Ogre::Quaternion currOr = mBall->getOrientation();
	
	Ogre::Vector3 newPos;
	bool insideBoundary = isBallWithinInnerBoundary(currPos);
	//std::cout << "curr: " << currPos << std::endl;
	//std::cout << "zPos: " << zPos << std::endl << std::endl;

	if(!insideBoundary){
		if(!pastBat && checkBatPresence(currPos)){
			//calculateBatRebound(currPos, currOr);
			zPos.x = zPos.x*-1;
			newPos = currPos+zPos;
		} else {
			if((currPos.x > 240 || currPos.x < -240)){
				//mSceneMgr->getSceneNode("ball")->setPosition(0, 0, 0);
				//newPos = Ogre::Vector3(0, 0, 0);
				zPos.x = zPos.x*-1;
				newPos = Ogre::Vector3(0, 30, 0);//currPos+zPos;
				pastBat = false;
			} else if(currPos.z > 190 || currPos.z < -190){
				zPos.z = zPos.z*-1;
				newPos = currPos+zPos;
				if(currPos.z > 190){
					newPos.z = 185;
				} else if(currPos.z < -190){
					newPos.z = -185;
				}
				//zPos.z = zPos.z*-1;
				//newPos = currPos+zPos;
			} else {
				newPos = currPos+zPos;
				pastBat = true;
			}
		}
	} else {
		newPos = currPos+zPos;
	}
	mBall->setDirection(zPos, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);
	mBall->setPosition(newPos);
}

bool TutorialApplication::isBallWithinInnerBoundary(const Ogre::Vector3 &pos){
	if((pos.x <= 215 && pos.x >= -215) && (pos.z <= 190 && pos.z >= -190)){
		return true;
	} else {
		return false;
	}
}

bool TutorialApplication::checkBatPresence(const Ogre::Vector3 &currPos) {
	Ogre::Vector3 paddle1 = mSceneMgr->getSceneNode("paddle1Node")->getPosition();
	Ogre::Vector3 paddle2 = mSceneMgr->getSceneNode("paddle2Node")->getPosition();

	if(currPos.x <= 0){
		if((paddle1.x - currPos.x) > -60){
			if((currPos.z > paddle1.z-45) && (currPos.z < paddle1.z+45)){
				return true;
			}
		}
	} else {
		if((paddle2.x - currPos.x) < 60){
			if((currPos.z > paddle2.z-45) && (currPos.z < paddle2.z+45)){
				return true;
			}
		}
	}

	return false;
}

void TutorialApplication::calculateBatRebound(const Ogre::Vector3 &currPos, const Ogre::Quaternion &currOr){
	
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	float deltaTime = mTimer.getMicroseconds() / 1000.0f;
	deltaTime /= 4;

	mTimer.reset();
	if(BaseApplication::frameRenderingQueued(evt)){
		movePaddles(deltaTime);
		moveBall(deltaTime);
		mSceneMgr->getLight("spotLight")->setDirection(mBall->getPosition()-mSceneMgr->getLight("spotLight")->getPosition());
		mSceneMgr->getLight("spotLight2")->setDirection(mBall->getPosition()-mSceneMgr->getLight("spotLight2")->getPosition());
		return true;
	}
	else {
		return false;
	}
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    //INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
	int main(int argc, char *argv[])
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
