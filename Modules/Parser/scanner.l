/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

%{
	#include <iostream>
	#include <cstdlib>
	#include "scanner.h"
	#include "interpreter.h"
	#include "parser.hpp"
	#include "location.hh"

	using namespace std;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() ParserModule::Parser::make_END(ParserModule::location());

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver.increaseLocation(yyleng);
	
	// !!!WARNING!!!
	// Location API is used, but the location is not initialized, 'cause I'm lazy. When making
	// a token with make_{something} method you can pass detailed token location. Current location
	// is accessible with m_driver.location() method. All puzzle elements are there - just
	// pass location value in every action code block below. I'm going to waste more time writing
	// this excuse than putting this boilerplate below...
	//
	// Location class can be found in location.hh and posistion.hh files. It's just a bit too much
	// boilerplate for this small example. Bummer.
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="ParserModule_"

%%
[ \t\n]+                        ;
"select"                        {
                                    return ParserModule::Parser::make_SELECT(ParserModule::location());
                                }
"insert"                        {
									//std::cout << "Got INSERT" << std::endl;
                                    return ParserModule::Parser::make_INSERT(ParserModule::location());
                                }
"delete"                        {
                                    return ParserModule::Parser::make_DELETE(ParserModule::location());
                                }
"first_name"                    {
									//std::cout << "Got first_name" << std::endl;
                                    return ParserModule::Parser::make_PARAM(yytext, ParserModule::location());
                                }
"last_name"                     {
									//std::cout << "Got last_name" << std::endl;
                                    return ParserModule::Parser::make_PARAM(yytext, ParserModule::location());
                                }
"city"                          {
									//std::cout << "Got city" << std::endl;
                                    return ParserModule::Parser::make_PARAM(yytext, ParserModule::location());
                                }
"group"                         {
									//std::cout << "Got group" << std::endl;
                                    return ParserModule::Parser::make_PARAM(yytext, ParserModule::location());
                                }
"settled"                       {
									//std::cout << "Got settled" << std::endl;
                                    return ParserModule::Parser::make_PARAM(yytext, ParserModule::location());
                                }
";"                             {
									//std::cout << "Got semicolon" << std::endl;
                                    return ParserModule::Parser::make_SEMICOLON(ParserModule::location());
                                }
"="                             {   //std::cout << "Got equal" << std::endl;
                                    return ParserModule::Parser::make_EQ(ParserModule::location());
                                }
"all"                           {	//std::cout << "Got all" << std::endl;
                                    return ParserModule::Parser::make_ALL(ParserModule::location());
                                }
<<EOF>>     					{	//std::cout << "EOF" << std::endl;
								   	return ParserModule::Parser::make_END(ParserModule::location()); }
[a-zA-Z0-9абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ]+                    {   //std::cout << "Got value = " << yytext << std::endl;
                                    return ParserModule::Parser::make_VALUE(yytext, ParserModule::location());
                                }

%%
