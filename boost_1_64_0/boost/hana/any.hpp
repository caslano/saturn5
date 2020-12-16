/*!
@file
Defines `boost::hana::any`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ANY_HPP
#define BOOST_HANA_ANY_HPP

#include <boost/hana/fwd/any.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto any_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Any = BOOST_HANA_DISPATCH_IF(any_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::any(xs) requires 'xs' to be a Searchable");
    #endif

        return Any::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct any_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::any_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ANY_HPP

/* any.hpp
V+FxyBySCvdh+Cn8I/wdpIwnvGZ+lr3DyXsR8vODapyB72Br+DU4CH4DpsJH4WD4HThM3MPh9+BI5Zb5Y3M/bMqmCPPH1BGqfdUqxhgvj4WTYGuZB+NZVfelPXTCDrAaXgTVPrlwFbxE5ivJy6qcJi+rcvoy+DzsBj9Qukb9dCX8G7xK5pGvhimwl8wn94Yz4DUyb4wftV6gP3wIXgu/CQfAJ+FA+FOYCn8BB8MmeB18D6bB9yFtJFXOD/Prw5HQ0Yr8H6PSC4fsjwwfkPtyEayR+3J1W2McLwmmwt5wKOwDR8BBMBNeI+VBXxm36Qdnwv7yvA2A8+FAWXeRDJfJ9adgIdYg4Vgu4Win5gOkfyXt5Cx4BRwP+8BsOBlOgi6/fxknmgyXKrfZDpc9dHm2IrTD18YZ5dvX4XD4EMyFD8MSv3/og4/A5XCDjKd/G/4Ifgc+r9ySrubertRZEdL1zjgjXe+Cvf3+YSq8G06Ey2ERXCHj/F+Bq+BKGc+/Dz4BV8PX4QMyXr8G/ka5Jd7mnp60ISLEewHp4+dCmCTuAXCx9DNuh3fCpTIOfjf8MVwBn4VfgUfgfVDmCWUPSrXvZrN5Qleccd888Fo4Dw6G8+F4WCXx98Lp8Dbohj5YA6vhvbAGroG1cC1cAL8LF8ItcBH8Bbwd6nnzkxKudRHmzZ/118/wOdgbPg/7w5/BQbABDoMvwHT4orQzfgmnwZfhfPiKtCdek/bEHmlP7IV3wX3muJfsdQinN+unQanf+0j93h/q606e47pRct1ouW6MOU4s++XB7hHGiT8nnfz8O1TnnLQ26rFYHV5zHznVJlTX9/LrSrma3cboH+XANHGPFvedcDJ8AebCV+FN8DBcDn8Db4at+K1psCecDsfCQlgEZ8A7YAl8FM6Fz8NS+EqM8Tt74Tx4BM6X+qcctvePR8CuEH+q/eqDE2EtnA8XwEVwMbwdfgk+CJfALfAO+HN4J9wH74Lvye9+Ir/7O3gPPA1XQJmflr2y1BqpZvPTD0h++xrsJ+4B4h4k7iHiXgLXwV/Ch+EeuB4egU/Dj+AGaW9+C/aFG2Ee/CH0wh9B0lH5vxtuhmvhE/AJ+GP4U1gPXxF/r8Gt8HX4jOSH4w7Z5wf+UuLVzaHWX6vP5dL+uQr2FXeyuD2wB6yFiXAlHAfvg5nw+zAJ/gL2hkdgH2nXDICd4UB4OUyW/DIIDocpcDQcDCfA62A+TIO3wGHQB4fDhXAEXA5HwgfgaLgV3gCfg2PkPjrUfirSfpH4Xqnm5o3Pra2N+BbJ+PYcKT+c0i9xwdHQDWfAUrgBlsFHoQc+A+dJf6IS7oe3wU/gAvh3uBDGxVC+wXi4GHaES2ASvAMOg3fCEXApzIR3w3z4ZVgI75HxkWUyPrIcFsOVcB68F/rgfbAGroJST8seF2pfjWb19POxxrzV67CLuBPE3QM2wYHKrfoDyn1JjHKb9ZV6rx7ujVBfTZZ5mSnwZjgVlsPp8H5YCNfAPPhDmA8fhzPgT/y/A3fAW811LfJeOqyLUF/9XdYvUViqcMfAQbAdTIMXQDWOAdW6YzhDvp8t33tgHLwDtob3yPcr5fuvwbbw68od6Oc0SLiKIqyjOyDp/CfYRdwJ4r4Av3+GneBf4OXwr/AqeBb2iVH+1DjZGThd/d2cd5f3X9Xaw2bz7m/HGTqHZJ3Ce7AvPAxvhu/DMngEVsAPYBX8C7wLHpN202/g0/C41NMfwRfF3+vwE3gAnoCfwU9hor9fAVPhSZgJfw9z4SlYCP8AZ8ao31H5+DO4UrkD+Ve94wqrIrQzD8v89fsyf03Zo+73B3AsPCrz4R/CMngMzoO/cZjjXvLOJ2VNhHE=
*/