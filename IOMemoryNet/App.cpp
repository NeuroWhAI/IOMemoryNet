#include "App.h"

#include "Graphic.h"
#include "ConsoleGraphic.h"

#include "Controller.h"
#include "ConsoleController.h"

#include "MemoryNet.h"
#include "Component.h"
#include "PulseSignalComponent.h"

#include "ComPort.h"


























App::App()
	: m_bOnRun(true)
	
	, m_pGraphic(new ConsoleGraphic())
	, m_pController(new ConsoleController())
	
	, m_pTestNet(new MemoryNet())
{

}


App::~App()
{

}

//////////////////////////////////////////////////////////////////

int App::init()
{
	m_pTestNet->init(4, 3);


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
	if (m_pComponentList.size() > 0)
	{
		for (auto& item : m_pComponentList)
		{
			m_pTestNet->removeComPort(item->getComPort());
		}
		m_pComponentList.clear();
	}


	m_pController->update();

	if (m_pController->onKeyDown_Quit()) m_bOnRun = false;
	
	for (size_t i = 0; i < m_pTestNet->getInputSize(); ++i)
	{
		if (m_pController->onKeyDown(i+'1'))
		{
			std::shared_ptr<Component> pNewCpt(new PulseSignalComponent());
			pNewCpt->connect(m_pTestNet->assignComPortAtInput(i, 1));
			m_pComponentList.emplace_back(pNewCpt);
		}
	}


	m_pTestNet->update();


	for (auto& item : m_pComponentList)
	{
		item->update();
	}


	return 0;
}


int App::render()
{
	m_pGraphic->drawMemoryNet(*m_pTestNet);

	m_pGraphic->drawSignalSet(*m_pTestNet->getInputSet());
	m_pGraphic->drawSignalSet(*m_pTestNet->getOutputSet());


	return 0;
}

//////////////////////////////////////////////////////////////////

bool App::isOnRun() const
{
	return m_bOnRun;
}

