#include "card_generator.h"
#include <random>

// CARD HAND //

CardHand::operator char* () {
	return pValues;
}
int CardHand::sum() {
	return pValues[0] + pValues[1] + pValues[2] + pValues[3] + pValues[4];
}
bool CardHand::isFlush() {
	static auto char_to_int = [](char c) {				// this is a lambda function that explicitly converts
		switch (c) {
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'D': return 10;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		case 'A': return 14;
		}
		return -1; // won't ever happen but needed to shut the compiler up
	};  // lambda that translates back.
	static auto check_flush = [](int* p) {	// does your flush check inline without loop
		return (p[0] + 1 == p[1] && p[0] + 2 == p[2] &&	// ascending
				p[0] + 3 == p[3] && p[0] + 4 == p[4]) ||
				(p[0] - 1 == p[1] && p[0] - 2 == p[2] && // descending
				p[0] - 3 == p[3] && p[0] - 4 == p[4]);
	};  // lambda that does the work
	
	int intv[5];
	for (int i = 0; i < 5; i++) intv[i] = char_to_int(pValues[i]);
	return check_flush(intv);// flush;
}

// CARD GENERATOR //

int CardGenerator::nGenerated = 0;

CardHand CardGenerator::get() {
	static std::uniform_int_distribution<> next(2, 14); // function static variables will be used in each call 
	static std::random_device seed;						// to this function without being members
	static std::mt19937 rng(seed());					// these are persistent between function calls
	static auto int_to_char = [](int i) {				// this is a lambda function that explicitly converts
		switch (i) {
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return 'D';
		case 11: return 'J';
		case 12: return 'Q';
		case 13: return 'K';
		case 14: return 'A';
		}
		return '0'; // won't ever happen but needed to shut the compiler up
	};
	nGenerated++;
	return			// returns the hand implicitly as a set of 5 values
	{
		{
		int_to_char(next(rng)),
		int_to_char(next(rng)),
		int_to_char(next(rng)),
		int_to_char(next(rng)),
		int_to_char(next(rng))
		}
	};
}
