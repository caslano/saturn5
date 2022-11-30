// Boost.Geometry

// Copyright (c) 2018-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_STR_CAST_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_STR_CAST_HPP

#include <cstdlib>
#include <string>
#include <type_traits>

#include <boost/config.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/throw_exception.hpp>

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
    bool IsIntegral = std::is_integral<T>::value,
    bool IsSigned = std::is_signed<T>::value
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
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
*/