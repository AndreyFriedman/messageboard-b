#include "Board.hpp"
#include "Direction.hpp"
#include <iostream>
#include <string>
#include <cmath>

using ariel::Direction;
using namespace std;

namespace ariel
{

    Point *Point::take_max(Point other) const {
        Point *p = new Point();
        p->x = max(this->x,other.x);
        p->y = max(this->y,other.y);
        return p;
    }
    Point *Point::take_min(Point other) const{
        Point *p = new Point();
        p->x = min(this->x,other.x);
        p->y = min(this->y,other.y);
        return p;
    }
    bool inside_(Point other,Board * b){
        if (b->max == NULL || b->min == NULL){return false;}
        return ( other.y <= b->max->y &&other.x <= b->max->x  &&other.y >= b->min->y  && other.x >= b->min->x);
    }    
    bool inside_Point(uint x, uint y,Board * b){
        Point p = Point(x,y);
        return inside_(p,b);
    }
    string Board::read(uint x, uint y, Direction dir, uint size){        
        Point p = Point(x,y);
        string s;
        for (size_t i = 0; i < size; i++){
            
            s += (inside_(p,this)) ? this->mat->at(p.x - this->min->x).at(p.y-this->min->y):'_';
            p.x += (dir == Direction::Horizontal) ? 0:1;
            p.y += (dir == Direction::Horizontal) ? 1:0;
        }
        return s;
    }
    void Board::post(uint x, uint y, Direction dir,string s){   
        
        Point temp = (dir == Direction::Horizontal)? Point(x, y+s.length()-1):Point(x + s.length()-1, y);
        if(start){
            start =false;
            this->min = new Point(x, y); 
            this->max = new Point(x, y);
        }
        if(inside_Point(x, y, this) && inside_(temp, this)){
            Point t = Point(x,y);
            for(uint i = 0; i < s.length(); i++){
                this->mat->at(t.x-this->min->x).at(t.y - this->min->y) = s.at(i);
                t.x = (dir==Direction::Horizontal)? t.x:t.x + 1;
                t.y = (dir==Direction::Vertical)? t.y:t.y + 1;
            }
        }
        else {
            Point *max = temp.take_max(*(this -> max));
            Point *min = Point(x, y).take_min(*(this -> min));  
            uint addstart = (this->min->y == min->y)?0:this->min->y - min->y+1; 
            uint addend = (max->y == this->max->y)? 0:max->y - this->max->y+1;
            for (size_t i = 0; i < this->mat->size() && (addend>0 || addstart>0); i++){
                (addstart>0)?addtoline(i,true,addstart):0;
                (addend>0)?addtoline(i,false,addend):0;
            }
            uint newsize = max->y - min->y + 1;
            addstart = (this->min->x == min->x)? 0:this->min->x - min->x+1; 
            addend = (max->x == this->max->x) ? 0:max->x - this->max->x+1;
            (addstart>0)?addlines(true,addstart,newsize):0; 
            (addend>0)?addlines(false,addend,newsize):0;
            ((addend + addstart)==0 && this->mat->empty()) ? addlines(true,1,newsize):0;
            delete this->max; 
            delete this->min;
            this->max = max; 
            this->min = min;
            this->post(x,y,dir,s);
        }
    }
    uint Board::addlines(bool start, uint count, uint size) const{
        if (count == 0 || size == 0) {
            return 0;
        }
        vector<char> temp = vector<char>(size,'_');
        this->mat->insert(start?this->mat->begin():this->mat->end(),count,temp); 
        return size;
    }
    uint Board::addtoline(uint line, bool start, uint size) const{
        if (size == 0){return 0;}
        vector<vector<char>> * mat = this->mat;
        auto position = start ? mat->at(line).begin():mat->at(line).end();
        mat->at(line).insert(position,size,'_');
        return size;
    } 
    void Board::show() const{
        uint line = this->min->x;
        for (size_t i = 0; i < this->mat->size(); i++){
            cout << line <<": ";
            for (size_t j = 0; j < this->mat->at(i).size(); j++){
                cout << this->mat->at(i).at(j);
            }
            cout << endl;
            line++;
        }
        cout << endl;
    }
}