#include "entities/animated_char.h"

#include "assets/animation.h"

animated_char* animated_char_new() {

  animated_char* ao = malloc(sizeof(animated_char));
  ao->position = vec3_zero();
  ao->scale = vec3_one();
  ao->rotation = quat_id();
  
  ao->renderable = asset_hndl_null();
  ao->skeleton = asset_hndl_null();

  ao->anim_top = asset_hndl_null();
  ao->anim_bot = asset_hndl_null();

  ao->animation_time = 0;
  
  ao->pose = NULL;
  
  return ao;
}

void animated_char_delete(animated_char* ao) {
  if (ao->pose) { frame_delete(ao->pose); }
  free(ao);
}

void animated_char_load_skeleton(animated_char* ao, asset_hndl ah) {
  if(ao->pose != NULL) { frame_delete(ao->pose); }
  ao->skeleton = ah;
  ao->pose = frame_copy(((skeleton*)asset_hndl_ptr(&ao->skeleton))->rest_pose);
  frame_gen_transforms(ao->pose);
}

void animated_char_update(animated_char* ao, float timestep) {
  
  ao->animation_time += timestep;
  

  animation* top = asset_hndl_ptr(&ao->anim_top);
  animation* bot = asset_hndl_ptr(&ao->anim_bot);

  if (top == NULL) { return; }
  if (bot == NULL) { return; }
  
  if (ao->pose != NULL) {
    frame_delete(ao->pose);
    ao->pose = NULL;
  }
  
  ao->pose = animation_sample(top, ao->animation_time);
  frame_gen_transforms(ao->pose);

  ao->pose = animation_sample(bot, ao->animation_time);
  frame_gen_transforms(ao->pose);

}
