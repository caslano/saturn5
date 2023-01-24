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
7o4yC+5JPEimG0cHcm+V3KN3KzPo3geZO0FydzmozLJbknuZ5G5E7kzJXYvcbADO6cjiZJa4k73vyIbls+TPBvzD5GYz+htfkNGblc8bdB+K5D52gPIlPb+cnmf+++h5xv9GeobldyW52WbA0fQ82wV442sXg/aYIfLl33EDmDFWUtuk6c9pCzNqLxrDjNr3xjCj9oVvmfGVbbXJHsiMr5K7yKfqEDK+spDbHcx8w0cYLBu0H/Rnk6YEdu6LVpGqjFGMwFLHxLzpe8aAT8G3WFAazpgITSjyeXcwX0ia3AG2X+k99TKwjbXVFKmdCdtLqk3Xy+JNma7bDJZN1937a74ckUJcR45WuJbUMnBdh7juSaXHlqE3DlB9POLiINXHI3a1B/tSBBrT9edfM9P171PZrRvS5XbY+sRy5LVPno0HYTZ+0Nl6HWBhs/G/i7j1etVUPeu1pCuasl5HDzEYnGB9u2YrlCVmeGS+7I7OzJWXggJst+Ulmft7bsq9OnGOs4WuyGdHuOqQ4tK2qvOgS/bJdgEsCGZGKXaB1COsIg4cwSHF2v1xSPFUOuwCvcP5IUV/m/o8aNt9eudBt8s2gp5kI1h3s6RYtzP1VvfizN7fX2lwceyKRT7vD5StDzv6so4k7Xnz701nzE687Gp9SDnMimEPA1E8+4TRR22LfPoMpOzbhBfaceuD+hB0APb0CROK/uGLhANfK4bB
*/