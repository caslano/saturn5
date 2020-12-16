/*!
@file
Defines `boost::hana::reverse_partial`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_REVERSE_PARTIAL_HPP
#define BOOST_HANA_FUNCTIONAL_REVERSE_PARTIAL_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Partially apply a function to some arguments.
    //!
    //! Given a function `f` and some arguments, `reverse_partial` returns a
    //! new function corresponding to `f` whose last arguments are partially
    //! applied. Specifically, `reverse_partial(f, x...)` is a function such
    //! that
    //! @code
    //!     reverse_partial(f, x...)(y...) == f(y..., x...)
    //! @endcode
    //!
    //! @note
    //! The arity of `f` must match the total number of arguments passed to
    //! it, i.e. `sizeof...(x) + sizeof...(y)`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/reverse_partial.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto reverse_partial = [](auto&& f, auto&& ...x) {
        return [perfect-capture](auto&& ...y) -> decltype(auto) {
            return forwarded(f)(forwarded(y)..., forwarded(x)...);
        };
    };
#else
    template <typename Indices, typename F, typename ...X>
    struct reverse_partial_t;

    struct make_reverse_partial_t {
        struct secret { };
        template <typename F, typename ...X>
        constexpr reverse_partial_t<
            std::make_index_sequence<sizeof...(X)>,
            typename detail::decay<F>::type,
            typename detail::decay<X>::type...
        > operator()(F&& f, X&& ...x) const {
            return {secret{}, static_cast<F&&>(f), static_cast<X&&>(x)...};
        }
    };

    template <std::size_t ...n, typename F, typename ...X>
    struct reverse_partial_t<std::index_sequence<n...>, F, X...> {
        reverse_partial_t() = default;

        template <typename ...T>
        constexpr reverse_partial_t(make_reverse_partial_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, X...> storage_;

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) const& {
            return hana::at_c<0>(storage_)(
                static_cast<Y&&>(y)...,
                hana::at_c<n+1>(storage_)...
            );
        }

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) & {
            return hana::at_c<0>(storage_)(
                static_cast<Y&&>(y)...,
                hana::at_c<n+1>(storage_)...
            );
        }

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) && {
            return static_cast<F&&>(hana::at_c<0>(storage_))(
                static_cast<Y&&>(y)...,
                static_cast<X&&>(hana::at_c<n+1>(storage_))...
            );
        }
    };

    constexpr make_reverse_partial_t reverse_partial{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_REVERSE_PARTIAL_HPP

/* reverse_partial.hpp
v66cz2xJN872b7h2b6IEJnPA72HpVQsSSR983K380Cc3KlV5m4bE+6sF/jXi8Ry5UT+UHV/bTv09wvuSLCHydxfTTyy9BifUy56FOE+Pc//WEIMrv7nfbNHviVt5m4hLsAnxX+74KGZ/Dbt7ZZRSw4MEvm01qL+LlHJgXMqmI99zgRwHBcpdVWtJLYQoym3wg7MpOFQ1inFh+BC8z1dV7KsQGB5OtTKVlX3+ifftuSXV4P7MB1p9+wxl17sLVA9S2XKWdxwuzOCKwhon2P5lfhs30yx8HCls22n4J++L8yrWWsAoa/ihD63BfzBR2ay75hq/bgLvCYpOHox++lL8AkthH0WpbPwA9hvy1ScguBv5OrsoFcA1G0v2BVEtjzSl1vdDH79PPPmkelnwiDg3o5eNzotk8UdlL1Fj1B76S2AkN+J+6oe/BNGc6cetaAEP3rllNRC260UhjAYIeOMjqwFwyvaXEHNIobWPbwXSiZP4b1Ebzy+w30KVnViN93/fJUt77lCv8rwvaa7WzqYIW3enEHk3oR+cZX4xLe80x58dynqJ4P1zKwvxc0HfSBTT2KUCc7AXlsWynicSHyS8/ATBW3NR3aarT1n8G43w37urLGc8519NpdZOFsh1Gn2ScM1EDoUB4bwvQYL7VnbqL/yMzgv84GHCzg3oQ9ZqcjEBmUu4yxN5DHWqNP6h+bze4RguclXE6/Jgny9S6nEI7+Fgv4OgwJNRrL+26tY46jYyV5ldrFKX3Hj/gqSniKpe3kO8gkdnFe9z3l8l/saQTAd4ezMfuAOvFzMVv7sS/JWJahx+ynpZy/mCkI2RYEkU8YrxEmg2QxKwTljr1aoW7ansmXpKvd6Bv4RHTmfx/m5wZb2gPBVDddnIQNTEcblyouo+wlm4wEPsV/FA70AOLrkxkqDkSwmZYMDe4oVudU5bR/iV567diWlpvFFiFIJpPlIro9E3sGsv2wp8MuCPwHgczL0w5r3quvwykRqVF32Ic7fhMrURFEm8cQjxeLx5P0sbix9SbfulbK+VoltrJFY3W2XHk7EHtxF/ayzO73gAt2iu+jZ3jEBuL42kbZDKLuLA/uClskKevP/Dj5nI7Wz/Hvl4yFe1hWT+fUJtOKdhT2dpNNpvUnbRaL6HaKHWRpZiPY9UjYs82nuaX2LsP4Z5s14SzNqlGoXPYf/uQx8yEXbaUeKX31QWkpP3z7xWGrID+6i1Ge83xHloft6DoH509FCqQlPOU6rNKqAa6a94771Uqf7n8ZdUxV7IK7pqkCSQarVarZnD+T1+rjdhQljg0DjM2wqfHsLeea66OZmZJfkdsffxX21TdmlhYe/BtNolserDi48sR1PsQYHKqH5xvNEsUVcjeQPNciNtRLwnHu8h0X6h6vbIENjen/WcIs613ylbMkNTdgbTbQifuuSBZMsPjVC3+mI1DnHPEdIYxnZOwThLLKey+j5KpY7iPnomVgf2KbunpURrskYplwQhrixEX9sgVk9e8f1MH+zpL/TXUcBnGfbbbvyJF1l/V/CPzxUokcr+aIf/ZYVSJbMEDuImrbOC+MI83jsuRz+IZj2zVwPdeE+NSyUfgif2FIjH/LqcS53xPIn/oBjxS6Y7mpV4kEVz/4/EPzC+ix4RSdBCld2OUSqwE+9L8PXt+ox+z4WWHoz/NB17oYHK2pWRLC2/q0ZJZ/T7XQJ76YJfNe6jBsJ6XxSDi21Ut1E08qFOD3oh9qN+iy6e14H+aJEl0DyK5FTZCb5LWI3+fOaOgFdP3iOhzHbwwD+eHT86q27NvCxiO9xZpZ+IJGyRwHAsqt10+kIo+iSH6mBn/OO/xeDdVeSDxA9JR1ZTpyc=
*/