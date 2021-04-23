#pragma once

class math{
    public:
    class Point{
        public:
        Point(){
            this->X = 0;
            this->Y = 0;
        };
        Point(unsigned int x, unsigned int y){
            this->X = x;
            this->Y = y;
        };
        long X;
        long Y;
    };
};
