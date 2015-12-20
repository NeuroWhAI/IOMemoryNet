#include "App.h"

#include "Graphic.h"
#include "ConsoleGraphic.h"

#include "Controller.h"
#include "ConsoleController.h"

#include "MemoryNet.h"
#include "Component.h"
#include "PulseSignalComponent.h"
#include "LampComponent.h"

#include "ComPort.h"
#include "MemoryCell.h"


























App::App()
	: m_bOnRun(true)

	, m_bOnLogging(false)
	
	, m_pGraphic(new ConsoleGraphic())
	, m_pController(new ConsoleController())
	
	, m_pTestNet(new MemoryNet())
{

}


App::~App()
{
	if (m_fw.is_open())
	{
		m_fw.close();
	}
}

//////////////////////////////////////////////////////////////////

int App::init()
{
	m_pTestNet->init(4, 3);

	// Lamp 생성 후 출력단의 0번에 연결
	std::shared_ptr<Component> pNewCpt(new LampComponent());
	auto pCom = m_pTestNet->assignComPortAtOutput(0, 1);
	pNewCpt->connect(pCom);
	m_pComponentList.emplace_back(pNewCpt);


	return 0;
}


int App::release()
{
	m_pTestNet->release();


	return 0;
}

//---------------------------------------------------------------

int App::update()
{
	m_pController->update();

	if (m_pController->onKeyDown_Quit()) m_bOnRun = false;
	
	for (size_t i = 0; i < m_pTestNet->getInputSize(); ++i)
	{
		if (m_pController->onKeyDown(i+'1'))
		{
			std::shared_ptr<Component> pNewCpt(new PulseSignalComponent());
			auto pCom = m_pTestNet->assignComPortAtInput(i, 1);
			pNewCpt->connect(pCom);
			pNewCpt->update();
			m_pTestNet->removeComPort(pCom);
		}
	}


	for (auto& pCpt : m_pComponentList)
	{
		pCpt->update();
	}

	LampComponent* pLamp = dynamic_cast<LampComponent*>(m_pComponentList[0].get());
	if (pLamp != nullptr && pLamp->getLight())
		m_pTestNet->addPN(10.0);
	else
		m_pTestNet->addPN(-10.0);


	m_pTestNet->update();


	if (m_pController->onKeyDown_Enter())
	{
		m_bOnLogging = !m_bOnLogging;

		if (m_bOnLogging)
		{
			m_fw.open("log.csv");
		}
		else
		{
			m_fw.close();
			m_fw.clear();
		}
	}

	if (m_bOnLogging  &&  m_fw.is_open())
	{
		const auto& cellList = m_pTestNet->getMemoryCellList();

		for (auto& pCell : cellList)
		{
			m_fw << pCell->getPotential() << ",";
		}

		m_fw << "0.0" << std::endl;
	}


	return 0;
}


int App::render()
{
	m_pGraphic->drawMemoryNet(*m_pTestNet);

	m_pGraphic->drawSignalSet(*m_pTestNet->getInputSet());
	m_pGraphic->drawSignalSet(*m_pTestNet->getOutputSet());

	LampComponent* pLamp = dynamic_cast<LampComponent*>(m_pComponentList[0].get());
	if (pLamp != nullptr && pLamp->getLight())
		m_pGraphic->drawText("* Lamp: ◆\n");
	else
		m_pGraphic->drawText("* Lamp: ◇\n");

	if (m_bOnLogging)
	{
		if (m_fw.is_open())
			m_pGraphic->drawText("* Logging...\n");
		else
			m_pGraphic->drawText("* Logging FAIL!\n");
	}


	return 0;
}

//////////////////////////////////////////////////////////////////

bool App::isOnRun() const
{
	return m_bOnRun;
}

