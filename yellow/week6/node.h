#pragma once

class Node {
    virtual string Evaluate() const = 0;
};

class EmptyNode : public Node {

};

class DateComparisonNode : public Node {

};

class EventComparisonNode : public Node {

};

class LogicalOperationNode : public Node {

};