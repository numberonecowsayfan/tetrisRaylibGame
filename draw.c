#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"




void drawBackground(int gridHeight, int gridWidth, int squarePixelSize, int gridThickness, Color gridColor){
    for (int i = 0; i < gridWidth; i++){
        DrawRectangle(i * squarePixelSize, 0, gridThickness, gridHeight * squarePixelSize, GRAY);  
    }
    for (int i = 0; i < gridHeight; i++){
        DrawRectangle(0, i * squarePixelSize, gridWidth * squarePixelSize, gridThickness, GRAY);  
    }
}

void drawSquareOnGrid(int xLocation, int yLocation, int squarePixelSize, Color squareColor){
    DrawRectangle(
        xLocation * squarePixelSize,       // x start pos
        yLocation * squarePixelSize,       // y start pos
        squarePixelSize, // x end pos
        squarePixelSize, // y end pos
        squareColor);
}

void drawTPiece(int xLocation, int yLocation, int squarePixelSize, Color squareColor){
    drawSquareOnGrid(xLocation, yLocation, squarePixelSize, RED);
    drawSquareOnGrid(xLocation - 1, yLocation, squarePixelSize, RED);
    drawSquareOnGrid(xLocation + 1, yLocation, squarePixelSize, RED);
    drawSquareOnGrid(xLocation, yLocation - 1 ,squarePixelSize, RED);
}