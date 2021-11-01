#include <algorithm>
#include <vector>
#include <memory>
#include <string>
#include "MathParserBaseVisitor.h"

#include "ast.hpp"

class Visitor: public MathParserBaseVisitor {
public:
	antlrcpp::Any visitLiteral(MathParser::LiteralContext *ctx) {
		return std::make_unique<IntegerExprAST>(
			std::stod(ctx->INTEGER()->getText())
		);
	}
	antlrcpp::Any visitAdd(MathParser::AddContext *ctx) {
		return std::make_unique<BinaryExprAST>(
			BinaryOperation::ADD,
			std::move(visit(ctx->expr(0)).as<std::unique_ptr<ExprAST>>()),
			std::move(visit(ctx->expr(1)).as<std::unique_ptr<ExprAST>>())
		);
	}
	antlrcpp::Any visitSub(MathParser::SubContext *ctx) {
		return std::make_unique<BinaryExprAST>(
			BinaryOperation::SUB,
			std::move(visit(ctx->expr(0)).as<std::unique_ptr<ExprAST>>()),
			std::move(visit(ctx->expr(1)).as<std::unique_ptr<ExprAST>>())
		);
	}
	antlrcpp::Any visitDiv(MathParser::DivContext *ctx) {
		return std::make_unique<BinaryExprAST>(
			BinaryOperation::DIV,
			std::move(visit(ctx->expr(0)).as<std::unique_ptr<ExprAST>>()),
			std::move(visit(ctx->expr(1)).as<std::unique_ptr<ExprAST>>())
		);
	}
	antlrcpp::Any visitMul(MathParser::MulContext *ctx) {
		return std::make_unique<BinaryExprAST>(
			BinaryOperation::MUL,
			std::move(visit(ctx->expr(0)).as<std::unique_ptr<ExprAST>>()),
			std::move(visit(ctx->expr(1)).as<std::unique_ptr<ExprAST>>())
		);
	}
	antlrcpp::Any visitFunc(MathParser::FuncContext *ctx) {
		std::vector<std::unique_ptr<ExprAST>> expressions;
		for(MathParser::ExprContext* ctx: ctx->exprs) {
			expressions.push_back(std::move(visit(ctx).as<std::unique_ptr<ExprAST>>()));
		}
		return std::make_unique<CallExprAST>(
			ctx->IDENT()->getText(),
			std::move(expressions)
		);
	}
	antlrcpp::Any visitParen(MathParser::ParenContext *ctx) {
		return visit(ctx->expr());
	}
};
