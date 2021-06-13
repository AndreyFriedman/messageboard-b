#ifndef BOARD_
#define BOARD_
#include <string>
#include "Direction.hpp"
#include <vector>
#include <limits>

namespace ariel
{
    typedef unsigned int uint;

    class Point 
    {
        public:
        uint x,y; 
        Point(){
            this->x=0;
            this->y=0;
        }
        Point(uint x, uint y){
            this->x = x;
            this->y = y;
        }
        Point *take_max  (Point other) const;
        Point *take_min (Point other) const;
    };
    class Board{
        public:
            Point *min;
            Point *max;
            std::vector<std::vector<char>> *mat;
            bool start;
            Board(){
                this->start = true;
                this->mat = new std::vector<std::vector<char>>();
            }
            ~Board(){
                delete this->min;
                delete this->max;
                delete this->mat;
            }
            std::string read(uint x, uint y, Direction direction, uint size);
            void post(uint x, uint y, Direction direction, std::string str);
            void show() const;
        private:
            uint addlines(bool start, uint count, uint size) const;
            uint addtoline(uint line, bool start, uint size) const;
    };
}
#endif