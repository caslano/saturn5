
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
NwviPnt3Bovs2V95JijlKRC11D2KnVtvq+e39zVdhxZRhyzUoUzqUH2S6NBfr6sdulrrUJunIGpzdf0/Eb+PewS+ZqmYhFv6To7fp6++OH5fGK7uzMVim9/QU+D3N/YlqOHKS4zRkjT8fnApob8lYdqGtJT/g/D7+2ZwaVE6fkH4fUYIfi9R8fuipQK/twtvjN/f7/l/w+8bjPjd2w4HeEtPgcc27W0Ffv/zbRpgKQ4wCiLCM6RSCdYcaLp8UbTfJeF/hPb/bBLtK02i/S+aRPvb9Vi0nQ6L6tD+FVeI6XquVkP7Jc2i/c/e4mjfbVaJB0T7xRrav1eP9ov/C7Sfrj+nQjD3RdB+CaH9Ej3aL/n/Rvvfvqmi/ZKLoP3R9zeF9vXSLMKCZVWEvkvhqnTdSrg/oQZxfLsafgRE8RPibDU+/50ux6oJ5f9YTW+/4r8PVBM+zZUTGJY5ydBmXsY2hxyTm9XBkyz3i8iyR3ji5X4xWfYYT4zcr32Wvb070R7c6PBWxdi9Z8If2Y9GxpszqjYb+ZSlXUP4lPmvqXju5cU6PuU44bmelyGeS4tHPGeOF7BleUXlU3JfU/mU7hWN+JSpbzTmU1wmz0iGaAoEn1LA127rQJdZ5VVueKM1vMrq4iZ4lV/Xa7yKged851L9+Ql5Xgzn5/bXG/Gcs1hfJ4BU4D4BnAwqBxcYzBRmFahMZtnrrTlRw4qbYzL7
*/