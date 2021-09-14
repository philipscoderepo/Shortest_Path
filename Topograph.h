#ifndef TOPOGRAPH_H_INCLUDED
#define TOPOGRAPH_H_INCLUDED

#include "Bmp.h"

const rgb RED_PIXEL = {255,0,0};
const rgb BLUE_PIXEL = {0,0,255};

class Topograph
{
public:
    ///**************Part 1********************************
    ///Constructor.  Open a ArcGIS ASCII Grid file
    ///read the header to assign height and width
    ///resize v and read elevation data
    Topograph(string fileName);

    int getHeight(){return height;}
    int getWidth(){return width;}
    int getMin(){return min;}
    int getMax(){return max;}

    ///find min and max elevation values
    ///call mapRange to convert each elevation to grayscale
    ///set each bmp(i,j) to its grayscale value
    void drawMap(Bmp& bmp){
        findMin();
        findMax();
        int val;
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                val = mapRange(v[i][j], min, max, 0, 255);
                 
                bmp(i,j).r = val;
                bmp(i,j).g = val;
                bmp(i,j).b = val;
            }
        }
        
        
    }

    ///**************Part 2********************************
    ///Draw one greedy path
    ///call moveForward to advance (i,j)
    ///set each bmp(i,j) to color
    ///returns the total sum of the elevation change
    int drawGreedyPath(Bmp& bmp, int startingRow, rgb color){
        int i = startingRow,
        j = 0,
        currentElev,
        totalElevChange = 0;
        
        while(j < width - 1){
            bmp(i,j) = color;
            currentElev = v[i][j];
            moveForward(i,j); 
            totalElevChange += fabs(v[i][j] - currentElev);             
        }
        
        return totalElevChange;
    }

    ///call drawGreedyPath for each startingRow, color red
    ///store the index of the path with lowest elevation change
    ///call drawGreedyPath for the lowest index, color blue
    void drawBestPath(Bmp& bmp){

        int lowestElevChange = drawGreedyPath(bmp, 0, RED_PIXEL),
        currentElevChange,
        lowestIndex = 0;
        for(int i = 1; i < height; i++){
            currentElevChange = drawGreedyPath(bmp, i, RED_PIXEL);
            
            if(currentElevChange < lowestElevChange){
                lowestIndex = i;
                lowestElevChange = currentElevChange;
                
            }
        }

        cout << "Best Path Elevation Change: " << lowestElevChange << endl;
        drawGreedyPath(bmp, lowestIndex, BLUE_PIXEL);
        
    }
    ///****************************************************

private:
    ///**************Part 1********************************
    void findMin();
    void findMax();
    ///scale n from [fromLow:fromHigh] to [toLow:toHigh]
    int mapRange(int n, int fromLow, int fromHigh, int toLow, int toHigh);

    vector<vector<int>> v;
    int height;
    int width;
    int min;
    int max;

    ///**************Part 2********************************
    ///Advance (i,j) along its greedy path
    ///Choose the right side adjacent index with the lowest elevation change
    ///For a tie, mid has highest priority, then down, then up
    ///i + 1 is down, i - 1 is up
    ///j + 1 is forward
    ///Be careful if i is on the upper or lower edge
    void moveForward(int& i, int& j);
};

#endif // TOPOGRAPH_H_INCLUDED
