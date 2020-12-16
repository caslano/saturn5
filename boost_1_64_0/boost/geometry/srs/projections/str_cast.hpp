// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_STR_CAST_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_STR_CAST_HPP

#include <boost/config.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>

#include <cstdlib>
#include <string>

namespace boost { namespace geometry
{

class bad_str_cast : public geometry::exception
{
    virtual char const* what() const throw()
    {
        return "Unable to convert from string.";
    }
};

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename T,
    bool IsIntegral = boost::is_integral<T>::value,
    bool IsSigned = boost::is_signed<T>::value
>
struct str_cast_traits_strtox
{
    static inline T apply(const char *str, char **str_end)
    {
        return strtod(str, str_end);
    }
};

template <typename T>
struct str_cast_traits_strtox<T, true, true>
{
    static inline T apply(const char *str, char **str_end)
    {
        return strtol(str, str_end, 0);
    }
};

template <typename T>
struct str_cast_traits_strtox<T, true, false>
{
    static inline T apply(const char *str, char **str_end)
    {
        return strtoul(str, str_end, 0);
    }
};

template <typename T>
struct str_cast_traits_strtox<T, false, false>
{
    static inline T apply(const char *str, char **str_end)
    {
        return strtod(str, str_end);
    }
};

// Assuming a compiler supporting r-value references
// supports long long and strtoll, strtoull, strtof, strtold
// If it's MSVC enable in MSVC++ 12.0 aka Visual Studio 2013
// TODO: in MSVC-11.0 _strtoi64() intrinsic could be used
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && (!defined(_MSC_VER) || (_MSC_VER >= 1800))
template <>
struct str_cast_traits_strtox<long long, true, true>
{
    static inline long long apply(const char *str, char **str_end)
    {
        return strtoll(str, str_end, 0);
    }
};

template <>
struct str_cast_traits_strtox<unsigned long long, true, false>
{
    static inline unsigned long long apply(const char *str, char **str_end)
    {
        return strtoull(str, str_end, 0);
    }
};

template <>
struct str_cast_traits_strtox<float, false, false>
{
    static inline float apply(const char *str, char **str_end)
    {
        return strtof(str, str_end);
    }
};

template <>
struct str_cast_traits_strtox<long double, false, false>
{
    static inline long double apply(const char *str, char **str_end)
    {
        return strtold(str, str_end);
    }
};
#endif // C++11 strtox supported

template <typename T>
struct str_cast_traits_generic
{
    static inline T apply(const char *str)
    {
        char * str_end = (char*)(void*)str;
        T res = str_cast_traits_strtox
                    <
                        typename boost::remove_cv<T>::type
                    >::apply(str, &str_end);
        if (str_end == str)
        {
            BOOST_THROW_EXCEPTION( bad_str_cast() );
        }
        return res;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename T>
struct str_cast_traits
{
    template <typename String>
    static inline T apply(String const& str)
    {
        return detail::str_cast_traits_generic<T>::apply(str.c_str());
    }
};

template <typename T, typename String>
inline T str_cast(String const& str)
{
    return str_cast_traits<T>::apply(str);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_STR_CAST_HPP

/* str_cast.hpp
2+dDSocPG+XqjDH8I6rcR1W5gDkUGah25RyCgbi8H5d8gnwP2688eS2DUHt9ku3tnx/ID2fmxt6CIGxv8Wlmt88ofvuUr33CtRf2oiUxuFTOhz7lrteFYOjSk3I/e8LdS6NnxyvnRp8FrJWtM3eqs6PP8flVtb2g1DVR2xsImsMiUj6Z4iqnAvF8eaxypiygeo15mZCXw+MH88UpKWMfcE1yntFzCtHENJxIJG4XcCstjL+chs4OsAEWielsTbOG8ZHjnCyh8W2CRg/nbB14AfYYcXeLKfcFvJ52q+zI9UzR9ctlsOsXmF3vY+X1q3E2dUQG4ms7+Dv5wEmjT3xJ9Z11qk98WfWJr9B5jWyLhpjA0zoWcGFzuS8bVnGkrzH5YpZ40SiO/G6Vjy9u8cIojbw+aC139TMn8Yk0fuhEz9R/vqHPiYLHZEFISxc+Ops4PU5/M3Af7SXR0hlQkvHbitdzlW1vxDN4QA9p22+5/lwCmWOxeBQcRT7f5Pa7LFgnaF/aZmVFAVqrwH+w4Z4iH7yPlU0VSpP0vN4q0LNoy83q/FfYfQna8jusLbe6+31oQ43Hnjs7yZc+YcyT31O+dIrOqP3GRR33H+oa7rqUhkcTwcfaH7C54QdsjPuR4d8/VjL9UM0NP1Ey/ZSd4xbU+hfTw2n+XMCzHiubpf9gHZPIpjOHXLv9LAZDWfE4oIVEaoMLO0f0CwkT78PReu3nog2p7EZruxorf8HsfNgS30wUH0KDpnks+uz4TEHaeza8s7P6GVGNPO5ViX93dyF40zfQ3b93R4+Ofbuwnv0SdjFiOlEV0/l1DBR7+0f63BKXDu5AQOmhQzowPRvR2Slt+yu1NzkM216hbCvHnolx+f2Z8URSjTEoC1sCPlHMlwsS9hvAjgjYON7XYWPRlQKGVQhesXDb4RaUOypgjtzr65jsaT5GRVzGGLIzqNc1EgcExBng//LknPo6g9Dc+zvml783/PLufN0F+B+VX/4paC0ScsyvPnZiFQ8JiU4/sj71l+D1LDabsiLNgkFobPublj8gHuthwkBcltuMeEGJXV+SPgQbmms6lGyWdow0B8QufMezoDiUeS5c0bm+mcWQVGyjDXKVPbGMOmuRkm1xM80lgTFPPtMZUKp7STNb0yv7LG32rumXqXqbTDkp/sJtiLwyVf4OqvxalF+k7N2AqyB0s5SOiha/3RG0WdG2KNrVoK0n2mo09dZKRbNK0Yj7J4Y7B3fniIGuS3v0FG6AyZ9aTV2Y7u3uveFL0OU8JdedmoPmL+wBCvlMOnkoLlJleJtVwdDYcOfmytiwtjnUPnJP94jWkgC0xmtj/O5itPP5eF6Hq87wx7sq/S5gdm8L1JWqHuzeM4Tkpj1DfTtIJhNBtr9Hc6g1mdtoSIPrGRCZa5ytiVO+f0/Fd8Av9kqHpDikxXkOdsfUg32w1K/uPct/yU8MO9Zb91V27GB2vCpm+pukK+E6ivv1ZnvA3zYoPhsVn8utYH8YHhlyUwZ7ukdgFHG7s6+fekJgIWqbzaqu4Wp1LXANL/hvCR6HiwXeYehR0usxTfdVPqZdpGy1rTlovgl3VqTbGOMajQlmGz9I1XdxYF9NOIewnb0iP6YrIwC3Sace/wN4HEykS9w0BpT8dLvi9c6lPD7njc39QcbfxOqEzlkXy/0vTrstem61DnqecTYuntmetHiQ77tvFX5ssXPKci7J97BbVW4chz3Qwgv+uuexPXSn9chyGp3QmSyX8DJ9jtPssAjqwv6MenstuebR5f4K2Az22bAPnfeKNjwsYUjaquhxRMKwWqzArpQwytn6u7t+dDZp/v/A89VWaoN+jsLu17i5YHj3OzM=
*/