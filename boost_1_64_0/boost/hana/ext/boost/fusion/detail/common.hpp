/*!
@file
Defines common methods for all Boost.Fusion sequences.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_DETAIL_COMMON_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_DETAIL_COMMON_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/concept/sequence.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/integral_constant.hpp>

#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename T>
        struct is_fusion_sequence {
            static constexpr bool value = false;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <typename S>
    struct at_impl<S, when<detail::is_fusion_sequence<S>::value>> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            return boost::fusion::at_c<n>(static_cast<Xs&&>(xs));
        }
    };

    template <typename S>
    struct is_empty_impl<S, when<detail::is_fusion_sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            using Empty = decltype(boost::fusion::empty(xs));
            return hana::bool_c<Empty::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <typename S>
    struct length_impl<S, when<detail::is_fusion_sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs const&) {
            using Size = typename boost::fusion::result_of::size<Xs>::type;
            return hana::size_c<Size::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <typename S>
    struct Sequence<S, when<detail::is_fusion_sequence<S>::value>> {
        static constexpr bool value = true;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_DETAIL_COMMON_HPP

/* common.hpp
9sDfxFu/PaAPV62nQpXNjoA9pNr37GsBz4rZqc++3uhZo7q3rNvllZslP4fALTm/UN+Z0lo33IF/7W7/HrwVuLe2eIc6zm7qdUxDmOLH5vLL6F2xBzX1wr6wPeJMayXhs+EOY7xYTRvmqE+Cdj74DGx/qdKn0v5P272njA1mOcoarNhqcY1QcP1+0V+PL58x+vw32wpH6+v3A6WtLp/ASQj7UfiMjqDOBmutAwCsqXDalPqP6KsgwyqbyHpFlz/RMbvKpe+ctYZd8u/BAXX/PLW66eqhkNL/p7KNceHHWW2vdFSr+HlI4qSrtqaRP//Mh4UKtgSO6fB4au1uMeSfciC7G9+hxF5C6NXiFoDNUS2eaboO76TM8Sj96fyIoNRer/nKj1GeX8jlmyRjjt7y45SL6dlc1lp3pR83Txh2lWbONuclZhoSAaV9a/u6iXodoRUc/5Y2jRowUGwAB/6ONomW7Dhx3ywjO80qT+F9fZwMqNe70I/h2TdFHhXFHkNQ1rpiRw1EWZHJr/Shi0MKxfvc7z6ZSBos671j3x8hnzNOBjPTEy3pVq6q5So6FxXeqE1plWL3d4Y18bz4pTx/pn2jNhXFCrad9WMXDwturVf7np3QrtGz4oy4ibl7MLjiSnX2F6tzV9swe/RMmX9AvbKCi9X5q23EFBXeslDUe4Qt+nUR5ZNYaXeruit+11aX1JaV2d2q/2iuthfgqjsrvxxa8Bs4NpwAhqSuoSW/c81ZOkcSdUYjDnyVcS/w9i9uvcTFa75Ykt85yZZciKPbYzfsw1vXPtLP4aHD1cCJTyaR8jmdUwB8opG6ng6B9WI5Mu/TZD1+Pc5q3AFXcaBTpMQX3XdXi5X7xrhI1Emn2FT9xYFjgAoq1kWrMlfiwG6NysVm+PM7l0b6fHGTPKC3Uq/fQgBQ1Po+AfUSKnxjxyj1ggSo+xwb8Kyfqii4GRnAVRjeFycqdZT71jRUKfd2qY47LKDPptqMkDrom5xPG5V4wydXdyOZJaq6zQCB+p3cpH7TUMHHtMhAHscKlfqMwHopeO/cxihzU2ODbFke6GtyI324Kqbls6c8aTOeapk5ZB1q3sEwswa7p9rpG7vAO8YUe4Pafjy/jZMKI+Tv6sVEf7n+GCNNA9n1xzv98dkyHvZUKLK4Sso713hujL1Bl7hP3hMD5K009OnM1fwuCehD3etJ3vpxY0SFb14279hjki1x8dZG9lrGb1kuGVRVcami2xX+el2Mqqwm++oM1VTzy1ZW4nICq25xsbG0wl46pazYUSmChJOBe4DRlSDHJmUtqysdpbqomVeAPAuSxpgnNJZltazLsyTm6o9KSakY5xRjjMtFJjwdgKNT1TqIaJzoSdFPD78pkfbox9fawD1UJ6DoQuBey0X8cZ/VySvjN0i5Sdfoe+6aSMlpMDVzmjlPrsvnM68VdpKtl/r6msFvtugPfR2OCOhLYp63/jp+FzNHtY0qw9mBcyEhkZTtH3dupJ+D2Bx+3jaP39UiDiJ7VOP0SKXzr32hqBf5ECML5tOZWxW8NO6kcWCWonNLn14u+pM2gfxyCb8DG8nhfPO4I1LiSsC5x9JIleureTPKw5Q6Q6BKPtHIm9bU18RXO2y+Od+l9mcE4tU17gaRAsjOSPHb8X381vNQTjd4SuKkhDvGytjLI/UYhwn9Mf550KiDbkAFa0t12Ve5ajSv3qw06sWEfWWr5DM1br/OrDbKxCTFpUWdTqs6scZf76h21fpSz165P+6rl1gkG6iY84TRhhmKPLJ//WsjvbGSTFsH+Oh1ir6JBtUev849LWQHuuirkWOqvnCDigdwGl87pf9nRR9OzNXhVU1/rLopsqk=
*/