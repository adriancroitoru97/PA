#include <bits/stdc++.h>
using namespace std;

struct Object {
    int weight;
    int price;

    Object(int _weight, int _price)
        : weight(_weight)
        , price(_price) { }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, w;
    vector<Object> objs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> w;
        for (int i = 0, weight, price; i < n; i++) {
            fin >> weight >> price;
            objs.push_back(Object(weight, price));
        }
        fin.close();
    }

    double get_result() {
        // TODO: Aflati profitul maxim care se poate obtine cu obiectele date.

        double profit = 0.;

        for (int i = 0; i < objs.size() - 1; i++) {
            for (int j = i + 1; j < objs.size(); j++) {
                if ((double)objs[i].price / objs[i].weight < (double)objs[j].price / objs[j].weight) {
                    swap(objs[i], objs[j]);
                }
            }
        }

        int i = 0;
        while (w > 0 && i < objs.size()) {
            if (w >= objs[i].weight) {
                w -= objs[i].weight;
                profit += objs[i].price;
                i++;
            } else {
                profit += ((double)(objs[i].price * w) / objs[i].weight);
                break;
            }
        }

        return profit;
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
