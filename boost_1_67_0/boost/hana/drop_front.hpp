/*!
@file
Defines `boost::hana::drop_front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_FRONT_HPP
#define BOOST_HANA_DROP_FRONT_HPP

#include <boost/hana/fwd/drop_front.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_front_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropFront = BOOST_HANA_DISPATCH_IF(drop_front_impl<It>,
            hana::Iterable<It>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_front(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_front(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        return DropFront::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_front_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_t<1>{});
    }
    //! @endcond

    template <typename It, bool condition>
    struct drop_front_impl<It, when<condition>> : default_ {
        template <typename Xs, typename N>
        static constexpr auto apply(Xs&&, N const&) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_FRONT_HPP

/* drop_front.hpp
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
*/