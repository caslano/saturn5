//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_IMPL_ERROR_HPP
#define BOOST_BEAST_TEST_IMPL_ERROR_HPP

#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string.hpp>
#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<
    boost::beast::test::error>
        : std::true_type
{
};
} // system
} // boost

namespace boost {
namespace beast {
namespace test {

BOOST_BEAST_DECL
error_code
make_error_code(error e) noexcept;

} // test
} // beast
} // boost

#endif

/* error.hpp
1AoIkDDd44ytJDP23Ss6LQLCA5xaVlY8URWeBaYnOczeiZlf6d4ote/zgIRpgj0iEyadUKrPvYnoB1UIH6Z2hm4Xd3Pn/eiojR5d70sya4qPyznqBvzicpWlzWHWFK/LmVwgaZnNkXWi1yDA49lgeqKx83TzEbf/KmeZm9Hra7e7wOu86OvYeVTie9TlGV+See9vmcR3h1PcJr4M25pTwXirLUbCJuLvUrfTkSbukRXKmyQYm1DrJQ2BASdZgzTxqr02a39NkyNlc6Zo6q68HjI96mENOnZ7dPWk3NvT9/hekdqDelp0TrJKPcwxhTXv0fQJrq2sbYqY5wGTkMkI640i6chrNtYMLZPR/B6OZCC6lolYa6NV27xzj0uUkccz0Nk+nsnM5xht3Ng0ilC9WIRjpp3YbY8N7OSQv6Muff4Js4hj8Tc++p8s1UuR+33+sk7Cve3a7rL2Imhc+lz8fOmDEpH2N8s/ytgre0Tce1yJziHOO1zna39mtvSt+/gcaqqXz7aVT9jvRcelbtrWMbmme7YZ+zVQzlXDEaZt84S4+7qedcx0lh2zznudntfWR2zP25+QcG+6ttI3fa7363yg5Ch6xJ3iDNJjHvHrNds8F9HdH4TX9f73JfwQ5yuOQj1myoVcti97xiXhxzsi9FnHOeI/wDnQMcPxpuZBdcxzw8Zwheil+YzXhLE9yyxw90vR6UkY3CYvE7zDmOeZE919UHRSCYPbhLlWwkS4nx9zTUjpyHVAnjHPqRccEOL7WTR62ehdI3q/7+Ct00R17kJnqFvn/Dnf1qwZHMEigvfeF9HvzzGCyjPpVqHlfqe030/SfQtvR/PcRY8Pg6/DZ5CNDfW5QzXWyqVPH/Ps0xk++nQux+gzHNM+o3qUqz5LtN2nJFScS/yRsCnfSV/OS8r2Xt/QfcFmHqG6Ok+YSaxcF64tNvMI42/qY+EZrF9wLo95AvHjJn6ve/UDPvJxL/koNPnwvVYxw3tPYBV5KTyzvNjnPDzjqF5eMHolfy/pM+6NyDLCrjB58b3ukOZRL6rvPy/4ez3HFncaT3+d3ntVzVhX83iZbdCeqtMlTsc1276SLRLPUkc8eZqNuPvdIQpgfyKa7j4VPsRWfto3VceRZO7vV3vN5Y1O63KdWyro6PP3y/EfVc1nePU9nr/r/aeP+rH6zFA1FHuxtrUeSJy7fo6b+vG8t9f7POpGn82pLiHPdQR714/oDLB0OEscrUDHHsnPtTHVGSv0e3rh1cvT0d+VBW7HSZrDIEieuLiZPHndP5s8mfu+eNE9qPYprLDx/tqf+rc2c8LW4v7Zp32Kifgni/83TrXjqve+ek+i19TzRGe/09+1vqv4f61x6P1rWRSmbpK/R4c33utQuz7us819+gUS15dOnTeqDv7WNVT8f1V/PZfuDSyEieL/g9PdrofTpk4nM9+Tdj264rVLdWKppylunUZzJnn1IaPTBx29Hz7l3T/a466N24U/++voJ+gS3qlud/tqgW5mtfpNYOiO7z3vfTO82lyuV5vTa5bur5PykmOF5hhl5DUebu5ScWz/k/sZ4A+mbfq8373fY2xXff/jIf6/fWy/32Ns99/PgrTTpjuJG14Cr4yk/1l5KXD3M5pk3hi6mXnHwJ4P1W1r9no1Pul2Jzp95csdf7j4t3dqPjV8a503WnZbbHtXdV2wiYQ7x9ZX0NH1IKsPXCM6b3rsBZgaQ/6g/obVbU+MWfJuQPXGrIzzdG+eXiefRDoTtuSUlGVBUp5nWdrX/LSvq+4j7GIZ7m8dRHUi+KffvhX3GscY/p+O+FpXzTXhHuO+aYjfddQ30CGc4wryZe2/SPlR6tfsJQv9Ddc=
*/