#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

#include <irrlicht.h>

#include "EventReceiver.hh"
#include "ProceduralTexture.hh"

#include "Galaxy.hh"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(){
  EventReceiver receiver;
  IrrlichtDevice* device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640,480), 16,
        		     false, true, false, &receiver);
  if (!device){
    return 1;
  }

  device->setWindowCaption(L"Hello World! - Rewriting test");

  auto driver = device->getVideoDriver();
  auto smgr = device->getSceneManager();
  auto guienv = device->getGUIEnvironment();

  auto text = guienv->addStaticText(L"",
                                    rect<s32>(10,10,260,22), true);

  // Set the ambient light
  smgr->setAmbientLight({0.1,0.1,0.1});

  auto camera = smgr->addCameraSceneNodeFPS(NULL, 100, 0.01);
  camera->setPosition({0,0,-10});
  camera->setTarget({0,0,0});

  // Draw an array of spheres
  Galaxy gal;
  gal.AddSphere({{1, 0,0},{0,0.25,0}});
  gal.AddSphere({{-1,0,0},{0,-0.25,0}});

  std::vector<IMeshSceneNode*> spheres;
  for(auto sp : gal.GetState().contents){
    auto sphere_node = smgr->addSphereSceneNode(0.5);
    if(sphere_node){
      sphere_node->setPosition(core::vector3df(sp.location.X(), sp.location.Y(), sp.location.Z()));
      sphere_node->setMaterialTexture(0, create_solid_texture(driver, 255, 0, 0));
    }
    spheres.push_back(sphere_node);
  }

  // Add a light source
  scene::ILightSceneNode* light = smgr->addLightSceneNode(0, {25,25,50}, {1,1,1}, 100);

  u32 prev_time = device->getTimer()->getTime();

  while(device->run()){
    // Find dT
    auto now = device->getTimer()->getTime();
    double dT = (now - prev_time) / 1000.0;
    prev_time = now;

    if(!device->isWindowActive()){
      device->yield();
      continue;
    }


    if(dT>0){
      gal.Step(dT);
      for(unsigned int i=0; i<spheres.size(); i++){
        auto loc = gal.GetState().contents[i].location;
        spheres[i]->setPosition(core::vector3df(loc.X(), loc.Y(), loc.Z()));
      }
    }

    // Adjust the FPS counter
    std::wstringstream ss;
    ss << "FPS: " << driver->getFPS()
       << " Mouse: (" << receiver.mouse().x << "," << receiver.mouse().y << ")"
       << " Mouse: (" << device->getCursorControl()->getRelativePosition().X << ","
       << device->getCursorControl()->getRelativePosition().Y << ")";
    auto wstring = ss.str();
    text->setText(wstring.c_str());

    // Draw everything
    driver->beginScene(true, true, SColor(255,100,101,140));
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
  }

  device->drop();
  return 0;
}
