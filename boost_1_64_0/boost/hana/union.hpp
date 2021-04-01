/*!
@file
Defines `boost::hana::union`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNION_HPP
#define BOOST_HANA_UNION_HPP

#include <boost/hana/fwd/union.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto union_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Union = BOOST_HANA_DISPATCH_IF(union_impl<S>,
            true
        );

        return Union::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct union_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNION_HPP

/* union.hpp
JCIjR9Z/ahOJHrUYqXYCitm563JJ9ECKlPRb9EWsp21vJ7xyWO6NQsskQ1OwK0mQf+iz0REPy1meLjhL/T058GFWn3XqRHR76cdBJdEndXNcIje2sogq6ORGqZNzrtl8wcIvCTP/wW6vKNfbLSCmF0JLAfTLhqFfc5ILn2bSOVXhRtcKNqsjtDCbRECSvTwa9QnGmx4OyS3/9Ef981E7UEb75wspXt0/ktnZdRBNr4eg6cjRfTMjJ+LE9+utFmhISZatXSw/Ktkng/FUdD3ciLULdgScSiCBx5MtCFg2hTRin4rFa8lr8TYcTDwS5J8knvWmpjsRabrr4/nnNMzCNZe9GvbqEeXSDGMp2dWIpbFRfEXPkl4eE737ARDYDuQ0YZ8tTdaH1OBqo7h4vAINGttS1I8rvHPoEULVNtGIddW8/lwP+MG/f+LESxzdh0C21mgbLorXTiTXTFSTwSch+B120Bt5puTBLG4nudey7iRvSF8a3piqi2ppJq/57TcffQroT06+u4TvqLiJIf8EEAi4R3NwxcDBETQoVw7tcLZS/P6JDOBlfJ1ElQ==
*/