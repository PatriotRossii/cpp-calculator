parser grammar Parser;

options {
	tokenVocab = Lexer;
}

expr:
	INTEGER
	| INTEGER Plus INTEGER
	| INTEGER Minus INTEGER
	| INTEGER Slash INTEGER
	| INTEGER Star INTEGER
	| LeftParen expr RightParen
	;	
