#include "GamePCH.h"
#include "Game.h"

using namespace fw;

typedef float (MathOperationFunction)(float a, float b);

float Add(float a, float b)
{
    return a + b;
}

float Subtract(float a, float b)
{
    return a - b;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Testing Function Pointers
    float value1 = 10.0f;
    float value2 = 5.0f;

    MathOperationFunction* op = &Add;
    
    float result = op(value1, value2);

    op = &Subtract;

    result = op(result, value2);

    int bp = 1;




    Framework* pFramework = new Framework();
    GameCore* pGame = new Game( pFramework );
    
    pFramework->Init( 600, 600 );
    pFramework->Run( pGame );
    pFramework->Shutdown();

    delete pGame;
    delete pFramework;

    MyMemory_ValidateAllocations( true );
}
