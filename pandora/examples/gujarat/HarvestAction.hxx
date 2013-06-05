
#ifndef __HarvestAction_hxx__
#define __HarvestAction_hxx__

#include <MDPAction.hxx>

namespace Engine
{
	class Agent;
}

namespace Gujarat
{

class GujaratAgent;
	
class HarvestAction : public MDPAction
{
	static std::string _className;
public:
	HarvestAction();
	virtual ~HarvestAction();
	// TODO templatitzar classe per agent
	void execute( Engine::Agent & agent );
	int getTimeNeeded() const;
	
	virtual Sector * getVisitedSector() = 0;
	
	friend class GujaratAgent;
	
	virtual void getOwnershipMDPSectorKnowledge(bool v[]) const = 0;
	
	std::string & getClassName() { return _className; }
};
	
std::string HarvestAction::_className = "HarvestAction";


} // namespace Gujarat

#endif // __HarvestAction_hxx__

