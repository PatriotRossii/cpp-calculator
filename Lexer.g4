lexer grammar Lexer;

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
