#include <iostream>
#include <string>
#include <vector>
using namespace std;

class RobinHood {
public:
    explicit RobinHood(int n) {
        hash_table.resize(n * 2);
        size = n * 2;
        for (auto &elem: hash_table)
            elem = EMPTY;
    }

    void insert(string x) {
        int current_PSL = 0;
        int this_PSL = 0;
        int place = hash_(x);

        cout << "~hash: " << place << endl;

        if (hash_table[place] == EMPTY)
            hash_table[place] = make_pair(x, current_PSL);

        else {
            string temp = x;

            current_PSL++;
            place++;

            while (hash_table[place] != EMPTY) {
                if (hash_table[place].second < current_PSL) {
                    //cout << "~Swapped " << temp << " and " << hash_table[place].first << endl;
                    swap(temp, hash_table[place].first);
                    swap(current_PSL, hash_table[place].second);
                }

                current_PSL++;
                this_PSL = max(current_PSL, this_PSL);

                place++;
                if (place == size) {
                    cout << "The Table needs rehashing!" << endl;
                    exit(0);
                }
            }

            average_PSL = this_PSL / 2;
            hash_table[place] = make_pair(temp, current_PSL);
        }
    }

    int look_for(string x) {
        int place = hash_(x);

        if (hash_table[place].first == x)
            return place;

        else {
            int start_index = place + average_PSL;
            int temp = 0;
            int min_PSL = average_PSL;
            int max_PSL = 0;

            while (true) {
                if (hash_table[start_index - temp].second > min_PSL
                    && hash_table[start_index + temp].second < max_PSL) {
                    return -1;
                }

                if (start_index - temp >= 0 &&
                    hash_table[start_index - temp].first == x) {
                    return start_index - temp;
                }
                min_PSL = min(min_PSL, hash_table[start_index - temp].second);

                if (start_index + temp < size &&
                    hash_table[start_index + temp].first == x) {
                    return start_index + temp;
                }
                max_PSL = max(max_PSL, hash_table[start_index + temp].second);

                temp++;
            }
        }
    }

    bool remove(string x) {
        int place = look_for(x);
        if (place == -1)
            return false;

        hash_table[place] = EMPTY;

        while (hash_table[place + 1] != EMPTY && place + 1 != size) {
            if (hash_table[place + 1].second == 0)
                break;

            hash_table[place] = hash_table[place + 1];
            hash_table[place + 1] = EMPTY;
            hash_table[place].second--;

            place++;
        }

        return true;
    }

    void print(int arg = 0) {
        for (int i = 0; i < size; ++i) {
            if (arg == 0) {
                if (hash_table[i] != EMPTY)
                    cout << i << ".[" << hash_table[i].first << ", " << hash_table[i].second << "]  ";
            }
            else {
                cout << i << ".";

                if (hash_table[i] == EMPTY)
                    cout << "[EMPTY]  ";
                else
                    cout << "[" << hash_table[i].first << ", " << hash_table[i].second << "]  ";
            }
        }

        cout << endl;
    }
private:
    int size;

    uint64_t hash_A = 0x0f24544fd,
    hash_B = 3, hash_C = 4;

    int average_PSL = 0;

    vector<pair<string, int>> hash_table;

    pair<string, int> EMPTY = make_pair("-1", -1);

    int hash_(const string &x) {
        uint64_t h = 0;

        for (int i = 0; i < x.size(); ++i)
            h += (((x[i] ^ i) << hash_B) ^ hash_A) >> hash_C;

        return h % (uint64_t)size;
    }
};

int main() {
    int N = 10;
    cout << "Enter the number of objects" << endl;
    cin >> N;
    auto *Table = new RobinHood(N);

    cout << "you can: \n"
            "add <num> \n"
            "find <num> \n"
            "remove <num> \n"
            "print" << endl;

    string user_in;
    string x;
    int arg = 0;

    while (cin >> user_in) {
        if (user_in == "add") {
            cin >> x;

            Table->insert(x);
        }

        if (user_in == "find") {
            cin >> x;
            int place = Table->look_for(x);

            if (place != -1)
                cout << "~Element exists [" << place << "]" << endl;
            else
                cout << "~Element does not exist" << endl;
        }

        if (user_in == "remove") {
            cin >> x;
            bool result = Table->remove(x);

            if (result)
                cout << "~Element was removed" << endl;
            else
                cout << "~Element does not exist" << endl;
        }

        if (user_in == "print") {
            cin >> arg;
            Table->print(arg);
        }
    }

    return 0;
}
