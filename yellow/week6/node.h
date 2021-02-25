#include <string>
#include <memory>
#include "date.h"
#include "token.h"
#pragma once

class Node{
public:
    virtual bool Evaluate(const Date& date, const string& event) = 0;

private:
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date & date, const string &event ) override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &, const Date &);

    bool Evaluate(const Date & date, const string &event) override;

private:
    const Comparison comparator;
    const Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &, const string &);

    bool Evaluate(const Date &date, const string &event) override;

private:
    const Comparison comparator;
    const string event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation&, const shared_ptr<Node>&, const shared_ptr<Node>&);

    bool Evaluate(const Date& date, const string& event) override;

private:
    const LogicalOperation operation;
    shared_ptr<Node> left_node;
    shared_ptr<Node> right_node;

};