#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <stdexcept>
#include <chrono>
#include <cassert>

class ThreadPool {
public:
	explicit ThreadPool(size_t poolSize);
	~ThreadPool();
	template <class Func, class... Args> auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
private:
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> tasks;
	std::mutex mut;
	std::condition_variable cv;
	bool dead = false;
};

inline ThreadPool::ThreadPool(size_t poolSize) {
	for (size_t i=0; i < poolSize; i++) {
		threads.emplace_back([this]() {
			while(true) {
				std::unique_lock<std::mutex> lock(this->mut);
				this->cv.wait(lock, [this]() {
					return this->dead || !this->tasks.empty();
				});
				if (dead && tasks.empty()) { return; }
				auto task = std::move(tasks.front());
				tasks.pop();
				task();
			}
		});
	}
}

ThreadPool::~ThreadPool() {
	dead = true;
	cv.notify_all();
	for (auto& t : threads)
		t.join();
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
	std::unique_lock<std::mutex> lock(mut);
	auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));
	if (dead) { throw std::runtime_error("Can't exec in dead ThreadPool"); }
	tasks.emplace([task](){ (*task)(); });
	cv.notify_one();
	return task->get_future();
}

#endif //THREADPOOL_H
