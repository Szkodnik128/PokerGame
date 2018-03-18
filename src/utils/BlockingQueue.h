//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_BLOCKINGQUEUE_H
#define POKERGAME_BLOCKINGQUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue {

private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cond;

public:
    T pop()
    {
        std::unique_lock<std::mutex> mlock(this->mutex);
        while (this->queue.empty()) {
            this->cond.wait(mlock);
        }
        auto item = this->queue.front();
        this->queue.pop();
        return item;
    }

    void push(const T &item)
    {
        std::unique_lock<std::mutex> mlock(this->mutex);
        this->queue.push(item);
        mlock.unlock();
        this->cond.notify_one();
    }
};


#endif //POKERGAME_BLOCKINGQUEUE_H
