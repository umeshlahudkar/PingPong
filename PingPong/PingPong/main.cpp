#include "Game/PingPong.h"


const int ScreenWidth = 180;
const int ScreenHeight = 220;

int main(int argc, char* argv[])
{
    if (PingPong::GetInstance().Init(ScreenWidth, ScreenHeight)) {

        PingPong::GetInstance().Run();
    }
    return 0;
}


