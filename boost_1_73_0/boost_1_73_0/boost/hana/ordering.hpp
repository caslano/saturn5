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
fQm3JJHCbZFkcu90b6DZf4/imcdxFjD+AyKErQWIeIXrBV7+FXHP47PpldgBFHTtYYde2WTrUyM3r2ykSzyy0NlYVusJMlxR6XLrEdOWunRy5cPmkNSpdlMPWuaIgrnCmIv15XYCVMoc+KxUUEbGj+GoU56MzY5wj1DUsDhiBVRUNpymsAq2AzOOMjKGhoM0cejCHAbAotlS+N1FS4iKmKHOx4PUYC2lomkFKrSCgMGgPiBRH+eCtVvZkaQ0l0TvaYXAYGbyVJOd6LLq/d4LaSanJKuCBlRCdcYJEIG7ceKZDV9hxgN4UcbSASjmZ+KLh1APLx7iA8kpRlcPMYXL6+7JG3O7z3vf6hBEuhtMMAiS1PdTDGFNd3ljX2VfmkbrMM0mRbmem+eGOCcEyF6IHKMFU9jyTffTUYfisqBz3JSCmJOXrCJ22o93hDbypKQc5FABtEfFTsWWB24fpSaoh3f5yf7oEQy6lYzGRQoYQ2HmKQrNlYcGu4wuKaGvEdPZNIpWW4I3G4IvjLHkLLz5M33KUjzNb4LlnD8XyKutYtSpuF0YgfoffhyhY63YZnKXbu/InAtT4MJ2RaHYdbpYZ9fbHBWTToLxwkW0TgunssA65VD25eUZkOpbKgpP8RFdz5nqiGkCw7ox3yaK
*/