

#include "SpriteSheet.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "/PingPong/PingPong/Utils/Utils.h"




SpriteSheet::SpriteSheet()
{

}

bool SpriteSheet::Load(const std::string& name)
{
    bool loadedImage = mBMPImage.Load(name + ".bmp");
    bool loadedSpriteSections = LoadSpriteSections(name + ".txt");

    return loadedImage && loadedSpriteSections;
}

Sprite SpriteSheet::GetSprite(const std::string& spriteName) const
{
    size_t length = mSections.size();

    for (size_t i = 0; i < length; ++i)
    {
        if (StringCompare(mSections[i].key, spriteName))
        {
            return mSections[i].sprite;
        }
    }

    return Sprite();
}

std::vector<std::string> SpriteSheet::SpriteNames() const
{
    std::vector<std::string> spriteNames;

    for (const auto& section : mSections)
    {
        spriteNames.push_back(section.key);
    }

    return spriteNames;
}

bool SpriteSheet::LoadSpriteSections(const std::string& path)
{
    std::ifstream file(path);

    if (file.is_open()) {
        std::string line;
        BMPImageSection section;
        while (std::getline(file, line)) {
            if (line.find(":key") != std::string::npos) {
                section.key = line.substr(5); // Get the key value after ":key "
            }
            else if (line.find(":xPos") != std::string::npos) {
                std::istringstream iss(line.substr(6)); // Get the xPos value after ":xPos "
                iss >> section.sprite.xPos;
            }
            else if (line.find(":yPos") != std::string::npos) {
                std::istringstream iss(line.substr(6)); // Get the yPos value after ":yPos "
                iss >> section.sprite.yPos;
            }
            else if (line.find(":width") != std::string::npos) {
                std::istringstream iss(line.substr(7)); // Get the width value after ":width "
                iss >> section.sprite.width;
            }
            else if (line.find(":height") != std::string::npos) {
                std::istringstream iss(line.substr(8)); // Get the height value after ":height "
                iss >> section.sprite.height;
                // Push the completed section into the vector and reset for the next section
                mSections.push_back(section);
                section = BMPImageSection();
            }
        }
        file.close();
        return true;
    }
    return false;
}