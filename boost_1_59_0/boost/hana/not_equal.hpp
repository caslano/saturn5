/*!
@file
Defines `boost::hana::not_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NOT_EQUAL_HPP
#define BOOST_HANA_NOT_EQUAL_HPP

#include <boost/hana/fwd/not_equal.hpp>

#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_to.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/not.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename X, typename Y>
    constexpr auto not_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using NotEqual = not_equal_impl<T, U>;
        return NotEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct not_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::equal(static_cast<X&&>(x),
                                          static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct not_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Comparable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_equal(hana::to<C>(static_cast<X&&>(x)),
                                   hana::to<C>(static_cast<Y&&>(y)));
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_NOT_EQUAL_HPP

/* not_equal.hpp
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
*/