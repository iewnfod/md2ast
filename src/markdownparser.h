#ifndef MARKDOWNPARSER_H
#define MARKDOWNPARSER_H

#include "astnode.h"

class MarkdownParser {
public:
	static ASTNode* toAST(const char *markdown);
};

#endif
