#pragma once

#include <vector>
#include <memory>
#include <string>

#include "MathParserBaseVisitor.h"

#include "ast.hpp"

class Visitor: public MathParserBaseVisitor {
public:
	antlrcpp::Any visitLiteral(MathParser::LiteralContext *ctx) {
		return (ExprAST*) new IntegerExprAST(
			std::stod(ctx->INTEGER()->getText())
		);
	}
	antlrcpp::Any visitAdd(MathParser::AddContext *ctx) {
		return (ExprAST*) new BinaryExprAST(
			BinaryOperation::ADD,
			std::move(visit(ctx->expr(0)).as<ExprAST*>()),
			std::move(visit(ctx->expr(1)).as<ExprAST*>())
		);
	}
	antlrcpp::Any visitSub(MathParser::SubContext *ctx) {
		return (ExprAST*) new BinaryExprAST(
			BinaryOperation::SUB,
			std::move(visit(ctx->expr(0)).as<ExprAST*>()),
			std::move(visit(ctx->expr(1)).as<ExprAST*>())
		);
	}
	antlrcpp::Any visitDiv(MathParser::DivContext *ctx) {
		return (ExprAST*) new BinaryExprAST(
			BinaryOperation::DIV,
			std::move(visit(ctx->expr(0)).as<ExprAST*>()),
			std::move(visit(ctx->expr(1)).as<ExprAST*>())
		);
	}
	antlrcpp::Any visitMul(MathParser::MulContext *ctx) {
		return (ExprAST*) new BinaryExprAST(
			BinaryOperation::MUL,
			std::move(visit(ctx->expr(0)).as<ExprAST*>()),
			std::move(visit(ctx->expr(1)).as<ExprAST*>())
		);
	}
	antlrcpp::Any visitFunc(MathParser::FuncContext *ctx) {
		std::vector<ExprAST*> expressions;
		for(MathParser::ExprContext* ctx: ctx->exprs) {
			expressions.push_back(std::move(visit(ctx).as<ExprAST*>()));
		}
		return (ExprAST*) new CallExprAST(
			ctx->IDENT()->getText(),
			std::move(expressions)
		);
	}
	antlrcpp::Any visitParen(MathParser::ParenContext *ctx) {
		return visit(ctx->expr());
	}
};
