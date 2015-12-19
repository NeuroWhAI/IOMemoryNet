#include "MemoryNet.h"

#include <assert.h>

#include "SignalSet.h"
#include "ComPort.h"
#include "MemoryCell.h"
#include "MemoryLinker.h"
#include "MemNetOperator.h"

#include "LinkHelper.h"

using SignalSetPtr = MemoryNet::SignalSetPtr;
using ComPortPtr = MemoryNet::ComPortPtr;
using MemoryCellPtr = MemoryNet::MemoryCellPtr;
using MemoryLinkerPtr = MemoryNet::MemoryLinkerPtr;
using MemNetOperatorPtr = MemoryNet::MemNetOperatorPtr;


























MemoryNet::MemoryNet()
	: m_maxSignalUnit(0.5)
	, m_pInSignalSet(new SignalSet())
	, m_pOutSignalSet(new SignalSet())

	, m_pNetOperator(new MemNetOperator())
{

}


MemoryNet::MemoryNet(size_t inSignalCount, size_t outSignalCount)
	: m_maxSignalUnit(0.5)
	, m_pInSignalSet(new SignalSet())
	, m_pOutSignalSet(new SignalSet())

	, m_pNetOperator(new MemNetOperator())
{
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
	// 출력을 입력으로 피드백
	m_pInSignalSet->copyRange(*m_pOutSignalSet,
		this->getInputSize(), m_pOutSignalSet->getSignalCount());

	// 현재 입력값에대해 기억을 탐색해 활성화 시킴
	bool bOnNewInputSet = true;

	for (auto& pCell : m_pCellList)
	{
		SignalSetPtr pInSignalSet = pCell->getInSignalSet();

		if (pInSignalSet->isEqual(*m_pInSignalSet, m_pInSignalSet->getSignalCount(),
			m_maxSignalUnit))
		{
			bOnNewInputSet = false; // 이미 비슷한 기억이 있으므로 새로운 입력값이 아님

			if (pCell->isActivated() == false)
			{
				// 활성화
				pCell->activate();
				m_pNetOperator->addCell(pCell);
			}
		}
	}

	// 새로운 값의 입력을 받음
	if (bOnNewInputSet)
	{
		// 새로운 기억 생성
		MemoryCellPtr pNewCell(new MemoryCell());

		// 출력단 설정
		SignalSetPtr pOutSignalSet(new SignalSet());
		pOutSignalSet->init(m_pOutSignalSet->getSignalCount());

		size_t outSetSize = pOutSignalSet->getSignalCount();
		for (size_t i = 0; i < outSetSize; ++i)
		{
			// NOTE: 임시
			// TODO: 현재 PN상태에 관련해서 값 계산
			pOutSignalSet->setSignalAt(i,
				(rand()%2) ? 0.3 : 0.0);
		}

		pNewCell->setOutSignalSet(pOutSignalSet);

		// 현재 입력을 기억
		pNewCell->setInSignalSet(m_pInSignalSet);

		// 활성화
		pNewCell->activate();
		m_pNetOperator->addCell(pNewCell);

		// 목록에 추가
		this->addMemoryCell(pNewCell);
	}

	// 입출력단 갱신
	m_pInSignalSet->update();
	m_pOutSignalSet->update();

	// 진행자 갱신
	m_pNetOperator->update();


	return 0;
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
	// 입력단에 대한 ComPort를 생성후 연결하고 목록에 등록
	ComPortPtr pCom(new ComPort());
	pCom->connect(m_pInSignalSet, index, count);

	m_pComList.emplace_back(pCom);


	return pCom;
}


ComPortPtr MemoryNet::assignComPortAtOutput(size_t index, size_t count)
{
	// 출력단에 대한 ComPort를 생성후 연결하고 목록에 등록
	ComPortPtr pCom(new ComPort());
	pCom->connect(m_pOutSignalSet, index, count);

	m_pComList.emplace_back(pCom);


	return pCom;
}

//---------------------------------------------------------------

int MemoryNet::removeComPort(ComPortPtr pCom)
{
	// ComPort목록에서 pCom을 찾아서 제거
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
	assert(pCell != nullptr && "MemoryNet::addMemoryCell의 pCell은 null일 수 없습니다.");
#endif

	// 활성화시 콜백되는 함수 등록
	pCell->setCellActivationCallback([&](Cell& cell) -> int {
		return whenActivateCell(cell);
	});
	pCell->setMemoryActivationCallback([&](MemoryCell& memCell) -> int {
		return whenActivateMemoryCell(memCell);
	});

	// 목록에 추가
	m_pCellList.emplace_back(pCell);


	return 0;
}


int MemoryNet::removeMemoryCell(const MemoryCellPtr pCell)
{
	m_pNetOperator->removeCell(pCell);

	// Cell목록에서 pCell을 찾아서 제거
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
	assert(pLinker != nullptr && "MemoryNet::addMemoryLinker의 pLinker는 null일 수 없습니다.");
#endif

	m_pLinkerList.emplace_back(pLinker);


	return 0;
}


int MemoryNet::removeMemoryLinker(const MemoryLinkerPtr pLinker)
{
	// Linker목록에서 pLinker를 찾아서 제거
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
	// 활성화된 다른 Cell에 대해
	m_pNetOperator->foreachHeadCell([&](CellPtr pOtherCell) {
		if (pOtherCell.get() == &cell) return;

		// shared_ptr로 넘기긴 해야하는데 cell이 스마트포인터가 아니므로
		// 소멸자 담당 함수를 아무것도 안하는 함수로 재정의함.
		CellPtr tempCellPtr(&cell, [](Cell*) {});

		// 연결 시도
		auto pNewLinker = LinkHelper<Cell, MemoryLinker>::connect(
			pOtherCell, tempCellPtr);

		// 연결이 잘 되었으면
		if (pNewLinker)
		{
			// 연관도에 비례해 초기 연결 가중치를 계산하고
			double weight = Cell::POTENTIAL_ACTIVE - pOtherCell->getPotential();
			if (weight < 0.1) weight = 0.1;
			pNewLinker->setWeight(0.1 / weight);

			// 생성된 연결을 목록에 추가
			this->addMemoryLinker(pNewLinker);
		}
	});


	return 0;
}


int MemoryNet::whenActivateMemoryCell(MemoryCell& memoryCell)
{
	// 출력에 더함
	m_pOutSignalSet->addSignals(*memoryCell.getOutSignalSet(),
		memoryCell.getPotential());


	return 0;
}

