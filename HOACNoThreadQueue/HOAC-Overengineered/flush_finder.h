#ifndef FLUSH_FINDER_H
#define FLUSH_FINDER_H


// class declaration. Splitting it in 4 parts is good for readability.
// First I declare public/private methods, then public/private member variables
// this keeps the stuff in one place

class FlushFinder {
public:
	// constructor to pass necessary information to this object
	FlushFinder(int flushes, bool verbose);
	// start function that will execute the algorithm (just for readability)
	void Start();
	// destroys the allocated memory
	~FlushFinder();
private:

public:
	// this class is the one that does the inserting and counting.
	// I'll implement some operators for syntactic sugar and yeah...that's it.
	// It will be a highly specialized iterator/inserter for this use case
	class FlushInserter {
	public:
		operator bool();			// tells me if i can still insert stuff
		void insert(char* flush);	// inserts values and advances the temporary pointer
		FlushInserter(char* pData, int nLines);
	private:
		FlushInserter() = delete;	// so no one can instantiate this type
		void advancePointer();		// advances the underlying pointer
		char* pCurrentLine;			// underlying pointer to the position in the buffer
		int nLinesLeft;				// number of writeable lines left
	};

	// this one is the opposite of the one above.
	// this class only allows forward movement to read the strings as c-style strings
	class StringReader {
	public:
		operator bool();			// tells me if i can still read more stuff
		char* operator()();			// returns the pointer to the current c-style string
		StringReader(char* pData, int nLines);
	private:
		StringReader() = delete;	// so no one can instantiate this type
		void advancePointer();		// advances the underlying pointer
		char* pCurrentLine;			// underlying pointer to the position in the buffer
		int nLinesLeft;				// number of writeable lines left
	};

private:
	// these ones are the obvious things. data container and algorithm configuration values
	char* pData; // pData -> the p tells me it's a pointer type
	int nFlushes; // nFlushes -> n tells me it's an integer
	bool bVerbose; // bVerbose -> b tells me it's a boolean
	// this kind of naming convention is pretty neat because it gives type 
	// information just by looking at the stuff, while also keeping the names
	// short. Long names are always worse to read


};
#endif