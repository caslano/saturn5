/*!
@file
Defines `boost::hana::tap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAP_HPP
#define BOOST_HANA_TAP_HPP

#include <boost/hana/fwd/tap.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename F>
    constexpr auto tap_t<M>::operator()(F&& f) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::tap<M> requires 'M' to be a Monad");
    #endif

        using Tap = BOOST_HANA_DISPATCH_IF(tap_impl<M>,
            hana::Monad<M>::value
        );

        return Tap::apply(static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename M>
        struct tap_helper {
            template <typename F, typename X>
            constexpr auto operator()(F&& f, X&& x) const {
                (void)static_cast<F&&>(f)(x);
                return hana::lift<M>(static_cast<X&&>(x));
            }
        };
    }

    template <typename M, bool condition>
    struct tap_impl<M, when<condition>> : default_ {
        template <typename F>
        static constexpr auto apply(F&& f)
        { return hana::partial(detail::tap_helper<M>{}, static_cast<F&&>(f)); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TAP_HPP

/* tap.hpp
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
*/