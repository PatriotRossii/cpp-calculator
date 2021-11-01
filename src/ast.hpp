#include <memory>
#include <vector>
#include <string>

#include "calculator/state.hpp"

enum class BinaryOperation {
	ADD, SUB, DIV, MUL
};

class ExprAST {
public:
	virtual ~ExprAST() { }
	virtual double eval(CalculatorState&) = 0;
};

class IntegerExprAST: public ExprAST {
	double value;
public:
	IntegerExprAST(double value): value(value) {}
	double eval(CalculatorState&) override {
		return value;
	}
};

class BinaryExprAST: public ExprAST {
	BinaryOperation operation;
	std::unique_ptr<ExprAST> LHS, RHS;
public:
	BinaryExprAST(BinaryOperation operation,
		std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
	: operation(operation), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
	double eval(CalculatorState& state) override {
		return LHS->eval(state) + RHS->eval(state);
	}
};

class CallExprAST: public ExprAST {
	std::string name;
	std::vector<std::unique_ptr<ExprAST>> args;
public:
	CallExprAST(const std::string& name,
		std::vector<std::unique_ptr<ExprAST>> args)
	: name(name), args(std::move(args)) { }
	double eval(CalculatorState& state) override {
		std::vector<double> values;
		std::transform(args.begin(), args.end(),
			std::back_inserter(values), [&state](const std::unique_ptr<ExprAST>& arg) {
				return arg->eval(state);
			}
		);
		return state.invoke(name, values);
	}
};