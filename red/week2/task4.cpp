#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include "map"

using namespace std;

class ReadingManager {
public:
    ReadingManager()
            : users(MAX_USER_COUNT_ + 1, 0),
              pages(1000, 0) {}

    void Read(int user_id, int page_count) {
        if (users[user_id] != 0){
            pages[users[user_id]]--;
            pages[page_count]++;
        } else{
            pages[0]++;
            pages[page_count]++;
        }
        users[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        if(users[user_id]==0){
            return 0;
        }else {
            if(pages[0]==1){
                return 1;
            }else {
                int num = 0;
                for (auto i = 1; i < users[user_id]; i++)
                    num += pages[i];
                return double(num) / (pages[0] - 1);
            }
        }
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;

    vector<int> users;
    vector<int> pages;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}