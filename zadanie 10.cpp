#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "Введите количество вещей: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Ошибка: введите положительное целое число." << endl;
        return 1;
    }

    //vector<int> weights(n);
    //cout << "Введите вес каждой вещи: ";
   // for (int i = 0; i < n; i++) {
       // if (!(cin >> weights[i]) || weights[i] <= 0) {
          //  cout << "Ошибка: введите положительное целое число для веса." << endl;
           // return 1;
       // }
  //  }

    vector<int> weights(n);
    for (int i = 0; i < n; ++i) {
        do
        {
            cout << "Вес вещи  " << i + 1 << ": ";
            cin >> weights[i];

            cin.clear();
            cin.sync();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (cin.fail() || weights[i] <= 0)
                cout << "Некорректные данные" << endl;
        } while (weights[i] <= 0 || cin.fail());
    }

    sort(weights.begin(), weights.end()); // Сортируем веса вещей

    int sum = 0;
    for (int weight : weights) {
        sum += weight;
    }

        int target = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        dp[0][0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= weights[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - weights[i - 1]];
                }
            }
        }

        int ans = target;
        while (!dp[n][ans]) {
            ans--;
        }

        cout << "Минимальная разница весов рюкзаков: " << sum - 2 * ans << endl;

        // Вывод разных весов с минимальной разницей
        cout << "Возможные комбинации весов: ";
        for (int i = ans; i <= target; i++) {
            if (dp[n][i]) {
                cout << i << " и " << sum - i << endl;
                break;
            }
        }
    }