/*!
@file
Defines `boost::hana::back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_BACK_HPP
#define BOOST_HANA_BACK_HPP

#include <boost/hana/fwd/back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) back_t::operator()(Xs&& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using Back = BOOST_HANA_DISPATCH_IF(back_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::back(xs) requires 'xs' to be an Iterable");
    #endif

        return Back::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename It, bool condition>
    struct back_impl<It, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            static_assert(len > 0, "hana::back(xs) requires 'xs' to be non-empty");
            return hana::at_c<len - 1>(static_cast<Xs&&>(xs));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_BACK_HPP

/* back.hpp
htDcbt4PbxA9zMhuHaoSuqq87iwtgRi1zn8F/9dhI18k9qT1L1XOhf1v8tFID1noPl7Xfwd3qXf93Hy2j7mftf5XGjH4j3xM4RjADeD+PuLj/g8xgPV78XN/PwvrBxH/BvAXMfE3jWXUTe3OOXVuSPHXzzi/ns/MT8fzMnya55eAf7R/fQncYRBziSz0ZfzzTSAeQGtrCMznh31MIY0V7f/n8C7S378zehDs76iJPQj2kJ8tqAeh4x8H4Mzys/+nN+yD4O9j5Muv6znsUVVYI19+XRfAX2K2jy8Qg9H1P8Dczm+z0DtrsnXfvPPrnIHb1cXLpLU1Cmaff98WzFEg9m4FvP8dMbDL7QSR/S1mNs3rEbAf8Ny513R0tDfW7tyBG//CwTnueU383frxBrkEX+I7U+ufgH+LmW9f53C/0dX6JwciP2naw27evrWdPUdX33+Dec6HAabIG2h9/30Q6tdOBrii3xt3gHuSe13vspntjWYS2UwXM1frv6Fg7xkBLn9OodZ/A/O62V6mSmXMW7F0Ki/0nbPMwcgt83GL3StxT0LcU8C9Z9zDtS/HDoyn+7m5tGcscAg0/n1jq76gi2yReUX75RDYX34UZKvsAHH+AoeiLonBdnViifHXpDtw8Hf7FPxdGxrbm9taW5t5ebr+NXjnvQ3ezo3I2sz3p5nXE9m412HI6XIxc33ZhJXnfRNINr4O3lIunjp/Yqo0R0+W2e/Q+c+H4257hgme3b0H9aUKFvcdp77/ArvLzFZSa0kxdv0RiKeY2dmclRFjzwI7bWYn0tm8GLv6SOQBB9nd0uP9ANhHGNjS4105iO8KA1t6vO8A+1gDW2q8df7zUfC7XGwFRU2L4hcF7906ca8A9wwfN5XJ9TuvH3n3UOKucDR00DxcqGnbgSrefqazYgjcFWa4ov70HMcg3u/iJS01qtmDRc4LsjMHbq2Lq8JC7HqNWv8MvBY3T+0UBcsxk/vdntY/Oxb6Z25uNqM6uF/lNysvoDfHfu9C7Amw13axlT+HyAyWLjNbx/+Og/6+l20vH8k47zC4q/m49n4Bk7n7W+v/H4/cHRe7VR0I0WgzK29dOgfB+5x4Hcppr68tHr5i95Ybn4C3lz6mWkrs+cPEvALMa97xMNWY5i3uWB/No1WGEL/2MZExbOdhSdl7Btg/e/tY5BzQ+ucnQkfGy8QeKWNvBX33g73YZ8SOQkWGnterhSug7Ur8RU5CfepwfqpXoH6E1n8Hf65wvtoxefWi9fl/MsZ92sSWyykdAPdnI1cuV+NXcP80c9VRIaOhR/yBU1CT3DTWUS2pwc7X+X/gr+vid0Q7nAwZe47L1UBMn4rv1ekgW+Jekfr8S3AHXNxoR03HzlEbjQ1GhTuFNHOSp+FuxMxnjw1o/w/cLjNX9DzZ63T4JsRGvXJyPgsqBCaVszIK9lQIW9315ZQLLmb7bmdAn93Pt1VK88WP1y7u2rw6/gf2DQY2JnkRL1b7s+1M59dln3n5UnsL+UxPg1vrt1stLm5baZy3PQsxMD+zW26c9ft/sO8xstXiYtb80P7/2fjG8XEl9+9bwBzzMeGciq1nrf97jvPrN/185TFIryut/4s2vBzahlS3unm0Mzmk4oIbnwvND0MbJNYZca8B91kDV2LeUZ+vfx60BYNceIpK01blSEmsc53/iDas5NlPd1JLPObxXKX6vux83HfP9IFffYKVS3vrJeCeYeBCUijFfWen498XIEZoYGeymQT3fCObzwD3CAO3N9+tPkL5cz719/+Fzq8v8bPxQaI22QOk5tixYF/lY5PLwL221qRvIXBX83LZ/XE6O3suwn2slyfqh0+BeZKLuWN0+1g=
*/