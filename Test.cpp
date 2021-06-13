#include "doctest.h"
#include "Board.hpp"
#include "Direction.hpp"
using namespace ariel;

TEST_CASE("crossing")
{
    Board * b = new Board();
    b->post(5,5,Direction::Vertical,"abcd");
    b->post(4,6,Direction::Horizontal,"efg");
    CHECK(b->read(6,5,Direction::Horizontal,1).compare("f")==0);
    CHECK(b->read(6,6,Direction::Horizontal,1).compare("g")==0);
    b->post(4,5,Direction::Vertical,"hij");
    CHECK(b->read(4,6,Direction::Vertical,1).compare("i")==0);
    CHECK(b->read(4,7,Direction::Vertical,1).compare("g")==0);
    b->post(3,4,Direction::Horizontal,"klm");
    CHECK(b->read(3,4,Direction::Horizontal,3).compare("klm")==0);
    b->post(3,9,Direction::Horizontal,"nop");
    CHECK(b->read(3,9,Direction::Horizontal,3).compare("nop")==0);
    b->post(3,5,Direction::Vertical,"qrs");
    CHECK(b->read(3,9,Direction::Vertical,3).compare("qrs")==0);
    b->post(4,1,Direction::Vertical,"tuv");
    CHECK(b->read(4,1,Direction::Vertical,3).compare("tuv")==0);
    b->post(3,6,Direction::Horizontal,"hello");
    CHECK(b->read(3,6,Direction::Horizontal,5).compare("hello")==0);
    b->post(4,1,Direction::Vertical,"hello");
    CHECK(b->read(4,1,Direction::Vertical,5).compare("hello")==0);
}
TEST_CASE("Mod writing")
{
    Board b;
    b.post(4,1,Direction::Vertical,"hello");
    CHECK(b.read(4,1,Direction::Vertical,5).compare("hello")==0);
    CHECK(b.read(5,1,Direction::Vertical,5).compare("_____")==0);
    CHECK(b.read(4,1,Direction::Horizontal,5).compare("h____")==0);
    CHECK(b.read(4,2,Direction::Horizontal,5).compare("e____")==0);
    CHECK(b.read(4,3,Direction::Horizontal,5).compare("l____")==0);
    CHECK(b.read(4,4,Direction::Horizontal,5).compare("l____")==0);
    CHECK(b.read(4,5,Direction::Horizontal,5).compare("o____")==0);
    CHECK(b.read(4,2,Direction::Vertical,5).compare("_____")==0);
    CHECK(b.read(4,0,Direction::Vertical,5).compare("_____")==0);
    CHECK(b.read(3,1,Direction::Horizontal,5).compare("_h___")==0);
    CHECK(b.read(3,2,Direction::Horizontal,5).compare("_e___")==0);
    CHECK(b.read(3,3,Direction::Horizontal,5).compare("_l___")==0);
    CHECK(b.read(3,4,Direction::Horizontal,5).compare("_l___")==0);
    CHECK(b.read(3,5,Direction::Horizontal,5).compare("_o___")==0);
    CHECK(b.read(2,1,Direction::Horizontal,5).compare("__h__")==0);
    CHECK(b.read(2,2,Direction::Horizontal,5).compare("__e__")==0);
    CHECK(b.read(2,3,Direction::Horizontal,5).compare("__l__")==0);
    CHECK(b.read(2,4,Direction::Horizontal,5).compare("__l__")==0);
    CHECK(b.read(2,5,Direction::Horizontal,5).compare("__o__")==0);
}


