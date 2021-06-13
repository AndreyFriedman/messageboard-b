#include "Board.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace ariel;

void showmatrix(vector<vector<char>> *mat){
    char temp;
    uint size1 =mat->size();
    uint size2;
    for (uint i = 0; i < mat->size(); i++){
        size2 = mat->at(i).size();
        for (uint j = 0; j < mat->at(i).size(); j++){
            temp = mat->at(i).at(j);
            cout << mat->at(i).at(j) << " ";
        }
        cout << endl;
    }
    
}

void addline_start(vector<vector<char>> *mat, uint size){
    vector<char> temp(size, '_');
    mat->insert(mat->begin( ),1,temp);
}
void addline_end(vector<vector<char>> *mat, uint size){
    vector<char> temp(size, '_');
    mat->insert(mat->end(),1,temp);
}
void inseret_at(uint x, uint y,vector<vector<char>> *mat ,const char value){
    mat->at(x).at(y) = value;
}
int main(int argc, char const *argv[]){
    Board b;
    b.post(0,0,Direction::Horizontal,"abc");
    b.show();
    Point temp = Point(0,2);
    cout << "The point: " << b.max->x << " "<< b.max->y << endl;
    return 0;
}
