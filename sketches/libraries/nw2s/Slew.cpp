/*

	nw2s::b - A microcontroller-based modular synth control framework
	Copyright (C) 2013 Scott Wilson (thomas.scott.wilson@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Slew.h"

using namespace nw2s;

DecaySlew* DecaySlew::create(int speed)
{
	return new DecaySlew(speed);
}

LinearSlew* LinearSlew::create(int speed)
{
	return new LinearSlew(speed);
}


DecaySlew::DecaySlew(int speed)
{
	this->initialized = false;
	this->speed = speed;
}

int DecaySlew::calculate_value(int input, int t)
{
	//TODO: Can't retrigger?
	//TODO: There seems to be a weird thing at the end when slewing up.
	
	if (!initialized)
	{
		lastvalue = input * 100L; 
		initialized = true;
	}
	
	long scale_input = input * 100L;

	this->lastvalue = scale_input + ( ( ( this->lastvalue - scale_input ) * ( ( ( this->speed - ((t + (this->speed/5))/(this->speed/5))) * 100L) / this->speed ) ) / 100L ); 
	
	return lastvalue / 100;
}

LinearSlew::LinearSlew(int speed)
{
	this->initialized = false;
	this->speed = speed;
}

int LinearSlew::calculate_value(int input, int t)
{	
	if (!initialized)
	{
		lastvalue = input; 
		initialized = true;
	}

	if (lastvalue == input)
	{
		return input;
	}
	else if (lastvalue > input)
	{
		return --lastvalue;
	}
	else
	{
		return ++lastvalue;
	}
}










