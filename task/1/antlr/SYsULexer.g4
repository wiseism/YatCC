lexer grammar SYsULexer;

LINE_COMMENT : '//' .*? '\r'? '\n';
BLOCK_COMMENT : '/*'.*?'*/';
LineAfterPreprocessing
    :   '#' ~[\r\n]*
    ;

Int : 'int';
Return : 'return';

LeftParen : '(';
RightParen : ')';
LeftBracket : '[';
RightBracket : ']';
LeftBrace : '{';
RightBrace : '}';

Plus : '+';
Minus : '-';
Multi : '*';
Div : '/';
Mod : '%';

Semi : ';';
Comma : ',';

Equal : '=';
EqualEqual : '==';
NotEqual : '!=';
Less : '<';
Greater : '>';
LessEqual : '<=';
GreaterEqual : '>=';
AndAnd : '&&';
OrOr : '||';
Not : '!';

Identifier
    :   IdentifierNondigit
        (   IdentifierNondigit
        |   Digit
        )*
    ;

fragment
IdentifierNondigit
    :   Nondigit
    ;

fragment
Nondigit
    :   [a-zA-Z_]
    ;

fragment
Digit
    :   [0-9]
    ;

Constant
    :   IntegerConstant
    ;

fragment
IntegerConstant
    :   DecimalConstant
    |   OctalConstant
    |   HexadecimalConstant
    ;

fragment
DecimalConstant
    :   NonzeroDigit Digit*
    ;

fragment
OctalConstant
    :   '0' OctalDigit*
    ;

fragment
HexadecimalConstant
    :   HexadecimalPrefix HexadecimalDigit+
    ;

fragment
HexadecimalPrefix
    :   '0' [xX]
    ;

fragment
NonzeroDigit
    :   [1-9]
    ;

fragment
OctalDigit
    :   [0-7]
    ;

fragment
HexadecimalDigit
    :   [0-9a-fA-F]
    ;


Whitespace
    :   [ \t]+
    ;

Newline
    :   (   '\r' '\n'?
        |   '\n'
        )
        -> skip
    ;
