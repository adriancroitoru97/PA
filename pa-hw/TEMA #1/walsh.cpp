#include <iostream>
#include <fstream>
#include <vector>

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int dim, nrOfPairs;
    std::vector<int> x, y;

    void read_input() {
        std::ifstream fin("walsh.in");
        fin >> dim >> nrOfPairs;
        for (int i = 0; i < nrOfPairs; i++) {
            int currentX, currentY;
            fin >> currentX >> currentY;
            x.push_back(currentX);
            y.push_back(currentY);
        }
        fin.close();
    }

    /* divide and conquer approach,
       recurrently goes on the matrix to the base level */
    int dacMatrix(int n, int x, int y) {
        if (n == 1) {
            return 0;
        } else {
            if (x <= n / 2) {
                if (y <= n / 2) {
                    /* 1st quadran */
                    return dacMatrix(n / 2, x, y);
                } else {
                    /* 2nd quadran */
                    return dacMatrix(n / 2, x, y - n / 2);
                }
            } else {
                if (y <= n / 2) {
                    /* 3rd quadran */
                    return dacMatrix(n / 2, x - n / 2, y);
                } else {
                    /* 4th quadran */
                    return !dacMatrix(n / 2, x - n / 2, y - n / 2);
                }
            }
        }
    }

    std::vector<int> get_result() {
        std::vector<int> results;

        for (int i = 0; i < nrOfPairs; i++) {
            results.push_back(dacMatrix(dim, x[i], y[i]));
        }

        return results;
    }

    void print_output(std::vector<int> results) {
        std::ofstream fout("walsh.out");
        for (unsigned int i = 0; i < results.size(); i++) {
            fout << results[i] << '\n';
        }
        fout.close();
    }
};

int main() {
    auto* task = new Task();
    if (!task) {
        std::cerr << "Task #1 constructor failed!\n";
        return -1;
    }

    task->solve();
    delete task;

    return 0;
}
