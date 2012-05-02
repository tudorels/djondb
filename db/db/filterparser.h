// =====================================================================================
//  Filename:  filterparser.h
// 
//  Description: This is the definition of the filterparser class which analyze where expressions
//               and execute filters over elements.
// 
//  Version:  1.0
//  Created:  04/24/2012 09:45:47 AM
//  Revision:  none
//  Compiler:  gcc
// 
//  Author:  Juan Pablo Crossley (crossley@gmail.com), 
// 
// License:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// =====================================================================================

#ifndef INCLUDE_FILTERPARSER_H
#define INCLUDE_FILTERPARSER_H

#include <string>
#include <vector>
#include <list>

class BSONObj;

enum FILTER_OPERATORS {
	FO_NOTOPERATOR,
	FO_TOKEN,
	FO_AND,
	FO_OR,
	FO_EQUALS,
	FO_NOT_EQUALS,
	FO_PARENTESIS_OPEN,
	FO_PARENTESIS_CLOSE,
	FO_NOT
};

enum EXPRESSION_TYPE {
	ET_CONSTANT,
	ET_SIMPLE,
	ET_BINARY,
	ET_UNARY
};

enum RESULT_TYPE {
	RT_INT,
	RT_DOUBLE,
	RT_BOOLEAN,
	RT_STRING,
	RT_BSON
};

enum TOKEN_TYPE {
	TT_EXPRESION,
	TT_OPENPARENTESIS,
	TT_CLOSEPARENTESIS,
	TT_CONSTANT,
	TT_EQUALS,
	TT_AND
};

class Token {
	public:
		Token(TOKEN_TYPE type, const std::string& content) {
			_content = new std::string(content);
			_type = type;
		}

		Token(TOKEN_TYPE type) {
			_content = NULL;
			_type = type;
		}

		Token(const Token& orig) {
			if (orig._content != NULL) 
				_content = new std::string(*orig._content);
			else
				_content = NULL;
			_type = orig._type;
		}

		~Token() {
			if (_content != NULL) delete _content;
		}

		TOKEN_TYPE type() { return _type; }
		std::string* content() {
			return _content;
		}

	private:
		std::string* _content;
		TOKEN_TYPE _type;
};

class ExpressionResult {
	public:
		ExpressionResult(RESULT_TYPE type, void* value);
		ExpressionResult(const ExpressionResult& orig);
		~ExpressionResult();

		RESULT_TYPE type();
		void* value();

	private:
		void* _value;
		RESULT_TYPE _type;
};

class BaseExpression {
	public:
		BaseExpression(EXPRESSION_TYPE type) {
			_type = type;
		}

		EXPRESSION_TYPE type() {
			return _type;
		}

		virtual ExpressionResult* eval(const BSONObj& bson) = 0;
		virtual BaseExpression* copyExpression() = 0;
	private:
		EXPRESSION_TYPE _type;
};

class ConstantExpression: public BaseExpression {
	public:
		ConstantExpression(const std::string& expression);
		ConstantExpression(const ConstantExpression& orig);
		~ConstantExpression();

		virtual ExpressionResult* eval(const BSONObj& bson);
		virtual BaseExpression* copyExpression();
	private:
		std::string _expression;
		ExpressionResult* _value;

	private:
		void parseConstantExpression();
};

class SimpleExpression: public BaseExpression {
	public:
		SimpleExpression(const std::string& expression);
		SimpleExpression(const SimpleExpression& orig);

		virtual ExpressionResult* eval(const BSONObj& bson);
		virtual BaseExpression* copyExpression();
	private:
		std::string _expression;
};

class BinaryExpression: public BaseExpression {
	public:
		BinaryExpression(FILTER_OPERATORS oper);
		BinaryExpression(const BinaryExpression& orig);

		void push(BaseExpression* expression);

		virtual ExpressionResult* eval(const BSONObj& bson);
		virtual BaseExpression* copyExpression();

		FILTER_OPERATORS oper() const;
	private:
		FILTER_OPERATORS _oper;
		BaseExpression* _left;
		BaseExpression* _right;
};

class UnaryExpression: public BaseExpression {
	public:
		UnaryExpression(FILTER_OPERATORS oper);
		UnaryExpression(const UnaryExpression& orig);

		virtual ExpressionResult* eval(const BSONObj& bson);
		virtual BaseExpression* copyExpression();
		void push(BaseExpression* expression);

	private:
		FILTER_OPERATORS _oper;
		BaseExpression* _expression;
};

class FilterParser {
	public:
		FilterParser(const FilterParser& orig);
		~FilterParser();
		ExpressionResult* eval(const BSONObj& bson);
		
		static FilterParser* parse(const std::string& expression);

	private:
		FilterParser(const std::string& expression, BaseExpression* root);

	private:
		std::string _expression;
	   BaseExpression* _root;

};
#endif // INCLUDE_FILTERPARSER_H
