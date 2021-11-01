#include <memory>
#include <vector>
#include <string>

enum class BinaryOperation {
	ADD, SUB, DIV, MUL
};

class ExprAST {
public:
	virtual ~ExprAST() { }
};

class IntegerExprAST: public ExprAST {
	double value;
public:
	IntegerExprAST(double value): value(value) {}
};

class BinaryExprAST: public ExprAST {
	BinaryOperation operation;
	std::unique_ptr<ExprAST> LHS, RHS;
public:
	BinaryExprAST(BinaryOperation operation,
		std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
	: operation(operation), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

class CallExprAST: public ExprAST {
	std::string name;
	std::vector<std::unique_ptr<ExprAST>> args;
public:
	CallExprAST(const std::string& name,
		std::vector<std::unique_ptr<ExprAST>> args)
	: name(name), args(std::move(args)) { }
};