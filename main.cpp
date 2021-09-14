
#include "Bmp.h"
#include "Topograph.h"
const string VIEWING_APP = "eog ";

int main()
{
    string inFileName = "map_input.txt";
    string fileName1 = "map.bmp";
    string fileName2 = "map2.bmp";
    
    Topograph top(inFileName);
    Bmp bmp(top.getHeight(), top.getWidth());

    cout << "Height: " << top.getHeight() << endl;
    cout << "Width: " << top.getWidth() << endl;

    top.drawMap(bmp);

    cout << "Min: " << top.getMin() << endl;
    cout << "Max: " << top.getMax() << endl;

    bmp.write(fileName1);

    system(("eog " + fileName1 + " &").c_str());

    top.drawBestPath(bmp);

    bmp.write(fileName2);

    system(("eog " + fileName2 + " &").c_str());

    return 0;
}
