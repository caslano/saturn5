//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_PRNG_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_PRNG_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/config.hpp>
#include <cstdint>
#include <random>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

using generator = std::uint32_t(*)();

//------------------------------------------------------------------------------

// Manually seed the prngs, must be called
// before acquiring a prng for the first time.
//
BOOST_BEAST_DECL
std::uint32_t const*
prng_seed(std::seed_seq* ss = nullptr);

// Acquire a PRNG using the TLS implementation if it
// is available, otherwise using the no-TLS implementation.
//
BOOST_BEAST_DECL
generator
make_prng(bool secure);

} // detail
} // websocket
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/prng.ipp>
#endif

#endif

/* prng.hpp
+LuJPTMYbY4+FX4tz/63oEdeusZol0ocP7neM3NtcWXk6UJx/yXQjzqZIG3y2PP7DZWOOTXiG9/oY8hUysYjU/N96vcyb/3WOf6icvOhl73z329G2H+IsNd8xTufflWE/akI+4EIe/VXvfbe2DV+Txvc21TljI4tykJbTu/Y59MGZ2ZOZ9HZZMRMVjFzjhq2kRkPfyz2b1RWF2l/6r++qQsfiv1g1LmZ/eL+hbY7J3yKbx9fHX4q7u+ZtQPPvOHML+Oudt3bSese82E6Zuksbpe53BaY9tdT3M6zfOcDtd7GiZ8XOEM+Rub+qjm6xZKmVnoNj/yqid+dVivqePkodfxF3vXuwYw/zvmQNW9463KaT10e7e2jon4T6OfI72aW/LrpGLsD5jrCf73Vp+5IlJ45kKL1Qcs3uE3maJ36RHx/fA7E9Vye94SVzYvOgazAb+q2qM+gcyCk3WcOhHDesQp29xzIGJ85kJHbisyBEM8fnwO52mcOZEyUOZDxLSLmQLQsN0UtSzMHErUcd271zIEQ1x+fA4ksx7M0/XO0Abyv88n/gHfZ5fhE1PTzbqrCzP1BpZixRbbE9XCwsxlbOPE3jTa2UPdGRh5MFvuWYBcr5P6mYt4tJhb4D3Y34wqNw8jHgPXOk7a9t993FvVb04xlxol9Z7C3FY76jeQ+8TMp6H5/Ih7z/rTK7/1J+/4M8feEewzCrHbh+qqfxb28uLdQd/7Rd0LmhXba7k8F3kVCuuNo7xobXCbPOzzy+c3YIlHiqOhJA/XYyPBG+Kfc1O6Eb2PGWLESvgbr5Ux4E/ZrSf9ov/T6yX3TNzwm4c4O2vJ9tq4jHy3X+lhJcq3g4mq5dl6wNnPoA2kXlVTujy9m/cKDLlmwFzPezJt7+4S0Y/QJnz15/OObk3R84/5utMLYF+haqKLjn847ve+NCyLst0TYuz7pteeqPaz2NRH21112t3xPbVt0HuganiclulzTeSD/98p2W4vMAxHXiZ0Hiibj4mV1EenX7+8XYNbgN39H1GfJK6mM02fRuJqatrde7OnRxm7qv5EZp9+JnThd8zvzjZy5Q9xmq1xzwtZXvyrHNJ9XidtElWuO35Ti1lCoHzOHa/qZR5P4p07J5lKifz/1lot3PYV+PzX2BVHHTgO1LI9oWTbFVFAd9puJf++2Ystyzmzzmh+1DDUO854frezw533P//YPvue78sczTtyoG11dH0ZOKJ/Gb8qb0Z41z/OqEfmcSVpHhkj4qeEkW0IHTXvUeFtJOKah+HvW3JlQn1vdGxkdl35izwnXIM3jgmVEru8qzK88gpqzJpLfsv2uDE2lHlehnD8LLLM2BN/SOu3EPUrt7AAp9gqmH42ov0Y3p4f4mx9uwLhgcjCk9d6Jr06R/jdZ5y/PFPescAL9e5PAFuus4EnyHv6KfBNizcik9LHS3+q7/OC3C/qgurrGegTXPpY4agTX0M7780zOe/5y8RvS+VhyVOzLWE89OOD0/2dI2Onh8prXsVa2ae/filsTI0vmSfgYMzZZIHnZJbTFmqfjZU6gED/TWGGIP+3vM+xrXEnSd6gkrZCnaPzJco0I+WXJtTPDlYIxVmowGDE/O9b0+XeLv3Lh4uYs+oifvLAnDjN2QZ6Je+XwvYERZh0reW6ef9c75vsZds0/eqAJtLdqVtH+PV37jGcwo7B/q3+7+3nt3+XdJ9O4e/ltCfaqtvv/Tm8XvzYxUft2ypVrtCGYpP37LvFn2kfUdYqj39J9WBoX2Ldid/fbO9/29vNvR9ibv+P1f2aE/SPsbv+x73rdm0fYh0TY52LX9HnWZ+0/xZJfvq7PyoS38swJ231kVt7vW58l64U=
*/