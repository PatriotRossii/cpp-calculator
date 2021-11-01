lexer grammar MathLexer;

Plus: '+';
Minus: '-';
Slash: '/';
Star: '*';

LeftParen: '(';
RightParen: ')';

INTEGER:
	DIGIT DIGIT*;

fragment DIGIT:
	[0-9];

WHITESPACE: [ \t\n] -> skip;
NEWLINE: ('\r' '\n'?) | '\n';