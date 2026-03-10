// Generated from D:/develops/git/github/cpp/YatCC/task/2/antlr/SYsUParser.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link SYsUParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface SYsUParserVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link SYsUParser#primaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrimaryExpression(SYsUParser.PrimaryExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#postfixExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPostfixExpression(SYsUParser.PostfixExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#argumentExpressionList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgumentExpressionList(SYsUParser.ArgumentExpressionListContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#unaryExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnaryExpression(SYsUParser.UnaryExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#unaryOperator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnaryOperator(SYsUParser.UnaryOperatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#multiplicativeExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicativeExpression(SYsUParser.MultiplicativeExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#additiveExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAdditiveExpression(SYsUParser.AdditiveExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#relationalExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelationalExpression(SYsUParser.RelationalExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#equalityExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEqualityExpression(SYsUParser.EqualityExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#logicalAndExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicalAndExpression(SYsUParser.LogicalAndExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#logicalOrExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicalOrExpression(SYsUParser.LogicalOrExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#assignmentExpression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignmentExpression(SYsUParser.AssignmentExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression(SYsUParser.ExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDeclaration(SYsUParser.DeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#declarationSpecifiers}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDeclarationSpecifiers(SYsUParser.DeclarationSpecifiersContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#declarationSpecifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDeclarationSpecifier(SYsUParser.DeclarationSpecifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#initDeclaratorList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInitDeclaratorList(SYsUParser.InitDeclaratorListContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#initDeclarator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInitDeclarator(SYsUParser.InitDeclaratorContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#typeSpecifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTypeSpecifier(SYsUParser.TypeSpecifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#declarator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDeclarator(SYsUParser.DeclaratorContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#directDeclarator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDirectDeclarator(SYsUParser.DirectDeclaratorContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#parameterList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParameterList(SYsUParser.ParameterListContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#parameterDeclaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParameterDeclaration(SYsUParser.ParameterDeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#identifierList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentifierList(SYsUParser.IdentifierListContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#initializer}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInitializer(SYsUParser.InitializerContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#initializerList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInitializerList(SYsUParser.InitializerListContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(SYsUParser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#compoundStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCompoundStatement(SYsUParser.CompoundStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#blockItemList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlockItemList(SYsUParser.BlockItemListContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#blockItem}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlockItem(SYsUParser.BlockItemContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#expressionStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpressionStatement(SYsUParser.ExpressionStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#selectionStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSelectionStatement(SYsUParser.SelectionStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#iterationStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIterationStatement(SYsUParser.IterationStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#jumpStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitJumpStatement(SYsUParser.JumpStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#compilationUnit}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCompilationUnit(SYsUParser.CompilationUnitContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#translationUnit}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTranslationUnit(SYsUParser.TranslationUnitContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#externalDeclaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExternalDeclaration(SYsUParser.ExternalDeclarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link SYsUParser#functionDefinition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionDefinition(SYsUParser.FunctionDefinitionContext ctx);
}