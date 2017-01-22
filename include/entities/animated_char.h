/**
*** :: Animated Object ::
***
***   A skeletally animated object
***   holds information about current animation time
***   Builds a new pose skeleton object on update
***
**/

#ifndef animated_char_h
#define animated_char_h

#include "cengine.h"
#include "casset.h"

#include "assets/skeleton.h"

typedef struct {
  
  vec3 position;
  vec3 scale;
  quat rotation;

  float animation_time;

  asset_hndl renderable;
  asset_hndl anim_top;
  asset_hndl anim_bot;
  asset_hndl skeleton;
  
  frame* pose;
  
} animated_char;

animated_char* animated_char_new();
void animated_char_delete(animated_char* ao);

void animated_char_load_skeleton(animated_char* ao, asset_hndl ah);

void animated_char_update(animated_char* ao, float timestep);

#endif
