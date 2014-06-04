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

#include <iterator>
#include <vector>
#include <stdexcept>

#ifdef __AVR__
#include <pnew.cpp>
#endif

#include <Arduino.h>

#include "Key.h"

using namespace std;
using namespace nw2s;



ScaleType nw2s::scaleTypeFromName(char* name)
{
	if (strcmp("major", name) == 0)
	{
		return MAJOR;
	}
	if (strcmp("minor", name) == 0)
	{
		return MINOR;
	}
	if (strcmp("chromatic", name) == 0)
	{
		return CHROMATIC;
	}

	/* For now, just default to chromatic if we don't find the scale */
	Serial.println("Unknown scale name " + String(name) + ". Just using chromatic instead.");
	return CHROMATIC; 
}

NoteName nw2s::noteFromName(char* name)
{
	if (strcmp("C", name) == 0)
	{
		return C;
	}
	if (strcmp("C#", name) == 0)
	{
		return C_SHARP;
	}
	if (strcmp("Db", name) == 0)
	{
		return D_FLAT;
	}
	if (strcmp("D", name) == 0)
	{
		return D;
	}
	if (strcmp("D#", name) == 0)
	{
		return D_SHARP;
	}
	if (strcmp("Eb", name) == 0)
	{
		return E_FLAT;
	}
	if (strcmp("E", name) == 0)
	{
		return E;
	}
	if (strcmp("E#", name) == 0)
	{
		return E_SHARP;
	}
	if (strcmp("F", name) == 0)
	{
		return F;
	}
	if (strcmp("F#", name) == 0)
	{
		return F_SHARP;
	}
	if (strcmp("Gb", name) == 0)
	{
		return G_FLAT;
	}
	if (strcmp("G", name) == 0)
	{
		return G;
	}
	if (strcmp("G#", name) == 0)
	{
		return G_SHARP;
	}
	if (strcmp("Ab", name) == 0)
	{
		return A_FLAT;
	}
	if (strcmp("A", name) == 0)
	{
		return A;
	}
	if (strcmp("A#", name) == 0)
	{
		return A_SHARP;
	}
	if (strcmp("Bb", name) == 0)
	{
		return B_FLAT;
	}
	if (strcmp("B", name) == 0)
	{
		return B;
	}
	if (strcmp("B#", name) == 0)
	{
		return B_SHARP;
	}

	/* For now, just default to chromatic if we don't find the scale */
	Serial.println("Unknown note name " + String(name) + ". Just using C instead.");
	return C; 
}

Key::Key(ScaleType scaletype, NoteName rootnote)
{
	this->scaletype = scaletype;
	this->rootnote = rootnote;
	
	this->initScaleMeta(scaletype, rootnote);	
}

ScaleNote& Key::operator [] (const int index)
{
	return this->notes[index];
}

size_t Key::getNoteCount()
{
	return this->notes.size();
}

NoteName Key::getRoot()
{
	return this->rootnote;
}

ScaleNote Key::getNote(int octave, int degree)
{
	for (int i = 0; i < notes.size(); i++)
	{
		if (notes[i].octave == octave && notes[i].degree == degree) return notes[i];
	}
	
	return nw2s::NOTE_NOT_FOUND;
}

ScaleNote Key::getRandomNote()
{
	return this->notes[random(this->notes.size())];
}

/* PRIVATE METHODS */

void Key::initScaleMeta(ScaleType scaletype, NoteName rootnote)
{	
	switch (scaletype)
	{
		case MAJOR:
		{
			int noteindexes[] = { 0, 2, 4, 5, 7, 9, 10 };
			initScaleNotes(7, noteindexes);
			break;
		}
			
		case MINOR:
		{
			int noteindexes[] = { 0, 2, 3, 5, 7, 8, 10 };
			initScaleNotes(7, noteindexes);
			break;
		}
					
		case CHROMATIC:
		{
			int noteindexes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			initScaleNotes(11, noteindexes);
			break;
		}
	}
}

void Key::initScaleNotes(int notesperoctave, int noteindexes[])
{
	this->notes = nw2s::ScaleNotes();
		
	for (int octaveindex = -1; octaveindex < 6; octaveindex++)
	{
		for (int noteindex = 0; noteindex < notesperoctave; noteindex++)
		{
			int cvlocation = noteindexes[noteindex] + this->rootnote + (octaveindex * 12);
			
			/* Once we're past the bounds, we're done */
			if (cvlocation >= nw2s::NOTE_CV_SIZE) break;

			/* Skip the negative locations */
			if (cvlocation > -1)
			{	
				ScaleNote note = { noteindex, SCALE_NOTES[cvlocation].cv, SCALE_NOTES[cvlocation].cvin, octaveindex, noteindex + 1 };
				this->notes.push_back(note);
			}
		}
	}
}

ScaleNote Key::quantizeOutput(int cv)
{
	/* Output quantizing is done when we're going from 0-4096 */
	for (int i = this->notes.size() - 1; i >= 0; i--)
	{
		//TODO: giving it a few bits of slop - good idea?
		if (cv >= this->notes[i].cv - 10) return this->notes[i];
	}

	return this->notes[0];
}

ScaleNote Key::quantizeInput(int cv)
{
	/* Output quantizing is done when we're going from 0-4096 */
	for (int i = this->notes.size() - 1; i >= 0; i--)
	{
		//TODO: giving it a few bits of slop - good idea?
		if (cv >= this->notes[i].cvin - 10) return this->notes[i];
	}

	return this->notes[0];
}

