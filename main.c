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
        printf("block dropped");
        printf("\n");
        return 1;
     }
     else{
         
        return 0;
    }
}

int controlBlock(Point2DStruct *Point2DStruct){

    assert(Point2DStruct != NULL);
    // crashes if null pointer
        if(IsKeyPressed(KEY_LEFT) && Point2DStruct->xVal > 0){
            Point2DStruct->xVal -= 1;
        }

        if(IsKeyPressed(KEY_RIGHT) && Point2DStruct->xVal < gridWidth - 1){
            //*pXVal += 1;
            Point2DStruct->xVal += 1;
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

    // int xVal = 4;
    // int yVal = 1;

    Point2DStruct mainPiecePoint2D = {INITXSTART, INITYSTART};

    Point2DStruct *pPoint2DStruct = &mainPiecePoint2D;

    //the reason why we can't just say struct *name = &name; is because each struct is its own unique data type

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
        //printf("X Val: %d, Y Val: %d", xVal, yVal);
                    //printf("\n");
        // drawSquareOnGrid(xVal, yVal, squarePixelSize, RED);

        // drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

        // xVal += blockDropTimeFunc();

        // printf("%d", blockDropTimeFunc());
        // printf("\n");

        mainPiecePoint2D.yVal += blockDropTimeFunc();


        controlBlock(pPoint2DStruct);
        // if(IsKeyPressed(KEY_LEFT) && xVal > 0){
        //     xVal -= 1;
        // }

        // if(IsKeyPressed(KEY_RIGHT) && xVal < gridWidth - 1){
        //     xVal += 1;
        // }

        if(mainPiecePoint2D.yVal == gridHeight){
            printf("block hit bottom atY %d", gridHeight);
            printf("\n");
            gridInfo[mainPiecePoint2D.xVal][gridHeight - 1] = 1;
        }



        for (int i = 0; i < gridWidth; i++){
            for(int j = 0; j < gridHeight; j++){
                if(gridInfo[i][j] == 1){
                    drawSquareOnGrid(i, j, squarePixelSize, GREEN);


                    //xVal = INITXSTART;
                    //yVal = INITYSTART;
                    

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