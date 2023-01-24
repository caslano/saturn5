/*!
@file
Defines `boost::hana::remove_at` and `boost::hana::remove_at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_AT_HPP
#define BOOST_HANA_REMOVE_AT_HPP

#include <boost/hana/fwd/remove_at.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto remove_at_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using RemoveAt = BOOST_HANA_DISPATCH_IF(remove_at_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::remove_at(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::remove_at(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::remove_at(xs, n) requires 'n' to be non-negative");

        return RemoveAt::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct remove_at_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto
        remove_at_helper(Xs&& xs, std::index_sequence<before...>,
                                  std::index_sequence<after...>)
        {
            return hana::make<S>(
                hana::at_c<before>(static_cast<Xs&&>(xs))...,
                hana::at_c<after + sizeof...(before) + 1>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            static_assert(n < len,
            "hana::remove_at(xs, n) requires 'n' to be in the bounds of the sequence");
            return remove_at_helper(static_cast<Xs&&>(xs),
                                    std::make_index_sequence<n>{},
                                    std::make_index_sequence<len - n - 1>{});
        }
    };

    template <std::size_t n>
    struct remove_at_c_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const
        { return hana::remove_at(static_cast<Xs&&>(xs), hana::size_c<n>); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_AT_HPP

/* remove_at.hpp
d1l7qgl9/+PydXklsN+kenY0NqG3thk1ad7vGD7kGt6U1o49cFuXgsd7WWdXO/r5iCUnwpe2AHicW5EdXfNh7eWKu1he3u7J9vQJ+7OPLZ/j+vndxM3oGyX5reKTsP7k96Ac6G7SUsu4Kx+Bv4e9jA505EfvC8dn4/5VtxQL6aXBFjcXrYH9NfWoVaKQfjd3uOv+eRA/oSpcSoW0S/Mp98ZuxfSd2kib06N8jzdjJ3YGeGDb1OZ0ss/1dV6icQDPbCd0pO1/WjbyVgKOZ81oH+5IvwuznHy5Ix6v7R2MjvQF37hJGx8PADi3o2sLOn9P84sfrr4E/pp3UrWgl+4K7tnFAutj5865LeiDUaebrJ+O4SVdPJ3omNEDp3apwOOV6ZboRM843fb5zBEQf6Pau5c60aUX/Hp364f5HdZN7Ey3WDd4f6/xWH9/7J7sTKv6rf71jBjXb9GTaknrdh1//+UEni+aXuEt6ZXbJnvTWh7ANb2NLekR7/5wcPyC9dvXQ9iKdrs56/x6yhHgjL5LWtFze3SfFjPFD8+/frmt6GN+c2VVle0Bvtvf04VuMeHhsGuVGL+nt8qFniXdIhhaqYb+/vVNkQu9rtmvET/Ge0N55EBxazpm2pr1a3tieTYblNya/nK09fN7p/F4KgaXtqZHhd55UqvF49dNJG1D56xZeFbZCcv78ZDUNrSqyYrpN4yY3kFa2JY++jLv
*/