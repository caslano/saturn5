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
6x43k4VoIzrRH2bxz+PNs3jmAgofmZazLSB2Bxpow8IfVETmCw7uRnVPLwOFf70AO1q6UCfwtez8oR+yIIhy5bK7xuEol3A8uFkFnJtV0MDNyufcLJSV/89uVtB/uFnIjYGVpn29m5WH6azqbw51vQhoGOr6EkDcrDyYN/lo3thCp18+NftaMD10F5FC+UjsFFZeRrFWUqyKFVIKK3U2H92D4OP6ID9M0PNrP8ziG84Pg0qFUnnuIG4sa325SQqNtWU/j0STlNjvcRxrQezBKlCyG6wAZXC+kQxB6eM4x6xNH3DMirBjVsTWJsCmr2SKLiAHD24+u6r63wZ3ml+9IxabC75YQEFDR6zA7IiV6W7IWP9x2BFbGYVGGrlhqHKulB07jrhhTVdxZ3CjKHbASNizY27llaAOPE4dKmvxc19yjltu44Q1BQ78sw/qi6Jc07uVI025EFXnkj+TYJe8srPZJS9gF4zBLnnxWNCVIk5XihroSiGnKyir8L93yalx/+GSIzqrephd8rNjG7rkt8Y2dMkLkTc8A6tIMWKZcy/5UvZ5GLfuF4ZgT7utpH55XjiWzNgLn3jY0+4KGTj4AHrh/a3Zwy76ysPOxwNbyCZX/dvAeosbeNgFuthCXUBRw4EtauRhLx6DB3a/3Oxho+oFaIkeQ4bWcyV42J7pahiWXvPIsOSy40fgYdnexTws2extfzwsAWP+307h
*/