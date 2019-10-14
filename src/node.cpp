#include "node.h"
#include <exception>

bool EmptyNode::Evaluate(const Date & date, const std::string & event)
{
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison cmp, const Date & date)
                                       : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date & date, const std::string & event)
{
    if (cmp_ == Comparison::Less)
        return date < date_;
    else if (cmp_ == Comparison::LessOrEqual)
        return date <= date_;
    else if (cmp_ == Comparison::Greater)
        return date > date_;
    else if (cmp_ == Comparison::GreaterOrEqual)
        return date >= date_;
    else if (cmp_ == Comparison::Equal)
        return date == date_;
    else if (cmp_ == Comparison::NotEqual)
        return date != date_;
    else 
        throw std::runtime_error("Bad comparision in DateComparisonNode");
}


EventComparisonNode::EventComparisonNode(const Comparison cmp, const std::string & event)
                                         : cmp_(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date & date, const std::string & event)
{
    if (cmp_ == Comparison::Less)
        return event < event_;
    else if (cmp_ == Comparison::LessOrEqual)
         return event <= event_;
    else if (cmp_ == Comparison::Greater)
        return event > event_;
    else if (cmp_ == Comparison::GreaterOrEqual)
        return event >= event_;
    else if (cmp_ == Comparison::Equal)
        return event == event_;
    else if (cmp_ == Comparison::NotEqual)
        return event != event_;
    else 
        throw std::runtime_error("Bad comparision in EventComparisonNode");
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation lo, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
                                           : logical_operation_(lo), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date & date, const std::string & event)
{
    if (logical_operation_ == LogicalOperation::Or)
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    else
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
}














