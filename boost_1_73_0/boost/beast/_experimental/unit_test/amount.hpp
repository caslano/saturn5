//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_AMOUNT_HPP
#define BOOST_BEAST_UNIT_TEST_AMOUNT_HPP

#include <cstddef>
#include <ostream>
#include <string>

namespace boost {
namespace beast {
namespace unit_test {

/** Utility for producing nicely composed output of amounts with units. */
class amount
{
private:
    std::size_t n_;
    std::string const& what_;

public:
    amount(amount const&) = default;
    amount& operator=(amount const&) = delete;

    template<class = void>
    amount(std::size_t n, std::string const& what);

    friend
    std::ostream&
    operator<<(std::ostream& s, amount const& t);
};

template<class>
amount::amount(std::size_t n, std::string const& what)
    : n_(n)
    , what_(what)
{
}

inline
std::ostream&
operator<<(std::ostream& s, amount const& t)
{
    s << t.n_ << " " << t.what_ <<((t.n_ != 1) ? "s" : "");
    return s;
}

} // unit_test
} // beast
} // boost

#endif

/* amount.hpp
Mj3xcfiTqOzG8kEWk/NPhmEbjS+bIL8yGe9NswDrN0OOpiCHYUerDS3YF03hb0zK9tZBzrcRuA5/a2Cm34OFL71J4S4yR0b1jLB489czp00mHwnsiAyKXtGH/ZIaPNOiCyH3QTq4n/rvJHKjCRfIJ5/t+CtgezH41XCzFnInbXC/AalpA+qSYSdFD0w27HoMiUGEaQP1wu8g3AzCbRk4PYg5C98Z7PPOxz/ltgKcLmAhcz4T
*/