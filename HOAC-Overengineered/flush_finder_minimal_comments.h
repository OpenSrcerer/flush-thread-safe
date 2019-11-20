#ifndef FLUSH_FINDER_H
#define FLUSH_FINDER_H


// class declaration. Splitting it in 4 parts is good for readability.
// First I declare public/private methods, then public/private member variables
// this keeps the stuff in one place

class FlushFinder {
public:
	FlushFinder(int flushes, bool verbose);
	void Start();
	~FlushFinder();
private:

public:
	class FlushInserter {
	public:
		operator bool();			
		void insert(char* flush);	
		FlushInserter(char* pData, int nLines);
	private:
		FlushInserter() = delete;	
		void advancePointer();		
		char* pCurrentLine;		
		int nLinesLeft;				
	};

	class StringReader {
	public:
		operator bool();		
		char* operator()();		
		StringReader(char* pData, int nLines);
	private:
		StringReader() = delete;	
		void advancePointer();	
		char* pCurrentLine;		
		int nLinesLeft;			
	};

private:
	char* pData;
	int nFlushes;
	bool bVerbose;
};
#endif