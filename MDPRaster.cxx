
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

#include <MDPRaster.hxx>


namespace Gujarat
{

MDPRaster::MDPRaster()
:IncrementalRaster()
{
}

MDPRaster::MDPRaster( const Engine::Raster& baseRaster, const Engine::Raster & intDunCounter )
: IncrementalRaster(baseRaster)
, _interDuneCounter(&intDunCounter)
{
	_delta = 0;
}

MDPRaster::MDPRaster( const MDPRaster& MRaster)
: IncrementalRaster((const IncrementalRaster &)MRaster) 
, _interDuneCounter(MRaster.getInterDuneCounterRaster())
// should call MDPRaster(*baseRaster.getBaseRaster(), *baseRaster.getInterDuneCounterRaster())
{
	_delta = 0;
}

MDPRaster::~MDPRaster()
{
}


const int &MDPRaster::getValue( Engine::Point2D<int> pos ) const
{	
	return IncrementalRaster::getValue(pos);
	/*
	int val = IncrementalRaster::getValue(pos);
	long intDun = _interDuneCounter->getValue(pos);
	int result = val  + (_delta * intDun);
	
	if(result<0)
	{
		result = 0;
	}
	
	return result;
	*/
}

void MDPRaster::setValue( Engine::Point2D<int> pos, int value )
{
	long intDun = _interDuneCounter->getValue(pos);

	value = value - (_delta * intDun);
	
	/* TODO : is this substraction needed???
	if (value < 0)
	{
		value = - (_delta * intDun);
	}
	*/
	IncrementalRaster::setValue(pos,value);	
}

/*	
bool	MDPRaster::operator==( const MDPRaster& other ) const
{
	for ( ChangeIterator i = firstChange(); 
		i != endOfChanges(); i++ )
	{
		ChangeIterator j = other._changes.find( i->first );
		if ( j == other.endOfChanges() ) return false;
		if ( i->second != j->second ) return false;
	}
	return true;
}
*/	
	
}