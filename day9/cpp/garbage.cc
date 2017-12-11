#include <iostream>

using namespace std;

int main(void) {
    int group_score = 0;
    int total_score = 0;
    int garbage_count = 0;
    char c;
    while(cin >> c) {
        switch (c) {
        case '{':
            ++group_score;
            break;
        case '}':
            total_score += group_score--;
            break;
        case '<':
            while (true) {
                cin >> c;
                if (c == '!') { cin.ignore(1); continue; }
                if (c == '>') break;
                ++garbage_count;
            }
            break;
        }
    }
    cout << total_score << endl << garbage_count << endl;
}
