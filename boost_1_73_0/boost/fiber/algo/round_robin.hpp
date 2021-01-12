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
OVHL8/Q2jpt7AgMp/0pmUzaSc4/xdvCQdaX05dfarFdkbdB0tHPc5hthJfqrrDXsfn0T66+e93e3mgeaWMMCTa3iQJbE4RnyyNQDWUcQvlf8XeKzOZDEM1tn5HRreIA2LHt+fijn0mLCfheVs+jb6HeIGHeZ9WGvir9WMc2Yiz0FWRBIsX6HHOQqXnV/pLaXwZLuHYFLid0+5ynSnmYto+6vRrbahYxRWrEH4Az200u17/cn
*/