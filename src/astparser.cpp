#include "astparser.h"
#include "astnode.h"
#include "md4c.h"

ASTNode* currentParent = nullptr;

void setCurrentParent(ASTNode *parent) {
	currentParent = parent;
}

int ASTParser::enter_block_callback(MD_BLOCKTYPE blockType, void* detail, void* userdata) {
	auto* node = new ASTNode();

	switch (blockType) {
		case MD_BLOCK_H: {
			const auto* d = static_cast<MD_BLOCK_H_DETAIL *>(detail);
			switch (d->level) {
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
			const auto* d = static_cast<MD_BLOCK_CODE_DETAIL *>(detail);
			const auto lang = d->lang.text;
			node->setLang(std::string(lang, d->lang.size));
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
	setCurrentParent(currentParent->getParent());
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
	MD_PARSER parser = {
		.abi_version = 0,
		.flags = MD_FLAG_COLLAPSEWHITESPACE | MD_FLAG_PERMISSIVEURLAUTOLINKS | MD_FLAG_TABLES | MD_FLAG_TASKLISTS,
		.enter_block = ASTParser::enter_block_callback,
		.leave_block = ASTParser::leave_block_callback,
		.enter_span = ASTParser::enter_span_callback,
		.leave_span = ASTParser::leave_span_callback,
		.text = ASTParser::text_callback,
		.debug_log = nullptr,
		.syntax = nullptr
	};
	return parser;
}
