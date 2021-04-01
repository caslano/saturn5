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
CstyBE+YSzhrobzTWsBn302xc7tEZgZwhJiWPDUjc7/iW1OZH80S1kWvq1UB5IQdS615sxdp99X2Ps9W6oAVHp9d2hZ/WvhUyEgeDuTSRRNcMPgAu+8gbdHpvFjJ/qs/rglTe7+GhU8y8pZaGSTZINm3ocMYm3vwsr+/Xat5Ygnb5QVbUJWFftyh8cG0o3iplVihb+ZJoQg/eSSeLXugrFnrkUMnoMDniUL2MPTubL+7f3Ofm+m7b5cI/KD9BX5Lp03gbIlZRW2zR9Q8Bnt1F2NOI3JMOi3aJeLMR2sUIEa34MLY70M2anidhioMrmzhxPJypek2CzaBxV/x5Ebe4+naOY+npLhscA7PTe7M3WrzE7oE1pkNJcW917HhxEWVTsXYwug02jy+UzzzmlrrVYMZPvg4cm+c2rjQu+pdltaFiZwq/eXUSpjxnFmVeGByOiIJxwVGy04A7fEf9wTfcjVUucPsHsRl5fycoLD1FVzi19Xn9UBHaX8noEL1SX9TW5c2zcDzcnjopplqTa0S1dsgR43S0ftzyosO8hAgTwWK7LmSRSlYtClDuQ==
*/