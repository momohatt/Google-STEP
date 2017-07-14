#include <iostream>
#include <vector>

#define BLACK 1
#define WHITE -1

using namespace std;

class Grid {
    public:
        int state;

        Grid() {
            state = 0;
        }
        void set(int i)
        {
            state = i;
        }
        void flip(int i)
        {
            state *= -1;
        }
}

Grid borad[8][8];


