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
                    cout << "~Swapped " << temp << " and " << hash_table[place].first << endl;
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

    void look_for(string x) {
        int place = hash_(x);

        if (hash_table[place].first == x)
            cout << "~Element exists [" << place << "]" << endl;

        else {
            int start_index = place + average_PSL;
            int temp = 0;
            int min_PSL = average_PSL;
            int max_PSL = 0;

            while (true) {
                if (hash_table[start_index - temp].second > min_PSL
                    && hash_table[start_index + temp].second < max_PSL) {
                    cout << "~Element does not exist" << endl;
                    return;
                }

                if (start_index - temp >= 0 &&
                    hash_table[start_index - temp].first == x) {
                    cout << "~Element exists [" << start_index - temp << "]" << endl;
                    return;
                }
                min_PSL = min(min_PSL, hash_table[start_index - temp].second);

                if (start_index + temp < size &&
                    hash_table[start_index + temp].first == x) {
                    cout << "~Element exists [" << start_index + temp << "]" << endl;
                    return;
                }
                max_PSL = max(max_PSL, hash_table[start_index + temp].second);

                temp++;
            }
        }
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            cout << i << ".";

            if (hash_table[i] == EMPTY)
                cout << "[EMPTY]  ";

            else
                cout << "[" << hash_table[i].first << ", " << hash_table[i].second << "]  ";
        }

        cout << endl;
    }
private:
    int size;
    int average_PSL = 0;

    vector<pair<string, int>> hash_table;

    pair<string, int> EMPTY = make_pair("-1", -1);

    int hash_(const string &x) {
        uint64_t h = 0;

        for (int i = 0; i < x.size(); ++i)
            h += (x[i] * i) ^ 0x0f24544fd;

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
            "print" << endl;

    string user_in;
    string x;
    while (cin >> user_in) {
        if (user_in == "add") {
            cin >> x;
            Table->insert(x);
        }

        if (user_in == "find") {
            cin >> x;
            Table->look_for(x);
        }

        if (user_in == "print") {
            Table->print();
        }
    }

    return 0;
}
