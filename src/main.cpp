#include <iostream>

#include "antlr4-runtime.h"

#include "MathLexer.h"
#include "MathParser.h"

#include "Visitor.hpp"

using namespace std;
using namespace antlr4;

int main(int argc, const char* argv[]) {
    std::string instruction;

    std::cout << "> ";
    while(std::getline(std::cin, instruction)) {
        ANTLRInputStream stream(instruction);

        MathLexer lexer(&stream);
        antlr4::CommonTokenStream tokens(&lexer);
        MathParser parser(&tokens);

        MathParser::ExprContext* tree = parser.expr();

        Visitor visitor;
        double result = visitor.visit(tree).as<double>();
        std::cout << result << "\n> ";
    }

    return 0;
}