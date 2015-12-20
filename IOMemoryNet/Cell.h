#ifndef __CELL_H__
#define __CELL_H__

#include <memory>
#include <functional>

class Linker;
class LinkerPort;
























class Cell
{
public:
	typedef std::shared_ptr<Linker> LinkerPtr;
	typedef std::shared_ptr<LinkerPort> LinkerPortPtr;


public:
	static const double POTENTIAL_REST;
	static const double POTENTIAL_HOLD;
	static const double POTENTIAL_ACTION;
	static const double POTENTIAL_REFRACTORY;


public:
	Cell();
	virtual ~Cell();


protected:
	double m_potential;


protected:
	LinkerPortPtr m_pInLinkerPort, m_pOutLinkerPort;


private:
	int (Cell::*currFunc)(void);
	std::function<int(Cell&)> whenCellActivatedFunc;


public:
	virtual int update();

	int seq_toActive();
	int seq_toRefractory();
	int seq_toRestByDown();
	int seq_toRestByUp();


public:
	int activate();
	double getPotential() const;
	void setPotential(double potential);
	void addPotential(double deltaPotential);

	// * 전위가 역치 이상인가?
	bool isActivated() const;
	// * 현재 전위를 보고 어떤 시퀀스로 접어들지 설정.
	void checkUpdateNecessity();
	// * 시퀀스가 진행중인가?
	bool isOnUpdate() const;
	// * 활성화 상태가 아니면서 입력값이 계속해서 들어오고 있는가?
	bool isUnderPressure() const;
	

public:
	LinkerPortPtr getInLinkerPort();
	LinkerPortPtr getOutLinkerPort();


public:
	int setCellActivationCallback(std::function<int(Cell&)> func);
};

#endif