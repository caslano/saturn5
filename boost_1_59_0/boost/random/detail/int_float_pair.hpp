/* boost random/detail/int_float_pair.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Copyright Steven Watanabe 2010-2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 */

#ifndef BOOST_RANDOM_DETAIL_INT_FLOAT_PAIR_HPP
#define BOOST_RANDOM_DETAIL_INT_FLOAT_PAIR_HPP

#include <utility>
#include <boost/integer.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>
#include <boost/random/detail/integer_log2.hpp>

namespace boost {
namespace random {
namespace detail {

template<class Engine>
inline typename boost::make_unsigned<typename Engine::result_type>::type
generate_one_digit(Engine& eng, std::size_t bits)
{
    typedef typename Engine::result_type base_result;
    typedef typename boost::make_unsigned<base_result>::type base_unsigned;
    
    base_unsigned range =
        detail::subtract<base_result>()((eng.max)(), (eng.min)());
    base_unsigned y0_mask = (base_unsigned(2) << (bits - 1)) - 1;
    base_unsigned y0 = (range + 1) & ~y0_mask;
    base_unsigned u;
    do {
        u = detail::subtract<base_result>()(eng(), (eng.min)());
    } while(y0 != 0 && u > base_unsigned(y0 - 1));
    return u & y0_mask;
}

template<class RealType, std::size_t w, class Engine>
std::pair<RealType, int> generate_int_float_pair(Engine& eng, boost::true_type)
{
    typedef typename Engine::result_type base_result;
    typedef typename boost::make_unsigned<base_result>::type base_unsigned;
    
    base_unsigned range =
        detail::subtract<base_result>()((eng.max)(), (eng.min)());
    
    std::size_t m =
        (range == (std::numeric_limits<base_unsigned>::max)()) ?
            std::numeric_limits<base_unsigned>::digits :
            detail::integer_log2(range + 1);
            
    int bucket = 0;
    // process as many full digits as possible into the int part
    for(std::size_t i = 0; i < w/m; ++i) {
        base_unsigned u = generate_one_digit(eng, m);
        bucket = (bucket << m) | u;
    }
    RealType r;

    const std::size_t digits = std::numeric_limits<RealType>::digits;
    {
        base_unsigned u = generate_one_digit(eng, m);
        base_unsigned mask = (base_unsigned(1) << (w%m)) - 1;
        bucket = (bucket << (w%m)) | (mask & u);
        const RealType mult = RealType(1)/RealType(base_unsigned(1) << (m - w%m));
        // zero out unused bits
        if (m - w%m > digits) {
            u &= ~(base_unsigned(1) << (m - digits));
        }
        r = RealType(u >> (w%m)) * mult;
    }
    for(std::size_t i = m - w%m; i + m < digits; i += m) {
        base_unsigned u = generate_one_digit(eng, m);
        r += u;
        r *= RealType(0.5)/RealType(base_unsigned(1) << (m - 1));
    }
    if (m - w%m < digits)
    {
        const std::size_t remaining = (digits - m + w%m) % m;
        base_unsigned u = generate_one_digit(eng, m);
        r += u & ((base_unsigned(2) << (remaining - 1)) - 1);
        const RealType mult = RealType(0.5)/RealType(base_unsigned(1) << (remaining - 1));
        r *= mult;
    }
    return std::make_pair(r, bucket);
}

template<class RealType, std::size_t w, class Engine>
inline std::pair<RealType, int> generate_int_float_pair(Engine& eng, boost::false_type)
{
    int bucket = uniform_int_distribution<>(0, (1 << w) - 1)(eng);
    RealType r = uniform_01<RealType>()(eng);
    return std::make_pair(r, bucket);
}

template<class RealType, std::size_t w, class Engine>
inline std::pair<RealType, int> generate_int_float_pair(Engine& eng)
{
    typedef typename Engine::result_type base_result;
    return generate_int_float_pair<RealType, w>(eng,
        boost::is_integral<base_result>());
}

} // namespace detail
} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_DETAIL_INT_FLOAT_PAIR_HPP

/* int_float_pair.hpp
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
*/