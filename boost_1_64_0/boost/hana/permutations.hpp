/*!
@file
Defines `boost::hana::permutations`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PERMUTATIONS_HPP
#define BOOST_HANA_PERMUTATIONS_HPP

#include <boost/hana/fwd/permutations.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto permutations_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Permutations = BOOST_HANA_DISPATCH_IF(permutations_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::permutations(xs) requires 'xs' to be a Sequence");
    #endif

        return Permutations::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    namespace detail {
        template <std::size_t N>
        struct permutation_indices {
            static constexpr auto value =
                detail::array<std::size_t, N>{}.iota(0).permutations();
        };
    }

    template <typename S, bool condition>
    struct permutations_impl<S, when<condition>> : default_ {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto
        nth_permutation(Xs const& xs, std::index_sequence<i...>) {
            constexpr auto indices = detail::permutation_indices<sizeof...(i)>::value;
            (void)indices; // workaround GCC warning when sizeof...(i) == 0
            return hana::make<S>(hana::at_c<indices[n][i]>(xs)...);
        }

        template <std::size_t N, typename Xs, std::size_t ...n>
        static constexpr auto
        permutations_helper(Xs const& xs, std::index_sequence<n...>) {
            return hana::make<S>(nth_permutation<n>(xs, std::make_index_sequence<N>{})...);
        }

        template <typename Xs>
        static constexpr auto apply(Xs const& xs) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            constexpr std::size_t total_perms = detail::factorial(N);
            return permutations_helper<N>(xs, std::make_index_sequence<total_perms>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PERMUTATIONS_HPP

/* permutations.hpp
D3u8vM4EblZVqS3HIsfdPtx0nf/b/qa/g5KGAm+/kdfrOS800EVYrmR7Nlb7mw8d/bVuy8addG0JL3f3zppCDjReQVFEzmZ8DH7AaU9AA2+HrmGanvgGTW9En15K31F16ZQbNnzj+EJF2qm53+cfrjrDXx/yAQtrEMPZ0a3DzfE2XG9+7avNfMBkLxWOADG5M8GP0SHMwMRc986GLnj+p/0XnM/tq0ZXVZ81AheijU34w8U7/3LcFwZeXjr8gqKBXruecIkZKOcDMRTeJoEA76Hz9jh8iX3ImRnPNteqUcYeyfP0zulgZMCMHcSEaZfwwrg0RV/oNj+S12aCaxk5enuic6M+LhnnXGipiiwXkNcB07V5Bv74aMptcYaHuzrtTQmdEr3RRZXhB2rH7syZkeY1vd2d/+p8febV0Bdd2YsHYR7Hsqdpb0/KVljzXWuhKjuq7OWTso3peiuzTjycl+3jPONllcO8K6VOvrdxT0UP3zqD2cqxvyFUBhXTaTAUFNtixi/XDfS5g/oP+GHyMMyWa6RvhJXsjEPpj/v3QwLOG+3fTlUdFYAMm/pkwicTXakVzqcQ++HhqQKU1J6LkODLcU5fY/aWXbUKR8vUTXYmBAgE2Dncdtzx8NO503yguf2ia8z9UHEqVHXDMc+DRZhT+m1Bqgz8Mc2C7ZsbO9KTJvw6kZumxEywC/zOCso+naO/SHhZUfd5o7qmIF7M9u5IbhyH9JopnkXZZU2X13aOVQ6WPJz4yFdM2EJvTfho0QxZ0VptRZgL/wIfeYNi73M+uRFDqWuJQybw+ZeY13+Y4Xe3rXH+w3Wg/7cwr199rTk2q84g6uSEZ/jP5/kG2ZQkfAxkpgHnz9D8E9xZLvsk+/aVrz3HoOmUbMB08Tu5u/303dncpnM14aVFXjvn/zab9S885J67oAcfOL3CnFENCuJj3XPa7u/OcNbWNzDlRn3A+JDM3oCflrSlc+8/4FZKERkQtiKJCVyME3X8ZtdO10TT9bLp2HIlf3qw9Z3jVnz4gMyG4auzNpmyloXNapI7nNxMJhpkxnAkrtofEl5KNNgzB5O1xAt9I1ZHYGBc+jopVqjRKsNWZBfHBz1JH/+xXKc9Q3A+WJYu8EbVGDoL+HgsvjFii2N3i+clbTJC1rqGdNpNvDgw5tbDw1v+zqNIjsAq4Xtj0jZnL6eUKvPsP2gb2SRf+LrpO1ZtZZXVfSnihngbr/heuDhF+msn9LnoM2VtFtEitIoIrMdOnOR4jZPNXEJfCl3YobStcVgMTrvsP828DXPsP87j9hri5FA3tdBVa8M0S/FJyOaN053QeV2oCtsXmcjNYzB8FuW5fNDVpqqzKhcIC+YnJ2a2OyHJaAo3NIYr7L/hOXGeXi+xjXFvgH1dKqqctzi29+qc5twiV/1Q1RVI0uLXJ1sJlE9sJVRn+qFxh6n17wVosJ94bM+KtILTDhA53KWlGoTDf3X+9rlp4R/NquX73fVmclnT9qbLi/k4UV+PGCfyD+C8eoiqpWxlm/l2HDVWke7ls/GtyjbPWymyu68C9jwl4nqIK/9liduklbj65VkfT0NfOiOsk6QsPkUNrYUV/DEt6+Mc5e0pjSj6yvZGjlhhTi2JS+Vtwv9hHrm9c0C/uml/4tThYRLr7MrXT23y+7y1VpbS86MJGDh5Di6Oy23goPbgu95mxNhP+A0zfnmjZaa6+qz8YB64wJFjwCX8tMDwtzovh/+0fbRWOb8TJVRdtdHWc/MBPzfD3ZGw3lCey0WdNCozqos7E936GPbbHH2K77k/SPoDOUuaBuzorhEYHQ/saWU5XwGAt0BFOrXt2jdI9QvaFmhdOfwrXrehRqc=
*/