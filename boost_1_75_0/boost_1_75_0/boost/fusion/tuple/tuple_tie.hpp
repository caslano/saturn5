/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_TIE_14122014_0115
#define FUSION_TUPLE_TIE_14122014_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<T&...>
    tie(T&... arg)
    {
        return tuple<T&...>(arg...);
    }
}}

#endif
#endif


/* tuple_tie.hpp
ibJgdCrib1V7NTGKKC6cq8/r8l+uxVe+5uu/GJ3ku9V7SUiZvEYz4VF/2BTjUakT34t3dxJAX1o8+5IXr3tRgIl5kfMjiddrolBENqL+ZAObmxb7pkPh1a4hWXt3rq84jznWK73i5CSmFNoQXYOMVw20bmWMDvMmz9rN1VObxLYFLsRzjHRJyT2UCcLtfFVxGvuSk5dozYD7vP6hc1/LhNlTTbXRY7m6O1Kh+3bFcOEbnQipMoP3YVXvY+rs99jRM02DI8DjXW3Up7Cp5DUFNjvw+at2Et6S8qzqr26Aor/9WbqZM8Km/XAUGeau3aFWd1I+n9vKFSJYip0PaB3l25x8SpJ9jyKC1umKUPEgjFL1BTiUUXfTEP7B6njF5qTlFnjZ+pOMtvPZZ6vwFlbhwp4/F/ifNX5J2zyz7Uij6qMxUOv3eGvu2/+KjMr1L/9SuvKFaH3ZgjAbjrQrUFa3ma2RsxN41+xZUkp8WMe3OKnmjD1NeY6r6zaU8y93hvsoS8PdDBuG9r9QLSr7KSHu2Bc6jRLJn/H7IDl0BPhZu/2zhWx7MTb0tILyza1Kazmsmo5aOAzmRMQFztwO2AvfOS/yl/DCOvPd8ov4w/m12Z2si2vM7mi4BCdVvq+s/JcBTXI9uzpwZbhHxYfwrglAx8zwQWtnbg2q1DRblQGO+ewO+/27qaKqC9eN/0MSrFwZgmua1kkdlxJfPCzI
*/