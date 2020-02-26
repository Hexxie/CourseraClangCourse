#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date): cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
    if(cmp_ == Comparison::Equal) {
        return date == date_;
    } else if (cmp_ == Comparison::Greater) {
        return date > date_;
    } else if (cmp_ == Comparison::GreaterOrEqual) {
        return date >= date_;
    } else if (cmp_ == Comparison::Less) {
        return date < date_;
    } else if (cmp_ == Comparison::LessOrEqual) {
        return date <= date_;
    } else if (cmp_ == Comparison::NotEqual) {
        return date != date_;
    }
}

EventComparisonNode::EventComparisonNode (const Comparison& cmp, const string &value) : cmp_(cmp), event_(value) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
    if(cmp_ == Comparison::Equal) {
        return event == event_;
    } else if (cmp_ == Comparison::Greater) {
        return event > event_;
    } else if (cmp_ == Comparison::GreaterOrEqual) {
        return event >= event_;
    } else if (cmp_ == Comparison::Less) {
        return event < event_;
    } else if (cmp_ == Comparison::LessOrEqual) {
        return event <= event_;
    } else if (cmp_ == Comparison::NotEqual) {
        return event != event_;
    }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& l_op, const shared_ptr<Node> left, const shared_ptr<Node> right)
    : l_op_(l_op), left_(left), right_(right) {}


bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
    bool a = left_->Evaluate(date, event);
    bool b = right_->Evaluate(date, event);

    if(l_op_ == LogicalOperation::And) {
        return a && b;
    } else if (l_op_ == LogicalOperation::Or) {
        return a || b;
    }
}