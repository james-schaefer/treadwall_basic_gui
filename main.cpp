#include "sciter-x.h"
#include "sciter-x-window.hpp"
#include <iostream>

// our custom interprocess communication.
#include "Shm_vars.h"

class frame: public sciter::window {
public:
  frame() : window(   SW_TITLEBAR | SW_RESIZEABLE | SW_CONTROLS | SW_MAIN 
                    | SW_ENABLE_DEBUG) {}

  sciter::value set_button(
                            sciter::value speed, 
                            sciter::value incline
                          ); 

  // map of native functions exposed to script:
  BEGIN_FUNCTION_MAP
    FUNCTION_2("set_button", set_button);
  END_FUNCTION_MAP

  // function expsed to script:
  sciter::string  nativeMessage();
};


sciter::value 
frame::set_button(
                   sciter::value speed, 
                   sciter::value incline
                 ) 
{
  std::cout << "speed is: " << speed.get(0) << std::endl
            << "incline is: " << incline.get(0) << std::endl;
  SHM::req_speed->set(speed.get(0)); 
  SHM::req_incline->set(incline.get(0)); 
}


#include "resources.cpp" // resources packaged into binary blob.

int uimain(std::function<int()> run ) {
  SHM::connect_existing_shm();

  // enable features you may need in your scripts:
  SciterSetOption(NULL, SCITER_SET_SCRIPT_RUNTIME_FEATURES,
    ALLOW_FILE_IO |
    ALLOW_SOCKET_IO | // a must for communication with Inspector
    ALLOW_EVAL |
    ALLOW_SYSINFO);

  // bind resources[] (defined in "resources.cpp") with the archive
  sciter::archive::instance().open(aux::elements_of(resources)); 

  aux::asset_ptr<frame> pwin = new frame();

  // note: this:://app URL is dedicated to the sciter::archive content associated
  //  with the application

  pwin->load( WSTR("this://app/treadwall_basic.html") );

  pwin->expand();

  return run();
}
