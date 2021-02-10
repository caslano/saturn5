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
/G0A3AKrw0cO00oYMKq0N0xzwPda5FwaXgAzUHCTa7HGL0KCrTiUouYwimfLSfQxgJtK5FXvZ6daMJVq6wIqtuWgec7FtnPTMG1BlegB/RfCWPTZWqFkiPAcLNcb07uhIFhtFLAtEzVbIxyzUFnbmN8Gg7zVNWYyKFRuBvmeirCym6+yWmI0G7YD1ViwClrDA6DzAWxUIUp6IkW42LTrWpgquA8LAWUxUBoMr+veHZoKbroUOCQ9WwGdhAajF5YeRklDaDeV2jw6iLT2jspWS4RDWvBcoZD4AFpZcO3OOyL2KD3LjvJvlOw+9gKUxKjAHyYwSXxYMyNMAJeT9CxepHA5nM+HUbqE+AMMo2Xv73wSvUdtCETVwG8bzQ1GoUFsmlrw4hH4D+10L0zPYLSYT+NZms3m8edlliTT0XiewkvwT15BpLYo7pNXPvi1WFP14Zfw59PwBS7Qt4wzs8sMt1Rn/EVJGfSanEE0vBh7h12vnmNpLeBXaLS63UGOWUoLOddWlCJnljsXyTKKZ8kk8X4SMq/bgsMbwuxEWL31nPtc4frXoRzRDjyrUB41quRgGKjHiml4RqjHvzvA9+NkNJ/M0kkcea7GXUZU4RLLkSspcbwJeUXiwSKfpeks6XIIQCp7v2a43nIdet6M
*/