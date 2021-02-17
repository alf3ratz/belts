//
// Created by User1337 on 17.02.2021.
//

#ifndef UNTITLED5_QUERY_H
#define UNTITLED5_QUERY_H

#endif //UNTITLED5_QUERY_H
#pragma once
#include "string"
#include "vector"
using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q);