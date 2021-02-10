/*!
@file
Defines `boost::hana::negate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NEGATE_HPP
#define BOOST_HANA_NEGATE_HPP

#include <boost/hana/fwd/negate.hpp>

#include <boost/hana/concept/group.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fwd/minus.hpp>
#include <boost/hana/zero.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X>
    constexpr decltype(auto) negate_t::operator()(X&& x) const {
        using G = typename hana::tag_of<X>::type;
        using Negate = BOOST_HANA_DISPATCH_IF(negate_impl<G>,
            hana::Group<G>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Group<G>::value,
        "hana::negate(x) requires 'x' to be in a Group");
    #endif

        return Negate::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename T, bool condition>
    struct negate_impl<T, when<condition>> : default_ {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::minus(hana::zero<T>(), static_cast<X&&>(x)); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct negate_impl<T, when<std::is_arithmetic<T>::value &&
                               !std::is_same<bool, T>::value>> {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return -static_cast<X&&>(x); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NEGATE_HPP

/* negate.hpp
1jSa4ewkEMhfUSB6hX5P25h2e6AaUNcdDU7edMe8+FLHS8UnG0+iyGoR8fGSl9JtAcMjJavMwHrEi2aRtt0as5Wg9UUR4SzS9IdF/KvZHk80j1568iD5QfvcvEF8xoA+l/Z61KvYRzOjXh2IOk8G0ywjzYQN2kJJFoniToNGcmGmMNxtxlROo5vINKv7LENDRmh7beTn0JFsw6oiv1ICVFuUZYObKycO8oWdrpMU9h3hwuo6DR5+AL7xiYdmumu8ISO3ZnDvjX12amVuzlgDEuFO2tZy7O3ktyff/cEdEp2Qd3H8EfGAJg3rfQCChrv07vgh8L96gIZzeQpfEcC+AiC7FgoF2J/GsROAlMUAnG+/DTL05Uo66Q3Aot0OlLi63urpya0XpO4yqWcSQHrTSm/whMLZfQ5NgHBgv1nLq0wzRoMyFjwsgvg/UK6eNa0ef+vYzxBmAy8XlXzqCPoI9q+ffnKelnTl/+S7Ut7iJhku+2zfrdJufsfdbD9R/RTR6zETSIAG3fLZ/KPpPE5vcjy6omwjI3vh4N5sxgTWZPM+EA58m0Vr4Lf4Y/+QBWa8jQe70SN7dR3LornyQz/28PjT06f0Kw80D6WriPymTz95TbB8cvAHHfognMnCCz/g4Tz78lIh6ibWcbF0
*/