
//          Copyright Nat Goodspeed + Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_ALGO_SHARED_WORK_H
#define BOOST_FIBERS_ALGO_SHARED_WORK_H

#include <condition_variable>
#include <chrono>
#include <deque>
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

class BOOST_FIBERS_DECL shared_work : public algorithm {
private:
    typedef std::deque< context * >  rqueue_type;
    typedef scheduler::ready_queue_type lqueue_type;

    static rqueue_type     	rqueue_;
    static std::mutex   	rqueue_mtx_;

    lqueue_type            	lqueue_{};
    std::mutex              mtx_{};
    std::condition_variable cnd_{};
    bool                    flag_{ false };
    bool                    suspend_{ false };

public:
    shared_work() = default;

    shared_work( bool suspend) :
        suspend_{ suspend } {
    }

	shared_work( shared_work const&) = delete;
	shared_work( shared_work &&) = delete;

	shared_work & operator=( shared_work const&) = delete;
	shared_work & operator=( shared_work &&) = delete;

    void awakened( context * ctx) noexcept override;

    context * pick_next() noexcept override;

    bool has_ready_fibers() const noexcept override {
        std::unique_lock< std::mutex > lock{ rqueue_mtx_ };
        return ! rqueue_.empty() || ! lqueue_.empty();
    }

	void suspend_until( std::chrono::steady_clock::time_point const& time_point) noexcept override;

	void notify() noexcept override;
};

}}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ALGO_SHARED_WORK_H

/* shared_work.hpp
NkPAvHVeSejhjEWsmTo5MKxz2cXJaJzI977AZO2l3ojkZu9C768eX8jRQcVEO7j6lu28Fz9UAh87DK1RIwEFK4Xyuf7B1rTzF6kj1+qtCsXuN6W9AMB07Sp3GJ1AAmSnrhGiH+OUULJbNC8unp19uxLHBSa09zzg/jxELdWm1o4xMIlEm7lTyRtO9yXN/44M7yeB96eiCP9tsor9zA910lnD2sOPqDiWr0M23O3U5TxuKRex0e8gB4MPKVCBFz/hL/vScB63rqxSfZe6/yK7UBP6PJ47iuB+JtAtz0YtKFAcFgA1n+wNyWRlA1zx1pZYLICodEXVnuXVwZoVOion2h7UMVt5aO2M6L1Dp7NCgBjmVSOJkE8GIUzP96dwJdWXYSv0oX/JOcUZTqgefxtTSssA5BnA+3aBUaiEWBFzsE/DI3hWKUXNxzS8rb84Hifl2IDqECl6+7w5d8yqRV7yezr2U/tLhYCVrXTsPeD1KEl16yJBmN8owO2ZA84nR9056+bwcWMQGrowhdSCS1UFAa5x32DzC8ZaghCYszrNsXEbhfS4mZfbiG3kuQ==
*/