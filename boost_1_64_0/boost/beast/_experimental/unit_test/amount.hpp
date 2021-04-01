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
WTdK4pdFplOafMncGpmWXAbLQNw2qc+qHHgjiFAq6wCrwSJjNsyCL1Jo2H7eFJ12bPggNoczqNpbjWgyP6je5HUCa3rFRECrK4QUajG58MIAPFIdap0MYCOojrnFdZJpoIOTe6poC2vtpF2W398SXt694BuUQG7Rig2ffnW+kkRg9jshvv/xnTJrEHPyvIThNb1OoXt8LnLeLvkIVztgq1TQXVjv0fT01rjxME7TxIlRR6deTEhqzYmu6wU6ixbnImJc/5/pNpn5/aAkZE11WeKwYlz3H9eeww7zgeXPltD/L1eJHIszHmLSdVf4Lf8pSmic2fXGniK9AQS65WB6yILysbG9Zt1V6cfHyXxcUeQKb2eRWEpU5B+RTMUXaxHHphyhScNw7eWkgdNCr/21ct/CzJCeSNzrvyiQrRYqvS9yiTef12FnIo03Sgbt+rSswf9JBSFPwLQE2sI8hbmqc8vp9wiDl6viL8iiXyugl7DGtAqZ6ldbykeS3u8aBBeJF8eqB8cx0NYCz9n+cy3uaaReA5RzryyJGjYYwFMMshSdHDxxjjh9kfb30g==
*/