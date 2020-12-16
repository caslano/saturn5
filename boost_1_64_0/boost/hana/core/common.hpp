/*!
@file
Defines `boost::hana::common` and `boost::hana::common_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_COMMON_HPP
#define BOOST_HANA_CORE_COMMON_HPP

#include <boost/hana/fwd/core/common.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/std_common_type.hpp>
#include <boost/hana/detail/void_t.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // common
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename T, typename U, typename>
    struct common : common<T, U, when<true>> { };
    //! @endcond

    template <typename T, typename U, bool condition>
    struct common<T, U, when<condition>>
        : detail::std_common_type<T, U>
    { };

    template <typename T>
    struct common<T, T> {
        using type = T;
    };

    //////////////////////////////////////////////////////////////////////////
    // has_common
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U, typename>
    struct has_common : std::false_type { };

    template <typename T, typename U>
    struct has_common<T, U, detail::void_t<typename common<T, U>::type>>
        : std::true_type
    { };

    //////////////////////////////////////////////////////////////////////////
    // Provided common data types for Constants
    //////////////////////////////////////////////////////////////////////////
    namespace constant_detail {
        //! @todo
        //! This is an awful hack to avoid having
        //! @code
        //!     common<integral_constant_tag<int>, integral_constant_tag<long>>
        //!         ==
        //!     CanonicalConstant<long>
        //! @endcode
        template <typename A, typename B, typename C>
        struct which {
            using type = detail::CanonicalConstant<C>;
        };

        template <template <typename ...> class A, typename T, typename U, typename C>
        struct which<A<T>, A<U>, C> {
            using type = A<C>;
        };
    }

    template <typename A, typename B>
    struct common<A, B, when<
        hana::Constant<A>::value &&
        hana::Constant<B>::value &&
        has_common<typename A::value_type, typename B::value_type>::value
    >> {
        using type = typename constant_detail::which<
            A, B,
            typename common<typename A::value_type,
                            typename B::value_type>::type
        >::type;
    };

    template <typename A, typename B>
    struct common<A, B, when<
        hana::Constant<A>::value &&
        !hana::Constant<B>::value &&
        has_common<typename A::value_type, B>::value
    >> {
        using type = typename common<typename A::value_type, B>::type;
    };

    template <typename A, typename B>
    struct common<A, B, when<
        !hana::Constant<A>::value &&
        hana::Constant<B>::value &&
        has_common<A, typename B::value_type>::value
    >> {
        using type = typename common<A, typename B::value_type>::type;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_COMMON_HPP

/* common.hpp
wdzJ3h5pImdBKIxnadmqd3IuRcE8yJb6fZymLB5WmcwvodklZelaXO2M5J2SH7pciGxxqa7y7veF8a4EPbdbKTnASpE1Mfd/LX2HlSQbsaiii8w1jHP/93YZec4kzU72SvOUHLRn2d6s3DrJ4Y5xzZ54P5gucw3j3N1aN8qpLAjG++doseKnzDWM52xNnakXZHZhvCv5V9+1kPxgnHvSi/gpsrcwG7Kmpy8VlfxgPC8DXC0DlWXCXMmuRC9fpswp9U/uWX28+ztV3rcBMF8yu5sekTJnsNxkq3p02iH9g1mR1V1UJ1RZJMyObKxvzqbKlqXK91K2Ffy7kuxKHKwAxYV2NB0te6vFWXn5y04nwfwobmW08zapC8yC4voN9+2lzOSu8XM6n/beIDWDOZEVzl06n8wLrCCZz8Wja2ReYAayYxszZJZCYK5khiutz8m8wLzITj7KK7MUB3Mn82w4KVpyh+Wk/Jb861BHvhVhnPvE5+ETZM6059xjf1i+X9Jhqg8eWTO/qoSJ1Owe/jNZxaU3jkjNYPnIFl+qnENqBlP7kDWLPYv8fVpZMEx9S2XVoNbU/qnKwmAGsjz1fbtLze5Jftlmem2XpcwgLB/FNS087byyWJgNWWg/d/l5YzwsP9noGdvLSK21+7XK6NVFWTLMieL6Xv68V+oJcyOb4PIgvzKz+8bXzCw9eYEyA8yR4vYXu2unzBdWmsy2uP+fnyNo13xRzqKHzCDMk+K+5bopcxYJ47qU+GA9WFkMjPPL51rcV2oGK0i2etWEklIXGPchoP4E+b5+rD1n93VLlyp7p10z7sCXxlKXNOO6tB8fHix1gZUj+3TZYbTkDuMcSm/tWk5ZOMyd7NqR77GSO4yfZW16me3KEmBcz4yro1sqS4PlJotvsXKH5Kfl8MNpUBN5Vz3Ae5qsRYch8u4PgFmSVdtRSWYwEPYfsgvreshzRsJsyRp9vvZI8oP5k52c1kj2IRnGuYfPyXFHcoBxzTqt+9JAevQQv9dFdvnBMMndA2bgPty5uEuZnxa3u8vQxZI7rCTZ7cj6MmdhsDxkM+fXu6osAuZFVvxujwxlcbDiZIeHny2uLAXG+Y38Oj9GWSbMh+x694PnJD9UNj/Z1uYv5Tn9YZx7/vjHv6R/sMJkAc4Lq0p+MJ6zWdM9ykv/tGt6NrM7JfnBeKdLmS0ar2w3jPfvztsSu5UlwrjvPe6XSZG51p9z8IqmMruPjeuy4Hm32tJbGMdd2rx+obJgGN+vS1vv67KbMO7tuPemQ2SuYdwj094zXkvuWlxsfDFz2VuYC9n5sX7Vpe8w3s3XXVudlZmHWZFFfx5TQ5nJE+O4l+H2hZU5weg50cvXsn/+MJ7P9O6z/lUWAvMgS9ldL1nmGsb9y9HbtrfUBcbv1KkpnUooi4UVIqt5MFp6lAhzI3t0uslm6TuMz7MTu3c8l7rAGmZbULb5rs6Ud1XAU+McEt7dkVqHwJpQ3PqYLoOUxcOqUlzbsgdHyf1gfmSDRqwZK/uHN2FZsobFujVU1gpmTjWrfWzEZWUdNSvl8+OuslAY9z1Xmbo2yobBuA/LW31aJD2Ccc0sy71/qiwK5kBW4fR6qVmcdj9T8yaS327tfvnj6t5XdkizkY0vX1SWBOPzc3qPsibKMmFcz7iLkYeU+aYbn5HJ1U+tk72F8bm0pJ7NPMkdxjls7lhC9jYKZkd2YE+XYZI7zIls+FfzXDKfsGpkvh8euMr+YRprkoWFWx+QGYRxXQpsfCMzEQhz4lm6Me7Pr/Fg3mTrTqzoJzsG47rYlMr7RlkCjOtyL+dbec40GJ+DK0vlLSLnJ/7GhivZhhi/itIHmLpmVrzT13Q=
*/