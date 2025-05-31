#include "astparser.h"
#include "astnode.h"
#include "md4c.h"
#include <cstddef>

ASTNode* currentParent = NULL;

void setCurrentParent(ASTNode *parent) {
	currentParent = parent;
}

int ASTParser::enter_block_callback(MD_BLOCKTYPE blockType, void* detail, void* userdata) {
	auto* node = new ASTNode();

	switch (blockType) {
		case MD_BLOCK_H: {
			MD_BLOCK_H_DETAIL* hDetail = (MD_BLOCK_H_DETAIL*) detail;
			switch (hDetail->level) {
				case 1: node->setNodeType(H1_TITLE); break;
				case 2: node->setNodeType(H2_TITLE); break;
				case 3: node->setNodeType(H3_TITLE); break;
				case 4: node->setNodeType(H4_TITLE); break;
				case 5: node->setNodeType(H5_TITLE); break;
				case 6: node->setNodeType(H6_TITLE); break;
				default: break;
			}
			break;
		}
		case MD_BLOCK_P:
			node->setNodeType(PARAGRAPH);
			break;
		case MD_BLOCK_CODE: {
			node->setNodeType(CODEBLOCK);
			MD_BLOCK_CODE_DETAIL* cDetail = (MD_BLOCK_CODE_DETAIL*) detail;
			node->setLang(cDetail->lang.text);
			break;
		}
		default: break;
	}

	if (currentParent) {
		currentParent->addChild(node);
		setCurrentParent(node);
	}
	return 0;
}

int ASTParser::leave_block_callback(MD_BLOCKTYPE blockType, void* detail, void* userdata) {
	setCurrentParent(currentParent->getParent());
	return 0;
}

int ASTParser::enter_span_callback(MD_SPANTYPE spanType, void* detail, void* userdata) {
	auto* node = new ASTNode();

	switch (spanType) {
		case MD_SPAN_CODE:
			node->setNodeType(INLINECODE);
			break;
		default:
			break;
	}

	if (currentParent) {
		currentParent->addChild(node);
		setCurrentParent(node);
	}
	return 0;
}

int ASTParser::leave_span_callback(MD_SPANTYPE spanType, void* detail, void* userdata) {
	return 0;
}

int ASTParser::text_callback(MD_TEXTTYPE textType, const MD_CHAR* text, MD_SIZE size, void* userdata) {
	auto *node = new ASTNode();
	node->setNodeType(TEXT);
	std::string d = std::string(text, size);
	node->setContent(d);

	if (currentParent) {
		currentParent->addChild(node);
	}
	return 0;
}


MD_PARSER MdParser() {
	auto *p = new ASTParser();

	MD_PARSER parser = {
		.abi_version = 0,
		.flags = MD_FLAG_COLLAPSEWHITESPACE | MD_FLAG_PERMISSIVEURLAUTOLINKS | MD_FLAG_TABLES | MD_FLAG_TASKLISTS,
		.enter_block = p->enter_block_callback,
		.leave_block = p->leave_block_callback,
		.enter_span = p->enter_span_callback,
		.leave_span = p->leave_span_callback,
		.text = p->text_callback,
		.debug_log = NULL,
		.syntax = NULL
	};
	return parser;
}
