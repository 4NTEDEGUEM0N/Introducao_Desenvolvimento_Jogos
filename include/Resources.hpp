#ifndef RESOURCES_HPP
#define RESOURCES_HPP
#include <memory>
#include <SDL_render.h>
#include <string>
#include <unordered_map>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

class Resources {
private:
    static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
    static unordered_map<string, Mix_Music*> musicTable;
    static unordered_map<string, Mix_Chunk*> soundTable;
    static unordered_map<string, shared_ptr<TTF_Font>> fontTable;

public:
    static shared_ptr<SDL_Texture> GetImage(string file);
    static void ClearImages();
    static Mix_Music* GetMusic(string file);
    static void ClearMusics();
    static Mix_Chunk* GetSound(string file);
    static void ClearSounds();
    static shared_ptr<TTF_Font> GetFont(string file, int size);
    static void ClearFonts();
};


#endif //RESOURCES_HPP
