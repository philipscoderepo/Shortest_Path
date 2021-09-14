#include "Topograph.h"

///**************Part 1********************************
///Constructor.  Open a ArcGIS ASCII Grid file
///read the header to assign height and width
///resize v and read elevation data
Topograph::Topograph(string fileName){
    ifstream ifs;
    string s;
    ifs.open(fileName);
    ifs >> s ;
    if(s == "ncols"){
        ifs >> width;
    }
    ifs >> s;
    if(s == "nrows"){
        ifs >> height;
    }

    //Ignore the header of this file
    getline(ifs, s);
    getline(ifs, s);
    getline(ifs, s);
    getline(ifs, s);

    int data;
    for(int i = 0; i < height; i++){
        v.push_back(vector<int>());
        for(int j = 0; j < width; j++){
            ifs >> data;
            v[i].push_back(data);
        }
    }
}

void Topograph::findMin(){
    min = v[0][0];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(v[i][j] < min){
                min = v[i][j];
            }
        }
    }
}

void Topograph::findMax(){
    max = v[0][0];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(v[i][j] > max){
                max = v[i][j];
            }
        }
    }
}

int Topograph::mapRange(int n, int fromLow, int fromHigh, int toLow, int toHigh){
    double ratio;
    
    ratio = (fromHigh - fromLow);
    ratio = (n - fromLow) / ratio;

    return (toHigh - toLow) * ratio;
}
///**************Part 2********************************
///Advance (i,j) along its greedy path
///Choose the right side adjacent index with the lowest elevation change
///For a tie, mid has highest priority, then down, then up
///i + 1 is down, i - 1 is up
///j + 1 is forward
///Be careful if i is on the upper or lower edge
void Topograph::moveForward(int& i, int& j){
    int mid, down, up;
    bool isUpperEdge = (i == 0),
    isLowerEdge = (i == height - 1);
    
    mid = fabs(v[i][j] - v[i][j+1]);

    if(isUpperEdge){
        down = fabs(v[i][j] - v[i+1][j+1]);

        if(mid <= down){
            j++;
        }
        else{
            i++;
            j++;
        }
    }
    else if(isLowerEdge){
        up = fabs(v[i][j] - v[i-1][j+1]);
        if(mid <= up){
            j++;
        }
        else{
            i--;
            j++;
        } 
    }
    else{
        down = fabs(v[i][j] - v[i+1][j+1]);
        up = fabs(v[i][j] - v[i-1][j+1]); 
        
        if((mid <= down) && (mid <= up)){
            j++;
        }
        else if(down <= up){
            i++;
            j++;
        }
        else{
            i--;
            j++;
        }
    }
    
}


