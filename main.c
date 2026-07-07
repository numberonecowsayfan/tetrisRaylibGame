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

typedef enum{
    CAN_MOVE_LEFT_OR_RIGHT = 0, CANT_MOVE_LEFT = 1, CANT_MOVE_RIGHT = 2
}BlockRightLeftMovement;

typedef struct{
    int xVal;
    int yVal;
} Point2DStruct;

void tBlock(Point2DStruct *Point2DStruct, int grid[gridWidth][gridHeight]){
    grid[Point2DStruct->xVal][Point2DStruct->yVal] = 2;
    grid[Point2DStruct->xVal + 1][Point2DStruct->yVal] = 2;
    grid[Point2DStruct->xVal - 1][Point2DStruct->yVal] = 2;
    grid[Point2DStruct->xVal][Point2DStruct->yVal + 1] = 2;
}

void clearCurrentBlocksOnGrid(int grid[gridWidth][gridHeight]){
    for (int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){
            if(grid[i][j] == 2){
                grid[i][j] = 0;
            }
        }
    }
}

int checkForValidBlockMovement(int grid[gridWidth][gridHeight]){
    // if 1, can't move left
    for (int i = 0; i < gridHeight; i++){
        if(grid[0][i] == 2){
            return CANT_MOVE_LEFT;
        }
    // if 2, can't move right
        else if(grid[gridWidth - 1][i] == 2){
            return CANT_MOVE_RIGHT;
        }

    }
    return CAN_MOVE_LEFT_OR_RIGHT;
}


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
            if(checkForValidBlockMovement(grid) != CANT_MOVE_LEFT){
                Point2DStruct->xVal -= 1;
            }
        }

        if(IsKeyPressed(KEY_RIGHT) && Point2DStruct->xVal < gridWidth - 1 && grid[(Point2DStruct->xVal) + 1][Point2DStruct->yVal] != 1){
            //*pXVal += 1;
            if(checkForValidBlockMovement(grid) != CANT_MOVE_RIGHT){
            Point2DStruct->xVal += 1;
            }
        }
        // dont put structs in main says grace
}


void drawCurrentBlocksOnGrid(int grid[gridWidth][gridHeight]){
    for (int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){
            if(grid[i][j] == 1){
                drawSquareOnGrid(i, j, squarePixelSize, GREEN);
            }
            if(grid[i][j] == 2){
                drawSquareOnGrid(i, j, squarePixelSize, RED);
            }
        }
    }

}

void resetBlockToTop(Point2DStruct *Point2DStruct){
    Point2DStruct->xVal = INITXSTART;
    Point2DStruct->yVal = INITYSTART;
}

void placeActiveBlocks(int grid[gridWidth][gridHeight]){
    
    for(int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){
            if(grid[i][j] == 2){
                grid[i][j] = 1;
            }
        }
    }

}

int checkForValidBlock(int grid[gridWidth][gridHeight]){
    // if returns 1 place the block
    for (int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){

            if(grid[i][j] == 2){
                
                drawSquareOnGrid(i, j, squarePixelSize, GREEN);

                if(grid[i][j + 1] == 1) {
                    return 1;

                }
            }
        }
    }
    return 0;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    const int gridThickness = 1;
    const Color gridColor = GRAY;

    const int screenWidth = gridWidth * squarePixelSize;
    const int screenHeight = gridHeight * squarePixelSize;


    int grid[gridWidth][gridHeight];
    //arrays are pointers????


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

    SetTargetFPS(260);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        BeginDrawing();

        tBlock(pPoint2DStruct, grid);

        controlBlock(pPoint2DStruct, grid);




        mainPiecePoint2D.yVal += blockDropTimeFunc();
        


        drawCurrentBlocksOnGrid(grid);

        drawBackground(gridHeight, gridWidth, squarePixelSize, gridThickness, gridColor);

        clearCurrentBlocksOnGrid(grid);




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