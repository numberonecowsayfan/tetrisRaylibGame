#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "draw.h"

#define gridWidth 10
#define gridHeight 18

void blockDropTime(){
    
    int blockDropTime = 0;

    int timeNeededToDropBlock = 1000;

    //GetTime();
    blockDropTime += 1;

    printf("%d", blockDropTime);
    printf("\n");

    // if(blockDropTime <= timeNeededToDropBlock){
    //     blockDropTime += 2;
    //     printf("current block drop time: %d", blockDropTime);
    //     printf("\n");
    // }
    // if(blockDropTime > timeNeededToDropBlock){
    //     blockDropTime = 0;
    //     printf("move block down by one");
    //     printf("\n");
    // }
    
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    //const int gridWidth = 10;
    //const int gridHeight = 18;
    const int squarePixelSize = 30;
    const int gridThickness = 1;
    const Color gridColor = GRAY;

    const int screenWidth = gridWidth * squarePixelSize;
    const int screenHeight = gridHeight * squarePixelSize;

    int gridInfo[gridWidth][gridHeight];

    // int tetrisPieceGravity;
    
    for (int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){
            gridInfo[i][j] = 0;
        }
    }

    // tetris grid is 10 cells wide 24 cells tall.

    InitWindow(screenWidth, screenHeight, "Raylib Tetris Game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw

        //----------------------------------------------------------------------------------
        BeginDrawing();

        drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

        //drawTPiece(4, 4, squarePixelSize, RED);
        drawSquareOnGrid(4, 4, squarePixelSize, RED);

        drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

        blockDropTime();

        ClearBackground(BLACK);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}