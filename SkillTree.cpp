#include "SkillTree.h"
#include "Skill.h"
#include <ostream>
#include <string.h>
using namespace std;

/************************
private:
	node * root;	
	int size;
************************/
SkillTree::SkillTree() : root(NULL), size(0), listPtr(0), TreeName(NULL)
{
}

SkillTree::SkillTree(const SkillTree& aTable):root(NULL), size(aTable.size), TreeName(NULL)
{
	*this = aTable;
}
SkillTree::SkillTree(char * SkillTreeName) : root(NULL), size(0), TreeName(NULL)
{
	TreeName = SkillTreeName;
}
const SkillTree& SkillTree::operator= (const SkillTree& aTable)
{
	if(this == &aTable)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		destroyTree(root, 0); 

		//copy the table
		copyTree(root, aTable.root);
		return *this;
	}
}
void SkillTree::copyTree (node*& newRoot, node * root)
{
	if(root)
	{
		//copy root
		newRoot = new node(root->item);
		copyTree(newRoot->list[listPtr + 1], root->list[listPtr + 1]);
	}
	else
	{
		listPtr = 0;
		newRoot = NULL;
	}
}

SkillTree::~SkillTree()
{
	destroyTree(root, 0); 
}

void SkillTree::destroyTree (node *& root, int tempPtr)
{
	if (root) 
	{
		while(root->list[tempPtr] && tempPtr < 3)
		{
			destroyTree(root->list[tempPtr++], 0);
		}		
		//cout<<"deleting "<<root->item<<endl; debug line
		delete root;
		root = NULL;
	}
}
void SkillTree::AddSkill(char * SkillName, char * SkillDescription, int SkillLevel)		
{
	Skill skill;
	char * SkillParent = "NULL";
	//cout<<"Attempting to add player \""<< SkillName <<"\"  to the database\n"; debug line
	skill.setSkillName(SkillName);
	skill.setSkillDescription(SkillDescription);
	skill.setSkillLevel(SkillLevel);
	skill.setSkillParent(SkillParent);
	insert(skill);
}

void SkillTree::AddSkill(char * SkillName, char * SkillDescription, int SkillLevel, char* SkillParent)
{
	Skill skill;
	//cout<<"Attempting to add player \""<< SkillName <<"\"  to the database\n"; debug line
	skill.setSkillName(SkillName);
	skill.setSkillDescription(SkillDescription);
	skill.setSkillLevel(SkillLevel);
	skill.setSkillParent(SkillParent);
	insert(skill);
}


Skill* SkillTree::FindSkill(char * SkillNameParent)
{
	if(root == NULL)
		return NULL;
	char SkillName[500];
	int tempPtr = 0;
	root->item.getSkillName(SkillName);
	if(strcmp(SkillNameParent, SkillName) == 0)
	{
		return &root->item;
	}
	Skill * ParentSkill = ProcessSkill(root->list[tempPtr], SkillNameParent, 0);
	return ParentSkill;
}
Skill* SkillTree::ProcessSkill(node * root,char *SkillNameParent, int tempPtr)
{
	if(root == NULL)
		return NULL;
	char SkillName[500];
	
	root->item.getSkillName(SkillName);
	if(strcmp(SkillNameParent, SkillName) == 0)
	{
		return &root->item;
	}
	while(root->list[tempPtr])
	{
		tempPtr++;
		Skill * ParentSkill = ProcessSkill(root->list[tempPtr],SkillNameParent, 0);
		if(ParentSkill != NULL)
			return ParentSkill;
	}
	return NULL;
}




SkillTree::node * SkillTree::FindNode(char * SkillNameParent)
{
	if(root == NULL)
		return NULL;
	char SkillName[500];
	int tempPtr = 0;
	root->item.getSkillName(SkillName);
	node * ParentSkill = ProcessNode(root, SkillNameParent, 0);
	return ParentSkill;
}
SkillTree::node * SkillTree::ProcessNode(node * root,char *SkillNameParent, int tempPtr)
{
	if(root == NULL)
		return NULL;
	char SkillName[500];
	
	root->item.getSkillName(SkillName);
	if(strcmp(SkillNameParent, SkillName) == 0)
	{
		return root;
	}
	while(root->list[tempPtr])
	{
		node * ParentSkill = ProcessNode(root->list[tempPtr++],SkillNameParent, 0);
		if(ParentSkill != NULL)
			return ParentSkill;
	}
	return NULL;
}
void SkillTree::insert (const Skill& aSkill)
{	
	insert(&root, aSkill, 0);
}
void SkillTree::insert (node ** root, const Skill& aSkill, int listPtr)
{
	if(*root == NULL)
	{	
		*root = new node(aSkill);
		size++;
	}
	else
	{
		if(aSkill.getLevel() == 0)
		{
			node * NewParentNode;
			NewParentNode = new node(aSkill);
			NewParentNode->list[0] = *root;
			*root = NewParentNode;
			return;
		}
		char SkillNameParent[500];
		aSkill.getSkillParent(SkillNameParent);
		node * parent = FindNode(SkillNameParent);
		if(parent == NULL || parent->childCount == 3)
		{
			//cout<<"ITS BROKEN"; debug line
			return;
		}
		parent->list[parent->childCount++] = new node(aSkill);
	}

}
static void printlevelSpacers(ostream& out, int spacers)
{
	for (int i = 0; i < spacers; i++)
		out << "  ";
}

void SkillTree::display (ostream& out, node * root, int level, int tempPtr)const
{
	cout<<"Skill Tree: " <<TreeName<<endl;
	if (root) 
	{
		displayNode(out, root, level, 0);
	}
	else
	{
		cout<<"  Empty\n";
	}
}
void SkillTree::displayNode (ostream& out, node * root, int level, int tempPtr)const
{
	level++;
	if (root) 
	{
		printlevelSpacers(out, level);
		out << root->item << endl;
		while(root->list[tempPtr])
		{
			displayNode(out, root->list[tempPtr++], level, 0);
			if(tempPtr == 3)
				return;
		}
	}
	else
		cout<<"  Empty\n";
}

void SkillTree::Display(std::ostream& outStm)
{
	outStream = &outStm;
	display(outStm, root, 0, 0);
}

int SkillTree::getSize (void) const
{
	return size;
}