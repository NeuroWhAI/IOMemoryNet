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

	// 세대 교체
	for (auto step : m_pNextStepList)
	{
		CellPtr pCell = step.first;
		const double& nextPotential = step.second;

		pCell->setPotential(nextPotential);

		// Cell이 활성화 되었으면 목록에 추가
		if (pCell->isActivated())
		{
			m_pHeadCellList.insert(pCell);


			// Hebb 학습
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

		// 값 갱신이 필요한지 확인하고 목록에 추가
		pCell->checkUpdateNecessity();

		if (pCell->isOnUpdate())
		{
			m_pUpdatingCellList.insert(pCell);
		}
	}
	m_pNextStepList.clear();


	// Cell 갱신 진행
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


	// 다음 세대 탐색
	std::list<CellPtr> willDeleteFromHeadList;

	for (auto pCell : m_pHeadCellList)
	{
		if (pCell->isActivated())
		{
			auto outLinkerPort = pCell->getOutLinkerPort();

			outLinkerPort->foreach([&](LinkerPtr pOutLinker) {

				// 다음 단의 Cell이 존재하고 휴지상태이면
				// 해당 Cell의 다음 상태값을 생성 or 누적한다.
				CellPtr nextCell = pOutLinker->getOutCell();
				if (nextCell
					&&
					nextCell->isActivated() == false)
				{
					// map에 삽입할 Key(nextCell)가 이미 존재하면 insert에 실패하는 특징을 이용해서
					// 처음 한번 insert에 성공하면 nextCell의 다음 상태값을 현재 상태값으로 초기화한다.
					m_pNextStepList.insert(
						std::make_pair(nextCell, nextCell->getPotential()));

					// 이후 nextCell의 다음 상태값을 입력값으로 누적함.
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


	// 삽입 성공여부 반환
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

