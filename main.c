#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "draw.h"

#define gridWidth 10
#define gridHeight 18

int blockDropTime = 0;

int blockDropTimeFunc(){
    

    blockDropTime += 1;

    if(blockDropTime > 60){
         blockDropTime = 0;
         return 1;
     }
     else{
         return 0;
    }


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

    int xVal = 4;
    int yVal = 1;

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
        drawSquareOnGrid(xVal, yVal, squarePixelSize, RED);

        drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

        // xVal += blockDropTimeFunc();

        printf("%d", blockDropTimeFunc());
        printf("\n");

        yVal += blockDropTimeFunc();

        if(IsKeyPressed(KEY_LEFT) && xVal > 0){
            xVal -= 1;
        }

        if(IsKeyPressed(KEY_RIGHT) && xVal < gridWidth - 1){
            xVal += 1;
        }

        if(yVal >= gridHeight - 1){
            printf("block hit bottom");
        }


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