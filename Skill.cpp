#include "Skill.h"
#include <iostream>
#include <iomanip>
using namespace std;
#pragma warning(disable:4996)		// allow call to strcpy
/*************************
private:
	char* SkillName;
	chr * SkillDescription;
	int SkillLevel;
*************************/
Skill::Skill():SkillName(NULL), SkillDescription(NULL), SkillParent(NULL), SkillLevel(0)
{
}

Skill::Skill(char* SkillName, char* SkillDescription, char * SkillParent):SkillName(NULL), SkillDescription(NULL), SkillParent(NULL), SkillLevel(0)
{	
	setSkillName(SkillName);
	setSkillDescription(SkillDescription);
	setSkillLevel(SkillLevel);
	setSkillParent(SkillParent);

}
	
Skill::Skill(const Skill& aSkill) : SkillName(NULL), SkillDescription(NULL), SkillParent(NULL), SkillLevel(0)
{
	setSkillName(aSkill.SkillName);
	setSkillDescription(aSkill.SkillDescription);
	setSkillLevel(aSkill.SkillLevel);
	setSkillParent(aSkill.SkillParent);
}

const Skill& Skill::operator=(const Skill& aSkill)
{
	//if it is a self copy, don't do anything
	if(this == &aSkill)
		return *this;
	//make current object *this a copy of the passed in SkillName
	else
	{
		setSkillName(aSkill.SkillName);
		setSkillDescription(aSkill.SkillDescription);
		setSkillLevel(aSkill.SkillLevel);
		setSkillParent(aSkill.SkillParent);
		return *this;
	}
}

Skill::~Skill()
{
	if(SkillName)
		delete[] SkillName;
	if(SkillDescription)
		delete[] SkillDescription;
	if(SkillParent)
		delete[] SkillParent;
}
////////////////////////////////////////////////////////////////
void Skill::getSkillName(char * SkillName) const
{
	strcpy(SkillName, this->SkillName);
}

void Skill::getSkillDescription(char * SkillDescription) const
{
	strcpy(SkillDescription, this->SkillDescription);
}

int Skill::getLevel() const
{
	return SkillLevel;
}
void Skill::getSkillParent(char * SkillParent) const
{
	strcpy(SkillParent, this->SkillParent);
}
void Skill::setSkillName(char * SkillName)
{
	//release the exisisting memory if there is any
	if(this->SkillName)
		delete [] this->SkillName;

	//set new skill
	this->SkillName = new char[strlen(SkillName)+1];
	strcpy(this->SkillName, SkillName);
}
void Skill::setSkillDescription(char * SkillDescription)
{
	//release the exisisting memory if there is any
	if(this->SkillDescription)
		delete [] this->SkillDescription;

	//set new skill
	this->SkillDescription = new char[strlen(SkillDescription)+1];
	strcpy(this->SkillDescription, SkillDescription);;
}
void Skill::setSkillParent(char * SkillParent)
{
	//release the exisisting memory if there is any
	if(this->SkillParent)
		delete [] this->SkillParent;

	//set new skill
	this->SkillParent = new char[strlen(SkillParent)+1];
	strcpy(this->SkillParent, SkillParent);
}
void Skill::setSkillLevel(int SkillLevel)
{
	this->SkillLevel= SkillLevel;
}

bool operator<(const Skill& d1, const Skill& d2)
{
	char SkillName1[100];
	char SkillName2[100];

	d1.getSkillName(SkillName1);
	d2.getSkillName(SkillName2);

	if(strcmp(SkillName1, SkillName2) < 0)
		return true;
	else
		return false;
}

bool operator==(Skill& d1,Skill& d2)
{
	char id1[500];
	char id2[500];

	d1.getSkillName(id1);
	d2.getSkillName(id2);

	if(strcmp(id1, id2) == 0)
		return true;
	else
		return false;
}
void Skill::Display(std::ostream& outStm)
{
	outStm <<SkillName << " -- " << SkillDescription << " [Lvl: "<< SkillLevel << "]";
}
ostream& operator<<(ostream& out, const Skill& aSkill)
{
	if(!aSkill.SkillName)
		return out;
	out << "- " << aSkill.SkillName << " -- " << aSkill.SkillDescription << " [Lvl: "<< aSkill.SkillLevel << "]";
	return out;
}