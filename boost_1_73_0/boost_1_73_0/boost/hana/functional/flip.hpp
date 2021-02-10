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
HQlOsZgdVJEPtAQkXGYpiAmJOlJ0mfHu5XhhIr3f3TRzw5S5ZZGCO10JDf0pkZxlckY3uMVYK2Sldfk+sTOfoZsodA5d9Rxlh86nl2kbaEWQsqgP6pxO1bkDZPFZc2fWPvfbpEsBNdqvuyWyBwofSLmxt/RgxnhmV7CJBnSDUyPmhK51IinSVmURNvcaCZs1c7b3NUSpXMeYLzXomyl9mzuRLqm/UqW33qDCpicIfV1Q5rKyqLuVlU3EyWdR2peGWeOlYLIPZHhiWCXRKpZr1+EBLNzpNV5S4cSMDRXXvh64rjK3UHEGtVV0r4jUGq2310atH1NFLaiXpQGbhBZtJUoWUilOM97ebIKhe2ClFBM2y45FXaYhF6inYjlWD51AYJ4WHvyDwuIscho9uF1WrYLSKKe81jFK5vf1LGIFuvg3uTs8kL7EImMg47LgeiCYlHI7ptuCtvh57dxSOewbJ1sachh4M8Clbiqtas1+WJT5P6mOH/jJErouGrPCZEtqpSX/Twp0e8BtfE2xhTwkzQ+F8qdaEz8XsjtqzP56lc5AFFuTHbRiBf8G7x2VUhWFHNN8xt85gY3Kp9rf3flrI5cbSgNntf4eXpw9yFl85ymwjKlKuwMlSPcZDieD4cXRT6M84MzGm2c5FfH6
*/