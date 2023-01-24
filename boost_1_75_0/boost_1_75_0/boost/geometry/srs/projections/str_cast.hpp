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
p7TKB3QHsnXcS/QtQt1zL4yN1VvwUAT1W08DSAqcUpf4EDEzvu7eiR0QJMbaQAamH81tq9p9Gb3ZukFfNTlNx4bMwi5s9K84QhFp9tLnAH3CMVuJTxHvZo96pud8F8q3J2EM4GsJlohe8k6sHmJw4LD2GPfXDeePB1SkS2W75SAkVjT5xzovvJV78CKTWxDUjeZN1oJh/dkf3Ek//2yN8/ytwLAKop3ljYDxBor5oHnb9wh4p35cFYR8KQI19C0J20h5Rp4bh+XxBL4JxVx0aIGJ9IUg5Cho4YFNiU43NuDFrrlRvofFXtD+SRDHw/tJn4RwzX0XO/9WG9p73zQDiBzyj1w3i2RPMvT/5rr/94903r/32pZmUk72Fpau/33O5qyx6gOdTQ8n+5NJhAv9vn1cJ1hUDGuPnmxB6GBk93NTYz1sfLcMfsNVY9UVbDLirKb5gsUoUfxY+7dR/nNPhfUsncXvNKTKOd4k6IoLR7vNFallsnq6P0Tg5SnoZRUTfkN63YC1WmalcrbQaGvX3tcr3ufu3rG/cnYXPHF4SQDA/y0FDi/uXtyKO1sKheLuVtxdFocWh8JCcXcr7oXFteji7rbYIovrnuYul7vkkkteMsm89wXmzW8y9xP3nX5eQU83WdUAcOOBEVmilyrKWhR0+nuSSL5qyeuPOMfPymJUKppDQbkSaofmeeGemaXz3BjCNT4C71HTMMaQ
*/