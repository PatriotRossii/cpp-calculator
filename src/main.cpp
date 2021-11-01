#include <iostream>

#include "antlr4-runtime.h"

#include "MathLexer.h"
#include "MathParser.h"

#include "Visitor.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open("input.txt");
    
    antlr4::ANTLRInputStream input(stream);
    MathLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    MathParser parser(&tokens);    

    MathParser::ExprContext* tree = parser.expr();

    Visitor visitor;
    double result = visitor.visit(tree).as<double>();
    std::cout << result;

    return 0;
}