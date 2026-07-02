#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "draw.h"
#include <assert.h>

#define gridWidth 10
#define gridHeight 18
#define INITXSTART 4
#define INITYSTART 1

int blockDropTime = 0;

typedef struct{
    int xVal;
    int yVal;
} Point2DStruct;

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

int controlBlock(Point2DStruct *Point2DStruct, int grid[gridWidth][gridHeight]){

    assert(Point2DStruct != NULL);
    // crashes if null pointer
        if(IsKeyPressed(KEY_LEFT) && Point2DStruct->xVal > 0 && grid[(Point2DStruct->xVal) - 1][Point2DStruct->yVal] != 1){
            Point2DStruct->xVal -= 1;
        }

        if(IsKeyPressed(KEY_RIGHT) && Point2DStruct->xVal < gridWidth - 1 && grid[(Point2DStruct->xVal) + 1][Point2DStruct->yVal] != 1){
            //*pXVal += 1;
            Point2DStruct->xVal += 1;
        }
        // dont put structs in main says grace
    
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


    int grid[gridWidth][gridHeight];
    //arrays are pointers????


    // int xVal = 4;
    // int yVal = 1;

    Point2DStruct mainPiecePoint2D = {INITXSTART, INITYSTART};

    Point2DStruct *pPoint2DStruct = &mainPiecePoint2D;

    //the reason why we can't just say struct *name = &name; is because each struct is its own unique data type

    // int tetrisPieceGravity;

    
    for (int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){
            grid[i][j] = 0;
        }
    }

    // tetris grid is 10 cells wide 24 cells tall.

    InitWindow(screenWidth, screenHeight, "Raylib Tetris Game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        BeginDrawing();

        drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

        

        if(grid[mainPiecePoint2D.xVal][mainPiecePoint2D.yVal + 1] != 1){
            mainPiecePoint2D.yVal += blockDropTimeFunc();
        }

        controlBlock(pPoint2DStruct, grid);
        

        if(mainPiecePoint2D.yVal == gridHeight){
            grid[mainPiecePoint2D.xVal][gridHeight - 1] = 1;
        }



        for (int i = 0; i < gridWidth; i++){
            for(int j = 0; j < gridHeight; j++){
                if(grid[i][j] == 1){
                    drawSquareOnGrid(i, j, squarePixelSize, GREEN);

                    }
                }
            }

        if(mainPiecePoint2D.yVal == gridHeight){
            mainPiecePoint2D.xVal = INITXSTART;
            mainPiecePoint2D.yVal = INITYSTART;
        }

        drawSquareOnGrid(mainPiecePoint2D.xVal, mainPiecePoint2D.yVal, squarePixelSize, RED);

        drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

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