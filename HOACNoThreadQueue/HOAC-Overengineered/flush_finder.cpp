#include "flush_finder.h"
#include "card_generator.h"
#include <cstring> // for std::memcpy
#include <iostream>
#include <chrono>

// CLASS ONLY USED IN HERE
// this class automates and beautifies the time stopping via RAII
class Timer {
public:
	Timer() {
		tStart = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		auto tEnd = std::chrono::high_resolution_clock::now();
		std::cout << "\nTime Elapsed: " <<
			(((float)std::chrono::duration_cast<std::chrono::milliseconds>(tEnd - tStart).count())/1000.0f) << " seconds\n";
	}
	std::chrono::time_point<std::chrono::high_resolution_clock> tStart;
};



// FLUSH FINDER IMPLEMENTATION //

FlushFinder::FlushFinder(int flushes, bool verbose) :nFlushes{ flushes }, bVerbose{ verbose } // initializer list in constructor. I like them :)
{
	// i'll need nFlushes sets of 5 cards and 1 extra space for a '0'-terminator. This gives me the convenience
	// of having valid '0' terminated c-style strings in there, so i can print them directly
	pData = new char[nFlushes * 6]{ '0' }; 
}

void FlushFinder::Start() {
	int count = 0;
	bool flush = false;
	{ // extra scope to trigger timer destruction
		Timer timer;
		// create the inserter
		FlushInserter inserter(pData, nFlushes);
		// while the inserter is valid:
		while (inserter) 
		{
			CardHand hand = CardGenerator::get(); // get random hand
			if (flush = hand.isFlush()) inserter.insert(hand);	// if flush, insert
			if (bVerbose)	// bah, code clutter. But this might be interesting
				std::cout
				<< "\rGenerating flush(es)... -> Checked pairs: "
				<< CardGenerator::nGenerated
				<< " | Flushes found: "
				<< (flush ? ++count : count);
		}
	}
	// create a reader that spits out the strings
	StringReader reader(pData, nFlushes);
	// while the reader is valid
	while (reader)
		std::cout
		<< "\t"
		<< reader() << "\n"; // read
}

FlushFinder::~FlushFinder() {
	delete[] pData;
}

// FLUSH INSERTER IMPLEMENTATION //

FlushFinder::FlushInserter::FlushInserter(char* pData, int nLines)
	: pCurrentLine{ pData }, nLinesLeft{ nLines }{}

FlushFinder::FlushInserter::operator bool() {
	return nLinesLeft > 0;	// no lines left
}

void FlushFinder::FlushInserter::insert(char* flush) {
	std::memcpy(pCurrentLine, flush, 5);	// copy the 5 values of that flush.
	advancePointer();						// advance....ok fuck this comment
}

void FlushFinder::FlushInserter::advancePointer() {
	if (nLinesLeft > 0) {	// if there's still space left
		pCurrentLine += 6;	// advance one whole line
		nLinesLeft--;		// now one line less is left
	}
}

// STRING READER IMPLEMENTATION //

FlushFinder::StringReader::StringReader(char* pData, int nLines)
	: pCurrentLine{ pData }, nLinesLeft{ nLines }{}

FlushFinder::StringReader::operator bool() {
	return nLinesLeft > 0;	// no lines left
}

char* FlushFinder::StringReader::operator()() {
	char* pString = pCurrentLine;
	advancePointer();
	return pString;
}

void FlushFinder::StringReader::advancePointer() {
	if (nLinesLeft > 0) {	// if there's still space left
		pCurrentLine += 6;	// advance one whole line
		nLinesLeft--;		// now one line less is left
	}
}


// in the .cpp file we implement the functions. this guarantees us the following: 
//	changing the implementation, as long as we don't change the .h file, does not
//	mean that any file using this class needs to be recompiled. This can speed up
//	the compilation process tremendously and makes it easy to think of the *.h 
//	file as a contract, that shows you what this class can do. The .cpp file, however,
//	defines, how this class can do stuff. Other classes don't need this information.
//
//	the only thing you can't do like this are templates. They need to be implemented in
//	the corresponding .h file due to compilation reasons.