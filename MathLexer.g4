lexer grammar MathLexer;

Plus: '+';
Minus: '-';
Slash: '/';
Star: '*';

Comma: ',';
LeftParen: '(';
RightParen: ')';

Dot: '.';

LITERAL:
	INTEGER | FLOAT;

INTEGER:
	BINARY_LITERAL
	| OCTAL_LITERAL
	| DECIMAL_LITERAL
	| HEXADECIMAL_LITERAL;

BINARY_LITERAL:
	('0b' | '0B') BINARY_DIGIT* ;

OCTAL_LITERAL:
	'0' OCTAL_DIGIT* ;

DECIMAL_LITERAL:
	[1-9] DIGIT*;

HEXADECIMAL_LITERAL:
	HEXADECIMAL_PREFIX HEXADECIMAL_DIGIT_SEQUENCE;

BINARY_DIGIT:
	[0-1];

OCTAL_DIGIT:
	[0-7];

NONZERO_DIGIT:
	[1-9];

HEXADECIMAL_PREFIX:
	'0x'
	| '0X';

HEXADECIMAL_DIGIT_SEQUENCE:
	 HEXADECIMAL_DIGIT+;

HEXADECIMAL_DIGIT:
	[0-9a-fA-F];

FLOAT:
	DIGIT_SEQUENCE DECIMAL_EXPONENT
	| DIGIT_SEQUENCE Dot DECIMAL_EXPONENT?
	| DIGIT_SEQUENCE? Dot DIGIT_SEQUENCE DECIMAL_EXPONENT?
	| ('0x' | '0X') HEX_DIGIT_SEQUENCE HEX_EXPONENT
	| ('0x' | '0X') HEX_DIGIT_SEQUENCE Dot HEX_EXPONENT
	| ('0x' | '0X') HEX_DIGIT_SEQUENCE? Dot HEX_DIGIT_SEQUENCE HEX_EXPONENT;

DIGIT_SEQUENCE:
	DIGIT+;

HEX_DIGIT_SEQUENCE:
	HEX_DIGIT+;

DECIMAL_EXPONENT:
	('e' | 'E') EXPONENT_SIGN? DIGIT_SEQUENCE;

HEX_EXPONENT:
	('p' | 'P') EXPONENT_SIGN? DIGIT_SEQUENCE;

EXPONENT_SIGN:
	'+' | '-';

IDENT:
	LETTER (DIGIT | LETTER)*
	;

fragment DIGIT:
	[0-9];

fragment HEX_DIGIT:
	[0-9a-fA-F];

fragment LETTER:
	[A-Za-z];

WHITESPACE: [ \t\n] -> skip;
NEWLINE: ('\r' '\n'?) | '\n';