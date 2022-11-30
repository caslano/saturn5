/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   code_conversion.hpp
 * \author Andrey Semashev
 * \date   08.11.2008
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_CODE_CONVERSION_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_CODE_CONVERSION_HPP_INCLUDED_

#include <cstddef>
#include <locale>
#include <string>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_character_type.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// Implementation note: We have to implement char<->wchar_t conversions even in the absence of the native wchar_t
// type. These conversions are used in sinks, e.g. to convert multibyte strings to wide-character filesystem paths.

//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const wchar_t* str1, std::size_t len, std::string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char* str1, std::size_t len, std::wstring& str2, std::size_t max_size, std::locale const& loc = std::locale());

#if !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)
#if !defined(BOOST_NO_CXX11_CHAR16_T)
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char16_t* str1, std::size_t len, std::string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char* str1, std::size_t len, std::u16string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char16_t* str1, std::size_t len, std::wstring& str2, std::size_t max_size, std::locale const& loc = std::locale());
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char32_t* str1, std::size_t len, std::string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char* str1, std::size_t len, std::u32string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char32_t* str1, std::size_t len, std::wstring& str2, std::size_t max_size, std::locale const& loc = std::locale());
#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T) && !defined(BOOST_NO_CXX11_CHAR32_T)
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char16_t* str1, std::size_t len, std::u32string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char32_t* str1, std::size_t len, std::u16string& str2, std::size_t max_size, std::locale const& loc = std::locale());
#endif
#endif // !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)

//! The function converts one string to the character type of another
template< typename SourceCharT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) == sizeof(TargetCharT), bool >::type
code_convert(const SourceCharT* str1, std::size_t len, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::size_t max_size, std::locale const& = std::locale())
{
    std::size_t size_left = str2.size() < max_size ? max_size - str2.size() : static_cast< std::size_t >(0u);
    const bool overflow = len > size_left;
    str2.append(reinterpret_cast< const TargetCharT* >(str1), overflow ? size_left : len);
    return !overflow;
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename SourceTraitsT, typename SourceAllocatorT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) == sizeof(TargetCharT), bool >::type
code_convert(std::basic_string< SourceCharT, SourceTraitsT, SourceAllocatorT > const& str1, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::size_t max_size, std::locale const& loc = std::locale())
{
    return aux::code_convert(str1.data(), str1.size(), str2, max_size, loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename SourceTraitsT, typename SourceAllocatorT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) == sizeof(TargetCharT), bool >::type
code_convert(std::basic_string< SourceCharT, SourceTraitsT, SourceAllocatorT > const& str1, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::locale const& loc = std::locale())
{
    return aux::code_convert(str1.data(), str1.size(), str2, str2.max_size(), loc);
}
//! The function converts one string to the character type of another
template< typename SourceCharT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) == sizeof(TargetCharT), bool >::type
code_convert(const SourceCharT* str1, std::size_t len, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::locale const& loc = std::locale())
{
    return aux::code_convert(str1, len, str2, str2.max_size(), loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename SourceTraitsT, typename SourceAllocatorT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) != sizeof(TargetCharT), bool >::type
code_convert(std::basic_string< SourceCharT, SourceTraitsT, SourceAllocatorT > const& str1, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::locale const& loc = std::locale())
{
    return aux::code_convert_impl(str1.c_str(), str1.size(), str2, str2.max_size(), loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) != sizeof(TargetCharT), bool >::type
code_convert(const SourceCharT* str1, std::size_t len, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::locale const& loc = std::locale())
{
    return aux::code_convert_impl(str1, len, str2, str2.max_size(), loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename SourceTraitsT, typename SourceAllocatorT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) != sizeof(TargetCharT), bool >::type
code_convert(std::basic_string< SourceCharT, SourceTraitsT, SourceAllocatorT > const& str1, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::size_t max_size, std::locale const& loc = std::locale())
{
    return aux::code_convert_impl(str1.c_str(), str1.size(), str2, max_size, loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) != sizeof(TargetCharT), bool >::type
code_convert(const SourceCharT* str1, std::size_t len, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::size_t max_size, std::locale const& loc = std::locale())
{
    return aux::code_convert_impl(str1, len, str2, max_size, loc);
}

//! The function converts the passed string to the narrow-character encoding
inline std::string const& to_narrow(std::string const& str)
{
    return str;
}

//! The function converts the passed string to the narrow-character encoding
inline std::string const& to_narrow(std::string const& str, std::locale const&)
{
    return str;
}

//! The function converts the passed string to the narrow-character encoding
inline std::string to_narrow(std::wstring const& str, std::locale const& loc = std::locale())
{
    std::string res;
    aux::code_convert_impl(str.c_str(), str.size(), res, res.max_size(), loc);
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_HAS_NRVO)
    return static_cast< std::string&& >(res);
#else
    return res;
#endif
}

//! The function converts the passed string to the wide-character encoding
inline std::wstring const& to_wide(std::wstring const& str)
{
    return str;
}

//! The function converts the passed string to the wide-character encoding
inline std::wstring const& to_wide(std::wstring const& str, std::locale const&)
{
    return str;
}

//! The function converts the passed string to the wide-character encoding
inline std::wstring to_wide(std::string const& str, std::locale const& loc = std::locale())
{
    std::wstring res;
    aux::code_convert_impl(str.c_str(), str.size(), res, res.max_size(), loc);
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_HAS_NRVO)
    return static_cast< std::wstring&& >(res);
#else
    return res;
#endif
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_CODE_CONVERSION_HPP_INCLUDED_

/* code_conversion.hpp
JR4MWaKkktmZFDfeZvxZX5hvOdknuhonrqNoiOT5nToFKY8kRDa+r8RgFFsBzFS7So/KlPeUOtnIzsO2VkraO9wUwRMV0MaLYKehT15vqIBaTvDl/0W+ChZafUWzWoqd6A6lNSP2YUBnh0s3rLDoUh8tJkahWxZZPTtagrq6pV+WG8tdzNsOEhuF4UCV4rP+86WBHHbH1NuYDJ1fYnY4mYDQ9DmNenlZRzOCDKIZfjnBaB5cVXDd+oxNoJW6h7dKdONyc67kSzYBJmhgZDm7VncOHyOJQyM6M4jGKG4UGLfb7dbGflwpOy5R8+Cfal17fTL7GeBJEPEQ0lmllZ2VI0HJXTjoECMyVAKcu6urc4xDp3GZTmx0F7AMhNBpDHQKZbGXXoXqf+6YWVc0ff3PRCbFOzybww9wJKYNhLzGW1dZbgrJpNGHpLAAodwOECfy2I4d5L8dxHymLLs6G9J2LMm4aCesXEQrStCc7mOOuBO3lMGflE93T/IA2ZktWxdalxiZ+Z1SBADyPliUxCnYhULXlU8TO40cY7Wqp2818PqON/2UalxaI+nESC6BfmH2ur4P04owROBo/7VFYgEoslxkcPioHxPeFrYGJ5YvI+88d7SXeiTy05pqaSyG6nOPKjR73xuRgn/+uVjsh77Uaf6aFGM6OgBmMara306J64P+kLFNTJHcPqt3S/yyzg2e6L0yVwLx4E7T33vI/jD5tWCJyfxE2XtMwNfNdRfcoqcCVAPp6u29imwlLBWyU1/VKjwc2QJEOefbZnXDpMYSi1826XZb7JN5o92cCabPH76X5IfcUEBmcioAMrrNH/WoNCVgBVuEK8w9hvXMll+6+DAXtZr+7mNPpDgH1knoq7h7O4Y6AE87YWrsAmrVv1rZnLva556vpyS2eeO+uBa4h5hzvbP9VxgoPa5lwHVp/F2WCnh5exq2IKGmD4/C9fjyL7fOVh5u36f4Qs8c42kOsm/DTAc11eDOxbsfXQlxUO5Na9nyxlku5C6KETnOFeLwyK3ygmZTkvzEG0rnMyeHcGHV6xwaYrlHt8t6adHA4oA00MhIUvsQst+/v79AZIAAwH9A/oD+AfsD/gfiD+QfqD/Qf2D+wP6B+wP/B+EP4h+kP8h/UP6g/kH7g/4H4w/mH6w/2H9w/uD+wfuD/4fgD+Efoj/Ef0j+kP4h+0P+h+IP5R+qP9R/aP7Q/qH7Q/+H4Q/jH6Y/zH9Y/rD+YfvD/ofjD+cfrj/cf3j+8P7h+8P/R+CP4B+hP8J/RP6I/hH7I/5H4o/kH6k/0n9k/sj+kfsj/0fhj+IfpT/Kf1T+qP5R+6P+R+OP5h+tP9p/dP78+6P7R++P/h+DP4Z/jP4Y/zH5Y/rH7I/5H4s/ln+s/lj/sflj+8fuj/0fhz+Of5z+OP9x+eP6x+2P+x+PP55/vP54//H54/vH/8//Z4+lc4DpvR5HZVvUzDGCLhAhpsmYdwUWIlnSe9t8gekMs34ZoK1U7Wk3OEF9I2UssnHu6j/mhyF/ZAUkid4baL07VHbcIArM3DQOOJxc5RAWLmSgH/vQOgYk0LP+oTxnkHrFMTQOtRvMaGD/Gu5NSYx3cwaAv3npKgyN27pL/V/VCpROcEvwpyo1qjYzjQU+HKPA6TCYp7NW88TY6iKImg1usFxYQ9DcLhlmSlkjTWftRsM4tKhdJdzM6dTYju11qnAvswcnDrL4KRQIkD+hyWnJAwpT02s4dMyBnQAUEgsD101zze4FFhJdt/VUT5k0IKINWk3VebVFjqDyel3CS1nphuIMNlKML4kGD20TkpXRweGGWQjieKqeIs6IvYtqvN5aztfgVzSC1s1hW+MgTMNWG/PwBHxSyIrS5CGuMxyYEJ0Kd7wQXwCSzmI0tvHn5Su9P58xSatp/AfmajWeEtUAUL2vghw6Z8eMv83jv+GaWadhfj2aaoFi0ZlchyYGgsnnViXlq6hMZ9FPIX4iywki/kzoE6lmLXhlZpI7x70ndl2Gdrh1cM+jYBySMm/keWJfIM3pJW7VraUO6gKipo3gxgkfPwe/kuqyJ6DGuHVgHMGnEr6QvCS/YhWk15zaxUCnHAgH7+MVaXPyEvUY9fCRTvVmQk1y5OMm3Hvi67RRYzGoaDzXrBDh3/tSHbgL8yNrPVZqAjdeuchgzZaR3m15oWlLvncwKOlTApD1zciSNjfC43Fy+froOvh6+CbGGYXncwXNuQidWzdqEUgciLja0324itefK/OxXr3+daOihqks+5QfoyizlWX/xNQiq1nPKa12P6ez0i6g/55MAymrBDs4dBGinFW/0IylXl8XQRnxvzD5IcV+Qp5vAr/+A00Q8NRsI+bKfC4f5V/QXXZFNB6XU+RY0PK/1qk79Rksulq6GQm19gDpHNqBmjra8+JTnklQCXQbXcF8Tx771UGQerJZ+aSwp0gAiiAAXINEPBM3T2ZdyhNh/w0FeZLkfJayy61fnPu96uP7koe5LKvA0TdykhnoyGD7RA9RASjVLxmpGcNrjr8mTJM3PPVCUveX+FwO0HPKpr7wunEEINc5cuQDLyLWL54r08ZYcc7Bt8KaFCFd/tpaUyqAFFiDuxjLZy6UBaaNmupJRKvvtF8PVBYViwmYv1hDDpyTuFVVIIVVUZVyaNGQ3Dy4/imABPRcwMu8a7lIXyYo4TPecNvAoqwAoxfX15XNvNtpixOd26xzbK7FoVyt789NdAhA0B3TZXJi6kiAMSrFDFDWKSB8yxvc+TTSZ0YGz5lTcMqgRc5CnT7fHuA+Gd5XtMQi/3m/u79lF5cI+vD/1jFTVlhhRPiGSxtD3FyznFMoUJviI7Fox5oX3ijW9/K2gzynSZtab5NL/K8j9ZXEukZnL61x1WabYkn9+QYSV/lGzRU0fDBk+fW95GBxUvSc8cXArC44NFtATFvTkLeXJ7WM3q+FDR/XOVdnNE6a7n2fCEQJimNQuHT7QzNceFRtoMV8lv+baoIURrOjoimnDRdgF0qyJjJRSFqPudNFb4yFC88qu8sodN+mFBorb81Pp7qVIWMiA+m8CUMPAbl9hbAmXP8S50l+63dGIx1cR6nUs5NhGbHnWlgda3SX/tcaPyt83il6lStHwskCQOLBJCO4O3WP7QUMskDhZ6KePJcZ+AzdJx8HLk6qgdgVexY1JpXuYzOYKx03Jv5III/j00u3AdRoIjLuW4bZQz65DEzoRKrmI9Q6/Ukvs3XeXcuKrM0gujc7koeOBNqCoCkiNCRYCFlY/9346AW5FOs+Moe8DR58H0kk0axEbLUOdwxbJMVHZTlUQt42uJyxCYnKscc/0MQAo+fRqE/KaYCrHrSIekUuiDFnuc+CVHiGw0a8dNtBRWisqIM90jx6eZcmIxYmHm5hP8DQunDO5PmG5WllbsIDU9Cv2ftAw9lGqi15ccK1femA6D8g0pGt+im9aotvWKyH7IlGGfnljNTBmCuiveBqjlcIzm9pXLDN3Nc9oG30Y/M2QDK/MgLE8tDfart8qjTErh0zpW2NuHFLiwn1PLMkndgiadv8L2gx9gg0qXtBkiSOiqepO/jtWRms1q3ITZmYB1dZGSW2jmwAn9kCRRGfRq5Au/WFVOe0dhbcecm7X33e0xIYnr2Xs4tCPu4LQ4TbcJOTkqCV21pmHZcdjryG5SXfOadd3I93xxbQZ7cx3N39rKqOW5wz2tjOgxXvvYg1ppJaJ3GkTXHLay69Thq2FYCZbj3N0H5zkdIDl73sfabKy+GnrnljWFh6zem9jjp/oHB4wM93U464sD3f/s9v3Iwrs6NMhAB1lgzMX4h+WJJHnPJjfY2P7r3iYKIhVXqF+HWuovCs+49AoedVmMZ/7sXOiw/M5+lUNP9KHtxe3cizOzam80j5f8b0MgHFmhKqbbbo46rkqGCP8tGORmQiMwNUlnuDpVS8WkeXBuHh7KmK8gCjQWdhqaWwUWKOVRjAbHG0rYW8XL7Rcyf7mlAFExqjj9VKRGZQWNtWyZ5Tga7TiS4HbModNhT8amHWrO4ZJdh3OZ29pQrrc698peo3XoVX4w+5VR2L5DKL/IkLosQ74mr3IQPprJuF6uoaoqdk+qgTjpMBZnBWKB3Ggk5osqk8j3JwDi0XTq9L3B7jHog/7Q2tyzBMEZU66xknEaArUmE3ZSGdW5eFWICGno8Q01fxOY2Ulbd+eABFAp9uz2EilSUAwhXD123t6p4y3ZDH/CkCSrlRNJmwFpymfznnnbjhXm6otmePpCjzMAhjDExIQw8sWkebY7d6H5jzTmozomnAZjyC+8nyH6NVWnDp+IbSgTe5so9Q/GGGaLEUdMD5M/sbQ4dwQKIaJWUIKPkTqCboBiCtcNLJDZyC5qUeUpTEM3EOlCtToBBG2syh1iFY+zuH1RFks2rWhpoElDsZJuUrQOgy/8ND5aIXj95Lzpkjv4G7HClSifSudzaUpeT71hZD9SdkSkarxfPgoR3oKpkBngZ48MS6kdDyz/YP7VDhoMP4lZiCfB0KT3nefXZbZnIWA7Oqy2VaFwaI2edpk2I1juydLlQT16BwEeKTbLadR3o/4K1aEse8ZS9XQka1i7gPLzYRgo/Cmv5P3rQUQVEUHp10Y+JSc8lPSd9XdhaW/Cz4JnyaPGKzSLHKZcEYoya2+nsmKosG239zg8cLGvPtg5PEbsoCJOuyU6AKFxPQnC9wlFHUyKlYBzr38Ua2l89oqdoSjJ16ZTV6eBzuZb/uixeeWnyo8sNHuqyDuIFHZ3SjdEkYcDwZfAAKWEHLIL2erB5qsJxjc3qBjlSpPFwiFoMMQOjUTOXHrjyIgnkwz1GHWZ1d4q0R4WHK2lMH60HHJ5cOjLpYBs6PYiIXKFUaUeJTT8gUPEmwHf0NLufeAzU9caUXdro+nPo0KBqQbTe5Ot5s2gAWSGHUZ2kJTuumSHQXZibuE6VPAFgkOSjX/3xaboJydZTuKBJDEWaOTCCwMYWnR4iClqnJ+OuIGd03VtAyXn3Q8RWfYpny94j8QB2PHXuwkuDQUXO4Q6NUZOtR9ZDXMz0bZ9OTRYvzCTRnoN3QBcfGyXIlKplDoJSqLN2qc+dh7LMKzm1mur+WiqvTJGS+ABI9obCD2G8tquuDc2MGulFrSVkV9RR4b9mD5QFCMM4cBNvuCZp6WJPRyLqUdpvvknSzadPGe/mjAJBV/adJ6jncIXX51b4vlfVmFIMaqdMimNh3skb7C0lQ0/KBdDO7y7seyl0ydtwrXVqlETQJ/LCQOfo/TgkwRHgnUkMT/sCFojpHkfyAcOgKsVUyjfy9l24KTGBdrQEpx57co5z2wWpeOkHhD0HlLBJHB7P8wJSoDX8rT0lNJKAPHaTDORzyRSgNonkJHyCnDb7kUwEkvmXyePMO/FlGOyXRHHu/nAVyHLeFigG6oycXrEZ/iAqNLWkSy0Q4FHMj5ZMmBpPjqPYOQ6RkwTpvrJYe2+vmGzBAymzlkArT0HuQubqHEcVukwq9c3VS/EfNrVUnfgVbc/vf+AyGGD28E72i40tA194i8Ryb+GSecHnqqg+G2eZzVxM7Z2YZpbgrjwRephb/f/q/6piD/+qSGBCdjyoFqq8xY10WCyQpAL4Cz66gEtYcf3ruLWdJqPa3uI9Sg0kb7bjaEVCn4WsSOiBd4tx+j4Ur3gfqcK3fVo7wv3UOyxu3h7VkS0TNK4CSM1cx6EijuUpW4dB61SfEF/rBsfYe0N7bQuccXwHBIM3rnMQQw4OzYqspcTKELBpqxSa/0c3D6FYI83vWyzKVc5CtZq+Amux7H+sgOXAkGPL4+dN+UKOqKL9S/PlxFIep5MVlJHNYzvaXwQ5/Pj7ob58BLUi8wh1gcNT1gfcVbReczXGsEWafqMGVxi9u9e4JKlHccrQWaaJwvIRKrAGDpbpGmAxCcRS9HGtooaqCU6O+5TOQw1VrSWs4h//bZkpKmX6GAwIgSS8gXm249ZH6kDsHKjtaUucTC8WlP7EId7JHyiEADjQa4V/9i4IV7JGsQnz30PVcZpR3YFvlUBv8gJ21VhkMdcHO1W4FRWv3HB56beD9P2SG2AE9SpXdeXFY1Z5naBIj6nFtfGrRUwQL0oIkM2967Un/ySQiEkvOXRU+8qGElHMx9TMuQIqB2anj34bARIljnDmP/8dSR2wbZkEEr6Lfj6wGmv8i1uBR9m8dc2VzMn3YPMxmDj13FuG1JKgR+0nQpxXqySZn8Ln9v4VjlqOVPNuzTBTrDX8uK/W5q5av1IdL30MLl27szPrtWIL6Cd1IKlb4oQ4Es4bP+/rundG3FYVvIJBxzCIPjJqBqMkcrXEaqt4rvsyv6Ed47z1sbcuU0fZ4kv3EFDyzy/8YbKqDoissvJ+TzcbTFLADQqiq5B4/12MAL3vuAZZxpvOzpZoTUkZd1ekRVxsJhNU5LPT79ZbD4Z8KrtLxEdIlwt81WxJxB9jLlE7rxPhTyx0/US7xUobrVjI+vgHA3ZmyAhG5uJqyCEEVYIxz9I6i8whL8t/YGYblrTARK7XZfUDvzvt8kUtjagTsbA+5GF0d12OK2JJU665P//OHv3gaG9y7EcOro9e2IkeKslNAoX8a5sY0VuLRIzK0rJeTFQtxCF/dxpcZNI+vMOz9oPIrPAanXDC2z97oeQkcSfinl3DlMq7NgCsvDpWDBimW1NzBEWwnW6QQhdE0WH6lGARsdU7Z5Eg7Br+yk324a2anQLKgHYZ5oqIxzTDPtRxKs2eSf2TVUQCCMrbYL7eCcYa95ryyU5hKCCOJboyBSd0hTn7JI92rd5UeiYFPtwvfUYzpzInJFlFonbCWHaliDna0qEEqetZW6u+HQTpQU0LC2eewrejJaQjx/gLhCwYW+cWki3adbRLSzyHHvhzTdJzmVkFhBDz7ZNENp08uZWd545iXQdsK0yQwg903EU8nN75PXKLVrlUqaYTQkqSJP3Nybi3Eg7F605EChu1uV4RAhNUF1mYaKfS07Wh9iOcJbjX+jgWX6JSdQ92tQLVNjzJZz/yhJ2otPcN5DnbL4nSwB8ozpVA6Uz70Vi9T50QWtG7NbS2Gm0dXs9LAfg9Nz0nWRlQLwCEVglycqNXDwRdmQ0L7ZYdofPbLRKfs7OEiafQg6IEJ05nuau9WIyRMWEI9nNEUKsfBhwFz/kFycgZ/tvCpmOdzsK9cZVWWrSMrxaAwuBmPy2N3iKL1KMqhRX46Ad585IRFTFoX4IjqcTH+I7VtVAnA+YhSibpKrfI224ltLzGBvq39nPEi7NJHwBjcAH+fHrlTJaVK9dXy8a0RRTZSs1b0oyN4yvx+P9kRJpnJE8FG+nvYx+M4loMCQCxMUif4rPxpNMGs/llmMyYROdquZCk4SF5v/8l/e0PeEYQgdwtigr0t4DHy4af6o4ZtamkPxwneMj0vjnj0OE7ouaI8bKdRO0dUpkrKwBkFPm8OcwVXa70rHyPrUNgN3Nf5xv7lZjDUfeg8EUrdrKp1raI1lGc0P6HcSofI7McXU5wugUJEgESUbgXnM3L7wWnR6ggb4ZHTj7Ath3kKh67waAp9iMzQ8eszDXbQoj4WlWjDSGl89wy6TWEpz/HxzIaqU1ecS0fjwCtJqVOHmI8/1WZa
*/