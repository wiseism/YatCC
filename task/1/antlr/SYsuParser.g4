parser grammar SYsuParser;
options {
    tokenVocab = SYsULexer;
}
// 起始规则
compilationUnit
    :   translationUnit? EOF
    ;

translationUnit
    :   externalDeclaration+
    ;

externalDeclaration
    :   functionDefinition
    |   declaration
    ;

functionDefinition
    :   typeSpecifier Identifier LeftParen parameterList? RightParen compoundStatement
    ;

typeSpecifier
    :   Int
    |   Void
    |   Const typeSpecifier
    ;

parameterList
    :   parameterDeclaration (Comma parameterDeclaration)*
    ;

parameterDeclaration
    :   typeSpecifier Identifier
    ;

declaration
    :   typeSpecifier Identifier (Equal initializer)? Semi
    ;

initializer
    :   expression
    ;

compoundStatement
    :   LeftBrace blockItemList? RightBrace
    ;

blockItemList
    :   blockItem+
    ;

blockItem
    :   declaration
    |   statement
    ;

statement
    :   expressionStatement
    |   compoundStatement
    |   selectionStatement
    |   returnStatement
    ;

expressionStatement
    :   expression? Semi
    ;

selectionStatement
    :   If LeftParen expression RightParen statement (Else statement)?
    ;

returnStatement
    :   Return expression? Semi
    ;

expression
    :   assignmentExpression
    ;

assignmentExpression
    :   logicalOrExpression
    |   Identifier Equal assignmentExpression
    ;

logicalOrExpression
    :   logicalAndExpression (Pipepipe logicalAndExpression)*
    ;

logicalAndExpression
    :   equalityExpression (AmpAmp equalityExpression)*
    ;

equalityExpression
    :   relationalExpression ((EqualEqual | NotEqual) relationalExpression)*
    ;

relationalExpression
    :   additiveExpression ((Less | Greater | LessEqual | GreaterEqual) additiveExpression)*
    ;

additiveExpression
    :   multiplicativeExpression ((Plus | Minus) multiplicativeExpression)*
    ;

multiplicativeExpression
    :   unaryExpression ((Star | Div | Mod) unaryExpression)*
    ;

unaryExpression
    :   postfixExpression
    |   (Plus | Minus | Not) unaryExpression
    ;

postfixExpression
    :   primaryExpression (LeftBracket expression RightBracket)*
    ;

primaryExpression
    :   Identifier
    |   Constant
    |   LeftParen expression RightParen
    ;
