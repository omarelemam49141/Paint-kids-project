#ifndef ACTION_CHNG_BG_CLR_H
#define ACTION_CHNG_BG_CLR_H

#include "Actions/Action.h"

//Add ActionChngBGClr Action class
class ActionChngBGClr : public Action
{
protected:
	ActionType inputColorAction;
	color BkGrndClr;

	bool IsColor;
public:
	class ActionChngBGClr(ApplicationManager* pApp);

	//Change the drawing color
	void Execute();
};

#endif

