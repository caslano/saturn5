/* boost random/generate_canonical.hpp header file
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 */

#ifndef BOOST_RANDOM_GENERATE_CANONICAL_HPP
#define BOOST_RANDOM_GENERATE_CANONICAL_HPP

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/limits.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>
#include <boost/random/detail/generator_bits.hpp>

namespace boost {
namespace random {

namespace detail {

template<class RealType, std::size_t bits, class URNG>
RealType generate_canonical_impl(URNG& g, boost::true_type /*is_integral*/)
{
    using std::pow;
    typedef typename URNG::result_type base_result;
    std::size_t digits = std::numeric_limits<RealType>::digits;
    RealType R = RealType((g.max)()) - RealType((g.min)()) + 1;
    RealType mult = R;
    RealType limit =
        pow(RealType(2),
            RealType((std::min)(static_cast<std::size_t>(bits), digits)));
    RealType S = RealType(detail::subtract<base_result>()(g(), (g.min)()));
    while(mult < limit) {
        RealType inc = RealType(detail::subtract<base_result>()(g(), (g.min)()));
        S += inc * mult;
        mult *= R;
    }
    return S / mult;
}

template<class RealType, std::size_t bits, class URNG>
RealType generate_canonical_impl(URNG& g, boost::false_type /*is_integral*/)
{
    using std::pow;
    using std::floor;
    BOOST_ASSERT((g.min)() == 0);
    BOOST_ASSERT((g.max)() == 1);
    std::size_t digits = std::numeric_limits<RealType>::digits;
    std::size_t engine_bits = detail::generator_bits<URNG>::value();
    std::size_t b = (std::min)(bits, digits);
    RealType R = pow(RealType(2), RealType(engine_bits));
    RealType mult = R;
    RealType limit = pow(RealType(2), RealType(b));
    RealType S = RealType(g() - (g.min)());
    while(mult < limit) {
        RealType inc(floor((RealType(g()) - RealType((g.min)())) * R));
        S += inc * mult;
        mult *= R;
    }
    return S / mult;
}

}

/**
 * Returns a value uniformly distributed in the range [0, 1)
 * with at least @c bits random bits.
 */
template<class RealType, std::size_t bits, class URNG>
RealType generate_canonical(URNG& g)
{
    RealType result = detail::generate_canonical_impl<RealType, bits>(
        g, boost::random::traits::is_integral<typename URNG::result_type>());
    BOOST_ASSERT(result >= 0);
    BOOST_ASSERT(result <= 1);
    if(result == 1) {
        result -= std::numeric_limits<RealType>::epsilon() / 2;
        BOOST_ASSERT(result != 1);
    }
    return result;
}

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_GENERATE_CANONICAL_HPP

/* generate_canonical.hpp
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
*/