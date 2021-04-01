
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H
#define BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H

#include <condition_variable>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <vector>

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/algo/algorithm.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/context_spinlock_queue.hpp>
#include <boost/fiber/detail/context_spmc_queue.hpp>
#include <boost/fiber/numa/pin_thread.hpp>
#include <boost/fiber/numa/topology.hpp>
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace numa {
namespace algo {

class BOOST_FIBERS_DECL work_stealing : public boost::fibers::algo::algorithm {
private:
    static std::vector< intrusive_ptr< work_stealing > >    schedulers_;

    std::uint32_t                                           cpu_id_;
    std::vector< std::uint32_t >                            local_cpus_;
    std::vector< std::uint32_t >                            remote_cpus_;
#ifdef BOOST_FIBERS_USE_SPMC_QUEUE
    detail::context_spmc_queue                              rqueue_{};
#else
    detail::context_spinlock_queue                          rqueue_{};
#endif
    std::mutex                                              mtx_{};
    std::condition_variable                                 cnd_{};
    bool                                                    flag_{ false };
    bool                                                    suspend_;

    static void init_( std::vector< boost::fibers::numa::node > const&,
                       std::vector< intrusive_ptr< work_stealing > > &);

public:
    work_stealing( std::uint32_t, std::uint32_t,
                   std::vector< boost::fibers::numa::node > const&,
                   bool = false);

    work_stealing( work_stealing const&) = delete;
    work_stealing( work_stealing &&) = delete;

    work_stealing & operator=( work_stealing const&) = delete;
    work_stealing & operator=( work_stealing &&) = delete;

    virtual void awakened( context *) noexcept;

    virtual context * pick_next() noexcept;

    virtual context * steal() noexcept {
        return rqueue_.steal();
    }

    virtual bool has_ready_fibers() const noexcept {
        return ! rqueue_.empty();
    }

    virtual void suspend_until( std::chrono::steady_clock::time_point const&) noexcept;

    virtual void notify() noexcept;
};

}}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H

/* work_stealing.hpp
V6OafHk7QKxu2iUcifroRPIX255H1Ec8vLGrZyra3eUayoo9qKnLK1tTJNLfs395Y9FOxkRk1YH+YGwy3FuLcfAy2v2/+QKLwIbmxl6dcDb+obc+QH3vOPgdezgw5NA0sjdxfeSleWvU1zO5fyNyZ/Y6aPJLZfDqBXOphwxCu3tiwnaEZtlwhtrb/N+CM4nWbJk4HmV8UpU75J0XgXm3FqiI/eHH1jEd3kmEM5QnrE9lgqfwnEGTNzv0kV3VVFgTvnXo8/dWTvlA+CktvA1CACdb53Y6EaK9U3053jtuwA2LZxp9BS/oszj322U+1w86DCMGzjgCFNZIZKhvceDOLYen6SvHAM90yt1t47p+puMLHSepsyKc6O1d+gNyUu0mTS0rqTQWSo/C2U5z1va1ERWEi2I82wvD0Oviwg/68CRc8OC7vmH6gEwxcs/AVWLP+rbM1CyqTIixH3oJ1cPZAMVCs9CWW8l6cZH6xzT+1xRx1phs6o65mH/icr58RUV1WpaL76J091bLAimvK15XmK3vSRMzpzIRXcFOKXwBBoSTHqw621uI7fg2BA==
*/