#include "Scene.h"

SceneName Title_Update(Context& ctx);
SceneName Setting_Update(Context& ctx);
SceneName Game_Update(Context& ctx);
SceneName Tutorial_Update(Context& ctx);

SceneFn ToSceneFn(SceneName scene){
    switch (scene){
    case SceneName::Title:    return &Title_Update;
    case SceneName::Setting:  return &Setting_Update;
    case SceneName::Game:     return &Game_Update;
    case SceneName::Tutorial: return &Tutorial_Update;
    default:                  return nullptr;
    }
}