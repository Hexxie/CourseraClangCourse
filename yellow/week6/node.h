#pragma once

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum class LogicalOperation {
  Or,
  And
};

class Node {
    virtual function<bool(void)> Evaluate() const = 0;
};

class EmptyNode : public Node {

};

class DateComparisonNode : public Node {

};

class EventComparisonNode : public Node {

};

class LogicalOperationNode : public Node {
    LogicalOperationNode()

};