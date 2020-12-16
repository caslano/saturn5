/*!
@file
Defines `boost::hana::span`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SPAN_HPP
#define BOOST_HANA_SPAN_HPP

#include <boost/hana/fwd/span.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/detail/first_unsatisfied_index.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto span_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Span = BOOST_HANA_DISPATCH_IF(span_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::span(xs, pred) requires 'xs' to be a Sequence");
    #endif

        return Span::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct span_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto span_helper(Xs&& xs, std::index_sequence<before...>,
                                                   std::index_sequence<after...>)
        {
            return hana::make_pair(
                hana::make<S>(hana::at_c<before>(static_cast<Xs&&>(xs))...),
                hana::make<S>(hana::at_c<sizeof...(before) + after>(static_cast<Xs&&>(xs))...)
            );
        }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using FirstUnsatisfied = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::first_unsatisfied_index<Pred&&>{})
            );
            constexpr std::size_t breakpoint = FirstUnsatisfied::value;
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return span_helper(static_cast<Xs&&>(xs),
                               std::make_index_sequence<breakpoint>{},
                               std::make_index_sequence<N - breakpoint>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SPAN_HPP

/* span.hpp
/E/S7wuPv4NbRXqWcRL9msRnaJMC1775s93Rf+SulPd+6dldybP752d3He1Pu9c4Gyv2GnDHcwDl426bwBzXNz30IZYdYVkCakxlV4Cyh0JZeJGbg9xonYj3xo9B+mgIj0WJBe+PrnOB4D8UlCNIIXCrW6IN7MvxOey6wVMBlkVqc7jShaGszM2MfC+7bCg7d7p/sDmCJc7mZe+6ApbF76rIsX0lLAsuj+DSMMcvucUrSvwS1cCXUrt0jEnKz+Tuo33FJC9M1wpr2op58Bg+3jvZmgVD19G5E4SNI3lJy/y0cnDcSY23u8WevFfQuq4RbccHJnYJbW7Tw4o21dAmP1RN68v7mIfc6ZYkcD5/48+ivLeUxvbBWdMvxNc/r6iji8kH69bbZXWkdW1pHtfPUDmrUoajzhBgy463dqZxQF8o6vSsNlor1SKgN02ldN+Do7A/gZTgIVHqhn94xRR7pdONsXL0C5htHUTot9SHTqhxeUypSQhSOWJjvJKuYW0b3mMbcOdA1PQsebVEi9hP3Iq6sXKO/XVueSNGORzv3B5dvmM7VLr2Gsc/prIJEu53tHA3cD5tgxCsbTrfdFazGmbrbW6d3Jl373TLnd349y2CuPCBRgMlmWdFXziTNuCPCc/W426+NcvXbcHfOCXPxXlGeW+pWimNkJJVOVfBWp5nlE5WzArum0FFH46d5PMA0sOqfd/Y+qClQl3KUu+Khxdz7mtU5m1trdwgG8Ng9ZntP2J3gsWZaBFjrWlVUMnqUYNbRQ7wec59+3nRN6G5V9BmlkFZVhE3jNL1rPWN7jiXZOko14A/U/pVrmoVQjrYA8n99w3qHLPxqvL7bK0X4QIcAmyCnfo4V4FAmnMhq7kf16IybtnZrg+QnKxLdR1jvEZRV8BvbOu+tZqtbT0UbdkxKBOxYjBe4hZFHdz3lROmZes5JvI2ec5SOstaZTpjjWbr8KFQ8dM8Ey3lO084aystONtPljN8F57S3U4MxupBa6bvOhGN8RuUXhgm2gaGt1ZhXqLtiWJYnB4lJ+XwZZCz1q0L216jjPJKBJxR3C/ud16+h6B1OtbzqvaIbIqX40lPyesEyZ+1Pzs4eih4CeLZ/fs53jiuFptgkT64L6j1YbizjaOPZ3dXm01bDbLMCEXjxe/+ozK/VPTMOYC9+3QP67v3lGb/IZkEbRLHSFMDgt9s4yhc2YB6k8sfguWjg4AO1vrdh6Ed4Qk/yn26X4Z1RlvI37+feUNq4dXbrBCb4mcm30s39H7QdQ6H3p/lkA2Y0IcA2Jz1gek54yeFHMlMx7UzjWHrCGuSOGnKiZUTtFsU/GFRCChXQueGpDCF6PoXv638/ZaHO4b7zavLftVyUO0gq/k5BNBLYGqO72FcGIK71vS+6fxXT3MJetf1XTOXU8lKYN8meZJQHEP7eNEux4Qe+ka12M+7b6z/R2G3yfvQq8s12lW6H4ZqvqALG6QiH9rVKd9t1FBV0ivLQEcFzkne2udR2p6p3ihrQo6khxxPbQE3wFyRJU9b12poO8vSh4o5szGPekkvY7i16cB0UNLjnM30mBewga5XHVRwmmMLZ/gXvtlb5b0CY5ALOYJ5NfhKVIaF+CDki3MOx7DO60vBqxlvVeO54ixFE8alM+szJAqfxmFe7DXlnJe6MkO4xdktfTfQ05HeQZM978aFnI4ZLqVutMhy0F12/3BBDOrzhQzOQpp+0Vk9jsWDtu6/vz29asQ49/sUvC1Ttexqwy0rlzOMIEz8N0Bc2tdMcsC1orYV1+yhWyeHKdMNbFyoJgaU0xSeHj8VRmKWX/eaSZxU2zlvO1u+FxA3eSt4Lqf8LoTnNkpbwQID5vY=
*/