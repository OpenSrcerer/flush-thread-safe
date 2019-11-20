#ifndef CARD_GENERATOR_H
#define CARD_GENERATOR_H

struct CardHand {
	operator char* ();
	int sum();			
	bool isFlush();		
	char pValues[5];	
};

class CardGenerator {
public:
	static CardHand get();
	static int nGenerated;		
private:
	CardGenerator() = delete;	
};
#endif