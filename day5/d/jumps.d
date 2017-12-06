import std.stdio;
import std.conv;

void main(string[] args) {
    const auto day2 = args.length > 1;
    int[] jumps;

    foreach (line; stdin.byLine()) {
        jumps ~= to!int(line);
    }

    auto steps = 0;
    auto pc = 0;
    while (pc >= 0 && pc < jumps.length) {
        auto offset = jumps[pc];
        if (day2 && offset >= 3)
            jumps[pc] = offset - 1;
        else
            jumps[pc] = offset + 1;
        pc += offset;
        ++steps;
    }

    writeln(steps);
}
