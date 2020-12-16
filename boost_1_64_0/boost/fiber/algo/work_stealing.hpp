
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
FvgAwm+S8FU2+CqCDyB8laLfCh8U9Ev4aht8NcEHEb5a0W+FDyH8+RK+xgZfQ/AhhK9R9Fvhw4L+ywl+qw1+K8GHEX6roj+J7rhwubkshSJzRglNAUWeTqIsL22ZNZ1xpz2pZLEY1G+c/BO5UHpjEm5rmsTRk92mUE/IOFQsi4WhGLmVWIaDVzzl+t0NsmBXKEhJi84SOhjWJVHh4uGQfHRtNiUQqaKtxqqIWF+NYJG6anl2J4JUfwp+VG0ODG9o/qZEM0yJ2hDzQmKDVNPAUeHRrqMl5FwBydQGLLw5U9ASedTocp2VLRxq/HyCxNMnMT5b1l1PBUUskpKm9pBsyZdsmYEPM6xsWQS+MH9pjDkjT3sCus1QutYNzMkThsDKnwK1Nee+hDhU5oumzQxyInq/UOeHth5Jf4cEcFSa0z+UI81OfsDai7jGLKNusmxXIrTLeL1Y2+eCxvzxstjHSMzDxQ4yuFoVe84tZcDB2yCvci9WVS5FXEXwZj15dZM7Nk2grQQU+DpjoMmvKDJV7jNRlGOsOJMGYAZB/Q0GdW0Xt0LyJ3g1viyxn47wcJ0mvPK4/tMDyD+heQiHpMOmkrg7/PUS0Ye6WYuG7EUxjvkgFMUWEv6B2MJ5fIIpF1s4VLawGFtY7MINqfWaJ33kVgNMbCl26FphY+4ZxJZUgnobjGu0FT2/BM9olN3yjEmdiGb7fku2effPaQJlsc2vFxAIdn0yymq6dPXZyh5PpINWfeEIh/Hff4TjxO9f+GOvE/pL5gHYJICPQ8bivEM8Q9zP0n1MoUj/1cJD5c3+t7k5tlhdFKLBugi9LrGXW+4tqjE2jpd3bcwCXwJAxPPMznlVt9Gmv15L09H/v6syGQ7njxedPVtsxvbiEwc9pY8edEVa8ruMVgVjm7c+g+Uj1aZCOR8NbkzG5p89VGVVLsRWGpcEOAHU8xsTYm8weTW95RhPmd78xirTW8D4uektaMwzvYWM6aa3sFHMbzKY3HNULEFsh/NBQl7VA8SXDnemu1Su2N311FTMfZByv71D7WC8Z+qOJtzvcKx/uvgE9pBMKadM0avAgkJsV2RkyYwslRGSGT6Z4VMZYchokCiqEMC8eBy4fvHGNM3v1LRAwy1oNP1ZTpX4nOjPabh2NZ9efpUcmv2eqGwNLlKq0ac7mjXPA/AK18zdDX/0E1TbrLiAEKnjkYU0x60xbujHSyVx+K9pLqmO/T8WaMEgn+RXgSX9soIpwFVNQHn4hl0+eXG6a+MqzDmabZ6lyr0aw8iIbq/koOh1bETnDRJ7NbapQ6GvBYvcmB4dyOdl5q6IHQutornjAEQ7Qs6bdWh7DMIReRk17zooQebYc4Oobaobm2o6Peol9LTSASstKbw0RKG7i8gtCQv3miK9o6n2dFF7F2vtv8oHb8atSBKw4JFmRtON307SHlmNFMSOlu6+1t4usU2dah1Hta64XVNrH6y1Ep4ciSFkrH79pH7bjpZxrBEMSLtyLuB3GWQJQDERV55CzWgpmjHY2oxnQHLR5gI0mkpsv7PkXxm4OkY/01jbdoUtHtwDdtsJswkDbl2XHXWNjgcLdD8zoaN5vpf3Fsm0kEwDI9pGpYVBW2BaiI6NTJEwnVSz4JiCNJy0/wHDAxIHlwkZtUNMZYIUAgCcpjJh4xVzmRBO8xsfxmv0/ZqCFQsut7DCr1hhIjsgyOaDtRfbyfYbbc3NpfmfjeyAsSdkIzvQVJKc5bl5pIWILA0RPiZCL7ssY3jIRkSWnQi4EdROhM8uuxwjOWSTXU5TCW3Yfi/y7JrX2j550YVu115mNVKmaGyNsaYXDxxH/5frBGIyYdW7hcn3bej8o6ybXVA=
*/