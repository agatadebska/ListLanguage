//
// Created by agata on 05.06.15.
//

#include "scanner.h"
#include "../../ast/Flag.h"

scanner::scanner(std::string fileName){
    _ioModule.openFile(fileName);
    strncpy(symbols, "-+*/%<>&|[]:{}()., ;=", 22);
}

int scanner::tokenize() {

    while(!_ioModule.inFile.eof()){
        token = "";
        ignoreWhitespaces();
        char peek = _ioModule.peekChar();
        char c;

        //----------------------------------not number
      if(isdigit(peek)) {
          tryNumber();
      }
      else {
          switch (peek) {
              case 'v' :
                  tryV();
                  break;
              case 'f' :
                  tryF();
                  break;
              case 'm' :
                  tryM();
                  break;
              case 'p' :
                  tryP();
                  break;
              case 'i' :
                  tryI();
                  break;
              case 'e' :
                  tryE();
                  break;
              case 'r' :
                  tryR();
                  break;
              case 'l' :
                  tryL();
                  break;
              case '-' :
                  token += _ioModule.getChar();
                  c = _ioModule.peekChar();
                  if (c == '>') {
                      token += _ioModule.getChar();
                      addToken(tokenType::Arrow);
                  }
                  else
                      addToken(tokenType::AdditiveOp);
                  break;
              case '+' :
                  token += _ioModule.getChar();
                  addToken(tokenType::AdditiveOp);
                  break;
              case '*':
                  token += _ioModule.getChar();
                  addToken(tokenType::MultiplOp);
                  break;
              case '/':
                  token += _ioModule.getChar();
                  addToken(tokenType::MultiplOp);
                  break;
              case '%':
                  token += _ioModule.getChar();
                  addToken(tokenType::MultiplOp);
                  break;
              case '<' :
                  token += _ioModule.getChar();
                  c = _ioModule.peekChar();
                  if (c == '=') {
                      token += _ioModule.getChar();
                      addToken(tokenType::RelationalOp);
                  }
                  else
                      addToken(tokenType::RelationalOp);
                  break;
              case '>' :
                  token += _ioModule.getChar();
                  c = _ioModule.peekChar();
                  if (c == '=') {
                      token += _ioModule.getChar();
                      addToken(tokenType::RelationalOp);
                  }
                  else
                      addToken(tokenType::RelationalOp);
                  break;
              case '&' :
                  token += _ioModule.getChar();
                  c = _ioModule.peekChar();
                  if (c == '&') {
                      token += _ioModule.getChar();
                      addToken(tokenType::AndOp);
                  }
                  break;
              case '|' :
                  token += _ioModule.getChar();
                  c = _ioModule.peekChar();
                  if (c == '|') {
                      token += _ioModule.getChar();
                      addToken(tokenType::OrOp);
                  }
                  break;
              case '=' :
                  token += _ioModule.getChar();
                  c = _ioModule.peekChar();
                  if (c == '=') {
                      token += _ioModule.getChar();
                      addToken(tokenType::EqualOp);
                  }
                  addToken(tokenType::AssigOp);
                  break;
              case '[' :
                  token += _ioModule.getChar();
                  addToken(tokenType::SquareBraceOpen);
                  break;
              case ']' :
                  token += _ioModule.getChar();
                  addToken(tokenType::SquareBraceClose);
                  break;
              case ':' :
                  token += _ioModule.getChar();
                  addToken(tokenType::Colon);
                  break;
              case ',' :
                  token += _ioModule.getChar();
                  addToken(tokenType::Comma);
                  break;
              case '.' :
                  token += _ioModule.getChar();
                  addToken(tokenType::Dot);
                  break;
              case '{' :
                  token += _ioModule.getChar();
                  addToken(tokenType::BraceOpen);
                  break;
              case '}' :
                  token += _ioModule.getChar();
                  addToken(tokenType::BraceClose);
                  break;
              case '(' :
                  token += _ioModule.getChar();
                  addToken(tokenType::ParentheseOpen);
                  break;
              case ')' :
                  token += _ioModule.getChar();
                  addToken(tokenType::ParentheseClose);
                  break;
              case ';' :
                  token += _ioModule.getChar();
                  addToken(tokenType::Semicolon);
                  break;
              case '!' :
                  token += _ioModule.getChar();
                  c = _ioModule.peekChar();
                  if (c == '=') {
                      token += _ioModule.getChar();
                      addToken(tokenType::EqualOp);
                  }
                  break;
              default:
                  tryId();
          }
      }

    }
}

void scanner::addToken(tokenType _type){
    if(_type < 8)
        _tokens.push_back(std::make_pair(_type, token));
    else
        _tokens.push_back(std::make_pair(_type, ""));
}

void scanner::ignoreWhitespaces() {
    while (std::isspace(_ioModule.inFile.peek()))
        _ioModule.getChar();
}

void scanner::tryV(){
    char peek;
    token += _ioModule.getChar();
    peek = _ioModule.peekChar();
    if (peek == 'a') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if (peek == 'r') {
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if (peek == ' ') {
               // _ioModule.getChar();
                addToken(tokenType::Var);
                return;
            }
        }
    }
    tryId();
}

void scanner::tryF(){
    char peek;
    token += _ioModule.getChar();
    peek = _ioModule.peekChar();
    if(peek == 'l') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if (peek == 'o') {
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if (peek == 'a') {
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if (peek == 't') {
                    token += _ioModule.getChar();
                    peek = _ioModule.peekChar();
                    if (peek == ' ') {
                       // _ioModule.getChar();
                        addToken(tokenType::Float);
                        return;
                    }
                }
            }
        }
    }
    else if(peek == 'o'){
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if(peek == 'r'){
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == ' ' || peek == '('){
              //  _ioModule.getChar();
                addToken(tokenType::For);
                return;
            }
        }
    }
    else if(peek == 'u'){
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if(peek == 'n'){
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == 'c'){
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if(peek == ' '){
                    addToken(tokenType::Func);
                    return;
                }
            }
        }
    }
    else if(peek == 'i'){
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if(peek == 'l') {
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == 't'){
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if(peek == 'e'){
                    token += _ioModule.getChar();
                    peek = _ioModule.peekChar();
                    if(peek == 'r') {
                        token += _ioModule.getChar();
                        peek = _ioModule.peekChar();
                        if(peek == ' ' || peek == '('){
                            addToken(tokenType::FuncName);
                            return;
                        }
                    }
                }
            }
        }
    }
    tryId();
}

void scanner::tryI(){
    char peek;
    token += _ioModule.getChar();
    peek = _ioModule.peekChar();
    if(peek == 'n') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if(peek == 't'){
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == ' '){
                addToken(tokenType::Int);
                return;
            }
        }
    }
    else if(peek == 'f'){
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if(peek == ' ' || peek == '('){
            addToken(tokenType::If);
            return;
        }
    }
    tryId();
}

void scanner::tryE(){
    char peek;
    token += _ioModule.getChar();
    peek = _ioModule.peekChar();
    if(peek == 'l') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if(peek = 's'){
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == 'e'){
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if(peek == ' ' || peek == '{'){
                    addToken(tokenType::Else);
                    return;
                }
            }
        }
    }
    tryId();
}

void scanner::tryR(){
    char peek;
    token += _ioModule.getChar();
    peek = _ioModule.peekChar();
    if(peek == 'e') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if (peek = 't') {
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == 'u'){
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if(peek == 'r'){
                    token += _ioModule.getChar();
                    peek = _ioModule.peekChar();
                    if(peek == 'n'){
                        token += _ioModule.getChar();
                        peek = _ioModule.peekChar();
                        if(peek == ' '){
                            addToken(tokenType::Return);
                            return;
                        }
                    }
                }
            }
        }
    }
    tryId();
}

void scanner::tryL(){
    char peek;
    token += _ioModule.getChar();
    peek = _ioModule.peekChar();
    if(peek == 'i') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if(peek == 's'){
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == 't'){
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if(peek == ' '){
                    addToken(tokenType::List);
                    return;
                }
            }
        }
    }
    else if(peek == 'e'){
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if(peek == 'n') {
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == 'g'){
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if(peek == 't'){
                    token += _ioModule.getChar();
                    peek = _ioModule.peekChar();
                    if(peek == 'h') {
                        token += _ioModule.getChar();
                        peek = _ioModule.peekChar();
                        if(peek == ' ' || peek == '('){
                            addToken(tokenType::FuncName);
                            return;
                        }
                    }
                }
            }
        }
    }
    tryId();
}

void scanner::tryP(){
    char peek;
    token += _ioModule.getChar();
    peek = _ioModule.peekChar();
    if(peek == 'r') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if (peek == 'i') {
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if (peek == 'n') {
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if (peek == 't') {
                    token += _ioModule.getChar();
                    peek = _ioModule.peekChar();
                    if (peek == ' ') {
                        // _ioModule.getChar();
                        addToken(tokenType::FuncName);
                        return;
                    }
                }
            }
        }
    }
    tryId();
}

void scanner::tryM(){
    char peek;
    token += _ioModule.getChar();
    peek = _ioModule.peekChar();
    if(peek == 'e') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if (peek == 'r') {
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if (peek == 'g') {
                token += _ioModule.getChar();
                peek = _ioModule.peekChar();
                if (peek == 'e') {
                    token += _ioModule.getChar();
                    peek = _ioModule.peekChar();
                    if(peek == ' ' || peek == '('){
                        addToken(tokenType::FuncName);
                        return;
                    }
                }
            }
        }
    }
    else if (peek == 'a') {
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
        if (peek == 'p') {
            token += _ioModule.getChar();
            peek = _ioModule.peekChar();
            if(peek == ' ' || peek == '('){
                addToken(tokenType::FuncName);
                return;
            }
        }
    }
    tryId();
}


void scanner::tryId(){
    if(_ioModule.eof())
        return;
    char peek = _ioModule.peekChar();
    while(strchr(symbols, peek) == nullptr){
        token += _ioModule.getChar();
        peek = _ioModule.peekChar();
    }
    addToken(tokenType::Id);
}

void scanner::tryNumber() {
    char peek = _ioModule.peekChar();
    while(isdigit(peek) && strchr(symbols, peek) == nullptr){
        token+= _ioModule.getChar();
        peek = _ioModule.peekChar();
    }
    if(peek == '.'){
        token+= _ioModule.getChar();
        peek = _ioModule.peekChar();
        while(isdigit(peek) && strchr(symbols, peek) == nullptr){
            token+= _ioModule.getChar();
            peek = _ioModule.peekChar();
        }
        addToken(tokenType::FloatVal);
    }
    else
        addToken(tokenType::IntVal);
}


void scanner::printTokens(){
   // std::vector<tokenType>::iterator i = _tokensTypes.begin();
    std::vector<std::pair<tokenType, std::string>>::iterator i = _tokens.begin();
    for(i; i!=_tokens.end(); ++i){
        std::cout << (*i).first << "        " << (*i).second << std::endl;
    }
}

std::string toString(tokenType& tok){
    switch(tok){
        case Int:
            return "int";
        case Float:
            return "float";
        case AndOp:
            return "&&";
        case OrOp:
            return "||";
        case AssigOp:
            return "=";
        case Comma:
            return ",";
        case Dot:
            return ".";
        case Colon:
            return ":";
        case Semicolon:
            return ";";
        case Var:
            return "var";
        case If:
            return "if";
        case Else:
            return "else";
        case For:
            return "for";
        case List:
            return "list";
        case Func:
            return "func";
        case Return:
            return  "return";
        case Arrow:
            return  "->";
        case ParentheseOpen:
            return "(";
        case ParentheseClose:
            return  ")";
        case BraceOpen:
            return  "{";
        case BraceClose:
            return "}";
        case SquareBraceOpen:
            return "[";
        case SquareBraceClose:
            return "]";
        default:
            "unknown";
    }
}