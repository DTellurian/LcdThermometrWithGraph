/*
 * SingleRowGraph.h
 *
 * Created: 04.03.2015 11:31:01
 *  Author: Mihalych
 * 11.03.2016 Shorstok
 * Added option to draw solid graph
  */ 


#ifndef SINGLEROWGRAPH_H_
#define SINGLEROWGRAPH_H_
//---------------------------------------------------------------------------

#include "BaseLcdControl.h"

//---------------------------------------------------------------------------

class SingleRowGraph : public BaseLcdControl
{
	public:
		SingleRowGraph(LcdController* lcdControllerPtr, uint8_t x, uint8_t y, uint8_t width, uint8_t userSymbolStartIndex);
		
		void SetData(uint8_t* data);
	private:
		uint8_t* createdSymbolsValue;//значения уже созданных символов
		uint8_t userSymbolStartIndex;

		const uint8_t bDrawSolidGraph;
};
//---------------------------------------------------------------------------
#endif /* SINGLEROWGRAPH_H_ */