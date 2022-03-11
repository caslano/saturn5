
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
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
*/