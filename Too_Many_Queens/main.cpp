#include <iostream>
#include <vector>
#include <cstdlib>

class Queen {
    public:
        Queen(int _x = 0, int _y = 0) {
            x = _x;
            y = _y;
        }

        bool colide(Queen const &other) {
            return (this != &other &&
                (x == other.x || y == other.y || std::abs(x - other.x) == std::abs(y - other.y)));
        }

        void forward(void) {
            y++;
        }

        int x;
        int y;
};

class Board {
    public:
        Board(int _queens) : queens(_queens) {
            for (int i = 0; i < queens.size() ; i++)
                queens[i].x = i;
        }

        std::vector<Queen> queens;
};

int main(int ac, char **av)
{

    return (0);
}
