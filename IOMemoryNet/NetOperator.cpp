#include "NetOperator.h"

#include <list>

#include "Cell.h"
#include "Linker.h"
#include "NetOption.h"
#include "ConditionScore.h"

#include "LinkerPort.h"



























NetOperator::NetOperator()
	: m_pNetOption(nullptr)
	, m_pCondition(nullptr)
{

}


NetOperator::~NetOperator()
{

}

////////////////////////////////////////////////////////////////////

int NetOperator::update()
{
	const double maxLinkerWeight = m_pNetOption->getMaxLinkerWeight();
	const double minLinkerWeight = m_pNetOption->getMinLinkerWeight();
	const double hebbRate = m_pNetOption->getHebbRate();
	const double pnScore = m_pCondition->getPN();

	// ���� ��ü
	for (auto step : m_pNextStepList)
	{
		CellPtr pCell = step.first;
		const double& nextPotential = step.second;

		pCell->setPotential(nextPotential);

		// Cell�� Ȱ��ȭ �Ǿ����� ��Ͽ� �߰�
		if (pCell->isActivated())
		{
			m_pHeadCellList.insert(pCell);


			// Hebb �н�
			pCell->getInLinkerPort()->foreach([&pCell, &maxLinkerWeight, &minLinkerWeight, &hebbRate, &pnScore](LinkerPtr pLinker) {
				
				double weight = pLinker->getWeight();
				CellPtr pInCell = pLinker->getInCell();

				if (pInCell && pInCell->isUnderPressure() == false)
				{
					double deltaW = ((pInCell->getPotential() - Cell::POTENTIAL_REFRACTORY) * weight)
						* hebbRate
						* pnScore;
					weight += deltaW;

					if (weight > maxLinkerWeight)
						weight = maxLinkerWeight;
					else if (weight < minLinkerWeight)
						weight = minLinkerWeight;

					pLinker->setWeight(weight);
				}
			});
		}

		// �� ������ �ʿ����� Ȯ���ϰ� ��Ͽ� �߰�
		pCell->checkUpdateNecessity();

		if (pCell->isOnUpdate())
		{
			m_pUpdatingCellList.insert(pCell);
		}
	}
	m_pNextStepList.clear();


	// Cell ���� ����
	std::list<CellPtr> willDeleteFromUpdatingList;

	for (auto pCell : m_pUpdatingCellList)
	{
		pCell->update();

		if (pCell->isOnUpdate() == false)
		{
			willDeleteFromUpdatingList.emplace_back(pCell);
		}
	}

	for (auto pCell : willDeleteFromUpdatingList)
	{
		m_pUpdatingCellList.erase(pCell);
	}


	// ���� ���� Ž��
	std::list<CellPtr> willDeleteFromHeadList;

	for (auto pCell : m_pHeadCellList)
	{
		if (pCell->isActivated())
		{
			auto outLinkerPort = pCell->getOutLinkerPort();

			outLinkerPort->foreach([&](LinkerPtr pOutLinker) {

				// ���� ���� Cell�� �����ϰ� ���������̸�
				// �ش� Cell�� ���� ���°��� ���� or �����Ѵ�.
				CellPtr nextCell = pOutLinker->getOutCell();
				if (nextCell
					&&
					nextCell->isActivated() == false)
				{
					// map�� ������ Key(nextCell)�� �̹� �����ϸ� insert�� �����ϴ� Ư¡�� �̿��ؼ�
					// ó�� �ѹ� insert�� �����ϸ� nextCell�� ���� ���°��� ���� ���°����� �ʱ�ȭ�Ѵ�.
					m_pNextStepList.insert(
						std::make_pair(nextCell, nextCell->getPotential()));

					// ���� nextCell�� ���� ���°��� �Է°����� ������.
					m_pNextStepList[nextCell] += pCell->getPotential() * pOutLinker->getWeight();
				}
			});
		}
		else
		{
			willDeleteFromHeadList.emplace_back(pCell);
		}
	}

	for (auto pCell : willDeleteFromHeadList)
	{
		m_pHeadCellList.erase(pCell);
	}


	return 0;
}

////////////////////////////////////////////////////////////////////

int NetOperator::setNetOption(NetOptionPtr pNetOption)
{
	m_pNetOption = pNetOption;


	return 0;
}


int NetOperator::setConditionScore(ConditionScorePtr pScore)
{
	m_pCondition = pScore;


	return 0;
}

////////////////////////////////////////////////////////////////////

bool NetOperator::addCell(CellPtr pCell)
{
	auto result = m_pNextStepList.insert(
		std::make_pair(pCell, pCell->getPotential()));


	// ���� �������� ��ȯ
	return (result.second);
}


int NetOperator::removeCell(const CellPtr pCell)
{
	m_pUpdatingCellList.erase(pCell);
	m_pHeadCellList.erase(pCell);
	m_pNextStepList.erase(pCell);


	return 0;
}

////////////////////////////////////////////////////////////////////

size_t NetOperator::countOfUpdatingCell() const
{
	return m_pUpdatingCellList.size();
}


size_t NetOperator::countOfHeadCell() const
{
	return m_pHeadCellList.size();
}


size_t NetOperator::countOfNextCell() const
{
	return m_pNextStepList.size();
}

//---------------------------------------------------------------

int NetOperator::foreachUpdatingCell(std::function<void(CellPtr)> func)
{
	for (auto& pCell : m_pUpdatingCellList)
	{
		func(pCell);
	}


	return 0;
}


int NetOperator::foreachHeadCell(std::function<void(CellPtr)> func)
{
	for (auto& pCell : m_pHeadCellList)
	{
		func(pCell);
	}


	return 0;
}

