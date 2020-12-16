/*!
@file
Defines `boost::hana::and_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AND_HPP
#define BOOST_HANA_AND_HPP

#include <boost/hana/fwd/and.hpp>

#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) and_t::operator()(X&& x, Y&& y) const {
        using Bool = typename hana::tag_of<X>::type;
        using And = BOOST_HANA_DISPATCH_IF(and_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::and_(x, y) requires 'x' to be a Logical");
    #endif

        return And::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }

    template <typename X, typename ...Y>
    constexpr decltype(auto) and_t::operator()(X&& x, Y&& ...y) const {
        return detail::variadic::foldl1(
            *this,
            static_cast<X&&>(x),
            static_cast<Y&&>(y)...
        );
    }
    //! @endcond

    template <typename L, bool condition>
    struct and_impl<L, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::if_(x, static_cast<Y&&>(y), x);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AND_HPP

/* and.hpp
g6thOXwQVsCfwSrYAL3wDVgD34W18PdwAfwcLoLticdieAm8HfrjecYh547DY9IO6a7Kablv+Lsa9oa9YD9YBq+Ft8EBcBkcCO+Fg+BDMAU+CwfDX8Hr4GtwCDwGh8G/wREwFs1RMB6mwy5wNEyEN8CBMAMOhplwAsyCc+B4uBDeCJfAbLgMTpD0mijpNQnugJPhLpgLVX4zz4embxUhv30vlnDBR2Eq3Cj90aUxmFx3QPLHQPVeiUxM4a8TzIZd4USo2rWwD5ws/d8pMBNOhePh/fBmmAdfgQVwt/z9Dfn7oBjj76kxxt8z4DR4C5wJ58JZcCm8Fa6Es+GDsBh+E5bAR6ELPgXLYAP0wFfhPPgWnA+PwQr4EayCf4JeGEu8fbAt5HrVb1kAB8LFMAveCWfBpXA2vBuWwC9DH7wH1sLl8Ha4At4LvwJXw3vhNrgKNsCv+sMH7zfHBfS5o2hFGAe9Q57TO2ESvFs9r2rMW5Xfy+FIuBK+ClfBfRBt1W/+quTX++Ff4degX2wd7AQfkvy6BvaPMX7HCR+R5/ebsBJukPxW5pAzKOGXJL+1h7MkvD+SduxmeDV8Qsapn5R27I/hcPl+PNwCs+FWqOY8oFfcZnu7d/T8/bjk782Sv5+IDZR/dXLdV2Oal3/7Wxv10SE4Bb4D8+G7sAi+B13wfXgH/BA+BD+CdfATuEXcT4s7NoZyB7aFv4UXwE/hxfB3sAv8PbwCnoaJ8I8wFX4Gh8I/wSx4Fk6Gn8Ob4d/grfDvcA50SD3I/+VcM7TkOe7nf+7kOa6T/PNd2A1+H/aBP5DyfhMcDcmbKh1+AefDF6AX/gguhI/BJXAzXA6fgGvhk/Db8Cn4GNwCfwG3Snn5NHwTPgNPw59I/nsetoYvwka40+8PviTl/8vwFNwF/wJ/BbuoOSDiAV+FPeBrcDrcB2fAJjgb7ocV8A3ogwfgV+HbsA6+BzfBw3ALfB++Co/4wwGPwnfhh5LvGxxyHhK8T/JTF/6/TY9fyHxEK78+jIUlMA4uhq3hnbAdrIcXwUZ4MWyCl8CPYTw8ATvCP8BOsB1anWF32EXqkQSYBrvBEbA7nAav8uvDHlK/JEp90kni4TXPs+HZkfyC0+GKkfkm/F0FP4aJKk8Z7fTfwVT4e5gB2/Cc3QTbyjhnO1gNT/H9CvgHuAr+Ea6Bn8FH4J/gFvgXqVf/KuXVWYn/5/AzGBtrlFcXwJf9ZQxshB3gfngRfA9eDI/CS6R87wg/g53818POUs53ge1gV9gJXgavgAnwSngl7A0T4SjYF46GyVIPDIK3wMHwVpgGi+EQWAGHSz0wQuqBkXAtTI812yly3gV1Z4R2yqDWRr8jBQ6FqXA4HAIz4FCYBUfA6XAknANHQTdMh5VwNPTCG2AtzJDyawx8EI6FG+FN8EmYB5+C+XArnAafg9Phi7AQvgRnwN/CTCnfsuCV8EbYA06AA+BEOAROgtlwMlTllHnWA3GP0J9fLv25FTADroQT4YMwB66F0+H9sBSulvHX++By9X2gPs1NkXGDCPXpDBlfmSXjK7PhBFgk44xz4GxYDN+FJfB96IInYTn8E3TDNv72BoyH82DnGOVfPadVsBf0wr5wLhwNS2EmvA1K/0n2wSeMEfpPg2X+dyjsC4dDlQ+kvhwJb4WjoE/+vhzeIOM718O14n5YuaWfHSN7sqv95ZWuqlMHSDnwWBujn/44vAz+GPaB9bAv/CMcBbfAcXArvAk+DavhM3ARfBbeDV+AX4cvwo3wl3Ar3A9/Dk/Bl+Ef4CF4Gv5RdBz++gG2hr+GF8PX4KVwD+wOG2ESbILD5O/qXFs4Bb4NC+ER6IEfwAp4FK6Cx+A=
*/