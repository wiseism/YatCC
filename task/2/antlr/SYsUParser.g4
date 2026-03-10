parser grammar SYsUParser;

options {
  tokenVocab=SYsULexer;
}

primaryExpression
    :   Identifier
    |   Constant
    |   LeftParen expression RightParen
    ;

postfixExpression
    :   primaryExpression
    |   postfixExpression LeftBracket expression RightBracket
    |   postfixExpression LeftParen argumentExpressionList? RightParen
    ;

argumentExpressionList
    :   assignmentExpression (Comma assignmentExpression)*
    ;

unaryExpression
    :   postfixExpression
    |   unaryOperator unaryExpression
    |   Not unaryExpression
    ;

unaryOperator
    :   Plus
    |   Minus
    ;

multiplicativeExpression
    :   unaryExpression ((Star|Div|Mod) unaryExpression)*
    ;

additiveExpression
    :   multiplicativeExpression ((Plus|Minus) multiplicativeExpression)*
    ;

relationalExpression
    :   additiveExpression ((Less|Greater|LessEqual|GreaterEqual) additiveExpression)*
    ;

equalityExpression
    :   relationalExpression ((EqualEqual|NotEqual) relationalExpression)*
    ;

logicalAndExpression
    :   equalityExpression (AmpAmp equalityExpression)*
    ;

logicalOrExpression
    :   logicalAndExpression (PipePipe logicalAndExpression)*
    ;

assignmentExpression
    :   logicalOrExpression
    |   unaryExpression Equal assignmentExpression
    ;

expression
    :   assignmentExpression (Comma assignmentExpression)*
    ;

declaration
    :   declarationSpecifiers initDeclaratorList? Semi
    ;

declarationSpecifiers
    :   declarationSpecifier+
    ;

declarationSpecifier
    :   typeSpecifier
    |   Const
    ;

initDeclaratorList
    :   initDeclarator (Comma initDeclarator)*
    ;

initDeclarator
    :   declarator (Equal initializer)?
    ;

typeSpecifier
    :   Int
    |   Void
    ;

declarator
    :   directDeclarator
    ;

directDeclarator
    :   Identifier
    |   directDeclarator LeftParen parameterList? RightParen
    |   directDeclarator LeftBracket assignmentExpression? RightBracket
    ;

parameterList
    :   parameterDeclaration (Comma parameterDeclaration)*
    ;

parameterDeclaration
    :   declarationSpecifiers declarator
    ;

identifierList
    :   Identifier (Comma Identifier)*
    ;

initializer
    :   assignmentExpression
    |   LeftBrace initializerList? Comma? RightBrace
    ;

initializerList
    :   initializer (Comma initializer)*
    ;

statement
    :   compoundStatement
    |   expressionStatement
    |   selectionStatement
    |   iterationStatement
    |   jumpStatement
    ;

compoundStatement
    :   LeftBrace blockItemList? RightBrace
    ;

blockItemList
    :   blockItem+
    ;

blockItem
    :   statement
    |   declaration
    ;

expressionStatement
    :   expression? Semi
    ;

selectionStatement
    :   If LeftParen expression RightParen statement (Else statement)?
    ;

iterationStatement
    :   While LeftParen expression RightParen statement
    ;

jumpStatement
    :   Return expression? Semi
    |   Break Semi
    |   Continue Semi
    ;

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
    :   declarationSpecifiers declarator compoundStatement
    ;
