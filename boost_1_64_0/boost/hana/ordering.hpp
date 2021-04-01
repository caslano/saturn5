/*!
@file
Defines `boost::hana::ordering`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ORDERING_HPP
#define BOOST_HANA_ORDERING_HPP

#include <boost/hana/fwd/ordering.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct less_by {
            F f;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const&
            { return hana::less(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) &
            { return hana::less(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto ordering_t::operator()(F&& f) const {
        return detail::less_by<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ORDERING_HPP

/* ordering.hpp
1AnGKbqGCPwA/b/Gh49KboRsh75eeJv4P2fa9oZHmVqKTcVHdBk9xX6vJ4NSrKmOaGZugv/5PE1A8MSkBXsEEiXMu/BPV8CzcKbLHI+gx3JSpOZLiDwrwSX3/J8uVnWRu/O0VSrpEm+7Tg3wMHpZl4v5AGHCTON9gtPb070rmnC3apkWUlgP826rprZVJ/tJac3VWFyFLq3kbsACWCNtXZdNloJLEpNWiG+zmHIAHMIV4WgaEF21KcRe4TfXdcWgsbCm9zASMLOz1/Nqhtv9ZSaZvKgfzGlx3trkp5+JYRZMJXpnO8iPNJ9tp4RxUzWb1ngkwncYQTb0QVuuILhejSQ2RK8KXQ52n3NwA0QtzwuYJdzreTcTY7d+m9UkZHn20KB7DBmCw1t02SfCFBdnIQuuWQIgvgVbInrdLjChbe1/7+edGi4AruF/aU39p39x8nZz/RNtBwan2S4OGPhjZryv7fbYN6rh3RyrhVgfGTB1UnBP5FopZX0mD5h/RvC9EB4s945G2pvos25tZsVVxLlw82Sm9G+vmujpr7jW7mfuMGrpNluxCB2NaA==
*/