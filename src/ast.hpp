#pragma once

#include <memory>
#include <vector>
#include <string>
#include <algorithm>

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
	ExprAST *LHS, *RHS;
public:
	BinaryExprAST(BinaryOperation operation,
		ExprAST* LHS, ExprAST* RHS)
	: operation(operation), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
	double eval(CalculatorState& state) override {
		switch(operation) {
		case BinaryOperation::ADD: return LHS->eval(state) + RHS->eval(state);
		case BinaryOperation::SUB: return LHS->eval(state) - RHS->eval(state);
		case BinaryOperation::DIV: return LHS->eval(state) / RHS->eval(state);
		case BinaryOperation::MUL: return LHS->eval(state) * RHS->eval(state);
		default: return 0;
		}
	}
};

class CallExprAST: public ExprAST {
	std::string name;
	std::vector<ExprAST*> args;
public:
	CallExprAST(const std::string& name,
		std::vector<ExprAST*> args)
	: name(name), args(std::move(args)) { }
	double eval(CalculatorState& state) override {
		std::vector<double> values;
		std::transform(args.begin(), args.end(),
			std::back_inserter(values), [&state](ExprAST* arg) {
				return arg->eval(state);
			}
		);
		return state.invoke(name, values);
	}
};