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
Qo1GUqxLjUqePehDJUn44zV/ma2jjj9kEXXMB7ryFFHHQ58idQw7gNTR+RFRx3xlys1EHdmBpzybT0K+ck9arOQrrNlzq7/hYOoMm6l0VwgnjlXwo7i6gcxGiC6CYk6XX3R08eUQiZNdYF1RH6qOH0HX86winlWkOZVfHqKSW8wqsKkW1/cgG8zPrGivPIfbK48B629hrxwmafbKlq1WRG/VZBEu1yqfnCZu7ooQ+nQut1c+qrNXhq/pOwfYt2sf33aWPj5hoJ4UqT25l/dkbPCejGrTkwzek78b2u/JKN6TIv3HdWfoYxfvSYHak3t4TxzBezK6TU/eb6XKBl6gJ6N5Twr0H1vPCHb4lKQTDN2frec5urHzTnacWFjOAbNEG08sUjkQlpiSLezvxYk2ggOaxrLkBhYjCZZlU28ftX5GHRck6SjkpwWCU9lTQPtwO3++y59/588XCpBXeZoeG+ixhh6r6LGcHosK9DYBfnFreaSuK+rUPQ2HGyS83zB8dbMuWG2Mk06eLXzaf6dt/ec+3Nazkds1319FaBjj7a0YRyfPFkRU707geAvzPENjuVqi4H6/vUXP/aIyZ76Ixcc4nCGTgcMhsRgwOfCO4UiJfpqHfCIuVgcvQ08tPR28LaAAdNIGnWqLd12+QTgOSuYsz623UEzSt3nQWYriqMYUhMMeJAk80UniXthKEkH1zvJBkoRuyJTH+/rE
*/