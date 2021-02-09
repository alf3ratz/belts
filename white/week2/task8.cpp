#include <iostream>
#include <vector>

using namespace std;
struct Person {
    bool is_worry;
};

int main() {
    int Q;
    vector<Person> queue;
    cin >> Q;
    string temp;
    int num,count=0;
    for (int i = 0; i < Q; ++i) {
        cin >> temp;
        if(temp!="WORRY_COUNT")
            cin>>num;
        else{
            for (const auto& x:queue) {
                if(x.is_worry)
                    count++;
            }
            cout<<count<<"\n";
            count=0;
            continue;
        }

        if (temp == "COME") {
            if (num > 0) {
                for (int j = 0; j < num; ++j)
                    queue.push_back({false});
            }else{
                num*=(-1);
                for (int j = 0; j < num; ++j)
                    queue.pop_back();
            }
        } else if (temp == "WORRY") {
            queue[num].is_worry=true;
        } else if(temp == "QUIET") {
            queue[num].is_worry=false;
        }

    }
    return 0;
}
