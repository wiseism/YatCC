// Generated from D:/develops/git/github/cpp/YatCC/task/2/antlr/SYsUParser.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link SYsUParser}.
 */
public interface SYsUParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link SYsUParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterPrimaryExpression(SYsUParser.PrimaryExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#primaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitPrimaryExpression(SYsUParser.PrimaryExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void enterPostfixExpression(SYsUParser.PostfixExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#postfixExpression}.
	 * @param ctx the parse tree
	 */
	void exitPostfixExpression(SYsUParser.PostfixExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#argumentExpressionList}.
	 * @param ctx the parse tree
	 */
	void enterArgumentExpressionList(SYsUParser.ArgumentExpressionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#argumentExpressionList}.
	 * @param ctx the parse tree
	 */
	void exitArgumentExpressionList(SYsUParser.ArgumentExpressionListContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryExpression(SYsUParser.UnaryExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#unaryExpression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryExpression(SYsUParser.UnaryExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#unaryOperator}.
	 * @param ctx the parse tree
	 */
	void enterUnaryOperator(SYsUParser.UnaryOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#unaryOperator}.
	 * @param ctx the parse tree
	 */
	void exitUnaryOperator(SYsUParser.UnaryOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicativeExpression(SYsUParser.MultiplicativeExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicativeExpression(SYsUParser.MultiplicativeExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void enterAdditiveExpression(SYsUParser.AdditiveExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#additiveExpression}.
	 * @param ctx the parse tree
	 */
	void exitAdditiveExpression(SYsUParser.AdditiveExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void enterRelationalExpression(SYsUParser.RelationalExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#relationalExpression}.
	 * @param ctx the parse tree
	 */
	void exitRelationalExpression(SYsUParser.RelationalExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void enterEqualityExpression(SYsUParser.EqualityExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#equalityExpression}.
	 * @param ctx the parse tree
	 */
	void exitEqualityExpression(SYsUParser.EqualityExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalAndExpression(SYsUParser.LogicalAndExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalAndExpression(SYsUParser.LogicalAndExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalOrExpression(SYsUParser.LogicalOrExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalOrExpression(SYsUParser.LogicalOrExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentExpression(SYsUParser.AssignmentExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#assignmentExpression}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentExpression(SYsUParser.AssignmentExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(SYsUParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(SYsUParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(SYsUParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(SYsUParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#declarationSpecifiers}.
	 * @param ctx the parse tree
	 */
	void enterDeclarationSpecifiers(SYsUParser.DeclarationSpecifiersContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#declarationSpecifiers}.
	 * @param ctx the parse tree
	 */
	void exitDeclarationSpecifiers(SYsUParser.DeclarationSpecifiersContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#declarationSpecifier}.
	 * @param ctx the parse tree
	 */
	void enterDeclarationSpecifier(SYsUParser.DeclarationSpecifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#declarationSpecifier}.
	 * @param ctx the parse tree
	 */
	void exitDeclarationSpecifier(SYsUParser.DeclarationSpecifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#initDeclaratorList}.
	 * @param ctx the parse tree
	 */
	void enterInitDeclaratorList(SYsUParser.InitDeclaratorListContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#initDeclaratorList}.
	 * @param ctx the parse tree
	 */
	void exitInitDeclaratorList(SYsUParser.InitDeclaratorListContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#initDeclarator}.
	 * @param ctx the parse tree
	 */
	void enterInitDeclarator(SYsUParser.InitDeclaratorContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#initDeclarator}.
	 * @param ctx the parse tree
	 */
	void exitInitDeclarator(SYsUParser.InitDeclaratorContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#typeSpecifier}.
	 * @param ctx the parse tree
	 */
	void enterTypeSpecifier(SYsUParser.TypeSpecifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#typeSpecifier}.
	 * @param ctx the parse tree
	 */
	void exitTypeSpecifier(SYsUParser.TypeSpecifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#declarator}.
	 * @param ctx the parse tree
	 */
	void enterDeclarator(SYsUParser.DeclaratorContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#declarator}.
	 * @param ctx the parse tree
	 */
	void exitDeclarator(SYsUParser.DeclaratorContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#directDeclarator}.
	 * @param ctx the parse tree
	 */
	void enterDirectDeclarator(SYsUParser.DirectDeclaratorContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#directDeclarator}.
	 * @param ctx the parse tree
	 */
	void exitDirectDeclarator(SYsUParser.DirectDeclaratorContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#parameterList}.
	 * @param ctx the parse tree
	 */
	void enterParameterList(SYsUParser.ParameterListContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#parameterList}.
	 * @param ctx the parse tree
	 */
	void exitParameterList(SYsUParser.ParameterListContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#parameterDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterParameterDeclaration(SYsUParser.ParameterDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#parameterDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitParameterDeclaration(SYsUParser.ParameterDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#identifierList}.
	 * @param ctx the parse tree
	 */
	void enterIdentifierList(SYsUParser.IdentifierListContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#identifierList}.
	 * @param ctx the parse tree
	 */
	void exitIdentifierList(SYsUParser.IdentifierListContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#initializer}.
	 * @param ctx the parse tree
	 */
	void enterInitializer(SYsUParser.InitializerContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#initializer}.
	 * @param ctx the parse tree
	 */
	void exitInitializer(SYsUParser.InitializerContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#initializerList}.
	 * @param ctx the parse tree
	 */
	void enterInitializerList(SYsUParser.InitializerListContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#initializerList}.
	 * @param ctx the parse tree
	 */
	void exitInitializerList(SYsUParser.InitializerListContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(SYsUParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(SYsUParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStatement(SYsUParser.CompoundStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStatement(SYsUParser.CompoundStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#blockItemList}.
	 * @param ctx the parse tree
	 */
	void enterBlockItemList(SYsUParser.BlockItemListContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#blockItemList}.
	 * @param ctx the parse tree
	 */
	void exitBlockItemList(SYsUParser.BlockItemListContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#blockItem}.
	 * @param ctx the parse tree
	 */
	void enterBlockItem(SYsUParser.BlockItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#blockItem}.
	 * @param ctx the parse tree
	 */
	void exitBlockItem(SYsUParser.BlockItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void enterExpressionStatement(SYsUParser.ExpressionStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void exitExpressionStatement(SYsUParser.ExpressionStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#selectionStatement}.
	 * @param ctx the parse tree
	 */
	void enterSelectionStatement(SYsUParser.SelectionStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#selectionStatement}.
	 * @param ctx the parse tree
	 */
	void exitSelectionStatement(SYsUParser.SelectionStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#iterationStatement}.
	 * @param ctx the parse tree
	 */
	void enterIterationStatement(SYsUParser.IterationStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#iterationStatement}.
	 * @param ctx the parse tree
	 */
	void exitIterationStatement(SYsUParser.IterationStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#jumpStatement}.
	 * @param ctx the parse tree
	 */
	void enterJumpStatement(SYsUParser.JumpStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#jumpStatement}.
	 * @param ctx the parse tree
	 */
	void exitJumpStatement(SYsUParser.JumpStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#compilationUnit}.
	 * @param ctx the parse tree
	 */
	void enterCompilationUnit(SYsUParser.CompilationUnitContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#compilationUnit}.
	 * @param ctx the parse tree
	 */
	void exitCompilationUnit(SYsUParser.CompilationUnitContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#translationUnit}.
	 * @param ctx the parse tree
	 */
	void enterTranslationUnit(SYsUParser.TranslationUnitContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#translationUnit}.
	 * @param ctx the parse tree
	 */
	void exitTranslationUnit(SYsUParser.TranslationUnitContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#externalDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterExternalDeclaration(SYsUParser.ExternalDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#externalDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitExternalDeclaration(SYsUParser.ExternalDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link SYsUParser#functionDefinition}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDefinition(SYsUParser.FunctionDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link SYsUParser#functionDefinition}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDefinition(SYsUParser.FunctionDefinitionContext ctx);
}