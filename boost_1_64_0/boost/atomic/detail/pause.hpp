/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2013 Tim Blechmann
 * (C) Copyright 2013 Andrey Semashev
 */

#ifndef BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_IX86))
extern "C" void _mm_pause(void);
#if defined(BOOST_MSVC)
#pragma intrinsic(_mm_pause)
#endif
#endif

namespace boost {
namespace atomics {
namespace detail {

BOOST_FORCEINLINE void pause() BOOST_NOEXCEPT
{
#if defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_IX86))
    _mm_pause();
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__("pause;");
#endif
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_PAUSE_HPP_INCLUDED_

/* pause.hpp
pp0/nApHwDxYAfPhzbAA3gnPgVVwlrb/2fALOAfazzbnwjZwro4fpTAdlsNMOA+OhufDu+ACWAUvguvgz1Vfw6zIvLTMbcuzUjM4UK/LRlRg821RBe1bv4v1LjwYbtJx4b3I98XMvK/MP5tnrBEh7dd1PLkCHq/fhxsEt8KR+l04+eaofsftet3j8Ua9v1qu32O7Dd6l3+l6BN4OH9N8noMr4Vv6ncBP4d3wc3gv/Ce8D8bZ/StsB1dD6oik7wkfg4ervz98Ur/D9iz8JXwBroKvwNfhq3AX/DOMi5N00h+/AQfDDXA4/Assgxsh10b0R98u+lsDt8CP4V/hZ/Aj+K3mt1P0o/OhcK22o4PgYr1eP4mrvV/tDvvCHvAI2BMeB3vBE2Fvre8/hdmwD8yBGXAizIQL4FHwYni0joPH6PjaFz4DD4sz9/k6hyjXynOfP4J+weZIGK/+Zuo/QP1J6j8MjoKjYDacCMfASXASnAzHwhlwHLwUjoeXwwlwKcyFN2j8qkbu/bkkxm+3bdz84+4DmnZi7HuBJrzfdN9xy3y/4X1Bm+pbbrugc3/QhN+R5v3/zD6hzu+6Xfn+vtsvdNX7/997hq5ZEbY24L7Cpd0etgbipuDm45bhnsJtxNXgku4IW91wWbhcXAluyR379xz9f/z9SPv/2W8D2RsA7vX+f4+a/f/lOVN+D+G66pjXPJP//m72oco9JrO/vE0lVvLBtnKSxmkrlyH+RRI/nClrS+eYtTqN77SV6yv+cvfeFsZOrreEXyT+bJO+t/M9UmMj10PCisQ/RuM6beRuFH/YlM29X9/VEt7CGT/Q7u1ECZsVaPe2pgns3igjx9CfHst2799Q7/328nrvzrVItOQ3x35uUx5AfluCrrEaufnt81UCe+wUvYf1XTnN54P4Qdai+IhODpU4v9Z3AEJWlfgfjE/gyTQnvr9/nTB5HWdsuzpKuqPDXyZ49ms07zt0kTiZUp5sk8c1zHn2MXuPnStxws66Yt63SJOwfuHImmfoa9vfwezf4M5vTF1+jnXRudPOc9h1P/GVHd7SU79S1fbqZEl/ADb28dgvxzvyKZEXnVLV7qzySzteKu8cjubedJzaP/PWv+RfGnchXy4+N/Qiz5NdRbZy1z4RD8h50uNb8xQTscE6/xv7GNdA4kSuTRtj4/mQhE+N+XsWud53q82eMv0l79SwHZ4sNiXzi5zvGV8p52phbBh6S/we4eyEm03bM+Uxdg9qK6V17XlJc0XC03HXWZfFv6h7ufjv+9JZ68hK0ev8+J9Zg3nGOoV1pzasxXSOM+90mz0QsN6aM9fY2GyQutHS6G6klC3N7Itq6b6oP9U+K0nOMzghA/uhSbhXcQNDXZl3bs4z/NPWSZRX4po2cn38CPrQm61E1kwmWP1Do637Qqcz73q5Je3G7C9aUiLyqJ1pnpxnQSiMPBcgzzbW/Wfw1oW0UVNfrqDkxfSCpDHnuzphhRUm/pGsMfW03ggdxdxsc+u2+EcD9sIJ3pNnvoRh7x9HX96cOcLuyN/iTKsl/aJ0wboXWSRONnGesOMkLvxZJE6uxumscTY0N/aI67BUOCAx8UDQMjHINu1h0UNP9Yes1SJ3s0BbtXslfqb6I/FbShk6aBlyWpg9005K7GOfPtkKOn9fSd8p5vN3lfDufuc3OthYd/6Ha8+fxH8JyUFl+LXkkRpzGa6X8C5+ZTDXaneLyLVa3D7oWmUewPyCHSd+8XVJ4WZJ8R2Twgw1xhbp/tY4Vx3IIc1TUk8WvxTJNyulfpz5xHnajtNy8R2ROCM1n7PwH6zvIKe3lfcQhYONq9uT6Y4U775N69rTM+tY3amtOGcc0uo=
*/