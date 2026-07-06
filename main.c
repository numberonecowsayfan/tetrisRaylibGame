#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "draw.h"
#include <assert.h>

#define gridWidth 10
#define gridHeight 18
#define INITXSTART 4
#define INITYSTART 1
#define squarePixelSize 30

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

void controlBlock(Point2DStruct *Point2DStruct, int grid[gridWidth][gridHeight]){

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

// void placeBlock(Point2DStruct *Point2DStruct, int grid[gridWidth][gridHeight]){

//     for (int i = 0; i < gridWidth; i++){
//             for(int j = 0; j < gridHeight; j++){
//                 if(grid[i][j] == 1){
//                     drawSquareOnGrid(i, j, squarePixelSize, GREEN);

//                     }
//                 }
//             }
//     if(Point2DStruct->yVal == gridHeight){
//             Point2DStruct->xVal = INITXSTART;
//             Point2DStruct->yVal = INITYSTART;
//             // make this function just place a block and put control block back at top, have logic for when
//             // to place block and reset be separate
//     }
// }

void drawCurrentBlocksOnGrid(int grid[gridWidth][gridHeight]){
    for (int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){
            if(grid[i][j] == 1){
                drawSquareOnGrid(i, j, squarePixelSize, GREEN);
            }
        }
    }

}

void resetBlockToTop(Point2DStruct *Point2DStruct){
    Point2DStruct->xVal = INITXSTART;
    Point2DStruct->yVal = INITYSTART;
}

void blockPlacement(int xVal, int yVal, int grid[gridWidth][gridHeight]){
    grid[xVal][yVal] = 1;
}

int checkForValidBlockPlacement(int xVal, int yVal, int grid[gridWidth][gridHeight]){
    if(yVal == gridHeight - 1){
        return 1;
    }
    else if(grid[xVal][(yVal) - 1] == 1){
        return 2;
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
    // const int squarePixelSize = 30;
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

    blockPlacement(1, 1, grid);
    grid[2][1] = 1;

    if(grid[2][1] == 1){
        printf("2 1 has a block");
        printf("\n");
    }
    // tetris grid is 10 cells wide 24 cells tall.

    InitWindow(screenWidth, screenHeight, "Raylib Tetris Game");

    SetTargetFPS(260);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        BeginDrawing();

        drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

        

        if (checkForValidBlockPlacement(mainPiecePoint2D.xVal, mainPiecePoint2D.yVal, grid) == 0){
            mainPiecePoint2D.yVal += blockDropTimeFunc();
        }

        controlBlock(pPoint2DStruct, grid);
        

        



        // for (int i = 0; i < gridWidth; i++){
        //     for(int j = 0; j < gridHeight; j++){
        //         if(grid[i][j] == 1){
        //             drawSquareOnGrid(i, j, squarePixelSize, GREEN);

        //             }
        //         }
        //     }
        
        

        if(checkForValidBlockPlacement(mainPiecePoint2D.xVal, mainPiecePoint2D.yVal, grid) == 1){
            // printf("valid placement");
            // printf("\n");
            blockPlacement(mainPiecePoint2D.xVal, mainPiecePoint2D.yVal, grid);
            resetBlockToTop(pPoint2DStruct);
        }
        else if(checkForValidBlockPlacement(mainPiecePoint2D.xVal, mainPiecePoint2D.yVal, grid) == 2){
            blockPlacement(mainPiecePoint2D.xVal, mainPiecePoint2D.yVal - 2, grid);
            resetBlockToTop(pPoint2DStruct);
        }

        

        drawSquareOnGrid(mainPiecePoint2D.xVal, mainPiecePoint2D.yVal, squarePixelSize, RED);

        drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

        drawCurrentBlocksOnGrid(grid);

        
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