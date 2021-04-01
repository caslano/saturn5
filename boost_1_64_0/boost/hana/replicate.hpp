/*!
@file
Defines `boost::hana::replicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLICATE_HPP
#define BOOST_HANA_REPLICATE_HPP

#include <boost/hana/fwd/replicate.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/cycle.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename X, typename N>
    constexpr auto replicate_t<M>::operator()(X&& x, N const& n) const {
        using Replicate = BOOST_HANA_DISPATCH_IF(replicate_impl<M>,
            hana::MonadPlus<M>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::replicate<M>(x, n) requires 'M' to be a MonadPlus");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::replicate<M>(x, n) requires 'n' to be an IntegralConstant");
    #endif

        return Replicate::apply(static_cast<X&&>(x), n);
    }
    //! @endcond

    template <typename M, bool condition>
    struct replicate_impl<M, when<condition>> : default_ {
        template <typename X, typename N>
        static constexpr auto apply(X&& x, N const& n) {
            return hana::cycle(hana::lift<M>(static_cast<X&&>(x)), n);
        }
    };

    template <typename S>
    struct replicate_impl<S, when<Sequence<S>::value>> {
        template <typename X, std::size_t ...i>
        static constexpr auto replicate_helper(X&& x, std::index_sequence<i...>)
        { return hana::make<S>(((void)i, x)...); }

        template <typename X, typename N>
        static constexpr auto apply(X&& x, N const&) {
            constexpr std::size_t n = N::value;
            return replicate_helper(static_cast<X&&>(x),
                                    std::make_index_sequence<n>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLICATE_HPP

/* replicate.hpp
lx5OUz7sU/mr1OAfbkDePzl/DxNuklWU92FemhWAJccIuiFU+5q2Ihv0gsSJqHNK2wBxkx9Etszx5FawRxcUCLCD2A/RtPCGzwTGZbVJbdZx6cI6ImHGbx6QgZnbsMw6x64WUITv4lyLpDhuHhlvIpkm+aMg2XXe2aHIzr0SMD2QzvlcBt1jF6BQcX+y5HZ91oqVRmXs7BUSbJMz/a0+ioUg5h2UaOenbiqdXE62ndE+Hw3PxDt/IzXd7L+KDeg8VRjlXM/ozLAPRLhV9Ga+idljF0P55yLGhB84RrWnQwfnFf7K33Eu6pwOilj7UQOaimHZYNKOh69OVaU0NlEwKrCXMQgd7/e/CK5BvCy4IbmYzhuoJv0qb6kHKAWZgkXnrreIu09T2MCIe9pbedagmozMoD8c3j/EMU7hqERgl/qfL0iFKUJvh5UVf+cVCi9u/9am5CC5YL5A3/Qbae09oolXlbDSFxvozzYiXHd4987wJpK3mCA/1gkbcKHnF9ucV+oKDJR84XQN4hdivO2zmuhh7Udv+YjLdLBA5m0H1fLNKCF/VbmWFDkV1A==
*/