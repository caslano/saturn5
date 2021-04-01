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
2Xfo9D4zY+TtE5sNKM/irhu5Whiit3uJnUnxJ50RWTT2MBg6/7sMjeOyx+OZ73F4Kj3TvDx33xPObN2eCS6O7Vd7Uj7IGbfR8RYLxMLgYrRBliqyGni71zcPNgNWCeNKh1X/Q3UPsdkdx4/IIyCuPFr1qDnf5+jEGoooTghywgVmREjllNzJVJGqB6Yxtnc6tgJzFXiai96xcyeN6ia3yV3VYwu6bFHeApDp/aYJ/oTs8D6hAWDoVUH1SIRiBSYa5Hy/AU8m1E84YXdEX2CFpavUVvtQ6Lnu2wWcbMjL/EyDOP0OIKaBiO8Pj7Jga0i9/Y1h4tluRua4UELR3syvNnf3jVwIfgq12RRVOH7beLm3uc2x6ag2sfzykAsE3oenybE91XxlO09BeKQW/eZ1N1alLiCQT6mcxw58lcU+CnJmEGAZZ8yi69RSIJBYeZD3GND0YrRiXSrECBG3gIOfbELByAKh8NWcaQ601iM/UGyJrxtVZVGTfMLVdRdM1eFVgoJ+nCvQVlS+0ktZfohAMCBJoGzDJPZg10AwLG1Ha8FWrIe4ZubeU4+McA==
*/