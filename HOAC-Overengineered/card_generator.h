#ifndef CARD_GENERATOR_H
#define CARD_GENERATOR_H

// simple struct representing 5 cards
struct CardHand {
		operator char* ();	// this one is just because i'm lazy
		int sum();			// this one is for non-duplicate stuff
		bool isFlush();		// well...
		char pValues[5];	// these are the underlying values
};
class CardGenerator {
public:
	static CardHand get();		// returns a random hand -> magic happens in the .cpp file
	static int nGenerated;		// the number of generations
private:
	CardGenerator() = delete;	// no constructor. 
};
#endif