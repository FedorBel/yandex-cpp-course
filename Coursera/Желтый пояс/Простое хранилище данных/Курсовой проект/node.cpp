#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison & cmp,
	const Date & date) : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date & date, const string & event) const
{
	if (cmp_ == Comparison::Equal)
	{
		return date == date_;
	}
	else if (cmp_ == Comparison::Greater)
	{
		return date > date_;
	}
	else if (cmp_ == Comparison::GreaterOrEqual)
	{
		return date >= date_;
	}
	else if (cmp_ == Comparison::Less)
	{
		return date < date_;
	}
	else if (cmp_ == Comparison::LessOrEqual)
	{
		return date <= date_;
	}
	else if (cmp_ == Comparison::NotEqual)
	{
		return date != date_;
	}
}

EventComparisonNode::EventComparisonNode(const Comparison & cmp,
	const string & value) : cmp_(cmp), value_(value) {}

bool EventComparisonNode::Evaluate(const Date & date, const string & event) const
{
	if (cmp_ == Comparison::Equal)
	{
		return event == value_;
	}
	else if (cmp_ == Comparison::Greater)
	{
		return event > value_;
	}
	else if (cmp_ == Comparison::GreaterOrEqual)
	{
		return event >= value_;
	}
	else if (cmp_ == Comparison::Less)
	{
		return event < value_;
	}
	else if (cmp_ == Comparison::LessOrEqual)
	{
		return event <= value_;
	}
	else if (cmp_ == Comparison::NotEqual)
	{
		return event != value_;
	}
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation & logical_operation,
	const shared_ptr<Node>& left, const shared_ptr<Node>& parse_expression) 
	: logical_operation_(logical_operation), left_(left), parse_expression_(parse_expression) {}

bool LogicalOperationNode::Evaluate(const Date & date, const string & event) const
{
	if (logical_operation_ == LogicalOperation::And)
	{
		return left_->Evaluate(date, event) && parse_expression_->Evaluate(date, event);
	}
	else
	{
		return left_->Evaluate(date, event) || parse_expression_->Evaluate(date, event);
	}
}

bool EmptyNode::Evaluate(const Date & date, const string & event) const
{
	return true;
}
