
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
Y/Sx9xyVLttmv/WPF5bC1Wr4aTiZDt9NppN06Q2Louuy7tpwB+bjdDGP4NNwuhh7c27xSjYuvnEWn4MoIZ0mOFrof48i6DcW0XkUX0ZZ7KYzHUIlBthHXm+4SLP4Q3YxvojnS9qm+YQtT+0uTVtis7jOqThrwDQs550a/WQ8huE0ifHWejc/XB8aVuBjXyBZB0uw33zkYn/b7ff+BVBLAwQKAAAACAAtZ0pSlrGJtakEAAB9CgAAOQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUFJPWFlfU1NMQ0VSVFRZUEUuM1VUBQABtkgkYK1VbW/bNhD+rl9xUL/YhSLnBW3XrSumOspixLEES25qIIBAS6eKq0wKIpXEWPffd6TkJelaNAUqwxZN8u4e3j3P0b924flPexzfuIPvPpn9ZvTQe28Ut/IvzPXXDbLsM/QfMrym9xNCTeDe6nM2hidZfYaRtcqGWG/MOMueEO7agDQ/E2N8nZkhzfSWg/1UNruWf6w0jKZjOHr9+hc4gOPD40MPTpngWEOiUWyw/ejBm8LO/FGxuztf4VsPUAOr/UcO04orULLUt6xFoHHNcxQKC2AKClR5yzf0hwvQFULJa4RpFK9niz89uK14Xg1+
*/