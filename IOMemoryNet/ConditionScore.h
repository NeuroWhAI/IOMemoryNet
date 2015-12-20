#ifndef __CONDITION_SCORE_H__
#define __CONDITION_SCORE_H__
























class ConditionScore
{
public:
	ConditionScore();
	virtual ~ConditionScore();


protected:
	double m_pn;


public:
	int update();


public:
	ConditionScore& operator= (const ConditionScore& rhs);
	int addConditionScore(const ConditionScore& rhs, double weight = 1.0);


public:
	double getPN() const;
	void addPN(double deltaPN);
};

#endif