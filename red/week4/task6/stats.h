
#ifndef UNTITLED9_STATS_H
#define UNTITLED9_STATS_H
#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
#include <set>

using namespace std;

class Stats {
public:
    Stats();

    void AddMethod(string_view method);

    void AddUri(string_view uri);

    const map<string_view, int> &GetMethodStats() const;

    const map<string_view, int> &GetUriStats() const;

private:
    map<string_view, int> method_to_count;
    map<string_view, int> uri_to_count;
    const set<string_view> METHODS = {"DELETE", "POST", "GET", "PUT"};
    const set<string_view> URIS = {"/", "/order", "/product", "/basket", "/help"};
};

HttpRequest ParseRequest(string_view line);

#endif //UNTITLED9_STATS_H
