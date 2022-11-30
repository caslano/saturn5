/*!
@file
Defines `boost::hana::repeat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPEAT_HPP
#define BOOST_HANA_REPEAT_HPP

#include <boost/hana/fwd/repeat.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    template <typename I, bool condition>
    struct repeat_impl<I, when<condition>> : default_ {
        template <typename F, std::size_t ...i>
        static constexpr void repeat_helper(F&& f, std::index_sequence<i...>) {
            using Swallow = std::size_t[];
            (void)Swallow{0, ((void)f(), i)...};
        }

        template <typename N, typename F>
        static constexpr auto apply(N const&, F&& f) {
            static_assert(N::value >= 0, "hana::repeat(n, f) requires 'n' to be non-negative");
            constexpr std::size_t n = N::value;
            repeat_helper(static_cast<F&&>(f), std::make_index_sequence<n>{});
        }
    };

    //! @cond
    template <typename N, typename F>
    constexpr void repeat_t::operator()(N const& n, F&& f) const {
        using I = typename hana::tag_of<N>::type;
        using Repeat = BOOST_HANA_DISPATCH_IF(repeat_impl<I>,
            hana::IntegralConstant<I>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::IntegralConstant<I>::value,
        "hana::repeat(n, f) requires 'n' to be an IntegralConstant");
    #endif

        return Repeat::apply(n, static_cast<F&&>(f));
    }
    //! @endcond
}} // end namespace boost::hana

#endif // !BOOST_HANA_REPEAT_HPP

/* repeat.hpp
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
*/