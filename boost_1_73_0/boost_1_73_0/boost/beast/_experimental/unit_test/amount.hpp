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
aUm9M9irIXB6CImK2DWis953FQ+K1N5Y2+K0E9Bxb0fxfyKCGBAgrZ9LaWtG31lRdva1SeVGAYPYYeZXjx12RENjL02DDf//Hv9MhSkQa8jyIyniPF2Rtd6ilXOetCzNdvl/UEsDBAoAAAAIAC1nSlKn7aWnVAYAAAMQAAAoAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9tdWx0aS1kb3VibGUuY1VUBQABtkgkYK1XbU/bSBD+zq+Yo2qbcImdcF+uDaBDtL2i9gABFeKEZC32Gu9heyPvmhC1/e/3zK6dOGl6qKcGEZvdeZ9nXgh3ft5ni3boyU/kfiN88HQcZ5X+R8Z2M3UUfSH/A64bPJ9SEtKS5UvUp6dZvlDPsUSNlj1+j6KnFN2wbfwVMudNxK84ARtzHunpvFJ3maXeUZ/Gr179TkPaHe2OBvRGlErmdGFleSuruwHtJe7kj0w8PgZGHgxIWhJ50Ii6zJQho1M7E5UkvOcqlqWRCQlDiTRxpW7xhyrJZpJSlUs6Oj27Pj75c0CzTMUZC5nrmkym6zyhTDxIqmQs1YOXMRWVJZ2CHcITZSwE1lbpMoBuSVZWhWEZrF7kRpN4ECoXt1AkLGXWTs3rMIzrKof1YaJjE8at+0Fmi4Un1zCi
*/