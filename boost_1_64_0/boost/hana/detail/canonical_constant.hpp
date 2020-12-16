/*!
@file
Defines `boost::hana::detail::CanonicalConstant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_CANONICAL_CONSTANT_HPP
#define BOOST_HANA_DETAIL_CANONICAL_CONSTANT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Tag representing a canonical `Constant`.
    //!
    //! This is an implementation detail used to provide many models for
    //! stuff like `Monoid`, `Group`, etc. To create a `CanonicalConstant`,
    //! simply create an object with a nested `hana_tag` equal to the proper
    //! specialization of `CanonicalConstant<T>`, and then also provide a
    //! `constexpr` static member `::%value` holding the value of the constant.
    template <typename T>
    struct CanonicalConstant {
        using value_type = T;
    };
} BOOST_HANA_NAMESPACE_END


#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/when.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // Constant
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct value_impl<detail::CanonicalConstant<T>> {
        template <typename X>
        static constexpr decltype(auto) apply()
        { return X::value; }
    };

    namespace detail {
        template <typename T, typename X>
        struct canonical_constant {
            static constexpr auto value = hana::to<T>(hana::value<X>());
            using hana_tag = detail::CanonicalConstant<T>;
        };
    }

    template <typename T, typename C>
    struct to_impl<detail::CanonicalConstant<T>, C, when<
        hana::Constant<C>::value &&
        is_convertible<typename C::value_type, T>::value
    >>
        : embedding<is_embedded<typename C::value_type, T>::value>
    {
        template <typename X>
        static constexpr detail::canonical_constant<T, X> apply(X const&)
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // IntegralConstant (when value_type is integral)
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct IntegralConstant<detail::CanonicalConstant<T>> {
        static constexpr bool value = std::is_integral<T>::value;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_CANONICAL_CONSTANT_HPP

/* canonical_constant.hpp
HMb1TSxa/JD0Wrtfq0TPSGUx2jVPrMvvqSwexjtd8qXnGGUJMK791KlDH5Qla2bv5r5JWZp2P+sFRxfIHLTnXL3nzGCZg2bvc7Omy3c+mMr117+uf/u5jTLLRJwjy3I+/UiZO0w9Z2H8/3uTzwHKgmBeZG/Xvf1TWVeYK1nQ2ddnlcXB7MkGLX1XXtlcmIEsqtOLc8pWaNccFuApNaRp1yzYN7eTskztmpvrPGyu7KpmCeP/PqLssXZN8/gmwcpM5hs/i+21/lKDK4yvOf3u7OLK/DRLGXZczgXDuNd3qkY0VhYB414nDChTWfqp2cKiHYtLz7T7fX0nK9uk3c93/Y13yo5qtuTTvSzpmVb7+H9GjlBWAOOeecd93C05+9n4WQKcdkl9rjC+5sxGXmaSMxg/S+S/+br3eCfEMIDjQzg4MjkyOTI5MvchzH0Ic/kwJEMYwtwyFEMyhCEMYQhDGJLlOhRzH8LchzAkQ2oIk1ye8L6eXp/9/jhnju/ned73fd7n2dk5p05r96z1j53miYqZs/fyJD2jwicOtZ+PVM4l5f/cdf2ROWNZsS5lJ03Jx41NFPMpO+2KVdcwNlWsU9nNidf9djadnKl5hbXsbIp5lZ06/rM3jc12cn4beHIFYy1nL/7xmw435r1mUZu/26TNjAXEdM7EOR9eY2yQmK7Lrx37XWYsKuZVtt15e9vvL8XFTK2XkseRG/f53dhYlXPhxV376eidjeXFupR9eODlM4w97NiOe0y5zlhFzKtMz0rNifuu35Fv/WObbDRb7WVZz4jTtl5y9En2c874/2q2nPyfGe+c7LHPdWImbmHttt1x1NZ2NpUtL48v3LTLp8ZiYqbWveVxl50fucvYcLEeZS/0mvyksYxYl7J+X7+6p51bx64OJF81VhTzKvstNqForOzEbZ+640pj7zi2WvO6y401HHssv4t9Ll/grDf7qafH2Jm+9r+4hU273373nG3r6VjwhL1GGRsk5lW2+si1fjI22Ikbd9uAZ22tHevzzafvGzvRyXn/iMWvMDZazKdst+9HXGZsvJMzPf+tI40VnLiTuv843tbaWW+DV7eYaazq2Mv9/7A562Ldyl5dNnWPrbWY6SWvZ9jJZ9486AVjHdfJPpW91+z9p7Fuxz7b6IFBxoKOrT9p9b1trcW8yjbzPjzL2BAxc/YV5XGdyQfMt7VWOfv8/fPw2uLG0mI+Za+2Lr7KWM6Jqz697IbGJjk24aMlb7K1FvMq0/1SFTP1XFke7zhlrr2H2WI+ZbHEs3bGel0vtVY2+tyJjxrzinUpC03rvNlYj2O9y71+NBYS03tpvDDann2ImFfZxev2nWZsuGMrbvPD78ZGOhaedOvdxsY6exl5XeguW2vHdvjovFm21k7O0UuuNsXYVCfumsv2u93WWkzX86QPlzrZWMOxOy/e9BxjntyiOUfM+eYgY11iXmX6+awn59xfKBs2tq2YX9kbF5dtrYepnH0XPg/eudwmtnfFupSt9uGRc2zvOvbYpVPuNTbeyTl7/J6rG5voWH5uaraxh8U6lN345yYv2Fo7683b7KNRttZOzp9ePqZqrO7EBaf9eKaxeU7cE5k1w7bnb1g0bon9n9vSmE9Mx/Xcfu5cYwEnbqtTnjnF3oNjW9+3t73bqFi3spV3efgNew/OeqPH9X/Q2GjHYrdu+6SxcWq9VRbW96lHOozlxTqUJUb5PjVWEPMpy45eel9jZcfOuGq47aWamFfZ0bEtRtued/ay6RETbF0WOHuZf/vu3fYebpS6KPPv4d/MmF9M7yV/wsBOYyExr7KP3v7uWGMRJ+6iD867xVhcrFPZS2c/8IG9BzHzGmVhfPE=
*/