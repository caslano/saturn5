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
vL12sqKwCYK6OZI8LpjlCXni1F1R520A9NV1gX3QDUpAlN+JZhzutCC3cqNopZ7OREU8gSQY5h2lk/UqTrJEqKueznC4H2S2oCAlixOIHtB8A9UCUI7jhpv4CtsYVog8xJ23LLBz4oziCrE6jhrq2QZ2/G42CALy1ijhc6vNADS9xJShZUHXORhh8tEHYnDGMgvO0JX6jpDFvkkJ8TbuyOJ9MQsXb2s8zSbOCgLiU9cntcJZ7Xx/zizDW1x8v1zcFoQWKKhDBdsHtbO2pCfZSqBvMBpEqJu1GdcnsQAJ9cRSY5zpQf6GAT/dZjZpJaLUOeo8ChtMFjDHoZ1yHVqNyWFwadn1YHOhczAqwQy7JlG+ZQP7iimpUymlWG/uQW/ilM7SF3bGNLGwl82mhT3KcfTwHC/5rN4GR5PGPJ0H4n2NSJH8nfN6/k3jhmHDqAG4YI+C7BX3KFKTl+MI1BRuPs2gpgp1zv+SZOMmybh+ZKJVeYBe3c9bq4TFBvuZn1AkZ4bIYChSYeezw6XxVN0INMVepvNq+w0OkorAppZe7obHWSbhxMppmkDoa5X4+HJIlAvyS6iYH2dpi1ficnqdOQXJHglIg1fBMc7Iz3MCoDSZ6DYHKWhekZnBcRiTwS+Yqadi3jExNFgnpnlEPSMomv9wCU+kxPxPBHn3pZnbiqHEvc3PerdN69vdtclR5xlBMv99UefSytsirkCo
*/