#include "astnode.h"

#include <sstream>
#include <bits/ostream.tcc>

ASTNodeType ASTNode::getASTNodeType() const {
	return this->nodeType;
}
void ASTNode::setNodeType(const ASTNodeType nodeType) {
	this->nodeType = nodeType;
}

void ASTNode::setContent(const char* content) {
	this->content = content;
}

void ASTNode::setContent(const std::string& content) {
	this->content = content;
}

void ASTNode::addChild(ASTNode* child) {
	this->children.push_back(child);
	child->parent = this;
}

void ASTNode::setLevel(const int level) {
	this->level = level;
}

void ASTNode::setLang(const char* lang) {
	this->lang = lang;
}

void ASTNode::setLang(const std::string &lang) {
	this->lang = lang;
}

ASTNode* ASTNode::getParent() const {
	return this->parent;
}

std::string ASTNode::getContent() const {
	return this->content;
}

int ASTNode::getLevel() const {
	return this->level;
}

std::string ASTNode::getLang() const {
	return this->lang;
}

std::vector<ASTNode*> ASTNode::getChildren() const {
	return this->children;
}

std::string ASTNode::getHref() const {
	return this->href;
}

void ASTNode::setHref(const char* href) {
    this->href = href;
}

void ASTNode::setHref(const std::string& href) {
    this->href = href;
}


ASTNode::ASTNode() {
	this->nodeType = UNKNOWN_NODE;
}

std::string ASTNode::toHTML() const {
	std::ostringstream html;

	switch (this->nodeType) {
		// text
		case TEXT:
			html << this->content;
			break;
		// block
		case DOCUMENT:
			html << "<html><body>" << this->children2HTML() << "</body></html>";
			break;
		case PARAGRAPH:
			html << "<p>" << this->children2HTML() << "</p>";
		    break;
		case H1_TITLE:
			html << "<h1>" << this->children2HTML() << "</h1>";
			break;
		case H2_TITLE:
			html << "<h2>" << this->children2HTML() << "</h2>";
			break;
		case H3_TITLE:
			html << "<h3>" << this->children2HTML() << "</h3>";
			break;
		case H4_TITLE:
			html << "<h4>" << this->children2HTML() << "</h4>";
			break;
		case H5_TITLE:
			html << "<h5>" << this->children2HTML() << "</h5>";
			break;
		case H6_TITLE:
			html << "<h6>" << this->children2HTML() << "</h6>";
			break;
		case INLINECODE:
			html << "<code>" << this->children2HTML() << "</code>";
			break;
		case CODEBLOCK:
			html << "<pre><code lang=\"" << this->lang << "\">" << this->children2HTML() << "</code></pre>";
			break;
		case LINK:
			html << "<a href=\"" << this->getHref() << "\">" << this->children2HTML() << "</a>";
			break;
		case UNKNOWN_NODE:
		default:
			html << this->children2HTML();
			break;
	}

	return html.str();
}

std::string ASTNode::children2HTML() const {
	std::ostringstream html;

	for (auto child : this->children) {
		html << child->toHTML();
	}

	return html.str();
}
