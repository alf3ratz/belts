#include <iostream>
#include <ostream>
#include <sstream>
//#include "test_runner.h"
#include <vector>


using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl<< (y) << endl
#define UNIQ_ID_IMPL_2(lineno) _a_local_var_##lineno
#define UNIQ_ID_IMPL(lineno) UNIQ_ID_IMPL_2(lineno)
#define UNIQ_ID UNIQ_ID_IMPL(__LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
    //int UNIQ_ID = 5; string UNIQ_ID = "hello"; // оба определения на одной строке
}
