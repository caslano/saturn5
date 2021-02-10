
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
YSkZNEpISyJDO5BtXT8nqQnJSDGkHfTZ9SnbcNzq+rLf6Lt6zb27CSDxGOkUm14foI/6zSm8D5leyfZBwKFHCAUvWVtbSm+DbY6J+rOTU59EnHBklUOqmTSN0tb1mj8bX7hd1WlVXgnJTeDRXo7ZrzmxKq8Q/QblDKtycpD8dDkbH708XpUz5OiSTkZJQpL/GjXoZhb5dlMJASgRKfLrPQf0/aF0aBDeYI87slvclbYjxUWELAuXKJnfjVVDsMLuoGCWYc/yECaOXe+Gyf0Ew9I58kvdjxe00cR8IXDYWqVRBU2NMuRIMU5fFCZCOVQ/HPgeLpbiNiBMpYteDVslCipT2RqSWhfjXX7EDiaA6E4hB0oduMG/UcbixXHN613Hk+SdALDWW4GBMEQXW2Lhmu/+vzbn4+VdWUgfrMEJhDAUWqFwApPK3fWCvq85bzr2egFrhaMUWElKx0bsOgXL53V9FPZN9mG4mKZetJhO3QKCp/Eonibewux180Co7sz48/BiNh17oSy9rrfdLPrjQecLKewRNrIoj2jxGP724L+DgRbuBwI+AvD3lxu/ZThweZirzcBHT980d7Q9cODifbrl/STyu7qGDd98nznWC62xpN9pinazYZJc4rXjm5e55rYzxpdHpOKlSqOh
*/