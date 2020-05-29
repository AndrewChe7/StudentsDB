%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define api.parser.class { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { ParserModule }
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "AST.h"

    namespace ParserModule {
        class Scanner;
        class Interpreter;
    }
}

// Bison calls yylex() function that must be provided by us to suck tokens
// from the scanner. This block will be placed at the beginning of IMPLEMENTATION file (cpp).
// We define this function here (function! not method).
// This function is called only inside Bison, so we make it static to limit symbol visibility for the linker
// to avoid potential linking conflicts.
%code top
{
    #include <iostream>
    #include "scanner.h"
    #include "parser.hpp"
    #include "interpreter.h"
    #include "location.hh"
    
    // yylex() arguments are defined in parser.y
    static ParserModule::Parser::symbol_type yylex(ParserModule::Scanner &scanner, ParserModule::Interpreter &driver) {
        return scanner.get_next_token();
    }
    
    // you can accomplish the same thing by inlining the code using preprocessor
    // x and y are same as in above static function
    // #define yylex(x, y) scanner.get_next_token()
    
    using namespace ParserModule;
}

%lex-param { ParserModule::Scanner &scanner }
%lex-param { ParserModule::Interpreter &driver }
%parse-param { ParserModule::Scanner &scanner }
%parse-param { ParserModule::Interpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "END";
%token SELECT "select";
%token DELETE "delete";
%token INSERT "insert";
%token NEWLINE "new line";
%token <std::string> VALUE "value";
%token <std::string> PARAM "param";
%token SEMICOLON ";";
%token EQ "=";
%token ALL "all";

%type<AST::Operation*> OPERATION
%type<AST::Operation*> OP
%type<AST::Operation*> COMMAND
%type<AST::Param> ARG

%start PROGRAM

%%
PROGRAM:        OPERATIONS END              {}
;
OPERATIONS:     OPERATION                   {driver.add_operation($1);}
|               OPERATIONS OPERATION        {driver.add_operation($2);}
;
OPERATION:      OP SEMICOLON                {$$ = $1;}
|               COMMAND ALL SEMICOLON       {$$ = $1;}
;
OP:             OP ARG                      {$1->addParam($2);
                                            $$ = $1;}
|               COMMAND ARG                 {$1->addParam($2);
                                            $$ = $1;}
;
ARG:            PARAM EQ VALUE              {
                                            std::string& name = $1;
                                            std::string& val = $3;
                                            $$ = AST::Param(name, val);}
;
COMMAND:        SELECT                      {$$ = new AST::OperationSelect();}
|               DELETE                      {$$ = new AST::OperationDelete();}
|               INSERT                      {$$ = new AST::OperationInsert();}
;

%%

// Bison expects us to provide implementation - otherwise linker complains
void ParserModule::Parser::error(const location &loc , const std::string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << "Error: " << message << endl << "Location: " << loc << endl;
	
        std::cout << "Error: " << message << std::endl << "Error location: " << driver.location() << std::endl;
}
