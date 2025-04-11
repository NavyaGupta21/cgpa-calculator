#include <bits/stdc++.h>
using namespace std;

double Mean(vector<int> marks) {
    double sum = 0;
    for (int mark : marks) {
        sum += mark;
    }
    return sum / marks.size();
}

double StdDev(vector<int> marks, double mean) {
    double sum = 0;
    for (int mark : marks) {
        sum += pow(mark - mean, 2);
    }
    return sqrt(sum / marks.size());
}

vector<pair<string, int>> calculateCGPA(vector<int> marks) {
    double mean = Mean(marks);
    double stddev = StdDev(marks, mean);
    vector<tuple<string, double, double, int>> gradeCutoffs = {
        {"O", min(mean + 1.5 * stddev, 91.0), 100, 10},
        {"A+", min(mean + 1.0 * stddev, 82.0), min(mean + 1.5 * stddev, 91.0), 9},
        {"A", min(mean + 0.5 * stddev, 73.0), min(mean + 1.0 * stddev, 82.0), 8},
        {"B+", min(mean + 0.0 * stddev, 64.0), min(mean + 0.5 * stddev, 73.0), 7},
        {"B", min(mean - 0.5 * stddev, 55.0), min(mean + 0.0 * stddev, 64.0), 6},
        {"C", min(mean - 1.0 * stddev, 46.0), min(mean - 0.5 * stddev, 55.0), 5}
    };

    double finalCutoffC = min(mean - 1.0 * stddev, 46.0);
    if (finalCutoffC < 35) {
        gradeCutoffs.push_back({"F", 0, finalCutoffC, 0});
    } else {
        gradeCutoffs.push_back({"P", 35, finalCutoffC, 4});
        gradeCutoffs.push_back({"F", 0, 35, 0});
    }

    vector<pair<string, int>> grades;
    for (int mark : marks) {
        for (auto grade : gradeCutoffs) {
            if (mark >= get<1>(grade) && mark < get<2>(grade)) {
                grades.push_back({get<0>(grade), get<3>(grade)});
                break;
            }
        }
    }
    return grades;
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    vector<int> marks(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter marks of Roll No. " << i + 1 << " out of 100: ";
        cin >> marks[i];
    }

    auto result = calculateCGPA(marks);
    cout << "Marks and Grades:\n";
    for (int i = 0; i < marks.size(); i++) {
        cout << "Roll No " << i + 1 << " Marks: " << marks[i] << " -> Grade: " << result[i].first << endl;
    }
    return 0;
}