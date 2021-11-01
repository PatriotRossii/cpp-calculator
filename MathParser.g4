parser grammar MathParser;

options {
	tokenVocab = MathLexer;
}

expr:
	INTEGER # Literal
	| expr Plus expr # Add
	| expr Minus expr # Sub
	| expr Slash expr # Div
	| expr Star expr # Mul
	| LeftParen expr RightParen # Paren
	;	