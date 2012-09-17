// =====================================================================================
//  Filename:  simpleexpression.cpp
// 
//  Description: Implementation of the "Simple" expressions, like simple xpaths
// 
//  Version:  1.0
//  Created:  04/24/2012 10:42:09 AM
//  Revision:  none
//  Compiler:  gcc
// 
//  Author:  YOUR NAME (), 
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


#include "filterparser.h"
#include "bson.h"

SimpleExpression::SimpleExpression(const std::string& expression)
	:BaseExpression(ET_SIMPLE)
{
	_expression = expression;
}

SimpleExpression::SimpleExpression(const SimpleExpression& orig)
	:BaseExpression(ET_SIMPLE)
{
	_expression = orig._expression;
}

SimpleExpression::~SimpleExpression() {
}

ExpressionResult* SimpleExpression::eval(const BSONObj& bson) {
	std::string expression = _expression.substr(2, _expression.length() - 3);
	BSONContent content = bson.getXpath(expression);

	RESULT_TYPE type;
	ExpressionResult* result = NULL;
	switch (content.type()) {
		case INT_TYPE:
			{
				type = RT_INT;
				int i = (int)content;
				result = new ExpressionResult(type, &i);
				break;
			}
		case DOUBLE_TYPE:
			{
				type = RT_DOUBLE;
				double d = (double)content;
				result = new ExpressionResult(type, &d);
				break;
			}
		case STRING_TYPE:
		case PTRCHAR_TYPE:
			{
				type = RT_STRING;
				std::string s = (std::string)content;
				result = new ExpressionResult(type, &s);
				break;
			}
		case NULL_TYPE:
			{
				type = RT_NULL;
				result = new ExpressionResult(type, NULL);
				break;
			}
	}
	return result;
}

BaseExpression* SimpleExpression::copyExpression() {
	SimpleExpression* result = new SimpleExpression(this->_expression);
	return result;
}