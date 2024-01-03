#include "Action.h"
#include "ActionSelectFigure.h"
#include "ActionAddSquare.h"

class ActionResizeShape :public Action {
public:
	ActionResizeShape(ApplicationManager* pApp);
	virtual void Execute();
};