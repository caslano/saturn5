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
NAD15oY96azG1iLR7qQcQbYeAtku9lXz1VZjtKMgPG9+BEdDH18q3VmOsVyFHplsDRONljPxHuhvxrn/FwxnixFY2rGXaspxSktccKdHT8fC6zP7ZpWwCoxfzl6/ZKlw58e7o7smY0s/RXcyDjbRJJdxWVR+zK5Yk51zu/6cNH+J3GcFIQdF9ZE27zdGs3Vtkt9XeMMS1h6fiAbuVQSE/CphQFknHp9JcGXxdohx34exoJKyPJG8T44i5iq5fDbL+fBsr1JeTndKBNu3hciMPbffofMWPpRzehPhlon1yr/CWmLrYiJDSrjQTvZhCoNSBMo6rvsw93D9n9l5atu8gUAuZ/m0ZP5HShsIxBqO68CcTFLCzl9y4lpCTKocYsAxE5mxxDMdTjxQEgRYyslBRiiPwRXBOmH5QL8XEtvNfXZoS2HulpLtG7eD0VGDxSvBqGcf3klosQefXBdNZNQbQB19iGTmiTu77xvWKpWai1Hj0kBi5y4pLV4ZNnhNPPZEFLxz0RHC4t7PbMy1mxj4kbS8In4f1rYVJJSvOCi7Uw2PlONcpustYBgEnQ==
*/