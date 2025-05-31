#ifndef ASTPARSER_H
#define ASTPARSER_H

#include "astnode.h"
#include "md4c.h"

class ASTParser {
public:
	static int enter_block_callback(MD_BLOCKTYPE blockType, void* detail, void* userdata);
	static int leave_block_callback(MD_BLOCKTYPE blockType, void* detail, void* userdata);
	static int enter_span_callback(MD_SPANTYPE spanType, void* detail, void* userdata);
	static int leave_span_callback(MD_SPANTYPE spanType, void* detail, void* userdata);
	static int text_callback(MD_TEXTTYPE textType, const MD_CHAR* text, MD_SIZE size, void* userdata);
};

MD_PARSER MdParser();
void setCurrentParent(ASTNode *parent);
void setLastParent(ASTNode *parent);

#endif
