#include "MemoryNet.h"

#include <assert.h>

#include "SignalSet.h"
#include "ComPort.h"
#include "MemoryCell.h"
#include "MemoryLinker.h"
#include "MemNetOperator.h"
#include "NetOption.h"
#include "ConditionScore.h"

#include "LinkHelper.h"

using SignalSetPtr = MemoryNet::SignalSetPtr;
using ComPortPtr = MemoryNet::ComPortPtr;
using MemoryCellPtr = MemoryNet::MemoryCellPtr;
using MemoryLinkerPtr = MemoryNet::MemoryLinkerPtr;
using MemNetOperatorPtr = MemoryNet::MemNetOperatorPtr;
using NetOptionPtr = MemoryNet::NetOptionPtr;
using ConditionScorePtr = MemoryNet::ConditionScorePtr;


























MemoryNet::MemoryNet()
	: m_pNetOption(new NetOption())
	, m_pCondition(new ConditionScore())
	, m_pNextCondition(new ConditionScore())
	
	, m_pInSignalSet(new SignalSet())
	, m_pOutSignalSet(new SignalSet())

	, m_pNetOperator(new MemNetOperator())
{
	m_pNetOperator->setNetOption(m_pNetOption);
	m_pNetOperator->setConditionScore(m_pCondition);
}


MemoryNet::MemoryNet(size_t inSignalCount, size_t outSignalCount)
	: m_pNetOption(new NetOption())
	, m_pCondition(new ConditionScore())
	, m_pNextCondition(new ConditionScore())

	, m_pInSignalSet(new SignalSet())
	, m_pOutSignalSet(new SignalSet())

	, m_pNetOperator(new MemNetOperator())
{
	m_pNetOperator->setNetOption(m_pNetOption);
	m_pNetOperator->setConditionScore(m_pCondition);


	this->init(inSignalCount, outSignalCount);
}


MemoryNet::~MemoryNet()
{

}

//////////////////////////////////////////////////////////////////

int MemoryNet::init(size_t inSignalCount, size_t outSignalCount)
{
	m_pInSignalSet->init(inSignalCount + outSignalCount);
	m_pOutSignalSet->init(outSignalCount);


	return 0;
}


int MemoryNet::release()
{



	return 0;
}

//---------------------------------------------------------------

int MemoryNet::update()
{
	// �� ���� ����
	*m_pCondition = *m_pNextCondition;

	// �ӵ������� ���� �̸� ���� ��� ��.
	const double maxSignalUnit = m_pNetOption->getMaxSignalUnit();
	const double pnScore = m_pCondition->getPN();

	// ����� �Է����� �ǵ��
	m_pInSignalSet->copyRange(*m_pOutSignalSet,
		this->getInputSize(), m_pOutSignalSet->getSignalCount());

	// ���� �Է°������� ����� Ž���� Ȱ��ȭ ��Ŵ
	bool bOnNewInputSet = true;

	for (auto& pCell : m_pCellList)
	{
		SignalSetPtr pInSignalSet = pCell->getInSignalSet();

		if (pInSignalSet->isEqual(*m_pInSignalSet, m_pInSignalSet->getSignalCount(),
			maxSignalUnit))
		{
			bOnNewInputSet = false; // �̹� ����� ����� �����Ƿ� ���ο� �Է°��� �ƴ�

			if (pCell->isActivated() == false)
			{
				// Ȱ��ȭ
				pCell->activate();
				m_pNetOperator->addCell(pCell);
			}
		}
	}

	// ���ο� ���� �Է��� ����
	if (bOnNewInputSet)
	{
		// ���ο� ��� ����
		MemoryCellPtr pNewCell(new MemoryCell());

		// �������� ����
		pNewCell->setConditionScore(*m_pCondition);

		// ��´� ����
		SignalSetPtr pOutSignalSet(new SignalSet());
		pOutSignalSet->init(m_pOutSignalSet->getSignalCount());

		size_t outSetSize = pOutSignalSet->getSignalCount();
		for (size_t i = 0; i < outSetSize; ++i)
		{
			// NOTE: �ӽ�
			double outSignal = pnScore / (8.0 + 4.0 * static_cast<double>(rand())/RAND_MAX);
			outSignal *= ((rand() % 2) ? 1.0 : -1.0);
			pOutSignalSet->setSignalAt(i, outSignal);
		}

		pNewCell->setOutSignalSet(pOutSignalSet);

		// ���� �Է��� ���
		pNewCell->setInSignalSet(m_pInSignalSet);

		// Ȱ��ȭ
		pNewCell->activate();
		m_pNetOperator->addCell(pNewCell);

		// ��Ͽ� �߰�
		this->addMemoryCell(pNewCell);
	}

	// ����´� ����
	m_pInSignalSet->update();
	m_pOutSignalSet->update();

	// ������ ����
	m_pNetOperator->update();

	// �������� ����
	// NOTE: m_pCondition�� ������ �� �̹Ƿ� m_pCondition������ update�� ���ʿ�.
	m_pNextCondition->update();


	return 0;
}

//////////////////////////////////////////////////////////////////

const ConditionScore& MemoryNet::getConditionScore() const
{
	return *m_pCondition;
}


void MemoryNet::addPN(double deltaPN)
{
	m_pNextCondition->addPN(deltaPN);
}

//////////////////////////////////////////////////////////////////

size_t MemoryNet::getInputSize() const
{
	return m_pInSignalSet->getSignalCount() - m_pOutSignalSet->getSignalCount();
}


size_t MemoryNet::getOutputSize() const
{
	return m_pOutSignalSet->getSignalCount();
}

//---------------------------------------------------------------

const SignalSetPtr MemoryNet::getInputSet() const
{
	return m_pInSignalSet;
}


const SignalSetPtr MemoryNet::getOutputSet() const
{
	return m_pOutSignalSet;
}

//////////////////////////////////////////////////////////////////

ComPortPtr MemoryNet::assignComPortAtInput(size_t index, size_t count)
{
	// �Է´ܿ� ���� ComPort�� ������ �����ϰ� ��Ͽ� ���
	ComPortPtr pCom(new ComPort());
	pCom->connect(m_pInSignalSet, index, count);

	m_pComList.emplace_back(pCom);


	return pCom;
}


ComPortPtr MemoryNet::assignComPortAtOutput(size_t index, size_t count)
{
	// ��´ܿ� ���� ComPort�� ������ �����ϰ� ��Ͽ� ���
	ComPortPtr pCom(new ComPort());
	pCom->connect(m_pOutSignalSet, index, count);

	m_pComList.emplace_back(pCom);


	return pCom;
}

//---------------------------------------------------------------

int MemoryNet::removeComPort(ComPortPtr pCom)
{
	// ComPort��Ͽ��� pCom�� ã�Ƽ� ����
	const size_t listSize = m_pComList.size();
	for (size_t i = 0; i < listSize; ++i)
	{
		if (m_pComList[i] == pCom)
		{
			m_pComList.erase(m_pComList.begin() + i);


			return 0;
		}
	}


	return -1;
}

//////////////////////////////////////////////////////////////////

int MemoryNet::addMemoryCell(MemoryCellPtr pCell)
{
#ifdef _DEBUG
	assert(pCell != nullptr && "MemoryNet::addMemoryCell�� pCell�� null�� �� �����ϴ�.");
#endif

	// Ȱ��ȭ�� �ݹ�Ǵ� �Լ� ���
	pCell->setCellActivationCallback([&](Cell& cell) -> int {
		return whenActivateCell(cell);
	});
	pCell->setMemoryActivationCallback([&](MemoryCell& memCell) -> int {
		return whenActivateMemoryCell(memCell);
	});

	// ��Ͽ� �߰�
	m_pCellList.emplace_back(pCell);


	return 0;
}


int MemoryNet::removeMemoryCell(const MemoryCellPtr pCell)
{
	m_pNetOperator->removeCell(pCell);

	// Cell��Ͽ��� pCell�� ã�Ƽ� ����
	const size_t listSize = m_pCellList.size();
	for (size_t c = 0; c < listSize; ++c)
	{
		if (m_pCellList[c] == pCell)
		{
			m_pCellList.erase(m_pCellList.begin() + c);


			break;
		}
	}


	return 0;
}

//---------------------------------------------------------------

int MemoryNet::addMemoryLinker(MemoryLinkerPtr pLinker)
{
#ifdef _DEBUG
	assert(pLinker != nullptr && "MemoryNet::addMemoryLinker�� pLinker�� null�� �� �����ϴ�.");
#endif

	m_pLinkerList.emplace_back(pLinker);


	return 0;
}


int MemoryNet::removeMemoryLinker(const MemoryLinkerPtr pLinker)
{
	// Linker��Ͽ��� pLinker�� ã�Ƽ� ����
	const size_t listSize = m_pLinkerList.size();
	for (size_t lk = 0; lk < listSize; ++lk)
	{
		if (m_pLinkerList[lk] == pLinker)
		{
			m_pLinkerList.erase(m_pLinkerList.begin() + lk);


			break;
		}
	}


	return 0;
}

//////////////////////////////////////////////////////////////////

const std::vector<MemoryCellPtr>& MemoryNet::getMemoryCellList() const
{
	return m_pCellList;
}


const std::vector<MemoryLinkerPtr>& MemoryNet::getMemoryLinkerList() const
{
	return m_pLinkerList;
}


const MemNetOperatorPtr MemoryNet::getMemNetOperator() const
{
	return m_pNetOperator;
}

//////////////////////////////////////////////////////////////////

int MemoryNet::whenActivateCell(Cell& cell)
{
	const double maxFirstLinkerWeight = m_pNetOption->getMaxFirstLinkerWeight();

	// shared_ptr�� �ѱ�� �ؾ��ϴµ� cell�� ����Ʈ�����Ͱ� �ƴϹǷ�
	// �Ҹ��� ��� �Լ��� �ƹ��͵� ���ϴ� �Լ��� ��������.
	CellPtr tempCellPtr(&cell, [](Cell*) {});

	// Ȱ��ȭ�� �ٸ� Cell�� ����
	m_pNetOperator->foreachHeadCell([&](CellPtr pOtherCell) {
		if (pOtherCell == tempCellPtr) return;

		// ���� �õ�
		auto pNewLinker = LinkHelper<Cell, MemoryLinker>::connect(
			pOtherCell, tempCellPtr);

		// ������ �� �Ǿ�����
		if (pNewLinker)
		{
			// �������� ����� �ʱ� ���� ����ġ�� ����ϰ�
			double weight = Cell::POTENTIAL_ACTION - pOtherCell->getPotential();
			if (weight < 0.1) weight = 0.1;
			pNewLinker->setWeight(maxFirstLinkerWeight*0.1 / weight);

			// ������ ������ ��Ͽ� �߰�
			this->addMemoryLinker(pNewLinker);
		}
	});


	return 0;
}


int MemoryNet::whenActivateMemoryCell(MemoryCell& memoryCell)
{
	const double pnScore = m_pCondition->getPN();

	// ��¿� ����
	m_pOutSignalSet->addSignals(*memoryCell.getOutSignalSet(),
		memoryCell.getPotential());

	// Cell�� �������� ����
	memoryCell.addConditionScore(*m_pCondition, 0.001);

	// ������ �������� ���� ���뿡 ����
	m_pNextCondition->addConditionScore(memoryCell.getConditionScore(), 0.1);

	// Cell�� ��°� ����
	/*auto outSignalSet = memoryCell.getOutSignalSet();
	size_t outSetSize = outSignalSet->getSignalCount();
	for (size_t i = 0; i < outSetSize; ++i)
	{
		double signal = outSignalSet->getSignalAt(i);

		if (abs(signal) < std::numeric_limits<double>::epsilon())
		{
			outSignalSet->setSignalAt(i, 0.0);
		}
		else
		{
			outSignalSet->addSignalAt(i, signal * pnScore / 32.0);
		}
	}*/


	return 0;
}

