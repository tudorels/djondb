grammar JSONGrammar;

options {
	language = C;
}


start_point
	: object_expr | array_expr EOF;
	
object_expr	
	:  LBRAN pair (COMMA pair)* RBRAN;

array_expr
	: LBRAK value (COMMA value)* RBRAK;
	
fragment pair
	: name COLON value;
	
fragment name
	:	ID;

fragment value
	:	(INT | FLOAT | STRING | object_expr | array_expr);

ID  :	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
    ;

INT :	'0'..'9'+
    ;

FLOAT
    :   ('0'..'9')+ '.' ('0'..'9')* EXPONENT?
    |   '.' ('0'..'9')+ EXPONENT?
    |   ('0'..'9')+ EXPONENT
    ;

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

WS  :   ( ' '
        | '\t'
        | '\r'
        | '\n'
        ) {$channel=HIDDEN;}
    ;

STRING
    :  '\'' ( ESC_SEQ | ~('\\'|'\'') )* '\''
    ;

fragment
EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;

fragment
HEX_DIGIT : ('0'..'9'|'a'..'f'|'A'..'F') ;

fragment
ESC_SEQ
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
    |   UNICODE_ESC
    |   OCTAL_ESC
    ;

fragment
OCTAL_ESC
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;

fragment
UNICODE_ESC
    :   '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;

fragment COMMA
	:	',';
fragment LBRAN
	:	'{';
fragment RBRAN
	:	'}';
fragment LBRAK
	:	'[';
fragment RBRAK
	:	']';
fragment COLON
	:	':';

// CHAR:  '\'' ( ESC_SEQ | ~('\''|'\\') ) '\''
//    ;
