
#include <SettlementAreas.hxx>

#include <queue>
#include <GujaratWorld.hxx>
#include <assert.h>
#include <math.h>

#include <GeneralState.hxx>
#include <Logger.hxx>

namespace Gujarat
{

SettlementAreas::SettlementAreas()
{		
}

SettlementAreas::~SettlementAreas()
{	
}


/*
void SettlementAreas::updateArea( const Engine::Point2D<int> & newPoint, Engine::Rectangle<int> & r)
{

	if (newPoint._x < r._origin._x)
	{
		r._size._x += r._origin._x - newPoint._x;
		r._origin._x = newPoint._x;
	}
	else if (newPoint._x > r._origin._x + (r._size._x -1) )
	{
		r._size._x = newPoint._x - r._origin._x + 1;    
	}

	if (newPoint._y < r._origin._y)
	{
		r._size._y += r._origin._y - newPoint._y;
		r._origin._y = newPoint._y;
	}
	else if (newPoint._y > r._origin._y + (r._size._y -1) )
	{
		r._size._y = newPoint._y - r._origin._y + 1;    
	}
}
*/
float SettlementAreas::computeAreaScore(const Engine::Rectangle<int> & newArea, GujaratWorld &w)
{
	int numInterdune = 0;
	int numCells = 0;

	Engine::Point2D<int> index;
	for(index._x = newArea._origin._x; index._x < newArea._origin._x + newArea._size._x ; index._x++)
	{
		for(index._y = newArea._origin._y; index._y < newArea._origin._y + newArea._size._y ; index._y++)
		{	
			numCells++;
			if (w.getValue(eSoils,index) == INTERDUNE)
			{
				numInterdune++;
			}
		}
	}
	if(!numCells)
	{
		return 0.0f;
	}
	return (float)numInterdune/numCells;
}

/*
void SettlementAreas::setNewArea( const Engine::Point2D<int> & position,GujaratWorld &w,std::vector<bool> & duneInArea)
{
	std::stringstream logName;
	logName << "SettlementAreas_world_" << w.getSimulation().getId();

	log_EDEBUG(logName.str(), "set new area for loc: " << position);

	// to begin
	Engine::Rectangle<int> newArea(position,Engine::Point2D<int>(1,1));  
	std::queue<Engine::Point2D<int> > targets;

	log_EDEBUG(logName.str(), "updating area for loc: " << position);
	updateArea( position, newArea );
	Engine::Point2D<int> initialLocal = position - w.getOverlapBoundaries()._origin;
	int width = w.getOverlapBoundaries()._size._x;
	log_EDEBUG(logName.str(), "dune in loc: " << position << " set to true with index: " << initialLocal._y*width + initialLocal._x);
	duneInArea[initialLocal._y*width + initialLocal._x] = true;

	targets.push(position);  
	log_EDEBUG(logName.str(), "dune in loc: " << position << " beginning loop");

	while(!targets.empty())
	{
		Engine::Point2D<int> currentPosition(targets.front());
		targets.pop();
		log_EDEBUG(logName.str(), "\tnew target: " << currentPosition);

		Engine::Point2D<int> child;
		for(child._x=currentPosition._x-1; child._x<=currentPosition._x+1; child._x++)
		{
			for(child._y=currentPosition._y-1; child._y<=currentPosition._y+1; child._y++)
			{					
				log_EDEBUG(logName.str(), "\tchecking pos: " << child);
				if(!w.getOverlapBoundaries().isInside(child))
				{
					continue;
				}
				Engine::Point2D<int> localPosition = child-w.getOverlapBoundaries()._origin;
				log_EDEBUG(logName.str(), "\tchecking index for duneInArea: " << localPosition._y*width + localPosition._x << " and getting value for point: " << child);
				if ( duneInArea[localPosition._y*width + localPosition._x] == false && w.getValue("duneMap",child)==DUNE ) //!newArea.isInside( newPoint ) 						
				{	
//						assert( w.getValue("soils",*currentLoc)==DUNE );
//						assert( ! ( (childX >= newArea._origin._x) && (childX <= newArea._origin._x + newArea._size._x -1) && (childY >= newArea._origin._y) && (childY <= newArea._origin._y + newArea._size._y -1)));


					//std::cout << "\t Checking new dune location: childX = "<<childX <<" childY= "<< childY <<std::endl;						
					//std::cout<<"\t\t childX "<< childX <<" in [ " << newArea._origin._x <<",.., "<<  newArea._origin._x + newArea._size._x -1<<" ]"<<std::endl;
					//std::cout<<"\t\t childY "<< childY <<" in [ " << newArea._origin._y <<",.., "<<  newArea._origin._y + newArea._size._y -1<<" ]"<<std::endl;

					
					log_EDEBUG(logName.str(), "\tupdating area for point: " << child);
					updateArea( child, newArea );
					log_EDEBUG(logName.str(), "\tdune in point: " << child<< " set to true with index: " << localPosition._y*width + localPosition._x);
					duneInArea[localPosition._y*width + localPosition._x] = true;
					targets.push(child);
				}
			}
		}
	}
	log_EDEBUG(logName.str(), "\tsetNewArea finished for position: " << position);
	//std::cout << loc._x << " "<< loc._y << " newArea: "<<newArea<<std::endl;
	_areas.push_back(newArea);
	_scoreAreas.push_back(computeAreaScore(newArea,w));
}
*/

void SettlementAreas::testDuneInside( const Engine::Rectangle<int> & newArea, GujaratWorld & w )
{
	Engine::Point2D<int> insidePosition(newArea._origin);
	for(insidePosition._x=newArea._origin._x; insidePosition._x<newArea._origin._x+newArea._size._x; insidePosition._x++)
	{
		for(insidePosition._y=newArea._origin._y; insidePosition._y<newArea._origin._y+newArea._size._y; insidePosition._y++)
		{
			// if only one point is dune, add new area
			if(w.getValue(eSoils, insidePosition)==DUNE)
			{
				_areas.push_back(newArea);
				_scoreAreas.push_back(computeAreaScore(newArea,w));
				//std::cout << "created area with rectangle: " << newArea << " and score: " << computeAreaScore(newArea,w) << std::endl;				
				return;
			}
		}
	}
	//std::cout << "area without dune with rectangle: " << newArea << std::endl;				
}

void SettlementAreas::generateAreas(GujaratWorld &w, int lowResolution)
{
	std::stringstream logName;
	logName << "SettlementAreas_world_" << w.getSimulation().getId();

	Engine::Point2D<int> position;
	for(position._x=w.getOverlapBoundaries()._origin._x; position._x<w.getOverlapBoundaries()._origin._x+w.getOverlapBoundaries()._size._x; position._x+=lowResolution)
	{
		for(position._y=w.getOverlapBoundaries()._origin._y; position._y<w.getOverlapBoundaries()._origin._y+w.getOverlapBoundaries()._size._y; position._y+=lowResolution)
		{
			log_DEBUG(logName.str(), "checking position: " << position << " with resolution: " << lowResolution);
			if(!w.getOverlapBoundaries().isInside(position))
			{
				continue;
			}
			Engine::Rectangle<int> newArea(position, Engine::Point2D<int>(lowResolution,lowResolution));

			// adjust border
			if(position._x+lowResolution>=w.getOverlapBoundaries()._origin._x+w.getOverlapBoundaries()._size._x)
			{
				newArea._size._x = w.getOverlapBoundaries()._origin._x+w.getOverlapBoundaries()._size._x-position._x;
			}
			if(position._y+lowResolution>=w.getOverlapBoundaries()._origin._y+w.getOverlapBoundaries()._size._y)
			{
				newArea._size._y = w.getOverlapBoundaries()._origin._y+w.getOverlapBoundaries()._size._y-position._y;
			}
			testDuneInside(newArea, w);
		}
	}
	log_DEBUG(logName.str(), "generate areas done");
}

void SettlementAreas::intersectionFilter(Engine::Rectangle<int> & r, std::vector<int> & candidates) const
{	
	// looping in search of candidates
	Engine::Rectangle<int> intersection;
	for(unsigned long i=0; i < _areas.size(); i++)
	{
		if(r.intersection(_areas[i],intersection))
		{
		//	if( insideTheCircle(intersection,a._location,a._homeRange) )
		//		insideTheCircle, an extra filter, future issue	
			candidates.push_back(i);
		}
	}
}
		
}//namespace
