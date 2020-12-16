/*!
@file
Defines `boost::hana::chain`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CHAIN_HPP
#define BOOST_HANA_CHAIN_HPP

#include <boost/hana/fwd/chain.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr decltype(auto) chain_t::operator()(Xs&& xs, F&& f) const {
        using M = typename hana::tag_of<Xs>::type;
        using Chain = BOOST_HANA_DISPATCH_IF(chain_impl<M>,
            hana::Monad<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::chain(xs, f) requires 'xs' to be a Monad");
    #endif

        return Chain::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename M, bool condition>
    struct chain_impl<M, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            return hana::flatten(hana::transform(static_cast<Xs&&>(xs),
                                                 static_cast<F&&>(f)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CHAIN_HPP

/* chain.hpp
Xb0e1vC4n21Tuy2BNaXzX8BeJIzNvK50/sv6Dnc1//x2iuLGE4L3gNeA3eNf0wJ3OFr/eAPcx434mb0qu159LcVy4jpA16ANSwXGWvW1GmnJ83GVDR322qNGNnt+Lo31GeAO+vczgbzvrcFcYSPcSQbGulsXMacPrJhAvorWP0I7/g7Y3i1ydtE8W2RjfKN/YOQqwS9+LVOy+Viwx0YDbJFz81/2zjw4kimO44N1K3ZRrPtWKEfEfUsyIWE3iWSwCLOTmZ5k7Fx6JrHuuK+4F4tF3IvFYrHu+76WDbuIJGxEKFexrqp1/Lr7+15e93QUVb/nD/pVdWW1mfn0O/q93/u93/s+af+Bu7qXixMUCtkdtXCL2zncyxf5cfnrWPp/wP3wCz8ufzmL93ny9vCFe98tDf5S0Z57wQyXlLFYs6KOk3n/nYx/3gG+PS9b0/pRubB7wW0p4SYMMsMMJ4LGYI9DlvoXZYjPGoWvc6x6Bew2Xza/VoC0f3dEfKwPV3c7ewLsw3zYOtvZ3uVYM/S+z85euLwu7W/Rn8wGv6sk3y2pIrO9L8p6q50QV1DKjBUM/v2soqxngvvVgIdrD0+O5zXXzh+XJvhb7Yy5Rq8/H7s9tenadIP//cCofFau1D/dBTGQfb5c7J03Wdkiz9PAnr5oNDZvzKmo6zV3dbhPfVLCpT0s9olSdJJ6tK42zFvXoswvBX98v5ePvVLkfOZuZyLvY3fDemPfaOxYPh+1DuPk5Yu8d4G/uISPOAUNcx/p/94dsadetqYYCen/BndDv/q2uzY5x01ya7BK//ceWEvzfwZt9S7jX8Ef7+1fNcWKiPa2BNxsjx83TmKH1L0xn/Eu5z97OuwbFo3G5uUKu2EY3IWferjl/Fri0v+9F95rd59KuPIGbv1swZwH5gxXPiurrZGD204RzPDeiLFSbcKJYesYTHbbW+q/gbncsJtJqyjsTLn+vY/DHBpwMV07QnSV8UywGz9xs+mtYY/TFsz193WY8z4qZWYSvPmU9g+Yk0rzqSUeXHBX2Q/7eNU4jmpnyk5RmOxn+Ur/F7hzPijlIhKTlYu2TA4Zh7umT37taEwCc5e1YJ8M9rDarsK2e/Uwe/G1lt9XIPUPwP5mNLaVeeYxSOofVDjsYz4pYVMT49chE9xhcHtL89xEC7G13GtVUv+gEmt0/lyrpLXpz/aC/X4pG68VL1eef16FOfNwCZe9nKX/C8xEabuyy5i7DxHc/cPwoZfmVUvdbip8QOCuMOTl6infraoRP+HiGdrHhm5w13VztY8N6x+AuA03V+vYIMd/sDv6FHaVHV+o5b0VbWrMgYixHvJyef08op+YCl6jK5+1DTXVjexn50v9czAn+TBpth1NG9nWYhtv+Qp2vgZjnw871QG0pjY1DHbCh51Mx1q5fdVS/7PW4Q4MlHC1zhkEfxj8k33yLTxbeXLvccd+i3KffBDi+4ZK+FrmLXL9D9zyUq62eYTUvzwYcZ0+bHg42MdFqX8Jdl6t78oTikYhkuM+D1bqH02AxsagYDY2CjlGwzRzJjYXcOdZxr+BP61vhI8QMBtfiCbz3Gxp/0zEPqj5vmxta2BzwB1apHINY4qN1TNebVUHnRG1nlsNJ6eafIXdYL6v1K2rUUV5tSgEd3w99nkp9Wpr/Js2nT0eWsb/gNv3vuDWHVhbVx0tyCgkXvt2V7H20+Bwb/ZwTaM1VaC1XHukiucy+bTBPkeV6z94hoXuZ7A3yCOINTpFUx829hDstfBjI4g1OoX/vFGp/wT+Sx5+Kst/Rpn0/zTCt9fnYjqiH5YxSKv4bczr6VL/Aext+v3Z9lKn/QD61iGW4Bm6ffKfNaayl7s=
*/