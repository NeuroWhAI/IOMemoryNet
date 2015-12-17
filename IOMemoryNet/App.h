/*
* Author: tlsehdgus321@naver.com

* Description: MVC�� ��ü���� ��� �����.
*/

#ifndef __APP_H__
#define __APP_H__

#include <memory>

class Graphic;
class Controller;

class MemoryNet;























class App
{
public:
	App();
	virtual ~App();


private:
	bool m_bOnRun;


private:
	std::shared_ptr<Graphic> m_pGraphic;
	std::shared_ptr<Controller> m_pController;


private:
	std::shared_ptr<MemoryNet> m_pTestNet;


public:
	int init();
	int release();

	int update();
	int render();


public:
	bool isOnRun() const;
};

#endif