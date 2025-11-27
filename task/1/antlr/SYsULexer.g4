lexer grammar SYsULexer;

LineComment : '//' .*? '\r'? '\n';
BlockComment : '/*'.*?'*/';

LineDirective:
    '#' WS*
    Number WS+
    ('"' FileName '"' | )
    (WS+ LineNumber)*
    WS*
    ;

// 片段规则（不会被单独作为token）
fragment Number: [0-9]+;
fragment LineNumber: [1234]+;
fragment FileName: ~["\r\n]*;
fragment WS: [ \t];

Int : 'int';
Return : 'return';
Const : 'const';
If : 'if';
Else : 'else';
Void : 'void';

LeftParen : '(';
RightParen : ')';
LeftBracket : '[';
RightBracket : ']';
LeftBrace : '{';
RightBrace : '}';

Plus : '+';
Minus : '-';
Star : '*';
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
AmpAmp : '&&';
Pipepipe : '||';
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
