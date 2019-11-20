#ifndef THREADSAFE_QUEUE_H
#define THREADSAFE_QUEUE_H
#include <queue>
#include <mutex>
#include <string>

class ThreadsafeQueue {
public:
	void Add(std::string const& msg) {
		MutexGuard mg(mMutex);
		mData.push(msg);
	}
	std::string Read() {
		MutexGuard mg(mMutex);
		auto msg = mData.front();
		mData.pop();
		return msg;
	}
	bool Empty() {
		MutexGuard mg(mMutex);
		return mData.empty();
	}
private:
	std::queue<std::string> mData;
	std::mutex mMutex;
	class MutexGuard {
	public:
		MutexGuard(std::mutex& mut) :mReference{ mut } {
			mReference.lock();
		}
		~MutexGuard() {
			mReference.unlock();
		}
	private:
		std::mutex& mReference;
	};
};
#endif