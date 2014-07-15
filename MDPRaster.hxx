
/*
 * Copyright (c) 2014
 * COMPUTER APPLICATIONS IN SCIENCE & ENGINEERING
 * BARCELONA SUPERCOMPUTING CENTRE - CENTRO NACIONAL DE SUPERCOMPUTACIÓN
 * http://www.bsc.es

 * This file is part of Pandora Library. This library is free software; 
 * you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 3.0 of the License, or (at your option) any later version.
 * 
 * Pandora is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef __MDPRaster_hxx__
#define __MDPRaster_hxx__

#include <Raster.hxx>
#include <map>
#include <IncrementalRaster.hxx>
#include <Point2D.hxx>

#include <ostream>

namespace Gujarat
{
	
	
class MDPRaster : public Engine::IncrementalRaster
{	
	
protected :
	float		_delta;
	const Engine::Raster * _interDuneCounter;
public :
	
	MDPRaster();
	MDPRaster( const Engine::Raster& baseRaster, const Engine::Raster & inDunCounter );	
	MDPRaster( const MDPRaster& MRaster);		
	
	
	virtual ~MDPRaster();		
	
	float getDelta() const { return _delta; } 	
	void setDelta(float d) { _delta = d; }
	//void setDelta( float d) { _delta = 1.12f*d; }	
	
	int getValue( Engine::Point2D<int> pos ) const;		
	void setValue( Engine::Point2D<int> pos, int value );
/*	
	bool operator==( const MDPRaster& other ) const;

	bool	operator!=( const MDPRaster& other ) const
	{
		return !(this->operator==( other));
	}

	bool	operator<( const MDPRaster& other ) const
	{
		return _changes.size() < other._changes.size();
	}
*/

	void txtDump(std::ostream & port);

	const Engine::Raster * getInterDuneCounterRaster() const { return _interDuneCounter; }
	const Engine::Raster * getBaseRaster() const { return _baseRaster; }
};


}

#endif // MDPRaster
