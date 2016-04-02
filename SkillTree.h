#ifndef SkillTree_H
#define SkillTree_H
#include <iostream>
using namespace std;
#include "Skill.h"
class SkillTree
{
public:
	SkillTree();
	SkillTree(const SkillTree& aTable);
	SkillTree(char * TreeName);
	~SkillTree();

	void AddSkill(char * name, char* desc, int level);
	void AddSkill(char * name, char* desc, int level, char* parentName);
	Skill * FindSkill(char * parentName);
	
	void Display(std::ostream& outStm);
	const SkillTree& operator= (const SkillTree& aTable);
	void insert(const Skill& aSkill);
	int getSize(void) const;
private:
	std::ostream* outStream;
	struct node
	{
		int childCount;
		Skill item;
		node * list[3];
		node(const Skill& aSkill): item(aSkill), childCount(0)
		{
			list[0] = NULL;
			list[1] = NULL;
			list[2] = NULL;
		}
	};
	node * root;	
	int size;
	int listPtr;
	char * TreeName;
	void insert(node ** root, const Skill& aSkill, int listPtr);
	void deleteNode(node *& target);
	void display(ostream& out, node * root, int level, int tempPtr) const;
	void displayNode (ostream& out, node * root, int level, int tempPtr)const;
	void destroyTree(node *&root, int tempPtr);
	void copyTree(node*& newRoot, node * root);
	Skill * ProcessSkill(node * root,char *SkillNameParent, int tempPtr);
	struct node * SkillTree::FindNode(char * SkillNameParent);
	struct node * SkillTree::ProcessNode(node * root,char *SkillNameParent, int tempPtr);
};
#endif