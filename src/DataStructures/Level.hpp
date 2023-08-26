#pragma once
#include <vector>
#include <string>
#include <raylib.h>

#include "NibblePair.hpp"
#include "GameMode.hpp"


namespace BlatFormer
{
    class Level : public GameMode
    {
        protected:
            string LevelPath{};
            std::vector<NibblePair> LevelData;
            Vector2 StartingPosition{};

            static Texture2D OrbTexture;
            static Texture2D FinishTexture;

            
            void RenderMap(double xOffset, double yOffset, float scale = 1);

            void SetGrid(int x, int y, uint8_t state);
            uint8_t GetGrid(int x, int y);

            
        
        public:
            



            static void RenderBlock(double x, double y, uint8_t state, float scale = 1);

            Level(string filepath): LevelPath(filepath){};

            virtual void Start();
            virtual void Render();
            virtual void Update();
            
            void Save();
            void Load();

            void Clear();

            
                
    };
}