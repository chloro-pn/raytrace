#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <vector>
#include <functional>
#include <list>
#include <condition_variable>
#include <mutex>

namespace pn_graphics {
  class ThreadPool {
  private:
    using size_type = uint64_t;
    using lock_type = std::mutex;
    std::vector<std::thread> threads_;
    using task_type = std::function<void()>;
    std::list<task_type> tasks_;
    size_type th_counts_;
    std::condition_variable cv_;
    lock_type mut_;
    bool stop_;

    using exception_callback = std::function<void(std::exception&)>;
    exception_callback ec_;

  public:
    ThreadPool(size_type count);

    void each_thread();

    void start();

    void stop();

    template<class F>
    void push_task(F&& func) {
      mut_.lock();
      tasks_.push_back(std::forward<F>(func));
      mut_.unlock();
      cv_.notify_one();
    }

    template<class T>
    void set_exception_callback(T&& ec) {
      ec_ = std::forward<T>(ec);
    }

    ~ThreadPool();
  };
}

#endif // THREAD_POOL_H
