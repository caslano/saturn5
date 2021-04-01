/*!
@file
Defines `boost::hana::greater_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_EQUAL_HPP
#define BOOST_HANA_GREATER_EQUAL_HPP

#include <boost/hana/fwd/greater_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using GreaterEqual = BOOST_HANA_DISPATCH_IF(
            decltype(greater_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater_equal(x, y) requires 'y' to be Orderable");
    #endif

        return GreaterEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct greater_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X x, Y y) {
            return hana::not_(hana::less(static_cast<X&&>(x),
                                         static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater_equal(hana::to<C>(static_cast<X&&>(x)),
                                       hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GREATER_EQUAL_HPP

/* greater_equal.hpp
8wGEXcd3O1BxQ+IG3L3Y9Bsw6YVMdtYzsVbZ9Er8taZ3BoLNceSBjaBOZzYaDtvlpw+r4TqyS/c/KnEt1CnKojj6nQjOz7L3R86DqZL/t5z+jiotgmD0jmuWEDA7hlzCorex9SyyJTHLDcGCYCyYdRB4e5w9/o3mqL5oY71BW+goww9IobhGM4WS/spJ79or+Jac3SX3OW2pmNfJSdsz2IAHyPc28bAwvZH6x1W1anNPXthHWwNWeDM7Fmuf/ZYT/OLmu+j6EtNm4ycLKUlZZUIo2lrPXCdxcZTQ2d0jX7U//qwQVQo270Bc0IfKc/552EYbLDMkmIOAEXrWWlNBGAoGH09ZLeX34QF7t8MvTdoQvXCAeyNsGQgexHvVdSEvl+KkjLRCD7b1Q/ZHqfpZOYcyapGWSCBdSOKPc4kQj5linv3zZ4Hk/6dPvQc7ha10CWS7neD/hDdBSymt7SFRVvBHjdGMjg2hsRjZCFVhJ5zvWczCprMiJxvQcBkRRZ59WEWdKzpgBMyTz/32LcraO5rNopPZPb5FDl58ySUkP1rcWHGpweczGWvk2w==
*/