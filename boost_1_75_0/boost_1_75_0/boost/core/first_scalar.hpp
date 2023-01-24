/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_FIRST_SCALAR_HPP
#define BOOST_CORE_FIRST_SCALAR_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace detail {

template<class T>
struct make_scalar {
    typedef T type;
};

template<class T, std::size_t N>
struct make_scalar<T[N]> {
    typedef typename make_scalar<T>::type type;
};

} /* detail */

template<class T>
BOOST_CONSTEXPR inline T*
first_scalar(T* p) BOOST_NOEXCEPT
{
    return p;
}

template<class T, std::size_t N>
BOOST_CONSTEXPR inline typename detail::make_scalar<T>::type*
first_scalar(T (*p)[N]) BOOST_NOEXCEPT
{
    return boost::first_scalar(&(*p)[0]);
}

} /* boost */

#endif

/* first_scalar.hpp
1vc5XriCCestnsT7Aw4uU5doFaYKAyerDwnWh7sxHofnJJ44n5+vE86XOZUxnIgJxOFZz3bk2FIunQWH9YLnpDuTP+Ks6yXKaFSVF2qmW+om1hXn3T49gt1EwGJXYTqtDeZf9g/EpRrUYLApwHfh0u1k9kaeQiOqRKZL3LD82wuUVZaCIHyOJ7Zr3suYl8Aowhud0R4sdWX9tEnlIP6IB9rqrlUiPKtULOMlD5z3GzPDuowgVVzxWP5bWfm0g8RZGyBvQXaciLNfuqrYoDJyeXL9+JOlIGfgRYAByNulGjfkQ7PXDORHWExzwxHnJftkZxpVsulG6IkiqUb8Sneck+wcbs0noi3tsNYD7an3+sRzJpoc10LDnNFGG7KLjaGGEpUpDayJYp2hnJuOYHG4ceBBFI6jelP2oIE8HCdu3SQ/5nPwqOTYoYMZPBLlU/JxXw6eGAVgc7nbk3+XMX0ipiWSd28yc7fJBiOoR84wPTe9k6APLDrk4DecDhEwcjmu55qgzrylIXcQI8hdNNQP2h+IP8Hk6LWlCBN8Vswv1wHlbkVfptYrNBqsRSZf7dD3rv1Yr6/QTk1MVpkUsQqTwizv5XqdwcTkE8d98lNX8BPKzYTlHE3EdyL/GBsDprxJFasqVlRoTOJOYVUXmxI5WtYRWNna4/z1w0k4mSBg+aKb03uQn0sTxRFEPPiQd4+hrFh6K5cacXgu2oec
*/