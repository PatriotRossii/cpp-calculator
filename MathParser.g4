parser grammar MathParser;

options {
	tokenVocab = MathLexer;
}

expr:
	LeftParen expr RightParen # Paren
	| expr Slash expr # Div
	| expr Star expr # Mul
	| expr Plus expr # Add
	| expr Minus expr # Sub
	| INTEGER # Literal
	;	