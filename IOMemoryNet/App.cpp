#include "App.h"

#include "Graphic.h"
#include "ConsoleGraphic.h"

#include "Controller.h"
#include "ConsoleController.h"

#include "MemoryNet.h"


























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
	m_pTestNet->init();


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


	m_pTestNet->update();


	return 0;
}


int App::render()
{
	m_pGraphic->drawMemoryNet(*m_pTestNet);


	return 0;
}

//////////////////////////////////////////////////////////////////

bool App::isOnRun() const
{
	return m_bOnRun;
}

