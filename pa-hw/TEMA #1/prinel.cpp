#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int N, K;
    std::vector<int> target, p;

    void read_input() {
        std::ifstream fin("prinel.in");

        fin >> N >> K;
        for (int i = 0; i < N; i++) {
            int temp;
            fin >> temp;
            target.push_back(temp);
        }
        for (int i = 0; i < N; i++) {
            int temp;
            fin >> temp;
            p.push_back(temp);
        }

        fin.close();
    }

    /*
     * Function used to calculate the cost of all operations.
     */
    int get_all_operations_cost(std::vector<int> weights) {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum += weights[target[i]];
        }
        return sum;
    }

    /*
     * Gets all divisors of an integer and return a vector of them.
     */
    std::vector<int> getDivisors(int n) {
        std::vector<int> v;
        int i;
        for (i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                v.push_back(n / i);
                v.push_back(i);
            }
        }

        i--;
        if (i * i == n) {
            v.pop_back();
        }

        return v;
    }

    /*
     * Bottom-up approach to calculate all costs from 1 to `target`.
     * The cost for 1 is always going to be 0. The rest of the costs are
     * calculated by finding the minium between the current cost for
     * that number and the minimum cost required to find the current number + 1
     */
    std::vector<int> getWeights(int target) {
        std::vector<int> weights(target + 1, INT32_MAX);

        weights[1] = 0;
        for (int i = 1; i <= target; i++) {
            std::vector<int> divisorsOfI = getDivisors(i);
            for (unsigned int j = 0; j < divisorsOfI.size(); j++) {
                if (i + divisorsOfI[j] <= target &&
                    weights[i + divisorsOfI[j]] > weights[i] + 1) {
                    weights[i + divisorsOfI[j]] = weights[i] + 1;
                }
            }
        }

        return weights;
    }

    /*
     * Returns the sum of all elements in a vector.
     */
    int sum_vector(std::vector<int> weights) {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum += weights[i];
        }

        return sum;
    }

    /*
     * Knapsack classic problem. Found out, based on the restriction given
     * that the maximum possible capacity would be
     * 1000 (maximum number of objects) * 20 (maximum cost for a number
     * between 1 and 100000) = 20000, so I improved the complexity by choosing
     * the minimum between this number and the given K, which can go uselessly up
     * to 1000000.
     */
	int rucsac(std::vector<int> weights) {
        int maxTotalCapacity = std::min(K, 20000);
		std::vector<std::vector<int>>
					dp(N + 1, std::vector<int>(maxTotalCapacity + 1, 0));

		for (int cap = 0; cap <= maxTotalCapacity; ++cap) {
			dp[0][cap] = 0;
		}

		for (int i = 1; i <= N; ++i) {
			for (int cap = 0; cap <= maxTotalCapacity; ++cap) {
				dp[i][cap] = dp[i - 1][cap];

				if (cap - weights[target[i - 1]] >= 0) {
					int sol_aux = dp[i - 1][cap - weights[target[i - 1]]] + p[i - 1];

					dp[i][cap] = std::max(dp[i][cap], sol_aux);
				}
			}
		}

		return dp[N][maxTotalCapacity];
	}

    int get_result() {
        int result = 0;

        /* the weighs are calculated from 1 to maximum
         * element of the target list
         */
        std::vector<int> weights =
            getWeights(*std::max_element(target.begin(), target.end()));

        /* all operations can be done, the result is maximum */
        if (get_all_operations_cost(weights) <= K) {
            return sum_vector(p);
        }

        result = rucsac(weights);

        return result;
    }

    void print_output(int result) {
        std::ofstream fout("prinel.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new Task();
    if (!task) {
        std::cerr << "Task #3 constructor failed!\n";
        return -1;
    }

    task->solve();
    delete task;

    return 0;
}
