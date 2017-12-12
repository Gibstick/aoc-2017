import std.conv, std.math, std.stdio;
import std.algorithm.comparison;

// coordinate system
// http://keekerdc.com/2011/03/hexagon-grids-coordinate-systems-and-distance-calculations/
/*
   \  n  /
nw  +---+ ne
   /     \
 -+       +-
   \     /
sw  +---+ se
   /  s  \

   \ 0,+ /
-,+ *---* +,0
   /     \
- *       *-
   \     /
-,0 *---* +,-
   / 0,- \

*/

void main() {
    char[2] input;
    char _discard;

    int x = 0, y = 0, z = 0;
    auto distance = 0;
    auto max_distance = 0;
    while(scanf("%2[^,]", input.ptr) == 1) {
        getchar(); // discard comma

        // otherwise we need to fill in the null character in the literal
        string direction = to!string(input.ptr);
        switch (direction) {
        case "n":
            ++y;
            break;
        case "ne":
            ++x;
            break;
        case "se":
            ++x; --y;
            break;
        case "s":
            --y;
            break;
        case "sw":
            --x;
            break;
        case "nw":
            --x; ++y;
            break;
        default:
            assert(false);
        }
        z = -(x + y);
        distance = max(abs(x), abs(y), abs(z));
        max_distance = max(distance, max_distance);
    }
    writefln("%d, %d, %d", x, y, z);
    writeln(distance);
    writeln(max_distance);

}
