lexer grammar MathLexer;

Plus: '+';
Minus: '-';
Slash: '/';
Star: '*';

LeftParen: '(';
RightParen: ')';

INTEGER:
	DIGIT DIGIT*;

IDENT:
	LETTER (DIGIT | LETTER)*
	;

fragment DIGIT:
	[0-9];

fragment LETTER:
	[A-Za-z];

WHITESPACE: [ \t\n] -> skip;
NEWLINE: ('\r' '\n'?) | '\n';