#include "../include/TileMap.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/GameObject.hpp"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(string file) {
    ifstream tileMapFile;
    tileMapFile.open(file);
    if (!tileMapFile.is_open()) {
        cerr << "Erro - TileMap::Load - Open" << endl;
        exit(1);
    }

    string linha;
    tileMapFile >> linha;
    stringstream ss(linha);

    string numero;
    int i = 0;
    while (getline(ss, numero, ',')) {
        if (i == 0)
            mapWidth = stoi(numero);
        else if (i == 1)
            mapHeight = stoi(numero);
        else if (i == 2)
            mapDepth = stoi(numero);
        i++;
    }

    int tileCount = 0;
    tileMatrix.reserve(mapWidth * mapHeight * mapDepth);
    while (tileMapFile >> linha) {
        stringstream ss(linha);

        while (getline(ss, numero, ',')) {
            tileMatrix.push_back(stoi(numero));
            tileCount++;
        }
    }

    if (tileCount != mapWidth * mapHeight * mapDepth) {
        cerr << "Erro - TileMap::Load - tileCount" << endl;
        exit(1);
    }

    tileMapFile.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight || z < 0 || z >= mapDepth) {
        cerr << "Erro - TileMap::At - Posição Inválida" << endl;
        exit(1);
    }
    return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}

void TileMap::RenderLayer(int layer) {
    int tileWidth = tileSet->GetTileWidth();
    int tileHeight = tileSet->GetTileHeight();

    float baseX = associated.box.X;
    float baseY = associated.box.Y;

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int index = At(x, y, layer);
            tileSet->RenderTile(index, baseX + x * tileWidth, baseY + y * tileHeight);
        }
    }
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; ++z) {
        RenderLayer(z);
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(float dt) {}

bool TileMap::Is(string type) {
    return type == "TileMap";
}
