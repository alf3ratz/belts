#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison &comp, const Date &date) :
        comparator(comp), date(date) {}
bool EmptyNode::Evaluate(const Date& date, const string& event) {
    return true;
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) {
    switch (comparator) {
        case Comparison::Greater : {
            return date > this->date;
        }
        case Comparison::GreaterOrEqual : {
            return date >= this->date;
        }
        case Comparison::Less : {
            return date < this->date;
        }
        case Comparison::LessOrEqual : {
            return date <= this->date;
        }
        case Comparison::Equal : {
            return date == this->date;
        }
        case Comparison::NotEqual : {
            return date != this->date;
        }
    }
}


bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
    switch (comparator) {
        case Comparison::Less : {
            return event < this->event;
        }
        case Comparison::LessOrEqual : {
            return event <= this->event;
        }
        case Comparison::Greater : {
            return event > this->event;
        }
        case Comparison::GreaterOrEqual : {
            return event >= this->event;
        }
        case Comparison::Equal : {
            return event == this->event;
        }
        case Comparison::NotEqual : {
            return event != this->event;
        }
        default: {
            throw invalid_argument("Unknown comparison :(");
        }
    }
}
EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& value) :
        comparator(cmp), event(value) {}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& operation,
                                           const shared_ptr<Node>& lhs,
                                           const shared_ptr<Node>& rhs): operation(operation){
    left_node = lhs;
    right_node = rhs;
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event){
    switch (operation) {
        case LogicalOperation::And : {
            return left_node->Evaluate(date, event) && right_node->Evaluate(date, event);
        }
        case LogicalOperation::Or : {
            return left_node->Evaluate(date, event) || right_node->Evaluate(date, event);
        }
        default: {
            throw invalid_argument("Unknown operation :(");
        }
    }
}