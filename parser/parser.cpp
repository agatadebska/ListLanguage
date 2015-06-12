//
// Created by agata on 07.06.15.
//

#include "parser.h"
#include "../ast/ListDeclaration.h"
#include "../ast/VarDeclaration.h"

void parser::parse(std::string fileName){
    scanner _scanner(fileName);
    _scanner.tokenize();

    std::vector<std::pair<tokenType, std::string>>::iterator i = _scanner._tokens.begin();
    while(i!=_scanner._tokens.end()){
    std::cout << (*i).first << "        " << (*i).second << std::endl;

        ++i;
    }
    i = _scanner._tokens.begin();
    start = _scanner._tokens.begin();
    end = _scanner._tokens.end();
    while(i != _scanner._tokens.end()){
        ast::Operation operation = tryOperation(&i, global);
        program.addOperation(operation);
    }

    std::cout << "name\ttype\tscope" << std::endl;
    for(std::vector<Symbol>::iterator i = symbols.begin(); i!= symbols.end(); ++i)
        std::cout << i->name << "\t \t" << i->type << "\t \t" << i->scope << std::endl;

}

void parser::showError(tokenType& token, std::string errElem, std::string str, std::string expect){
    std::cerr << "[" << errElem << "] Syntax error  ";
    if(token < 8)
        std::cerr << "before '" << str < "'  ";
    else
        std::cerr << "before '" << toString(token) << "'  ";
    std::cerr << "'" <<  expect << "' expected" << std::endl;
    errored = true;
    exit(1);
}


ast::Range parser::tryRange(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    int start;
    int end = -1;
    if(i->first == SquareBraceOpen) {
        if ((++i)->first == IntVal) {
            start = stoi(i->second);
            if ((++i)->first == Colon) {
                if ((++i)->first == SquareBraceClose) {
                    *j = ++i;
                    return ast::Range(start);
                }
                else if (i->first == IntVal) {
                    end = stoi(i->second);
                    if ((++i)->first == SquareBraceClose) {
                        *j = ++i;
                        return ast::Range(start, end);
                    }
                }
                showError(i->first, "Range", ":", "] or integer value");
                return ast::Range();
            }
            showError(i->first, "Range", i->second, ":");
            return ast::Range();
        }
        showError(i->first, "Range", "[", "integer value");
        return ast::Range();

       // exit(1);
    }
    return ast::Range();
}

ast::Variable parser::tryVariable(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == tokenType::Int && (++i)->first == Id){
        *j = ++i;
        return ast::Variable(ast::Type::Int, (i-1)->second);
    }
    else if(i->first == tokenType::Float && (++i)->first == Id) {
        *j = ++i;
        return ast::Variable(ast::Type::Float, (i-1)->second);
    }
    return ast::Variable();
}

ast::Elements parser::tryElements(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == IntVal || i->first == FloatVal || i->first == Id){
        ast::Element elem(i->second);
        ast::Elements elements;
        elements.addNextElement(elem);
        while((++i)->first == Comma){
            if((++i)->first == IntVal || i->first == FloatVal || i->first == Id) {
                elem = ast::Element(i->second);
                elements.addNextElement(elem);
            }
            else{
                showError(i->first, "Elements", ",", "number od variable name");
                //       exit(1);
                return ast::Elements();
            }
        }
        *j = i;
        return elements;
    }

    return ast::Elements();         //pusty Elements bo nie sa to Elements
}

ast::ListGetter parser::tryListGetter(std::vector<std::pair<tokenType, std::string>>::iterator* j){     //przesuwa iterator o tyle ile przeczytalo
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == Id){
        ast::Id id(i->second);
        if((++i)->first == SquareBraceOpen){
            if((++i)->first == IntVal){
                int num(stoi(i->second));
                if((++i)->first == SquareBraceClose){
                    *j = ++i;
                    return ast::ListGetter(id, num);
                }
                showError(i->first, "List getter", ",", "[");
                return ast::ListGetter();
            }
            showError(i->first, "List getter", "[", "integer value");
            return ast::ListGetter();
           // exit(1);
        }
    }
    return ast::ListGetter();
}

ast::AssignVar parser::tryAssignVar(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == Id){
        std::string id = i->second;                  //id
        if((++i)->first == AssigOp){                 //id =
            std::vector<std::pair<tokenType, std::string>>::iterator iter = ++i;
            ast::ListGetter listGetter = tryListGetter(&i);
            if(iter != i){
                *j = i;
                return ast::AssignVar(id, listGetter);
            }
            ast::FunctionCall functionCall = tryFunctionCall(&i);
            if(iter != i){
                *j = i;
                return ast::AssignVar(id, functionCall);
            }
            ast::Expression expression = tryExpression(&i, NULL);
            if(iter != i){
                *j = i;
                return ast::AssignVar(id, expression);
            }
            showError(i->first, "Assign var", "=", "list getter, function call or expression");
          //  exit(1);
        }
    }
    return ast::AssignVar();
}

ast::Type parser::tryType(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == tokenType::Int){
        ++i;
        *j = i;
        return ast::Type(ast::Type::Int);
    }
    else if(i->first == tokenType::Float){
        ++i;
        *j = i;
        return  ast::Type(ast::Type::Float);
    }
    return ast::Type();
}

ast::MultiplicativeExpression parser::tryMultiplicativeExpression(std::vector<std::pair<tokenType, std::string>>::iterator* j, ast::MultiplicativeExpression* expr){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == Id || i->first == IntVal || i->first == FloatVal){
        ast::MultiplicativeExpression multiplicativeExpression(i->second);
        if((i+1)->first == MultiplOp){
            tryMultiplicativeExpression(&(++i), &multiplicativeExpression);
        }
        *j = i;
        return multiplicativeExpression;
    }
    else if(i->first == MultiplOp && expr != NULL){
        if((i+1)->first == Id || (i+1)->first == IntVal || (i+1)->first == FloatVal){
            expr->addRightOperand(i->second, (++i)->second);
            *j = i;
            return *expr;
        }
    }
    return ast::MultiplicativeExpression();
}

ast::AdditiveExpression parser::tryAdditiveExpression(std::vector<std::pair<tokenType, std::string>>::iterator* j, ast::AdditiveExpression* expr){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == AdditiveOp && expr != NULL){
        std::string oper = i->second;
        ++i;
        ast::MultiplicativeExpression multiplicativeExpression1 = tryMultiplicativeExpression(&i ,NULL);
        expr->addRightOperand(oper, &multiplicativeExpression1);
        *j = i;
        return *expr;
    }
    ast::MultiplicativeExpression multiplicativeExpression = tryMultiplicativeExpression(&i, NULL);
    ast::AdditiveExpression additiveExpression = ast::AdditiveExpression(multiplicativeExpression);
    if((i+1)->first == AdditiveOp){
        tryAdditiveExpression(&(++i), &additiveExpression);
    }
    *j = i;
    return additiveExpression;

}

ast::RelationalExpression parser::tryRelationalExpression(std::vector<std::pair<tokenType, std::string>>::iterator* j, ast::RelationalExpression* expr){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == RelationalOp && expr != NULL){
        std::string oper = i->second;
        ++i;
        ast::AdditiveExpression additiveExpression1 = tryAdditiveExpression(&i ,NULL);
        expr->addRightOperand(oper, &additiveExpression1);
        *j = i;
        return *expr;
    }
    ast::AdditiveExpression additiveExpression = tryAdditiveExpression(&i, NULL);
    ast::RelationalExpression relationalExpression = ast::RelationalExpression(additiveExpression);
    if((i+1)->first == RelationalOp){
        tryRelationalExpression(&(++i), &relationalExpression);
    }
    *j = i;
    return relationalExpression;
}

ast::EqualityExpression parser::tryEqualityExpression(std::vector<std::pair<tokenType, std::string>>::iterator* j, ast::EqualityExpression* expr){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == EqualOp && expr != NULL){
        std::string oper = i->second;
        ++i;
        ast::RelationalExpression relationalExpression1 = tryRelationalExpression(&i ,NULL);
        expr->addRightOperand(oper, &relationalExpression1);
        *j = i;
        return *expr;
    }
    ast::RelationalExpression relationalExpression = tryRelationalExpression(&i, NULL);
    ast::EqualityExpression equalityExpression = ast::EqualityExpression(relationalExpression);
    if((i+1)->first == EqualOp){
        tryEqualityExpression(&(++i), &equalityExpression);
    }
    *j = i;
    return equalityExpression;
}

ast::AndExpression parser::tryAndExpression(std::vector<std::pair<tokenType, std::string>>::iterator* j, ast::AndExpression* expr){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == AndOp && expr != NULL){
        ++i;
        ast::EqualityExpression equalityExpression1 = tryEqualityExpression(&i ,NULL);
        expr->addRightOperand(&equalityExpression1);
        *j = i;
        return *expr;
    }
    ast::EqualityExpression equalityExpression = tryEqualityExpression(&i, NULL);
    ast::AndExpression andExpression = ast::AndExpression(equalityExpression);
    if((i+1)->first == AndOp){
        tryAndExpression(&(++i), &andExpression);
    }
    *j = i;
    return andExpression;
}

ast::Expression parser::tryExpression(std::vector<std::pair<tokenType, std::string>>::iterator* j, ast::Expression* expr){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == OrOp && expr != NULL){
        ++i;
        ast::AndExpression andExpression1 = tryAndExpression(&i ,NULL);
        expr->addRightOperand(&andExpression1);
        *j = i;
        return *expr;
    }
    ast::AndExpression andExpression = tryAndExpression(&i, NULL);
    ast::Expression expression = ast::Expression(andExpression);
    if((i+1)->first == OrOp){
        tryExpression(&(++i), &expression);
    }
    if(expr == NULL && expression.isGood())
        *j = ++i;
    else
        *j = i;
    return expression;
}

ast::Parameters parser::tryParameters(std::vector<std::pair<tokenType, std::string>>::iterator* j, scopeType scope){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    ast::Variable variable =  tryVariable(&i);
    if(i != *j){
        ast::Parameters params;
        params.addParameter(variable);
        symbolType type;
        if(variable._type == ast::Type:: Int)
            type = Integer;
        else if(variable._type == ast::Type:: Float)
            type = Floating;
        addSymbol(variable._id, type, scope);
        while(i->first == Comma){
            ++i;
            std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
            ast::Variable variable1 =  tryVariable(&i);
            if(i != iter) {
                params.addParameter(variable1);
                if(variable1._type == ast::Type:: Int)
                    type = Integer;
                else if(variable1._type == ast::Type:: Float)
                    type = Floating;
                addSymbol(variable1._id, type, scope);
            }
            else{
                showError(i->first, "Parameters", ",", "variable");
                return ast::Parameters();
            }
        }
        *j = i;
        return params;
    }
    return ast::Parameters();
}

ast::VarDeclaration parser::tryVarDeclaration(std::vector<std::pair<tokenType, std::string>>::iterator* j, scopeType scope){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if((i)->first == Var){
        ++(i);
        std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
        ast::Type type = tryType(&i);
        if(iter != i){
            iter = i;
            ast::AssignVar assignVar = tryAssignVar(&i);
            if(iter != i) {
                *j = i;
                symbolType type1;
                if(type == ast::Type::Int)
                    type1 = Integer;
                else if(type == ast::Type::Float)
                    type1 = Floating;
                addSymbol(assignVar.getId(), type1, scope);
                return ast::VarDeclaration(type, assignVar);
            }
            else{
                showError(i->first, "Variable declaration", toString(type), "assign variable");
                return ast::VarDeclaration();
            }
        }
        showError(i->first, "Variable declaration", "var", "variable type");
    }
    return ast::VarDeclaration();
}

ast::FunctionCall parser::tryFunctionCall(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == Id) {
        ast::Id id(i->second);
        ++i;
        if (i->first == ParentheseOpen) {
            ++i;
            std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
            ast::Elements elements = tryElements(&i);
            if (i != iter) {
                if (i->first == ParentheseClose) {
                    *j = ++i;
                    return ast::FunctionCall(id, elements);
                }
                else{
                    showError(i->first, "Function call", "elements", ")");
                    return ast::FunctionCall();
                }
            }
            else if(i->first == Func){
                if((++i)->first == Id){
                    ast::Id id1(i->second);
                    if((++i)->first == Arrow){
                        iter = ++i;
                        ast::Expression expression = tryExpression(&i, NULL);
                        if(iter != i){
                            if(i->first == ParentheseClose){
                                *j = ++i;
                                return ast::FunctionCall(id, id1, expression);
                            }
                            else{
                                showError(i->first, "Function call", "expression", "')'");
                                return ast::FunctionCall();
                            }
                        }
                        showError(i->first, "Function call", "->", "expression");
                        return ast::FunctionCall();
                    }
                    showError(i->first, "Function call", id1, "'->'");
                    return ast::FunctionCall();
                }
                showError(i->first, "Function call", "func", "variable name");
                return ast::FunctionCall();
            }
            else{
                showError(i->first, "Function call", "(", "elements or 'func'");
                return ast::FunctionCall();
            }
        }
    }
        ast::FunctionName functionName = tryFunctionName(&i);
        if (*j != i) {
            if (i->first == ParentheseOpen) {
                ++i;
                std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
                ast::Elements elements = tryElements(&i);
                if (i != iter) {
                    if (i->first == ParentheseClose) {
                        *j = ++i;
                        return ast::FunctionCall(functionName, elements);
                    }
                    else {
                        showError(i->first, "Function call", "elements", ")");
                        return ast::FunctionCall();
                    }
                }
                else if (i->first == Func) {
                    if ((++i)->first == Id) {
                        ast::Id id1(i->second);
                        if ((++i)->first == Arrow) {
                            iter = ++i;
                            ast::Expression expression = tryExpression(&i, NULL);
                            if (iter != i) {
                                if (i->first == ParentheseClose) {
                                    *j = ++i;
                                    return ast::FunctionCall(functionName, id1, expression);
                                } else {
                                    showError(i->first, "Function call", "expression", "')'");
                                    return ast::FunctionCall();
                                }
                            }
                            showError(i->first, "Function call", "->", "expression");
                            return ast::FunctionCall();
                        }
                        showError(i->first, "Function call", id1, "'->'");
                        return ast::FunctionCall();
                    }
                    showError(i->first, "Function call", "func", "variable name");
                    return ast::FunctionCall();
                }
                else {
                    showError(i->first, "Function call", "(", "elements or 'func'");
                    return ast::FunctionCall();
                }

            }
        }
    return ast::FunctionCall();


}

ast::FunctionName parser::tryFunctionName(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == FuncName){
        *j = ++i;
        return ast::functionNameFromString(i->second);
    }
}


ast::IfStatement parser::tryIfStatement(std::vector<std::pair<tokenType, std::string>>::iterator* j, scopeType scope){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == If){
        if((++i)->first == ParentheseOpen){
            ++i;
            std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
            ast::Expression expression = tryExpression(&i, NULL);
            if(iter != i) {
                if (i->first == ParentheseClose) {
                    if ((++i)->first == BraceOpen) {
                        iter = ++i;
                        ast::Statement statement = tryStatement(&i, scope);
                        if (i->first == BraceClose) {
                            *j = ++i;
                            return ast::IfStatement(expression, statement);
                        }
                        showError(i->first, "If statement", "", "}");
                        return ast::IfStatement();
                    }
                    showError(i->first, "If statement", ")", "{");
                    return ast::IfStatement();
                }
                showError(i->first, "If statement", "expression", ")");
                return ast::IfStatement();
            }
            showError(i->first, "If statement", "(", "expression");
            return ast::IfStatement();
        }
        showError(i->first, "If statement", "if", "(");
        return ast::IfStatement();
    }
    return ast::IfStatement();

}


ast::ElseStatement parser::tryElseStatement(std::vector<std::pair<tokenType, std::string>>::iterator* j, scopeType scope){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == Else){
        if((++i)->first == BraceOpen){
            ast::Statement statement = tryStatement(&(++i), scope);
            if(i->first == BraceClose){
                *j = ++i;
                return ast::ElseStatement(statement);
            }
            showError(i->first, "Else statement", "{", "}");
            return ast::ElseStatement();
        }
        else{
            std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
            ast::IfStatement ifStatement = tryIfStatement(&i, scope);
            if(iter != i){
                *j = i;
                return ast::ElseStatement(ifStatement);
            }
        }
        showError(i->first, "Else statement", "else", "{");
        return ast::ElseStatement();
    }
    return ast::ElseStatement();
}


ast::ReturnStatement parser::tryReturnStatement(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == Return){
        if((++i)->first == Id || i->first == IntVal || i->first == FloatVal){
            std::string val(i->second);
            *j = ++i;
            return ast::ReturnStatement(val);
        }
        showError(i->first, "Return statement", "return", "number or variable name");
        return ast::ReturnStatement();
    }
    return ast::ReturnStatement();
}

ast::Statement parser::tryStatement(std::vector<std::pair<tokenType, std::string>>::iterator* j, scopeType scope){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    ast::Operation operation = tryOperation(&i, scope);
    if(i != *j) {
        ast::Statement statement;
        do{
            *j = i;
            statement.addOperation(operation);
            operation = tryOperation(&i, scope);
        }while(i != *j);
        *j = i;
        return statement;
    }
    return ast::Statement();
}

ast::ForStatement parser::tryForStatement(std::vector<std::pair<tokenType, std::string>>::iterator* j){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == For && (++i)->first == ParentheseOpen) {
        ast::ForStatement forStatement;
        if ((++i)->first == Id) {
            ast::Id id(i->second);
            forStatement.addInitId(id);                                //for(id,...
            if ((++i)->first == Comma) {
                ++i;
                std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
                ast::Expression expression = tryExpression(&i, NULL);
                if (iter != i && i->first == Comma && (++i)->first == Id) {
                    forStatement.addCondition(expression);              //for(id, expression, ...
                    id = ast::Id(i->second);
                    if ((++i)->first == AssigOp) {
                        iter = ++i;
                        expression = tryExpression(&i, NULL);
                        if (iter != i){
                            if(i->first == ParentheseClose) {
                            forStatement.addIncrement(id, expression);          //for(id, expression, id=expression)
                            }
                            else {
                                showError(i->first, "For statement", "expression", ")");
                                return ast::ForStatement();
                            }
                        }
                        else {
                            showError(i->first, "For statement", "=", "expression");
                            return ast::ForStatement();
                        }
                    }
                    else {
                        showError(i->first, "For statement", id, "=");
                        return ast::ForStatement();
                    }
                }
                else{
                    showError(i->first, "For statement", "expression", ",");
                    return ast::ForStatement();
                }
            }
            else if (i->first == AssigOp) {
                ++i;
                std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
                ast::Expression expression = tryExpression(&i, NULL);
                if (iter != i) {
                    if(i->first == Comma)
                    {
                        forStatement.addInitExpression(expression);             //for(id=expression, ...
                        iter = ++i;
                        expression = tryExpression(&i, NULL);
                        if (iter != i && i->first == Comma && (++i)->first == Id) {
                            forStatement.addCondition(expression);              //for(id=expression, expression, ...
                            id = ast::Id(i->second);
                            if ((++i)->first == AssigOp) {
                                iter = ++i;
                                expression = tryExpression(&i, NULL);
                                if (iter != i && i->first == ParentheseClose) {
                                    forStatement.addIncrement(id, expression);          //for(id=expression, expression, id=expression)
                                }
                                else {
                                    showError(i->first, "For statement", "expression", ")");
                                    return ast::ForStatement();
                                }
                            }
                            else {
                                showError(i->first, "For statement", id, "=");
                                return ast::ForStatement();
                            }
                        }
                        else {
                            showError(i->first, "For statement", "expression", ",");
                            return ast::ForStatement();
                        }
                    }
                    else{
                        showError(i->first, "For statement", "expression", ",");
                        return ast::ForStatement();
                    }
                }
            }
        }
        else {
            std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
            ast::VarDeclaration varDeclaration = tryVarDeclaration(&i, scopeType::forStatement);
            if (iter != i){
                if(i->first == Comma) {
                    forStatement.addInitVarDeclaration(varDeclaration);             //for(type id=expression, ...
                    iter = ++i;
                    ast::Expression expression = tryExpression(&i, NULL);
                    if (iter != i && i->first == Comma && (++i)->first == Id) {
                        forStatement.addCondition(expression);              //for(type id=expression, expression, ...
                        ast::Id id = ast::Id(i->second);
                        if ((++i)->first == AssigOp) {
                            iter = ++i;
                            expression = tryExpression(&i, NULL);
                            if (iter != i && i->first == ParentheseClose) {
                                forStatement.addIncrement(id, expression);          //for(type id=expression, expression, id=expression)
                            }
                            else {
                                showError(i->first, "For statement", "expression", ")");
                                return ast::ForStatement();
                            }
                        }
                        else {
                            showError(i->first, "For statement", id, "=");
                            return ast::ForStatement();
                        }
                    }
                    else {
                        showError(i->first, "For statement", "variable", ",");
                        return ast::ForStatement();
                    }
                }
            }
        }
        if((++i)->first = BraceOpen){
            std::vector<std::pair<tokenType, std::string>>::iterator iter = ++i;
            ast::Statement statement = tryStatement(&i, blockLocal);
            if(iter != i) {
                if (i->first == BraceClose) {
                    forStatement.addStatement(statement);
                    *j = ++i;
                    return forStatement;
                }
                else {
                    showError(i->first, "For statement", "", "}");
                    return ast::ForStatement();
                }
            }
        }
    }
    return  ast::ForStatement();

}


ast::Operation parser::tryOperation(std::vector<std::pair<tokenType, std::string>>::iterator* j, scopeType scope){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    ast::ListDeclaration listDeclaration = tryListDeclaration(&i, scope);
    if(i != *j){
        if(i->first == Semicolon){
            *j = ++i;
            return ast::Operation(listDeclaration);
        }
        else
            std::cerr << "Missing semicolon" << std::endl;
    }
    else{
        std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
        ast::IfStatement ifStatement = tryIfStatement(&i ,scope);
        if(iter != i){
            ast::Operation operation(ifStatement);
            while(iter != i && i != end){
                ast::ElseStatement elseStatement= tryElseStatement(&i, scope);
                if(iter != i)
                    operation.addElseStatement(elseStatement);

            }
            *j = i;
            return operation;
        }
        else{
            iter = i;
            ast::ForStatement forStatement = tryForStatement(&i);
            if(iter != i) {
                *j = i;
                return ast::Operation(forStatement);
            }
            else{
                ast::AssignVar assignVar = tryAssignVar(&i);
                if(iter != i){
                    if ((i)->first == Semicolon) {
                        *j = ++i;
                        return ast::Operation(assignVar);
                    }
                    else
                        std::cerr << "Missing semicolon" << std::endl;
                }
                else{
                    ast::VarDeclaration varDeclaration = tryVarDeclaration(&i, scope);
                    if(iter != i){
                        if ((i)->first == Semicolon) {
                            *j = ++i;
                            return ast::Operation(varDeclaration);
                        }
                        else
                            std::cerr << "Missing semicolon" << std::endl;
                    }
                    else{
                        ast::FunctionCall functionCall = tryFunctionCall(&i);
                        if(iter != i){
                            if ((i)->first == Semicolon) {
                                *j = ++i;
                                return ast::Operation(functionCall);
                            }
                            else
                                std::cerr << "Missing semicolon" << std::endl;
                        }
                        else{
                            ast::FunctionDeclaration functionDeclaration = tryFunctionDeclaration(&i, scope);
                            if(iter != i){
                                *j = i;
                                return ast::Operation(functionDeclaration);
                            }
                            else{
                                ast::Expression expression = tryExpression(&i, NULL);
                                if(iter != i){
                                    if ((i)->first == Semicolon) {
                                        *j = ++i;
                                        return ast::Operation(expression);
                                    }
                                    else
                                        std::cerr << "Missing semicolon" << std::endl;
                                }
                                else{
                                    ast::ReturnStatement returnStatement = tryReturnStatement(&i);
                                    if(iter != i){
                                        if ((i)->first == Semicolon) {
                                            *j = ++i;
                                            return ast::Operation(returnStatement);
                                        }
                                        else
                                            std::cerr << "Missing semicolon" << std::endl;
                                    }
                                }

                            }
                        }
                    }
                }
            }
        }
    }
    return ast::Operation();
}

ast::FunctionDeclaration parser::tryFunctionDeclaration(std::vector<std::pair<tokenType, std::string>>::iterator* j, scopeType scope){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    addSymbol("", (symbolType) 0, (scopeType) 0);
    scopeType scopeLocal = funcParam;
    if(i->first == Func){
        if((++i)->first == Id){
            ast::Id id(i->second);
            if((++i)->first == Colon){
                ++i;
                std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
                ast::Type type = tryType(&i);
                if(i != iter){
                    if(i->first == ParentheseOpen){
                        iter = ++i;
                        ast::Parameters parameters = tryParameters(&i, scopeLocal);
                            if(i->first == ParentheseClose && (++i)->first == BraceOpen){
                                iter = ++i;
                                scopeLocal = blockLocal;
                                ast::Statement statement = tryStatement(&i, scopeLocal);
                                if(i->first == BraceClose){
                                    *j = ++i;
                                    symbolType type1;
                                    if(type == ast::Type:: Int)
                                        type1 = IntFunc;
                                    else if(type == ast::Type:: Float)
                                        type1 = FloatFunc;
                                    addSymbol(id, type1, scope);
                                    return ast::FunctionDeclaration(id, type, parameters, statement);
                                }
                                showError(i->first, "Function declaration", "", "}");
                                return ast::FunctionDeclaration();
                            }
                            showError(i->first, "Function declaration", "parameters", ")");
                            return ast::FunctionDeclaration();
                    }
                    showError(i->first, "Function declaration", toString(type), "(");
                    return ast::FunctionDeclaration();
                }
                else if(i->first == List){
                    ++i;
                    iter = i;
                    ast::Type type = tryType(&i);
                    if(iter != i) {
                        if ((++i)->first == ParentheseOpen) {
                            iter = ++i;
                            ast::Parameters parameters = tryParameters(&i, scopeLocal);
                            if (i->first == ParentheseClose && (++i)->first == BraceOpen) {
                                iter = ++i;
                                scopeLocal = blockLocal;
                                ast::Statement statement = tryStatement(&i, scope);
                                iter = i;
                                ast::ReturnStatement returnStatement = tryReturnStatement(&i);
                                if (iter != i) {
                                    if (i->first == BraceClose) {
                                        *j = ++i;
                                        addSymbol(id, IntListFunc, scope);
                                        return ast::FunctionDeclaration(id, parameters, statement);
                                    }
                                    else {
                                        showError(i->first, "Function declaration", "", "}");
                                        return ast::FunctionDeclaration();
                                    }
                                }
                                else {
                                    showError(i->first, "Function declaration", "", "returnStatement");
                                    return ast::FunctionDeclaration();
                                }
                            }
                            else {
                                showError(i->first, "Function declaration", "parameters", ")");
                                return ast::FunctionDeclaration();
                            }
                        }
                        else {
                            showError(i->first, "Function declaration", toString(type), "(");
                            return ast::FunctionDeclaration();
                        }
                    }
                    else {
                        showError(i->first, "Function declaration", "list", "type");
                        return ast::FunctionDeclaration();
                    }
                }
                else {
                    showError(i->first, "Function declaration", ":", "type or 'list'");
                    return ast::FunctionDeclaration();
                }
            }
            else {
                showError(i->first, "Function declaration", id, ":");
                return ast::FunctionDeclaration();
            }
        }
        else {
            showError(i->first, "Function declaration", "func", ":");
            return ast::FunctionDeclaration();
        }
    }
    return ast::FunctionDeclaration();
}




ast::ListDeclaration parser::tryListDeclaration(std::vector<std::pair<tokenType, std::string>>::iterator* j, scopeType scope){
    std::vector<std::pair<tokenType, std::string>>::iterator i = *j;
    if(i->first == List){
        ++i;
        std::vector<std::pair<tokenType, std::string>>::iterator iter = i;
        ast::Variable variable = tryVariable(&i);
        if(iter != i && i->first == AssigOp){            //list variable =
            if((++i)->first == BraceOpen){                   //list variable = {
                iter = ++i;
                ast::Elements elements = tryElements(&i);
                if(iter != i && i->first == BraceClose){     //list variable = { elements }
                    *j = ++i;
                    symbolType type1;
                    if(variable._type == ast::Type::Int)
                        type1 = IntList;
                    else if(variable._type == ast::Type::Float)
                        type1 = FloatList;
                    addSymbol(variable._id, type1, scope);
                    return ast::ListDeclaration(variable, elements);
                }
                showError(i->first, "List declaration", "elements", "}");
                return ast::ListDeclaration();
            }
            else if(i->first == Id){                         //list variable = id
                ast::Id id(i->second);
                iter = ++i;
                ast::Range range = tryRange(&i);
                if(iter != i){                                  //list variable = id range
                    *j = i;
                    symbolType type1;
                    if(variable._type == ast::Type::Int)
                        type1 = IntList;
                    else if(variable._type == ast::Type::Float)
                        type1 = FloatList;
                    addSymbol(variable._id, type1, scope);
                    return ast::ListDeclaration(variable, id, range);
                }
                else{                                           //list variable = id
                    *j = i;
                    symbolType type1;
                    if(variable._type == ast::Type::Int)
                        type1 = IntList;
                    else if(variable._type == ast::Type::Float)
                        type1 = FloatList;
                    addSymbol(variable._id, type1, scope);
                    return ast::ListDeclaration(variable, id);
                }
            }
            iter = i;
            ast::FunctionCall functionCall = tryFunctionCall(&i);
            if(iter != i){                                      //list variable = functionCall
                *j = i;
                symbolType type1;
                if(variable._type == ast::Type::Int)
                    type1 = IntList;
                else if(variable._type == ast::Type::Float)
                    type1 = FloatList;
                addSymbol(variable._id, type1, scope);
                return ast::ListDeclaration(variable, functionCall);
            }
            showError(i->first, "List declaration", "=", "'{' , variable name or function call");
            return ast::ListDeclaration();
        }
        showError(i->first, "List declaration", "variable", "=");
        return ast::ListDeclaration();
    }
    return ast::ListDeclaration();
}


int parser::semanticAnalysis(){
    std::vector<ast::Operation>::iterator i = program._operations.begin();
    for(i; i != program._operations.end(); ++i){
//        if(*i )
    }
}

int parser::addSymbol(std::string name, symbolType type, scopeType scope){
    Symbol s;
    s.name = name;
    s.type = type;
    s.scope = scope;
    symbols.push_back(s);
    return (int)(symbols.size()-1);
}