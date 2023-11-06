#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

class PascalTriangle {
public:
    PascalTriangle(int n) {
        this->n = n;
        mat = new int *[n];
        for (int i = 0; i < n; ++i) {
            mat[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                mat[i][j] = 0;
            }
        }
        formPascal();
    }

    void formPascal() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                mat[i][j] = 1;
            }
        }
        for (int i = 2; i < n; ++i) {
            mat[i][0] = mat[i][i] = 1;
            for (int j = 1; j < n - 1; ++j) {
                mat[i][j] = mat[i - 1][j - 1] + mat[i - 1][j];
            }
        }
    }

    int **getMatrix() {
        return mat;
    }

    void output() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    void deleteTriangleMatrix() {
        for (int i = 0; i < n; ++i) {
            delete[] mat[i];
        }
        delete[] mat;

    }

private:
    int **mat;
    int n;
};

//<editor-fold desc="Ispisi">
const char topLeftCorner = '\xDA';
const char bottomLeftCorner = '\xC0';
const char topRightCorner = '\xBF';
const char bottomRightCorner = '\xD9';
const char middleLeftCorner = '\xC3';
const char middleRightCorner = '\xB4';
const char horizontalLine = '\xC4';
const char verticalLine = '\xB3';
const char intersection = '\xC5';
const char middleDown = '\xC2';
const char middleUp = '\xC1';


string printline(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += '\xC4';
    }
    return s;
}

string printspace(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += ' ';
    }
    return s;
}

void upperTableHeading(int n, bool closing = true, bool end = true) {
    cout << topLeftCorner << printline(n);
    if (closing) cout << topRightCorner;
    if (end) cout << endl;
}

void lowerTableHeading(int n, bool closing = true, bool end = true) {
    cout << bottomLeftCorner << printline(n);
    if (closing) cout << bottomRightCorner;
    if (end) cout << endl;
}

//</editor-fold>
class LozanicTriangle {
public:
    LozanicTriangle(int n) {
        this->n = n;
        this->index_ternary = -1;
        this->index_interpolate = -1;
        this->num_ternary = 0;
        this->num_interpolate = 0;
        traversable_arr = new long[(n + 1) / 2];
        mat = new long *[n];
        for (int i = 0; i < n; ++i) {
            mat[i] = new long[n];
            for (int j = 0; j < n; ++j) {
                mat[i][j] = 0;
            }
        }
        pascalTriangle = new PascalTriangle(n);
        pascalTriangle->formPascal();

        formLozanicTriangle();
    }

    void formLozanicTriangle() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                mat[i][j] = 1;
            }
        }
        for (int i = 3; i < n; ++i) {
            mat[i][0] = mat[i][i] = 1;
            for (int j = 1; j < n - 1; ++j) {
                mat[i][j] = mat[i - 1][j - 1] + mat[i - 1][j];
                if (i % 2 == 0 && j % 2 == 1) {
                    mat[i][j] -= pascalTriangle->getMatrix()[i / 2 - 1][(j - 1) / 2];
                }
            }
        }
        arr_len = (n + 1) / 2;
        for (int i = 0; i < arr_len; ++i) {
            traversable_arr[i] = mat[n - 1][i];
        }
        cout << "Formed arr: " << endl;
        for (int i = 0; i < arr_len; ++i) {
            cout << traversable_arr[i] << " ";
        }
        cout << endl;
    }

    void output() {
        int a = 100;
        cout << printline(a) << endl;
        for (int i = 0; i < n; ++i) {
            cout << printspace(a / 2 - (i + 1));
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] != 0)
                    cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << printline(a) << endl;
    }

    void deleteTriangleMatrix() {
        for (int i = 0; i < n; ++i) {
            delete[] mat[i];
        }
        delete[] mat;
        delete[] traversable_arr;
        pascalTriangle->deleteTriangleMatrix();
    }

    int interpolateSearch_num(int k) {
        long *arr = traversable_arr;
        int low = 0, high = arr_len - 1, mid, num = 0;
        //<editor-fold desc="Output">
        cout << endl << topLeftCorner << printline(12) << " INTERPOLATION " << printline(12) << topRightCorner << endl;
        //</editor-fold>
        while (low <= high && arr[low] <= k && arr[high] >= k) {
            num++;
            mid = low + (high - low) * (k - arr[low]) / (arr[high] - arr[low]);
            //<editor-fold desc="Output">
            cout << endl << middleLeftCorner << printline(13) << " Iteration " << num << ' ' << printline(13)
                 << middleRightCorner << endl;
            cout << endl;
            cout << printspace(14) << "  HIGH: " << high << " (" << arr[high] << ")" << endl;
            cout << printspace(14) << "  MID: " << mid << " (" << arr[mid] << ")" << endl;
            cout << printspace(14) << "  LOW: " << low << " (" << arr[low] << ")" << endl;
            //</editor-fold>
            if (arr[mid] == k) {
                break;
            } else if (k < arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        if (low > high || arr[low] > k || arr[high] < k)
            this->index_interpolate = -1;
        else
            this->index_interpolate = mid;
        lowerTableHeading(39);
        this->num_interpolate = num;
        return num;
    }


    int ternary_search(int key) {
        long *arr = traversable_arr;
        int low = 0, high = arr_len - 1;
        int mid1, mid2, num = 0;
        //<editor-fold desc="output">
        cout << endl << topLeftCorner << printline(13) << " TERNARY SEARCH " << printline(10) << topRightCorner
             << endl;
        //</editor-fold>
        while (low <= high) {
            num++;
            mid1 = low + (high - low) / 3;
            mid2 = high - (high - low) / 3;
            //<editor-fold desc="Output">
            cout << endl << middleLeftCorner << printline(13) << " Iteration " << num << ' ' << printline(13)
                 << middleRightCorner << endl;
            cout << endl;
            cout << printspace(14) << "  MID1: " << mid1 << " (" << arr[mid1] << ")" << endl;
            cout << printspace(14) << "  MID2: " << mid2 << " (" << arr[mid2] << ")" << endl;
            //</editor-fold>
            if (arr[mid1] == key) {
                this->index_ternary = mid1;
                break;
            } else if (arr[mid2] == key) {
                this->index_ternary = mid2;
                break;
            } else if (key < arr[mid1]) {
                high = mid1 - 1;
            } else if (key > arr[mid2]) {
                low = mid2 + 1;
            } else {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }

        if (low > high) {
            this->index_ternary = -1; // Item not found
        }

        lowerTableHeading(39); // Your console output function
        this->num_ternary = num;

        return num;
    }



    double getTimeInterpolation(int k) {
        auto start = chrono::high_resolution_clock::now();
        interpolateSearch_num(k);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        double time = static_cast<double>(duration.count());
        time = time / 1000.0;
        return round(time * 100) / 100;
    }

    double getTimeTernary(int k) {
        auto start = chrono::high_resolution_clock::now();
        ternary_search(k);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
        double time = (double) (duration.count());
        time = time / 1000.0;
        return round(time * 100) / 100;;
    }

    int getNumTernary() const {
        return num_ternary;
    }

    int getNumInterpolate() const {
        return num_interpolate;
    }

    int getIndexInterpolate() const {
        return index_interpolate;
    }

    int getIndexTernary() const {
        return index_ternary;
    }


private:
    PascalTriangle *pascalTriangle;
    long **mat;
    int n;
    long *traversable_arr;
    int arr_len;
    int index_ternary, num_ternary;
    int index_interpolate, num_interpolate;
};


void meniUnosaLoz() {
    int size = 45;
    upperTableHeading(size);
    cout << verticalLine << printspace(5) << "Enter index row of Lozanic triangle:" << printspace(4) << verticalLine << endl;
    lowerTableHeading(size);
}

void startSim() {
    cout << endl;
    int size = 35;
    upperTableHeading(size);
    cout << verticalLine << printspace(11) << "Choose option:" << printspace(10) << verticalLine << endl;
    cout << middleLeftCorner << printline(35) << middleRightCorner << endl;
    cout << verticalLine << printspace(5) << "(1) Start simulation" << printspace(10) << verticalLine << endl;
    cout << middleLeftCorner << printline(35) << middleRightCorner << endl;
    cout << verticalLine << printspace(5) << "(0) Exit simulation" << printspace(11) << verticalLine << endl;
    lowerTableHeading(size);
}

void simulation_results(int interpolation_iter, int ternary_iter, double time_iter, double time_tern) {
    const string &i_it = to_string(interpolation_iter);
    const string &t_it = to_string(ternary_iter);
    string i_s = to_string(time_iter);
    string t_s = to_string(time_tern);

    size_t decimalPos = i_s.find('.');

    if (decimalPos + 3 < i_s.length()) {
        i_s = i_s.substr(0, decimalPos + 3);
    }
    decimalPos = t_s.find('.');

    if (decimalPos + 3 < t_s.length()) {
        t_s = t_s.substr(0, decimalPos + 3);
    }

    int size = 38;
    upperTableHeading(17, false, false);
    cout << middleDown << printline(10) << middleDown << printline(10) << topRightCorner << endl;

    cout << verticalLine << printspace(5) << "RESULTS" << printspace(5) << verticalLine << " INTERPOL "
         << verticalLine << "  TERNARY " << verticalLine << endl;
    cout << middleLeftCorner << printline(17) << intersection << printline(10) << verticalLine << printline(10)
         << middleRightCorner << endl;
    cout << verticalLine << "    ITERATIONS   " << verticalLine;
    cout << printspace(4) << i_it << printspace(6 - i_it.length()) << verticalLine << printspace(4) << t_it
         << printspace(6 - t_it.length()) << verticalLine << endl;
    cout << middleLeftCorner << printline(17) << intersection << printline(10) << verticalLine << printline(10)
         << middleRightCorner << endl;
    cout << verticalLine << "    TIME (ms)    " << verticalLine;

    cout << printspace(3) << i_s << printspace(7 - i_s.length()) << verticalLine << printspace(3) << t_s
         << printspace(7 - t_s.length()) << verticalLine << endl;

    lowerTableHeading(17, false, false);
    cout << middleUp << printline(10) << middleUp << printline(10) << bottomRightCorner << endl;
}


void uspesnost_pretrage(bool ok) {
    if (ok) {
        upperTableHeading(39);
        cout << verticalLine << printspace(9) << "Search was successful." << printspace(8) << verticalLine << endl;
        lowerTableHeading(39);
    } else {
        upperTableHeading(39);
        cout << verticalLine << printspace(8) << "Search was unsuccessful." << printspace(7) << verticalLine << endl;
        lowerTableHeading(39);
    }
}

void meni() {
    while (true) {
        int choosing = -1;
        startSim();
        while(true) {
            cout << "-> ";
            cin >> choosing;
            if(choosing == 0){
                return;
            } else if(choosing == 1) break;
        }
        cout << endl;
        meniUnosaLoz();
        int n;
        while (true) {
            cout << "-> ";
            cin >> n;
            if (n > 0) break;
        }
        LozanicTriangle *triangle = new LozanicTriangle(n + 1);
        int key;
        cout << "Which key would you like to search for?" << endl << "->";
        cin >> key;
        triangle->output();

        double timeInterpolation = triangle->getTimeInterpolation(key);
        uspesnost_pretrage(triangle->getIndexInterpolate() != -1);

        double timeTernary = triangle->getTimeTernary(key);
        uspesnost_pretrage(triangle->getIndexTernary() != -1);

        int iterations_interpolate = triangle->getNumInterpolate();
        int iterations_ternary = triangle->getNumTernary();

        simulation_results(iterations_interpolate, iterations_ternary, timeInterpolation, timeTernary);

        triangle->deleteTriangleMatrix();
        delete triangle;
    }

}

int main() {
    meni();
}
