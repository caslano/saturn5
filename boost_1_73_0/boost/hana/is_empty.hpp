/*!
@file
Defines `boost::hana::is_empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_EMPTY_HPP
#define BOOST_HANA_IS_EMPTY_HPP

#include <boost/hana/fwd/is_empty.hpp>

#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto is_empty_t::operator()(Xs const& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using IsEmpty = BOOST_HANA_DISPATCH_IF(is_empty_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::is_empty(xs) requires 'xs' to be an Iterable");
    #endif

        return IsEmpty::apply(xs);
    }
    //! @endcond

    template <typename It, bool condition>
    struct is_empty_impl<It, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IS_EMPTY_HPP

/* is_empty.hpp
60cLb2LdFGf3Y5kRaqPsLVdh4zw5ceUHpeVON13+HNIGjhRVH9owuR4cs+6i0s61YTAzoEKIeLh0Fsu9hQCwqeFEWsOo3k2ea1F3ahWrpXv7uncIswUcBj5OqObRIknO0ev7cDSEb3B/E/PhOG3SwKV0tZMLwCqcg4CTrsYyCGdYLcPczTZeW+HJtXRQXqamV0SD2/TpgOJdbOzKGeoSQ2/dsAN5KX0jTLTQe84l5NZ4wpNY
*/