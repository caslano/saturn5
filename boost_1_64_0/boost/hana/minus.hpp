/*!
@file
Defines `boost::hana::minus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MINUS_HPP
#define BOOST_HANA_MINUS_HPP

#include <boost/hana/fwd/minus.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/group.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/fwd/negate.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) minus_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Minus = BOOST_HANA_DISPATCH_IF(decltype(minus_impl<T, U>{}),
            hana::Group<T>::value &&
            hana::Group<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Group<T>::value,
        "hana::minus(x, y) requires 'x' to be in a Group");

        static_assert(hana::Group<U>::value,
        "hana::minus(x, y) requires 'y' to be in a Group");
    #endif

        return Minus::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct minus_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename T, bool condition>
    struct minus_impl<T, T, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::plus(static_cast<X&&>(x),
                              hana::negate(static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct minus_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Group, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::minus(hana::to<C>(static_cast<X&&>(x)),
                               hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct minus_impl<T, T, when<std::is_arithmetic<T>::value &&
                                 !std::is_same<bool, T>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) - static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Group
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_minus {
            static constexpr auto value = hana::minus(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct minus_impl<C, C, when<
        hana::Constant<C>::value &&
        Group<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_minus<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MINUS_HPP

/* minus.hpp
muKmvtp8pxaz2JFv0rE/0Zt2ETzVfn+b+W76Qt9fp3HRyDzV0niz+c5pkL9iV0dP8JPPdWXvdsv0PNzE+vzpstXEO9619yP2G4Qb/Epj/wn7Hdc3/v3Tv6TYnOpe3sWW/AZ9N1ESOxrHLtq8gdqu5Ih8Nq9n43RO97TD3QXtM084n3hd4DRnnnk337V1P6/b4a0+ugqAFVvbVJ8VtGa/zMq1N+jR2IB0a/abDOaRXrrG9i6C+f48GBOv1O5dP50Do3cAWF0MtzYnau+y7f4lb/cEhoFjpSbs1tJvWblWFCqdI1trf23nV64O96FhGI7aA2Awte39F5Ur7duQw+xamKv/ysKARxSLIImm9rll83kdDeMBxkgbLKbgjagM9Q16jYfN3S0sDJEfjG0fbmfLePNYPNQ7UzmOzznl99TlgXkYM50An9Oe5ZS7ROxaWNQwZbjE/IsfqL8lpRcQJ9C6ErzMcIAti7oye8pSWdGVmdO1K1vpykwI4QHtPY/SZY9M0pWiqeuC6mzq7yvBInW769OTbBnbK8bm2wkGb8fxApXxIepsw56ry9NQev2J7nC8iGA4km5/f4UuX5UypAY8lWJIU9n8um/Q5X7Emk5132rK3KZ3dd/T8gCSRlFtWkMfpLL5dG80UOVqAbcqNEWXxvOfVzVlRmXGyj71L1tmVGSsvR/9FfNdP7exB3WyYx/3yTnlaPjOBTZfn5kDs872vC/MKT8cKTfCEfHVl2wcQG3i2MnQP9ffYdW6sTdW3ymX5SNd/wJoVLzAl6ETI4sL9e3rknZZPiKzoM7v7KKDLxBljittJHCYaptRFtRpNh/jq5y6UlR+VktZ6comWepMdcrV2qMbeH4Ul1kqwvmUuV3cp3p0lSa9CopKhJzwbLtt/e/26heQWoOg8oQMGPVL1//DI3s+Ll6Y1mEZof5/agHVv+JRLv2wisKqwGRGpgJewYwtLQ4bU53FmTj2KPcNs4w9P5EJfEwOMPmIQAPaOOZaNO4xaJB1voPCwZUI6TVRICuWz1X/YHIJAd/R/vl9ZPWlt1/kpDAxJT3KWcNxhoFIUlzVw8LrcLLXO/6mfPZoqsvwrkvxX5yxykRWFUUl66LDNaVOc7Smn5PM8oyDJxeBlHVZy7jDU65f3Nk72lPPy1tYjOgx+b4YZGSv4bzlQGfvx6HUdm8u3A85zZNZ5Yd1UzfKRsLVZ/+Uw52uk9CrU+i+jdVqD+fHOe0wqtSrWKH02S7csgMnvbwuywjvhn24Xztt9JOgyZQn9rrtC713cbjlUlahztBA1jBmjRzZPv0D8Dz/Txqq/Pla72iBhYW9+qMZ7GIexnGQx76CpbcgQTn+AcvnMZXSC7Oq6ebxSsugKpr3IfyOZgIEWt5aeHTfLzr2GmWkIfue91iLZiW1S3IJZijdXvYop02BwPxFadjgQfTwcP2piqF0kAYESKLATQHFJu21ISvCsiyrcH4b3NUsWPyF13E8lfChZSlDWYsd5KbqheHcPmX3YF6nFnniN3VVZGobS5SjNGijaveOaOt91K2XlqF6act79c5SPcqLyOvhyAqCIirzOhGPPjiCO7EOsLixjSy5+8YkwZoKaAuD7o3/Vo/hY6b8iWWVVzJFZ3nsBG4hjSPJZMfa7+KQJg4eT/hN0TQetPtKBAR5Hdqw28YXtOOjmgxjO2N5087BNsdXiToKylgF7Vk4fuLk4tKp08tn1u2gHFFMLacNkYrf4Bd5VQqP7BR4WM/J0RhehJRPm8UAcvCkIooxsnUR/Fc8ba+cOJyf57h8DIdfFHlhM1IzLK6Zirk7mWXG1uyvnbbVIkDbUmw186SMRRV5pMLks7KnsPfSWz3WyXs=
*/