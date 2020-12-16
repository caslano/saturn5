/*!
@file
Defines `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_HPP
#define BOOST_HANA_NONE_HPP

#include <boost/hana/fwd/none.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/none_of.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto none_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using None = BOOST_HANA_DISPATCH_IF(none_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none(xs) requires 'xs' to be a Searchable");
    #endif

        return None::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::none_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_HPP

/* none.hpp
jj9s2S7f9XYi0KxOnv+u+3Yj47SWUS2gPHF57KeAc+NY4swLwnA+Xb5hmD2KyTT3dGUpP8D+ChWqEaZUTKyej9mCK/s2MpFlUWItUQUjQCW4NVX6V2jflUAOp6fORnVhwZ13iN91XnkhIwzlyRST5/o5Jwu9+My+l2USDLu3M9Ehc+36aivDEB/cyvwSec6IZ3BcS8rLKEiSRstzNunshM4Ch24tMshJQZamlxaczThoLu7W9Oc5nsW4yhJZQxzGAWJIsnPgqw7NTNSVn0Zxk4qHneES3yXJCp5X4Hpufvo6r6s6L8R0d4KZYVszs4O/eL0ef+e5lDF28mSkrqpHe+N2+4KzA5vk/UmrXD50zqHrHXfecWXYRGmeCK15NXSXaC/isEGBfss4q7NcFDvntZsGVoRJ9AItznE8426TP7TW5jL+TjiuM7inhXmch8htrxIkbtEF/YjkUod2JdSZ0tTYG2KTJ7HdRY+ju85VUctdYHDyJb2WGyMxTPIy8gs10XvAcpGUIez8/ei13PO3SMosy2tPSA2uxQy9KwEDbixgb8y3/rC7fpbFvP4px+N7ogqKsvHCwCGO4Eq9fRGxo1w5L4I+Kq9rn+ijjg1BjInvtad7g/7miQE/lyV02VWdCBjxunv4xSvcduKcSKugTDWky9RtRSabve6K3j7kh0Edy1yEeG5r7byAxUormzsT7Rff6tTGortLPvE67vuRn2ELR5f169ocn88XHe/pFQM/qnKomRz5XVc0XQBnknlKxx8f4HhKiCSZrAofgmifMOOPTzm0S1HWaVYVCTZrI4/+pzawPr/uOg7txoubKs2FrhB4ajm5ff4DpyvBT1XhxUEWCEyMtnPRVkQu9clUC25Ahj5bPJxupVI6BZGXxuaZg1Me7JBd7wlXPyh9WcjEiy6XNvn1cjzL0LPUsvCUsKCO+l48gueccG0RZVg1dR1XVj5gC5/VHhzS+PL6Z0ovT6Vf5QKbI6PG3hTf6fQxEj4UO36aeh09SkqjCRoDqunRGJ1ntsufusLRx3i1imWhFlN3s9on3YSzfhKsvaZM6ypS4P9NJ4Ev7bvsZreW/3CFK4/VUZHEnleayVWWFlBUDfVLlul/SDLFtd221EUa13HeiABmGD0TIfXnAnPFEcy/foHjQcdzD6vZl7YJXP6kvB0/PcFp67nWNkNaAG0rkgCK400rtug72+/FdZ01Vfpxg1tPAUOlnd3N3nq2fNbwOj50mmETJFkBBkCl/nJmKOhMd2mmQZqFRRnYhcx92x5GZ/p1e2drnUVeHUP54zH11zzahht4vASOC0dlJKssLmsz3k4DpnTGoY4T06FJZR4GyX+iTxMuBinl8Lmmk++swVSnkSeUZ+7oYMuVl6846fJXk4dZVAQaGjsFufShohPBwjhFQ+BgOd453ULENQhDL6B2Eoe2b3nypDvHYIyoBHx4YJR0s22wc7ZN9ynp+umniVR52NqcvD3/0Ldez+1rBrVskgU17gaITDPpe1EYHOaYhC2nnduEt7uBuqqKo1wGhqgyXjmLtdnzhzjZ069JaLmCJpx7l0eHnbYw2q9yaed1Dg1IkRja+tkWSHqxQpw59qEbzZqqzqBfMz08tP0/bC9J6mJpMKn9gHTLHE8hAhn7uAWXlvbR4a5L97snXV1cldQhzop6lu4WxOSz6yqe9JVWEAJdOhuv7fQ5Un4AUVyoo/3oEBaKQxLRmd/NSVdWjaAjSrKkMeNtRtpMLhdbNU6mH7mOqx8pyiRICr/uEWeT7srr91zs5RaKwgR6D8nn/T+0xtHPbfJxWCrCNA7rEvaehzsUJ2JE93gOG+Yi9uqklkkEXlfi3gYbAiVGtjg=
*/