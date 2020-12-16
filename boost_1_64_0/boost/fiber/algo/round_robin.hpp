//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_ALGO_ROUND_ROBIN_H
#define BOOST_FIBERS_ALGO_ROUND_ROBIN_H

#include <condition_variable>
#include <chrono>
#include <mutex>

#include <boost/config.hpp>

#include <boost/fiber/algo/algorithm.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {
namespace algo {

class BOOST_FIBERS_DECL round_robin : public algorithm {
private:
    typedef scheduler::ready_queue_type rqueue_type;

    rqueue_type                 rqueue_{};
    std::mutex                  mtx_{};
    std::condition_variable     cnd_{};
    bool                        flag_{ false };

public:
    round_robin() = default;

    round_robin( round_robin const&) = delete;
    round_robin & operator=( round_robin const&) = delete;

    void awakened( context *) noexcept override;

    context * pick_next() noexcept override;

    bool has_ready_fibers() const noexcept override;

    void suspend_until( std::chrono::steady_clock::time_point const&) noexcept override;

    void notify() noexcept override;
};

}}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ALGO_ROUND_ROBIN_H

/* round_robin.hpp
xjtRFy6YS7rQx7qQCgGRXScBJLcPyxjtoLNQFZMmwpNCF4kplMaHyhr1M8f/b+f5q5+EchbL40ugoh/SIyxAW2PnJCXIyuFe7PB1N+9o1GcX7VH0W243T5pTjAchAFT7CuTwvHmKqJrjjo/SFPnZdTj7WYk65gGe/fSbjuOkdgGC0/RMaKXHCGSuALnXCpIiQKJXcJgzAaoDepbeTdP0wddplvGeIoR+gfAeK8KNFM3zNH2q/lZj+vewRRyVDcnebKwvkD1QCWMqxRagw8YWEToiiE9Mcb04h6X1NrdIbUKfsrfnhYX129Pzalt7Pi+P257y775/e/Id49enUst4fFHMtQuEnlatTZcKd+5DPB/ZpIL5tevhCUqlTEuWpUZRKU/tzyGHI5aFlDkzIo1aGYGNYeTZCmxUgppk41D20WMlJGVSwUeXyoK9oGC0AyA5l5F89qDMa0voI1NVq15ROd+667fqi2myVZ+5Bdh3axTCOxTYK25uVbnXFbmZwwDcrjTVrnsJyVuMZMiDJt+Bxm7kZDFiGXjrnbLIT9ySqJUMnqLA81TeEs776gGZdzpVWjFFEfw+5NjprJsq6TxA2yrGMZ41Cs8nHOJA8x45RdIZlu2smSPLPeeSbenDOH6qcKwk7AdKVVtCmrZMo7ZAWAOKJjGSkwlJQvRKUTOFwjuqVmRRoQFzZKFe0XYA/emjLP/7ZQYu/d3I9ddAMvZs7LBNHDHH96/e+g67w8Pn8fqC8GPZG+atCZV0HAe1eN9bcLGKQ4oHSGHPfpgXq+5jhe0tVSHFp2VIsZCDHOlH6sweJEUVjxKyXgLZciuyF24A8zUc8VC/QFBUcZ5DdbZZeHcoxJ7Ahto608oQZqepbOq1+TF3dOmtpi1JM0WLMikiuGo1tuhua4vOwBb9DposnE1/G+UKUT/sq/BmGYFb0R1yU4yxI2G8RGCstGL84HrAONlt+h5dBL9eJx55S4To3kuWZS80TwA23SNH69kAXXurS847Gp6wIBZjw0o5Gr9mF847BXmhVmMOl9IE4YIaIuIMImLRKiTiQSsRrZAI3J5mCXU204U6uQHnrJRjcRoDoZGnGGQCT3qsQC4F1J/0Y9xgJ0O9sYKg7DOEAAaSaOH7GiAW8o7LWcGx+9n0AXurqDFRHZBXdrqxTvpAAelDBMhtpkXmXujLRrti2YQyH8/6jy5TIQByXEThJu4IM/nP62eLFhnDB8Ff9Y1N390N7L9Z4nkMBtkW3f4fiW/oTSZ8W5c3iO91B3yZEt/cAfBXxerOGNAgvokPmfARqldmEapzERodzmV2LJr6l0qgViNN9T+W12D9wB97/YMkqtcuo/r33CWxNLhfT4A3k+BrB+LcrEZuDuJv1557h8TWiP1/At+GmYRv1Y1afH9f0kR84yW+D4JafHc3FV9biW/FCC2+wQpfI+b3b84gVCUDEFW1CcsXixlLHPhKCV823Q6/tlHwwyT8by60w09oFHwLCb9kuB2+qwM8g269RYCqLy8/qO3zdq/lvltsQV61kbrcL6wvv4K26mF6zRKeKr/6XJEM02uOq6ybMNMu8muEhbsLbc8qtnD+CWIyXOuBZ88CGVU2jsynp5DxtXwKG1/Ip0LjE/lUZKwfYoqdQdty5FqPT3r7WTTBjmTKjWde6SH1RErRdGLzcqh52x6iPZqW5v1sPBjgVI+JJbiFcO9AEUbtjliUUT6LsNwrsIyzYhkGWCwINgsEZRYEvQjBj3UIUgBBgbS6MjrM2ODm0FnkE1nQBQhdikA3x4ruhXHO6ALGlTp0/QndCw8iurlWdCXjZCBdoREbOBhlWH4POZ/2ZaQp3tc+Cw6FqVgWFdtdUZ8=
*/