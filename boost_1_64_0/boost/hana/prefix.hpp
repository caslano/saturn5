/*!
@file
Defines `boost::hana::prefix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREFIX_HPP
#define BOOST_HANA_PREFIX_HPP

#include <boost/hana/fwd/prefix.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pref>
    constexpr auto prefix_t::operator()(Xs&& xs, Pref&& pref) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prefix = BOOST_HANA_DISPATCH_IF(prefix_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::prefix(xs, pref) requires 'xs' to be a MonadPlus");
    #endif

        return Prefix::apply(static_cast<Xs&&>(xs), static_cast<Pref&&>(pref));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prefix_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Z>
        static constexpr decltype(auto) apply(Xs&& xs, Z&& z) {
            return hana::chain(static_cast<Xs&&>(xs),
                hana::partial(hana::append, hana::lift<M>(static_cast<Z&&>(z))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PREFIX_HPP

/* prefix.hpp
cZcWo8khPiJiXk1bwyQHDbO+9kWeFbZx9e3ssiCDU1/Z3jvray+zpsllMVtrEbyBGJDfVULfuHjZdZkNi3N+94Hw2HL2got3kJcnPJSP+QfZOPNtwO4GX1wAZ284Rzfan/I4jzmtdPcX2Re1PmKPiV6zUZkuqA/fTurvhAdCsL09ggdefE45T9zTsSEU4+nX6f1PZ9p2VT2wRbgI58L2yitz+kFolRfN4NYjzj4PfxRwJeby441/nZ592J/rwnSgS8GT5m+4J2Z0si3KVklPNz5PpXSxn1XSz0I02B9tPQxTQ8f7Pm8uX9MPSOiVaHTT1ri9eHrEVwry6yqTXgXZOqRtLvoSm2RVelIuts/rfFpSpxZtj52u7gbWWaCJagcJsBMPe3pLmvW3lpAYMVDzSs/W37cm9BKNtqrpi3I+0IAzXLjXf3bWbmMKPXS9ndeNEV+Qb34wox10pyEVDmxi8D5z2RqKqkS27myd5U01khbwjDg4RZvQDsnInCb3WHISx5+at/Xu+9u039IdMKHVolJFUxeDntOu+AWc9lMktMrttVndy8rTunv+9qazQF/fVoStSv08yWk7Aemk0K3UFFaO7TeH9DY4a6st2sapr+EhdAY3ATiduurIcSSZS09IaCvMpcHkVX0W/wQE6Znb3iT0GQ5fq7pe5+Jw//QBdmm664YxIp0Wpxuca1JpZVE6sh3U5QirLpP0XUhGSOmGoS0bic8ybqSENEN0JCNwul7YQdvK2SS5U8ypI/b2CK9URJqvpjRoolGNloK7Nzx6RvODlKYxzmlVVfT9OM0tozzLaW5fV23eO88MjDwqCWDUfMwv/Nt0zLtiaJWqe4FFu7WHS7bzKkB1BzP548oJXS5MLjF+2Oe0hASyCzkgohdP2KsR9+XmnPY2vTRYSrJwnknp3D+GcsleXFa4LA6FOJj0QOtRDxSqoTsgpz1RZ6ZUuivF6LGK15vQqF260/Hyt+8xc7PKDvAbhNXpA+F9G8vHb3OKlx9EgTNd2VYcHKWeIPk56Y8Sqq+rynRWTCIMwVHOY+Q9L6G1GAtje+w/fiw2N/jaCghymMUP3zuYy9Kv53w6gYnbmMJm42V3L8QfnGGOvZfTWJHL2kWoVGInNXlI8eJm86Nx/j15m4nNHScSIzyyt1C8Pd0isQcVcd5zWgmZLccBnGNBY2VtB5+ECHJH1QebB8Hk3Ev/Lt2PhlLZuofw4KU9BDf0usNDx+UAgnr8XDskeyT0ufN/Nk1mIE1g+XmE5Hs4ex0Sd2jPntE1RhZZllmvv4zwtqnOMaM9m9M6M1+HbAtSV5ymfZCraS6mNLYvW+3EY5kt0tBcTNoohWxkWVrIDKFd3C87tpHucjPaosLBW5gCFZ6Vlvy+EtpOqLwb9KAcYLT7tluH2yA/OMs48T2Y83FsbGmVKoU5ODjtPmg/nW2PpHva7Lt41w2I4qlOdDVukoTPcJKwi+BgMkW/WN9n2DRX/S7HP1paj7QPJVofrWN//ZFYY04nwfBW9hbKuFvJ0kHkob6ZYAWhEbde09KHG9onLIpvJGXWD3Zu7QoeG5GWlrYir8sm5XwRXxhZD468HuHbgxr8k7nvtD8D3AWFY7c8NpSLuVsb50B4OiSspXv7ulQVMJgIZ+pJoAvxXFxkEz2+Pu5vI+vhsQ1Pm5dxTs0e6GJ8MI3lXkDlfDtpurvWcKymlx9GfCMUG01Y1i8b8zwPJyIsbca+fZkwXgJbHDQHDAPnG2m+fyihYgyT6TtUzr+ZRoych8Sx+BPl42haCxEEGhd6hr4/NlNehm30KHPTiI3EMYJmvAJW02Yse3Feds5zLLxJ84XKeiD1gMmEDwFgpljmmos=
*/