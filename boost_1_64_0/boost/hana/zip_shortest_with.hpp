/*!
@file
Defines `boost::hana::zip_shortest_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_SHORTEST_WITH_HPP
#define BOOST_HANA_ZIP_SHORTEST_WITH_HPP

#include <boost/hana/fwd/zip_shortest_with.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/take_front.hpp>
#include <boost/hana/zip_with.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename F, typename Xs, typename ...Ys>
    constexpr auto
    zip_shortest_with_t::operator()(F&& f, Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_shortest_with(f, xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_shortest_with_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<F&&>(f),
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_shortest_with_impl<S, when<condition>> : default_ {
        template <typename F, typename ...Xs>
        static constexpr decltype(auto) apply(F&& f, Xs&& ...xs) {
            constexpr std::size_t lengths[] = {
                decltype(hana::length(xs))::value...
            };
            constexpr std::size_t min_len =
                *detail::min_element(lengths, lengths + sizeof...(xs));
            return hana::zip_with(static_cast<F&&>(f),
                hana::take_front(static_cast<Xs&&>(xs), hana::size_c<min_len>)...
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_SHORTEST_WITH_HPP

/* zip_shortest_with.hpp
UdFM4TwCju+3VgAggXJ1I8TAStV5oop0x7YfjfmXX/yrdXbtBqE9XjgvkJT3LhzKcWRE8DEcNGcroZmnykIicYjnjLZEU6o1uCxl97laPxzwmFwg5mN1BPnh+KQfFQbVxRQbQN/aekVE7hcb0KlMkglRJwO9YM0c/FnjuuPF/966h+qOUVfyZUZopRbs1QHUnSeCEBR0BWuXmMrNbjMXgNf/NEBsaJpSokXCu5ASa7jpt3mnX6Y398Y6WvFDk9+1+NQ/edemi9Sli37XLK98YFTF86tZnH6Acx5+MptveRR8AVfxwOCWI+s50/UMpBYBgvfdgWWuYtT8WxeQR4Fb8+0f69aHqrNmeKNzNEIT9DEpTirM7lAWgeW82ob1beQ/qDFbe9P/XGeR3pzzRK6hX9rTtRq2M1IiKYTi90CQBnmdqyh+IbrsqrK6W0jR2bjoE4JoGg1DRV3JP+P9/GQfTxiaYoIMHdx/CSx8mlqRzna5H3ojw1OqA6BV/k+eD/Ozn+1s11qjg0jfLN5DtF3YYK0cVfo1bC+m9KhgaKjfSE04Zcc+ezV3YndCIw==
*/