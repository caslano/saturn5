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
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
*/