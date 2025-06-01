#include "markdownparser.h"
#include <cstddef>
#include <cstring>
#include <string>
#include "astnode.h"
#include "astparser.h"
#include "md4c.h"

ASTNode *MarkdownParser::toAST(const char *markdown) {
	auto *root = new ASTNode();
	root->setNodeType(DOCUMENT);
	setCurrentParent(root);

	MD_PARSER parser = MdParser();

	int res = md_parse(markdown, std::strlen(markdown), &parser, nullptr);

	return root;
}

ASTNode *MarkdownParser::toAST(const std::string &markdown) {
	return toAST(markdown.c_str());
}
