
#ifndef __AbandonPlotAction_hxx__
#define __AbandonPlotAction_hxx__

#include <MDPAction.hxx>

namespace Gujarat
{

class GujaratAgent;
	
class AbandonPlotAction : public MDPAction
{
public:
	AbandonPlotAction();
	virtual ~AbandonPlotAction();
	// TODO templatitzar classe per agent
	void execute( GujaratAgent & agent );
	int getTimeNeeded();
	bool equal(MDPAction * a, const GujaratAgent & gua) { return dynamic_cast<AbandonPlotAction*>(act);}
};
	
} // namespace Gujarat

#endif // __AbandonPlotAction_hxx__

