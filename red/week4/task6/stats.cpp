#include "stats.h"

const map<string_view, int> &Stats::GetUriStats() const {
    return uri_to_count;
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return method_to_count;
}

void Stats::AddUri(string_view uri) {
    if (URIS.count(uri) == 0) {
        uri_to_count["unknown"]++;
        return;
    }
    uri_to_count[uri]++;
}

void Stats::AddMethod(string_view method) {
    if (METHODS.count(method) == 0) {
        method_to_count["UNKNOWN"]++;
        return;
    }
    method_to_count[method]++;
}

Stats::Stats() {
    method_to_count = {{"GET",     0},
                       {"POST",    0},
                       {"PUT",     0},
                       {"DELETE",  0},
                       {"UNKNOWN", 0}};
    uri_to_count = {{"/",        0},
                    {"/order",   0},
                    {"/product", 0},
                    {"/basket",  0},
                    {"/help",    0},
                    {"unknown",  0}};
}

HttpRequest ParseRequest(string_view line) {//DELETE /product HTTP/1.1
    string_view str = line;
    vector<string_view> result;
    while (str[0] == ' ') {
        str.remove_prefix(1);
    }
    while (true) {
        size_t space = str.find(' ');
        result.push_back(str.substr(0, space));
        if (space == str.npos) {
            break;
        } else {
            str.remove_prefix(space + 1);
        }
    }

    string_view method = result[0];//.substr(1, result[0].length() - 1);
    string_view uri = result[1];//.substr(1,result[1].length()-1);
    string_view protocol = result[2];
    return {method, uri, protocol};

}
