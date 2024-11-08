#ifndef RESOURCES_HPP
#define RESOURCES_HPP
#include <SDL_render.h>
#include <string>
#include <unordered_map>
#include <SDL_mixer.h>

using namespace std;

class Resources {
private:
    static unordered_map<string, SDL_Texture*> imageTable;
    static unordered_map<string, Mix_Music*> musicTable;
    static unordered_map<string, Mix_Chunk*> soundTable;

public:
    static SDL_Texture* GetImage(string file);
    static void ClearImages();
    static Mix_Music* GetMusic(string file);
    static void ClearMusics();
    static Mix_Chunk* GetSound(string file);
    static void ClearSounds();
};


#endif //RESOURCES_HPP
