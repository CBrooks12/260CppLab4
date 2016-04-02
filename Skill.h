#ifndef Skill_H
#define Skill_H
#include <iostream>
using namespace std;
class Skill
{
public:
	Skill();
	Skill(char * SkillName, char * SkillDescription, char * SkillParent);
	Skill(const Skill& aSkill);		//copy constructor: make current object a copy of "aSkill"
	~Skill();

	void getSkillName(char * SkillName) const;
	void getSkillDescription(char * SkillDescription) const;
	void getSkillParent(char * SkillParent) const;
	int getLevel() const;
	void Display(std::ostream& outStm);

	int getSkillLevel() const;
	void setSkillName(char * SkillName);
	void setSkillDescription(char * SkillDescription);
	void setSkillLevel(int SkillLevel);
	void setSkillParent(char * SkillParent);
	const Skill& operator=(const Skill& SkillName);	 //overloading assignment operator
	friend ostream& operator<<(ostream& out, const Skill& SkillName);

private:
	char * SkillName;
	char * SkillDescription;
	char * SkillParent;
	int SkillLevel;
	std::ostream* outStream;
};
bool operator< (const Skill& d1, const Skill& d2);
bool operator== (const Skill& d1, const Skill& d2);
#endif
