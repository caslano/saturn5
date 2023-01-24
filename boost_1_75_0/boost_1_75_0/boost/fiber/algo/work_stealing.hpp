
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBERS_ALGO_WORK_STEALING_H
#define BOOST_FIBERS_ALGO_WORK_STEALING_H

#include <atomic>
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
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace algo {

class BOOST_FIBERS_DECL work_stealing : public algorithm {
private:
    static std::atomic< std::uint32_t >                     counter_;
    static std::vector< intrusive_ptr< work_stealing > >    schedulers_;

    std::uint32_t                                           id_;
    std::uint32_t                                           thread_count_;
#ifdef BOOST_FIBERS_USE_SPMC_QUEUE
    detail::context_spmc_queue                              rqueue_{};
#else
    detail::context_spinlock_queue                          rqueue_{};
#endif
    std::mutex                                              mtx_{};
    std::condition_variable                                 cnd_{};
    bool                                                    flag_{ false };
    bool                                                    suspend_;

    static void init_( std::uint32_t, std::vector< intrusive_ptr< work_stealing > > &);

public:
    work_stealing( std::uint32_t, bool = false);

    work_stealing( work_stealing const&) = delete;
    work_stealing( work_stealing &&) = delete;

    work_stealing & operator=( work_stealing const&) = delete;
    work_stealing & operator=( work_stealing &&) = delete;

    void awakened( context *) noexcept override;

    context * pick_next() noexcept override;

    virtual context * steal() noexcept {
        return rqueue_.steal();
    }

    bool has_ready_fibers() const noexcept override {
        return ! rqueue_.empty();
    }

    void suspend_until( std::chrono::steady_clock::time_point const&) noexcept override;

    void notify() noexcept override;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ALGO_WORK_STEALING_H

/* work_stealing.hpp
XGMhitPq64kt8Wi4/dqLhts0VoSMxYC4ptJ0fPcJitt0BUsrPUkqCEgzXnFymgJDVcz9vXTpQAD7pMjEJW29FDLFbhMSa771hEJzlD4vSpenjsgqKkUk94KoNF7/YbxvpUEjy3ZmW4dOvm3kHMi3o5QR9D96ENOQawhiCyjvV9bnc/9P+eSstZi/L4an8gdAs/Lcf/708shHtV7zbAfEh2G8Yz6yCefvUe24iTHYRMx+92qVMYC1d4Kk4EwA48HLHQGMBxmXUARMmmdsBJ4XPbcYvOa+DtUvXsEFrqCaxrK59ow05nGK5QRxlvBnVGvhqBlWFxg4TcaM7Dkb41bWFOsDSDjgLkfL2OSIC2LReD80yb3DYRZwhnBSDWrUOPwKIV/Z5uqYfOXHMShfWcCb/H0M0VOcxyNjNDPGL8b4XLnsHyMkMAWqmqoPl7mRc5nDosx6R5ZoSF6j9J1LBo35eZr8Jcrmnqsqlybj0cGactIunxb+PZpMSShWSrCn15tKRgJEprP2TSUpCLajGT6/JcEhhzjkBrtc4xzQkGna0oUh6dhe1gGfAJLezZD0QVeTtXTfottolpbjlyOjMlMLAqMEzECU8DHCIMPpDZmp8xhK+AfnxgAr1GCxE01/Awo2oMq0xTiCNSuxVo1AGlijP5XuAyN83lKgUNxqS819tGZcpjZNsGGqVYzGKoqwilZ9Fa28ilZdFae1KtK/
*/