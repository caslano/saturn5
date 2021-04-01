/*!
@file
Defines `boost::hana::flip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_FLIP_HPP
#define BOOST_HANA_FUNCTIONAL_FLIP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invoke a function with its two first arguments reversed.
    //!
    //! Specifically, `flip(f)` is a function such that
    //! @code
    //!     flip(f)(x, y, z...) == f(y, x, z...)
    //! @endcode
    //!
    //! ### Example
    //! @include example/functional/flip.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto flip = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y, auto&& ...z) -> decltype(auto) {
            return forwarded(f)(forwarded(y), forwarded(x), forwarded(z)...);
        };
    };
#else
    template <typename F>
    struct flip_t {
        F f;

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) const& {
            return f(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) & {
            return f(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) && {
            return std::move(f)(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }
    };

    constexpr detail::create<flip_t> flip{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_FLIP_HPP

/* flip.hpp
tYxVLib91z5YjFgWg4scw85gQS/K4eGgL7Z9SZVMDBGEe+M/ZdkBUsRT5njE+c98AjYyTi3sRclaqk4IMP+0ziEW7PkYTtK/wg5pLtk36GuNE7azTI4ERjCg+cR3ln1o0F0a3PlTQ2w6ltmvd/EWdffI3tTd2X0ENGfNODoFqz0t/jmIlPw2ONcPnPFYLh3W5eERbx+N6G/Kp0TM76YPoyQZdoEd5KhWJ0wRdj1f/ZaAB21KsCmOcZi6xwts2S9m+rULAihJlnJKuZX6BLXVGC0FESndJyQLow6pSPUq3yAfR10LyRa9D7hwtNX/1EkvCyMSLXFzWyHI2OWuBJprZwaWzLwErr5odWQo8DmfJdaR53NFJv16YuawjuktxOK3aN4TOWrtzvbP3KQzVy6drHxmnJKH6wK7OTI9R2bfCsKGdpkJ8lIHcdw5ZfV/QQ+wdk9g7lnmCMfnzhtkxZAY2ZTTYExzD4pmKs18De6SxcgmoX8tOSmyOQi5dQAHJb1mtPJHbZOGTjSxUGEpK8TZdRGXo2kSPlXMYSCRTmdwDCMOxJaqO+OZXvmaOg==
*/