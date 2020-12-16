/*!
@file
Defines `boost::hana::mult`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MULT_HPP
#define BOOST_HANA_MULT_HPP

#include <boost/hana/fwd/mult.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) mult_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Mult = BOOST_HANA_DISPATCH_IF(decltype(mult_impl<T, U>{}),
            hana::Ring<T>::value &&
            hana::Ring<U>::value &&
            !is_default<mult_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Ring<T>::value,
        "hana::mult(x, y) requires 'x' to be in a Ring");

        static_assert(hana::Ring<U>::value,
        "hana::mult(x, y) requires 'y' to be in a Ring");

        static_assert(!is_default<mult_impl<T, U>>::value,
        "hana::mult(x, y) requires 'x' and 'y' to be embeddable "
        "in a common Ring");
    #endif

        return Mult::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct mult_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct mult_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Ring, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::mult(hana::to<C>(static_cast<X&&>(x)),
                              hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for non-boolean arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct mult_impl<T, T, when<std::is_arithmetic<T>::value &&
                                !std::is_same<bool, T>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) * static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Ring
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_mult {
            static constexpr auto value = hana::mult(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct mult_impl<C, C, when<
        hana::Constant<C>::value &&
        Ring<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_mult<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MULT_HPP

/* mult.hpp
YQ69XZU3KeTfR0KBY5aCqdgqHscHE0j3SptnXnC68/DnN+Hv7HkYhx4kBcE1fkuZ3U+Snv6lqVNPRToONHSnbFxQ+5P2wTNSeKtC5O9h3+3hSr0myrMSF8TRobnaMnxGMrEyC9JiCyY7DdJerIcYCliMiIiAxeYVxuZv8dw1LJjMs6P1zY5e6GrunudD6QFtrBS8EfQqYoJ3BMpt3dVX3zflY+tjPsOqlIiHonvn7vdvdWimoiriNEy8mtM0w+KSY/4yy2kvh74sQ8+H0juDWswmz8BRStyBPc7isG1e4ziWZFFlOLWUZgbzYP0SLL0npq581FS59GWTMXqc1MOWGBZLL7kh9w8tGynTovHF2aNzkxk7hAawXNeSe3GT+iHywBwdAjsoYO/H1KJy63WLy7x+H3lqT1+fuvlk8jTK/ML3GJ7xqK8jMTnSN5j9zoeBh+dVCGSoRlv327R9TPYMHBasVJR15eGSB1kSI7Q5sat2d1evWpiZrYNdDZeyN4J3PsCJxaOSumS4Aj/lKb0c479Oe3FrgrIMSxmJaAS/Yyei0lg/9OsXTSPU7giSXd/6dH0uDlWn2LEY3cbKyFfrYgBvQQDHXjixZV+9SlcGiXC0f6Erex0rm4xUp3Eft3p/ihkMZmVx8d72C/t9MjRsRTLoXbsybSEGNevuJuRbZF0mXfgXfm5hNnYRQUYBjqYM/2+I7mRfS4xbXU7YV91igLKN6UUlt3a2dmANPSJLFsdbvwi524yX2eIpNt81SS41gXK7AT2wdC58xYWxevnhLjJhDTo6z+BwRj62Zc/lZfqQ6spuQDIvZgSBLges3m2oDHSVtI8yOyevIZygxb6/lb67dK5HfTUzxeq8gOjo2J4bFLuVvkMQZO827yAaFDR4h/IA67K1YhVzCs0xhZS1Y/4J3ifbFh3udER3k19/vT/mTz7aGQFq+2i6iTBRANmgnLkEO+EQQ9vWTxM98Ii6GmJubVt+S2Xm2jjUG+Imj3HdHNP8A9zYfFRDj7SP1Catm7+p9Wj4Txm5w4ed9IKZEwshTZuwyBtPKDbd3dYywOKijbHOY8Vl7tkD0cMLZZV17yotPbUdjafbc6KeDc5U9gxycFU4x4o4z72IcOGsVZvVUsv6Glf/GsTfzh/F8RUiipMyCHJPdIKr++677dCHjFJlMTbaSN95TAW2+Vl6B3Q2ZO7ZkMRhJsssE0G7NePO5Z5pipWwNHc2tEhy6hF2v+d4JO47fuCnMqwFSJ7SY8fRzLhBQkTpflWqncrOcc7xYl/PcCsscKD8J5y7mzaB1mQEAMFiVzwqd+WwIA/Dpoqlbmd18BR9jKPTRoxy1TxgX+Da9+3Y5a78EdZVkmZBKa5kdzRsO7yVdgYobyfHcSYHiiICS2KUcRSzezLJpLmrU/KDqMmLABdVuUYes8kanHKPKy0wvSuyq+E+xUjyHVk4j4usytqnpUdbcIr54HHYwM8iPwoTIVdW6hUL+1DbJ9/14ZZJ3NR1kAmzrIwv7sle3mjvDsoH546YIy0rb+1Nh9vT6bgNaL632d5pb0b6a9xpKxlY/fXNOh2zfCT7dl2jL71yVZpvVrfsXxmvGjjSH69BSWy+ke4YK++k+UY640c+8pFGbwqF7OweZe7Zr7vdfHnC+LDouq0+fBj4Q28F7SHfmCMVh5rds757FSWHbR4ExEndPeubV0eZewajzLzfMLkDIZR38TBL8sETSYbwwnAFFyolgFzsZIyt2fItWI/sPpW9ee/2YVqBRHkLE8zhLMz48GB6AOmPYC7OwhgDsgG191kzMG6M4+dROaz0zx+NVRds2UsceUmH46Z6r3LKRlNup3BvKjNrmJW9tqM=
*/