
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_BARRIER_H
#define BOOST_FIBERS_BARRIER_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/mutex.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL barrier {
private:
    std::size_t         initial_;
    std::size_t         current_;
    std::size_t         cycle_{ 0 };
    mutex               mtx_{};
    condition_variable  cond_{};

public:
    explicit barrier( std::size_t);

    barrier( barrier const&) = delete;
    barrier & operator=( barrier const&) = delete;

    bool wait();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_BARRIER_H

/* barrier.hpp
4i0Sc2WPKVWR8PGqBuENB4vRtm7Yr2557mkt8tP4fdIOelWMH9aD+sda4kfU0X7V9NRLuKVIwPbtYVGJPojNEYll7xVZ4kB08/SMwNwYTcnhN3r1JgDr1Wmi12IM/8WeCOHvum7yP48H43HgVVNco8RcJoRiWl5JXf2dLV74/Ut30uVOKoQHl8HQGa4Mw3B9BN/GsgXB5OnWPgx91/WrEc4soYzCAIGMLcmIA5BWJUj+RYso2WSKMCcs9OE76UVO2CQM1frsVYvxSRstcpl1kzAKMjmAENnCQ/ynoH5FY0pc9R7CP0Lj7YiYTwM/ashtv+egzsjwclRj5exg7u23nt8J/zOnq783gFJ5+vV+Up9k0Hw0ue2To0B7iPMsJRyAQpAs8WQcM7jLXuFzRFEVP5hH2b3EHS+rr8C0RbCEivMbyov+0xQJyMcffuF37LEsMKQXYsfQWHousDFqEbGTZlk/gZ7oS+lHZV0V0bzxjH2zSguacJE+aJkZBLQIgeu3vncMQBUiv4JeHyHN5o6w2pGAVXSG4R7OYxKDOb1O3eDccGVqjgd0/uMqNQ==
*/