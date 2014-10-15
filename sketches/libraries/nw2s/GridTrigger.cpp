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

#include "GridTrigger.h"
#include "Entropy.h"

#define GATE_DURATION 50

using namespace nw2s;

GridTriggerController* GridTriggerController::create(GridDevice deviceType, uint8_t columnCount, uint8_t rowCount, int clockDivision, PinDigitalOut out0, PinDigitalOut out1, PinDigitalOut out2, PinDigitalOut out3, PinDigitalOut out4, PinDigitalOut out5, PinDigitalOut out6)
{	
	return new GridTriggerController(deviceType, columnCount, rowCount, clockDivision, out0, out1, out2, out3, out4, out5, out6);
}

GridTriggerController::GridTriggerController(GridDevice deviceType, uint8_t columnCount, uint8_t rowCount, int clockDivision, PinDigitalOut out0, PinDigitalOut out1, PinDigitalOut out2, PinDigitalOut out3, PinDigitalOut out4, PinDigitalOut out5, PinDigitalOut out6) : USBGridController(deviceType, columnCount, rowCount)
{
	this->beat = 0;
	this->clock_division = clockDivision;
	this->columnCount = columnCount;
	
	this->gates[1] = Gate::create(out0, GATE_DURATION);
	this->gates[2] = Gate::create(out1, GATE_DURATION);
	this->gates[3] = Gate::create(out2, GATE_DURATION);
	this->gates[4] = Gate::create(out3, GATE_DURATION);
	this->gates[5] = Gate::create(out4, GATE_DURATION);
	this->gates[6] = Gate::create(out5, GATE_DURATION);
	this->gates[7] = Gate::create(out6, GATE_DURATION);
	
	/* initialize the memory */
	if (!memoryInitialized)
	{
		for (uint8_t page = 0; page < 16; page++)
		{
			for (uint8_t column = 0; column < 16; column++)
			{
				for (uint8_t row = 0; row < 16; row++)
				{
					if ((page == column) && (row == 0))
					{
						this->cells[page][column][row] = 1;
					}
					else
					{
						this->cells[page][column][row] = 0;
					}
				}
			}
		}
		
		memoryInitialized = true;
	}
		
	/* Give it a moment... */
	delay(200);	
}

void GridTriggerController::setShuffleToggle(PinDigitalIn input)
{
	this->shuffleInput = input;
}

void GridTriggerController::setShuffleScopeInput(PinDigitalIn input)
{
	this->shuffleScopeInput = input;
}

void GridTriggerController::setNextPageToggle(PinDigitalIn input)
{
	this->nextPageInput = input;
}

//TODO
void GridTriggerController::setResetPageToggle(PinDigitalIn input)
{
	this->resetPageInput = input;
}

void GridTriggerController::setClockInput(PinDigitalIn input)
{
	this->clockInput = input;
}

void GridTriggerController::timer(unsigned long t)
{
	for (uint8_t i = 1; i < 8; i++)
	{
		this->gates[i]->timer(t);
	}
	
	/* Clock is rising */
	if (this->clockInput != DIGITAL_IN_NONE && !this->clockState && digitalRead(this->clockInput))
	{
		this->clockState = t;

		/* Simulate a clock pulse */
		this->reset();
	}
	
	/* Clock is falling and at least 20ms after rising */
	if (this->clockInput != DIGITAL_IN_NONE && (this->clockState != 0) && ((this->clockState + 20) < t) && !digitalRead(this->clockInput))
	{
		this->clockState = 0;
	}
	
	/* Shuffle input signal rising */
	if (this->shuffleInput != DIGITAL_IN_NONE && !this->shuffleState && digitalRead(this->shuffleInput))
	{		
		this->shuffleState = true;

		if (!digitalRead(this->shuffleScopeInput))
		{
			if (this->lastpress[1] != 0)
			{
				this->shuffleRow(this->lastpress[1]);
			}
		}
		else
		{
			for (uint8_t i = 1; i < rowCount; i++)
			{
				this->shuffleRow(i);
			}
		}
		
		this->refreshGrid();

		this->setLED(this->currentPage, this->currentPage, 0, 1);
	}
	
	/* Next page trigger is rising */
	if (this->nextPageInput != DIGITAL_IN_NONE && !this->nextPageState && digitalRead(this->nextPageInput))
	{
		this->nextPageState = t;		
		this->currentPage = (this->currentPage + 1) % this->columnCount;

		this->refreshGrid();
		
		this->setLED(this->currentPage, this->currentPage, 0, 1);
	}
	
	/* Next page trigger is falling and at least 20ms after rising */
	if (this->nextPageInput != DIGITAL_IN_NONE && (this->nextPageState != 0) && ((this->nextPageState + 20) < t) && !digitalRead(this->nextPageInput))
	{
		this->nextPageState = 0;
	}
	
	
}

void GridTriggerController::reset()
{
	if (isReady() && this->currentPage != this->beat) this->clearLED(this->currentPage, beat, 0);

	beat = (beat + 1) % columnCount;

	if (isReady()) this->setLED(this->currentPage, beat, 0, 1);

	for (uint8_t i = 1; i < 8; i++)
	{
		if (getValue(this->currentPage, beat, i))
		{
			this->gates[i]->reset();
		}
	}

	if (!digitalRead(this->shuffleInput))
	{
		this->shuffleState = false;
	}
}

void GridTriggerController::buttonPressed(uint8_t column, uint8_t row)
{	
	Serial.print(column, HEX);
	Serial.print(" ");
	Serial.println(row, HEX);
	
	/* Top row is reserved for the clock - pressing sets the current page */
	if (row == 0) 
	{		
		this->switchPage(column);
		
		//this->setLED(this->currentPage, this->currentPage, 0, 1);
	}	
	else if (!getValue(this->currentPage, column, row))
	{
		if (isReady()) this->setLED(this->currentPage, column, row, 1);
	}
	else
	{
		if (isReady()) this->clearLED(this->currentPage, column, row);
	}
}

void GridTriggerController::buttonReleased(uint8_t column, uint8_t row)
{
	/* This guy doesn't really care */
	return;
}

void GridTriggerController::shuffleRow(uint8_t rowIndex)
{
	/* Pseudo random shuffling of triggers, but keeping the same number of them set */
	
	/* 75% chance that we swap bits across the midpoint  12344321   */
	for (uint8_t i = 0; i < this->columnCount / 2; i++)
	{		
		if (Entropy::getBit() | Entropy::getBit())
		{
			uint8_t position1 = i;
			uint8_t position2 = columnCount - 1 - i;

			uint8_t value1 = getValue(this->currentPage, position1, rowIndex);
			uint8_t value2 = getValue(this->currentPage, position2, rowIndex);
			
			this->cells[this->currentPage][position2][rowIndex] = value1;
			this->cells[this->currentPage][position1][rowIndex] = value2;
		}
	}
		
	/* 75% chance that we flip a bit with its pair across the middle 12341234 */
	for (uint8_t i = 0; i < this->columnCount / 2; i++)
	{
		if (Entropy::getBit() | Entropy::getBit())
		{
			uint8_t position1 = i;
			uint8_t position2 = i + this->columnCount / 2;

			uint8_t value1 = getValue(this->currentPage, position1, rowIndex);
			uint8_t value2 = getValue(this->currentPage, position2, rowIndex);
			
			this->cells[this->currentPage][position2][rowIndex] = value1;
			this->cells[this->currentPage][position1][rowIndex] = value2;			
		}
	}

	/* 75% chance that we flip a bit with its neighbor 11223344 */
	for (uint8_t i = 0; i < this->columnCount / 2; i++)
	{
		if (Entropy::getBit() | Entropy::getBit())
		{
			uint8_t position1 = i * 2;
			uint8_t position2 = (i * 2) + 1;

			uint8_t value1 = getValue(this->currentPage, position1, rowIndex);
			uint8_t value2 = getValue(this->currentPage, position2, rowIndex);
			
			this->cells[this->currentPage][position2][rowIndex] = value1;
			this->cells[this->currentPage][position1][rowIndex] = value2;
		}
	}
}




