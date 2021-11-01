#include <string>

#include "MathParserBaseVisitor.h"

class Visitor: public MathParserBaseVisitor {
	antlrcpp::Any visitLiteral(MathParser::LiteralContext *ctx) {
		return std::stod(ctx->INTEGER()->getText());
	}
	antlrcpp::Any visitAdd(MathParser::AddContext *ctx) {
		return visit(ctx->expr(0)).as<double>() + visit(ctx->expr(1)).as<double>();
	}
	antlrcpp::Any visitSub(MathParser::SubContext *ctx) {
		return visit(ctx->expr(0)).as<double>() - visit(ctx->expr(1)).as<double>();
	}
	antlrcpp::Any visitDiv(MathParser::DivContext *ctx) {
		return visit(ctx->expr(0)).as<double>() / visit(ctx->expr(1)).as<double>();
	}
	antlrcpp::Any visitMul(MathParser::MulContext *ctx) {
		return visit(ctx->expr(0)).as<double>() * visit(ctx->expr(1)).as<double>();
	}
	antlrcpp::Any visitParen(MathParser::ParenContext *ctx) {
		return visit(ctx->expr());
	}
};
