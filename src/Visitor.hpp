#include <string>

#include <unordered_map>
#include <functional>
#include <cmath>

#include "MathParserBaseVisitor.h"

class Visitor: public MathParserBaseVisitor {
private:
	std::map<std::string, std::function<double(double)>> functions{
		{"sin", [](double x) {
			return std::sin(x);
		}},
		{"cos", [](double x) {
			return std::cos(x);
		}},
		{"abs", [](double x) {
			return std::abs(x);
		}}
	};
public:
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
	antlrcpp::Any visitFunc(MathParser::FuncContext *ctx) {
		return functions[ctx->IDENT()->getText()](visit(ctx->expr()).as<double>());
	}
	antlrcpp::Any visitParen(MathParser::ParenContext *ctx) {
		return visit(ctx->expr());
	}
};
