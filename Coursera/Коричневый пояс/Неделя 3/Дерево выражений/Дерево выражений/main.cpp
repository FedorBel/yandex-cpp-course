#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class ValueExpr : public Expression
{
public:
	ValueExpr(int value) : value_(value) {}

	// Вычисляет значение выражения
	int Evaluate() const override
	{
		return value_;
	}

	// Форматирует выражение как строку
	// Каждый узел берётся в скобки, независимо от приоритета
	std::string ToString() const override
	{
		return to_string(value_);
	}

private:
	int value_;
};

class BinaryOperation : public Expression
{
public:
	BinaryOperation(ExpressionPtr left, ExpressionPtr right) : lhs_(move(left)), rhs_(move(right))
	{
	}

protected:
	ExpressionPtr lhs_;
	ExpressionPtr rhs_;
};

class SumExpr : public BinaryOperation
{
public:
	SumExpr(ExpressionPtr left, ExpressionPtr right) : BinaryOperation(move(left), move(right)) {}

	// Вычисляет значение выражения
	int Evaluate() const override
	{
		return lhs_->Evaluate() + rhs_->Evaluate();
	}

	// Форматирует выражение как строку
	// Каждый узел берётся в скобки, независимо от приоритета
	std::string ToString() const override
	{
		return '(' + lhs_->ToString() + ')' + '+' + '(' + rhs_->ToString() + ')';
	}
};

class ProductExpr : public BinaryOperation
{
public:
	ProductExpr(ExpressionPtr left, ExpressionPtr right) : BinaryOperation(move(left), move(right)) {}

	// Вычисляет значение выражения
	int Evaluate() const override
	{
		return lhs_->Evaluate() * rhs_->Evaluate();
	}

	// Форматирует выражение как строку
	// Каждый узел берётся в скобки, независимо от приоритета
	std::string ToString() const override
	{
		return '(' + lhs_->ToString() + ')' + '*' + '(' + rhs_->ToString() + ')';
	}
};

ExpressionPtr Value(int value)
{
	return make_unique<ValueExpr>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right)
{
	return make_unique<SumExpr>(move(left), move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{
	return make_unique<ProductExpr>(move(left), move(right));
}

string Print(const Expression *e)
{
	if (!e)
	{
		return "Null expression provided";
	}
	stringstream output;
	output << e->ToString() << " = " << e->Evaluate();
	return output.str();
}

void Test()
{
	ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
	ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

	ExpressionPtr e2 = Sum(move(e1), Value(5));
	ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

	ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, Test);
	return 0;
}