/*!
@file
Defines `boost::hana::length`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LENGTH_HPP
#define BOOST_HANA_LENGTH_HPP

#include <boost/hana/fwd/length.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto length_t::operator()(Xs const& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Length = BOOST_HANA_DISPATCH_IF(length_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::length(xs) requires 'xs' to be Foldable");
    #endif

        return Length::apply(xs);
    }
    //! @endcond

    namespace detail {
        struct argn {
            template <typename ...Xs>
            constexpr hana::size_t<sizeof...(Xs)> operator()(Xs const& ...) const
            { return {}; }
        };
    }

    template <typename T, bool condition>
    struct length_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs const& xs) {
            return hana::unpack(xs, detail::argn{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LENGTH_HPP

/* length.hpp
VKcrQrvMNMjSO3BdGzPoaigqnloJsE1RXsR27XzI6EUVDOHUAFz7v3m9U6bwBhEa1fE1e7A6ZNdn7dOrt80hnOVHZoJIvE9HRWkWYjpYaZF1AuMMuSclaCuaFIMtdHAfAtHG581BiLOAbZOVJ+ov2j5oLF+UHGmw8HpDzhLPl1QLLEh//UA3ec+z0pvgOqPqQFbKTYkuppggM4028rBJ28iGJr6W253DWIcXW+g5Hq7MKlOwwaOHGTXq9C7woyE8LiWPwULchbQr0gZlgjPU3CcmRSXOKlhOjqXS7kim5U+iOlGY7hq3dGSZDWgVRGiNoBOmGqisRJiVB2sk9SwsLlUDcZndEu3i8F6QTCS0UfCBZ8c6bQimAIE2gnRyWGx86vVVkp2GZ1PJvkD6OqIVHzPoVQSNiMPY44Tsg+IyMonFIMfLlAI+C+MsBzhZZkWlSWvscCjVYah/kDXUl8KSKVKbwObzPBeGeHQIxcz380Te5tpXVluW3yjxmDBlY2raZBxRKJAqhUUbOoWf3ofPVQS0ecKwN042jE+ULkNfhDlm4Tw8FFVgSveLK8BosS1NAe0uyexea9j3h6Nm/6LTfes+hbKSywHj5jHUPtA7sXF1ou2qav9yehEV502elMtj6Pa7LhPDKoygSUNI
*/