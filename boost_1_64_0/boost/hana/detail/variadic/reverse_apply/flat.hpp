/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply_flat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/at.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <int ...i, typename F, typename ...X>
    constexpr decltype(auto)
    reverse_apply_flat_helper(std::integer_sequence<int, i...>, F&& f, X&& ...x)
    {
        return static_cast<F&&>(f)(
            detail::variadic::at<sizeof...(x) - i - 1>(
                static_cast<X&&>(x)...
            )...
        );
    }

    template <typename F, typename ...X>
    constexpr decltype(auto) reverse_apply_flat(F&& f, X&& ...x) {
        return reverse_apply_flat_helper(
            std::make_integer_sequence<int, sizeof...(x)>{},
            static_cast<F&&>(f),
            static_cast<X&&>(x)...
        );
    }
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP

/* flat.hpp
wt3swvPUDUlUjVxaTgTbdvxcpo13LtcZ0nyRm26TQRirls71hHIqlunxkPKTKUcrNIA9VPDLO4gXlE053UCIRbV5pDFq+l3kz5bpj7Oc2hH9ANvogO+NBJZMbC3bwpdqg7u5hVUPrXbfIUA4w4X1PIeK9WxxMz2dytc2huUmqJkXfVcSrCb7U/ZILPKZjXsEHn+3JZlXl2R0GIGMx1XP1UfGdiJDtRxzusbMlQJkVX0C/Ez0nTPClOV3aTcmKOHVhGdgkC65DYmcD0yeYYc8GhajZEihDWuDKbaHtVQ23tzcP1pWqamnlTqaiXuBRaoaqH5d5+XEgtGVvJj61ExqHZ4/G0X7f+Bam2uiPl+1q/mAhO8hm51RWgLEaE7hlm3rymFCXdMsbfSx/IMoxR1u/yKLbeUqoV8BG5o66Ol1bIrMAW5TFKiysl4VYLFlDZvmGnTzUZhY+cXWPs2hIRwMi2Neb1yY/zzaiz6gWpvR2LyDtEyNa68L/BxrwA2MQ2gSMitBeRjrRW9p+dl2y/n5R6hReiGtO479pe353E6d29yIpePeBgMOlHnHQA==
*/