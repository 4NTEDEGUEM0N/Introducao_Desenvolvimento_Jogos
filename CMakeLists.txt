cmake_minimum_required(VERSION 3.28)
project(Introducao_Desenvolvimento_Jogos)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_compile_definitions(DEBUG)

add_executable(Introducao_Desenvolvimento_Jogos
        main.cpp
        include/Game.hpp
        src/Game.cpp
        include/StageState.hpp
        src/StageState.cpp
        include/Sprite.hpp
        src/Sprite.cpp
        include/Music.hpp
        src/Music.cpp
        include/Vec2.hpp
        src/Vec2.cpp
        include/Rect.hpp
        src/Rect.cpp
        include/Component.hpp
        include/GameObject.hpp
        src/GameObject.cpp
        include/Animation.hpp
        src/Animation.cpp
        include/SpriteRenderer.hpp
        src/SpriteRenderer.cpp
        src/Component.cpp
        include/Zombie.hpp
        src/Zombie.cpp
        include/Animator.hpp
        src/Animator.cpp
        include/TileSet.hpp
        src/TileSet.cpp
        include/TileMap.hpp
        src/TileMap.cpp
        include/Sound.hpp
        src/Sound.cpp
        include/Resources.hpp
        src/Resources.cpp
        include/InputManager.hpp
        src/InputManager.cpp
        include/Timer.hpp
        src/Timer.cpp
        include/Camera.hpp
        src/Camera.cpp
        include/Character.hpp
        include/Gun.hpp
        src/Character.cpp
        src/Gun.cpp
        include/PlayerController.hpp
        src/PlayerController.cpp
        include/Bullet.hpp
        src/Bullet.cpp
        include/Collider.hpp
        src/Collider.cpp
        include/Collision.hpp
        include/WaveSpawner.hpp
        include/Wave.hpp
        src/Wave.cpp
        src/WaveSpawner.cpp
        include/AIController.hpp
        src/AIController.cpp
        include/State.hpp
        src/State.cpp
        include/TitleState.hpp
        src/TitleState.cpp
        include/Text.hpp
        src/Text.cpp
        include/EndState.hpp
        include/GameData.hpp
        src/EndState.cpp
        src/GameData.cpp
)
target_link_libraries(Introducao_Desenvolvimento_Jogos
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_mixer::SDL2_mixer
        SDL2_ttf::SDL2_ttf
)