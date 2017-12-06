#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <cstdlib> // abs
#include <cstdio>

using std::map;
using std::pair;
using std::make_pair;
using std::stoi;
using std::abs;
using std::cout;
using std::tie;

std::pair<int, int> operator +(const std::pair<int, int> x, const std::pair<int, int> y) {
    return std::make_pair(x.first + y.first, x.second + y.second);
}

enum class Direction {UP = 0, LEFT, DOWN, RIGHT};

const char* direction_string(Direction dir) {
    switch (dir) {
    case Direction::UP:
        return "UP";
    case Direction::LEFT:
        return "LEFT";
    case Direction::DOWN:
        return "DOWN";
    case Direction::RIGHT:
        return "RIGHT";
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Arguments: MODE TARGET\n");
        exit(0);
    }
    int target = stoi(argv[2]);
    bool do_sum;
    if (std::string(argv[1]) == std::string("sum")) {
        do_sum = true;
    } else {
        do_sum = false;
    }

    map<pair<int, int>, int> spiral;
    map<pair<int, int>, int> spiral_sum;

    const std::array<pair<int, int>,8> sum_location_offsets{
        make_pair(1, 0),
        make_pair(1, 1),
        make_pair(0, 1),
        make_pair(-1, 1),
        make_pair(-1, 0),
        make_pair(-1, -1),
        make_pair(0, -1),
        make_pair(1, -1)
    };


    auto location = make_pair(0, 0);
    spiral[location] = 1;
    spiral_sum[location] = 1;
    int cur = 2;
    Direction direction = Direction::RIGHT;

    auto condition = [&](auto location) {
        if (do_sum)
            return spiral_sum[location] <= target;
        else
            return spiral[location] < target;
    };

    while (condition(location)) {
        // 1. if it's a normal corner, rotate
        // 2. move
        // 3. if it's a bottom-right corner, rotate
        // 4. place
        int x, y;
        tie(x, y) = location;
        const bool corner = (abs(x) == abs(y));

        //printf("val: %d\n", cur);
        //printf("loc: %d, %d\n", x, y);
        //printf("dir: %s\n", direction_string(direction));

        Direction move_direction = direction;
        if (corner && direction != Direction::RIGHT) {
            move_direction = Direction((static_cast<int>(direction) + 1) % 4);
            //printf("ROTATING CCW\n");
        }

        // determine new location
        switch (move_direction) {
        case Direction::RIGHT:
            location = make_pair(x + 1, y);
            break;
        case Direction::UP:
            location = make_pair(x, y + 1);
            break;
        case Direction::LEFT:
            location = make_pair(x - 1, y);
            break;
        case Direction::DOWN:
            location = make_pair(x, y - 1);
            break;
        }

        // special case for bottom right corner
        if (corner && direction == Direction::RIGHT) {
            direction = Direction::UP;
            //printf("BOTTOM RIGHT CORNER CASE\n");
        } else {
            direction = move_direction;
        }

        // place at current location

        if (do_sum) {
            int sum = 0;
            for (const auto offset: sum_location_offsets) {
                const auto test_location = location + offset;
                sum += spiral_sum[test_location];
            }
            spiral_sum[location] = sum;
        } else {
            spiral[location] = cur++;
        }

        //printf("\n");
    }

    if (do_sum) {
        printf("Sum:      %d\n", spiral_sum[location]);
    } else {
        printf("Location: (%d, %d)\n", location.first, location.second);
        printf("Distance: %d\n", abs(location.first) + abs(location.second));
    }

}
