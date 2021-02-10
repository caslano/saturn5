/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SUPPORT_UNUSED_20070305_1038)
#define BOOST_FUSION_SUPPORT_UNUSED_20070305_1038

#include <boost/fusion/support/config.hpp>
#include <iosfwd>

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4522) // multiple assignment operators specified warning
#endif

#define BOOST_FUSION_UNUSED_HAS_IO

namespace boost { namespace fusion
{
    struct unused_type
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_DEFAULTED_FUNCTION(
        unused_type() BOOST_FUSION_NOEXCEPT_ON_DEFAULTED,
        {
        })

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_DEFAULTED_FUNCTION(
        unused_type(unused_type const&) BOOST_FUSION_NOEXCEPT_ON_DEFAULTED,
        {
        })

        template <typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        unused_type(T const&) BOOST_NOEXCEPT
        {
        }

        BOOST_FUSION_CONSTEXPR_THIS BOOST_FUSION_GPU_ENABLED
        unused_type const&
        operator=(unused_type const&) const BOOST_NOEXCEPT
        {
            return *this;
        }
    };

    BOOST_CONSTEXPR_OR_CONST unused_type unused = unused_type();

    namespace detail
    {
        struct unused_only
        {
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_only(unused_type const&) BOOST_NOEXCEPT {}
        };
    }

    BOOST_CONSTEXPR
    inline std::ostream& operator<<(std::ostream& out, detail::unused_only const&) BOOST_NOEXCEPT
    {
        return out;
    }

    BOOST_CONSTEXPR
    inline std::istream& operator>>(std::istream& in, unused_type&) BOOST_NOEXCEPT
    {
        return in;
    }
}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#endif

/* unused.hpp
l2ynSrbdbsKXhDQ2c408GZJ+znq7JiF1wjKZDFYvj8jf1VC+nak4wtcK4jwIY7xFQZe7bPoyf0zpgtCzk60QaHlypEL1cwUbPP3+ezlpjm/Y6Lfwj/LOdpPdeIVrkm+AyYO1XU0abmK/YOb2EjNSta1mnZELTVuVOZ5QUndASVCp3s1UhreIVRpmt/xcTKC5PKzoShhfB5HjD2Yzm6SOiYhqEOBVtukg6WAuImw1BzpHR9CtyYwAqfMm1hMbf0oOqD7THaeItKw/ylpxhKttFg5g+UXhwas3j7HQUhijF9r2T0a85LsTU6aGNiHFi05FgF54093wKXc6XKeTqdIgh/29etquU0FfaL+hljdufJZIZKuyqqj7mvo590t4Uluk576ups5aUOypBy1Ycv0oaQKJFTOuWa6MQcr4XheuO8EQRCxr19ilId4txCXPHPH4ttMrpWGZiV28JDmuvuEJh6EdpEOsKf6xRlWcbYUYhO/HUbYbOPLAstR8Cm1bGk9ZFsJZpopLCgF4Q65j+sq+tjhO9XBvZVdZq0AJ3Vi3I4eWOjXez0oINaVyvA/f8VxxaQw/rrRGISsoKbKMCX42EZC6RABh6GtDvuL2V6WVC4tsEhNZOyqyTkTExkSwECKFPOgaSYSXw+5Usoi5
*/