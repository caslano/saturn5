/*!
@file
Defines `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_HPP
#define BOOST_HANA_GREATER_HPP

#include <boost/hana/fwd/greater.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Greater = BOOST_HANA_DISPATCH_IF(decltype(greater_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater(x, y) requires 'y' to be Orderable");
    #endif

        return Greater::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond
    template <typename T, typename U, bool condition>
    struct greater_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less(static_cast<Y&&>(y),
                              static_cast<X&&>(x));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater(hana::to<C>(static_cast<X&&>(x)),
                                 hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GREATER_HPP

/* greater.hpp
hN5WWXk/ie1zfPcL6fjXa2lAqkFdAIz6ttR2nTEE7tje6CUoMQDwltcvmkKSd/R7fmC3L8wg3Tvh1zoWVUY3RsS0xaLblmooupffh9xX7XLaq85tPyGJ8tOO5UTHb/iHGETcYw/15cOXKscEp+w8fGwQk8rAApVLQju0dDMsht/iCsPRDn5ajtf0ZKDk3Mky7dnuYBfMPMZFNfKdtssLSfyTRD288wK9isf5NkcBrpeAeLqX9pwEuSUvluO1+gMRbjy5i5KR+bkPwaqd/m/pJMXG8a4SYt5s4KTDSYGOvT4QX3bumZuiiGXLvVWOcVnv6F6oFulhSXh5lAWPYED9hEGdP8ulTg47/aon2E2E1SduYuP92ZJMBzkwYCtHnkl7kldrusydx8ml9rM9oaXxrzAfJbs/stURdpJJrq20IgMwv0byFwsvv+8cSe3Q+1YdZ3/ql0qFMhpy1Cw+tN7WKoUjtdQT9jVd/o70e+HjI5XHA2mi8xzE137vq+VkV0hZqpUFgSNGuXoeuupkx6pFejALZG1ptHUi+XuF7rfDAnjna8Y2wjTaA/E8amVUCxXanH+1GWHWIK6wmK6mRnjejRrSO2qvG1R48cJoXnns8u0iWpkWzMl9wJEPK37v59i8Nd+DIVOIRt0PG7C1cpLJ50W6mSFT9ItOOO4mCtdUI0D1UZ64Wf/jDd39RlTWcpNT81rMin6rM78drHah
*/