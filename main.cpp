#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RobinHood {
public:
    explicit RobinHood(int n) {
        hash_table.resize(n);
        size = n;
        for (auto &elem: hash_table)
            elem = EMPTY;
    }
    void insert(string x) {
        int PSL = 0;
        int place = hash_(x);
        if (hash_table[place] == EMPTY)
            hash_table[place] = make_pair(x, PSL);
        else {
            string temp = x;
            int iter = 0;
            while(hash_table[place] != EMPTY) {
                iter++;
                if (iter >= hash_table.size()) {
                    cout << "The Table is full!" << endl;
                    exit(0);
                }
                //cout << temp << " " << PSL << endl;
                if (PSL >= hash_table[place].second){
                    swap(temp, hash_table[place].first);
                    PSL = hash_table[place].second;
                }
                place++;
                if (place >= hash_table.size())
                    place = 0;
                PSL++;
            }
            hash_table[place] = make_pair(temp, PSL);
        }
    }
    void print() {
        for (const auto &elem: hash_table)
            cout << "[" << elem.first << ", " << elem.second << "]  ";
        cout << endl;
    }
private:
    int size;
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
    //cin >> N;
    auto *Table = new RobinHood(N);
    string user_in;
    string x;
    while (cin >> user_in) {
        if (user_in == "add") {
            cin >> x;
            Table->insert(x);
            Table->print();
        }
        if (user_in == "print") {
            Table->print();
        }
    }

    return 0;
}
