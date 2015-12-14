#ifndef _APP_H_
#define _APP_H_

class App
{
public:
	App();
	virtual ~App();


public:
	int init();
	int release();

	int update();
	int render();
};

#endif