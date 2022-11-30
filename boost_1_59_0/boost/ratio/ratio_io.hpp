//  ratio_io
//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o under lvm/libc++ to Boost

#ifndef BOOST_RATIO_RATIO_IO_HPP
#define BOOST_RATIO_RATIO_IO_HPP

/*

    ratio_io synopsis

#include <ratio>
#include <string>

namespace boost
{

template <class Ratio, class CharT>
struct ratio_string
{
    static basic_string<CharT> prefix();
    static basic_string<CharT> symbol();
};

}  // boost

*/
#include <boost/ratio/config.hpp>

#ifdef BOOST_RATIO_PROVIDES_DEPRECATED_FEATURES_SINCE_V2_0_0
#include <boost/ratio/detail/ratio_io.hpp>
#else

#include <boost/config.hpp>
#include <boost/ratio/ratio.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <string>
#include <sstream>


#if defined(BOOST_NO_CXX11_UNICODE_LITERALS) || defined(BOOST_NO_CXX11_CHAR16_T) || defined(BOOST_NO_CXX11_CHAR32_T) || defined(BOOST_NO_CXX11_U16STRING) || defined(BOOST_NO_CXX11_U32STRING)
#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT
#undef BOOST_RATIO_HAS_UNICODE_SUPPORT
#endif
#else
#define BOOST_RATIO_HAS_UNICODE_SUPPORT 1
#endif

namespace boost {

//template <class Ratio>
//struct ratio_string_is_localizable : false_type {};
//template <class Ratio>
//struct ratio_string_id : integral_constant<int,0> {};

template <class Ratio, class CharT>
struct ratio_string
{
    static std::basic_string<CharT> symbol() {return prefix();}
    static std::basic_string<CharT> prefix();
};

template <class Ratio, class CharT>
std::basic_string<CharT>
ratio_string<Ratio, CharT>::prefix()
{
    std::basic_ostringstream<CharT> os;
    os << CharT('[') << Ratio::num << CharT('/')
                        << Ratio::den << CharT(']');
    return os.str();
}

#ifdef BOOST_RATIO_HAS_STATIC_STRING
namespace ratio_detail {
template <class Ratio, class CharT>
struct ratio_string_static
{
    static std::string symbol() {
        return std::basic_string<CharT>(
                static_string::c_str<
                        typename ratio_static_string<Ratio, CharT>::symbol
                    >::value);
    }
    static std::string prefix()  {
        return std::basic_string<CharT>(
                static_string::c_str<
                    typename ratio_static_string<Ratio, CharT>::prefix
                >::value);
    }
};
}
#endif
// atto
//template <>
//struct ratio_string_is_localizable<atto> : true_type {};
//
//template <>
//struct ratio_string_id<atto> : integral_constant<int,-18> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<atto, CharT> :
    ratio_detail::ratio_string_static<atto,CharT>
{};

#else
template <>
struct ratio_string<atto, char>
{
    static std::string symbol() {return std::string(1, 'a');}
    static std::string prefix()  {return std::string("atto");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<atto, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'a');}
    static std::u16string prefix()  {return std::u16string(u"atto");}
};

template <>
struct ratio_string<atto, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'a');}
    static std::u32string prefix()  {return std::u32string(U"atto");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<atto, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'a');}
    static std::wstring prefix()  {return std::wstring(L"atto");}
};
#endif
#endif

// femto

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<femto, CharT> :
    ratio_detail::ratio_string_static<femto,CharT>
{};

#else

template <>
struct ratio_string<femto, char>
{
    static std::string symbol() {return std::string(1, 'f');}
    static std::string prefix()  {return std::string("femto");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<femto, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'f');}
    static std::u16string prefix()  {return std::u16string(u"femto");}
};

template <>
struct ratio_string<femto, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'f');}
    static std::u32string prefix()  {return std::u32string(U"femto");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<femto, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'f');}
    static std::wstring prefix()  {return std::wstring(L"femto");}
};
#endif
#endif

// pico

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<pico, CharT> :
    ratio_detail::ratio_string_static<pico,CharT>
{};

#else
template <>
struct ratio_string<pico, char>
{
    static std::string symbol() {return std::string(1, 'p');}
    static std::string prefix()  {return std::string("pico");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<pico, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'p');}
    static std::u16string prefix()  {return std::u16string(u"pico");}
};

template <>
struct ratio_string<pico, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'p');}
    static std::u32string prefix()  {return std::u32string(U"pico");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<pico, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'p');}
    static std::wstring prefix()  {return std::wstring(L"pico");}
};
#endif
#endif

// nano

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<nano, CharT> :
    ratio_detail::ratio_string_static<nano,CharT>
{};

#else
template <>
struct ratio_string<nano, char>
{
    static std::string symbol() {return std::string(1, 'n');}
    static std::string prefix()  {return std::string("nano");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<nano, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'n');}
    static std::u16string prefix()  {return std::u16string(u"nano");}
};

template <>
struct ratio_string<nano, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'n');}
    static std::u32string prefix()  {return std::u32string(U"nano");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<nano, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'n');}
    static std::wstring prefix()  {return std::wstring(L"nano");}
};
#endif
#endif

// micro

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<micro, CharT> :
    ratio_detail::ratio_string_static<micro,CharT>
{};

#else
template <>
struct ratio_string<micro, char>
{
    static std::string symbol() {return std::string("\xC2\xB5");}
    static std::string prefix()  {return std::string("micro");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<micro, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'\xB5');}
    static std::u16string prefix()  {return std::u16string(u"micro");}
};

template <>
struct ratio_string<micro, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'\xB5');}
    static std::u32string prefix()  {return std::u32string(U"micro");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<micro, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'\xB5');}
    static std::wstring prefix()  {return std::wstring(L"micro");}
};
#endif
#endif

// milli

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<milli, CharT> :
    ratio_detail::ratio_string_static<milli,CharT>
{};

#else
template <>
struct ratio_string<milli, char>
{
    static std::string symbol() {return std::string(1, 'm');}
    static std::string prefix()  {return std::string("milli");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<milli, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'm');}
    static std::u16string prefix()  {return std::u16string(u"milli");}
};

template <>
struct ratio_string<milli, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'm');}
    static std::u32string prefix()  {return std::u32string(U"milli");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<milli, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'm');}
    static std::wstring prefix()  {return std::wstring(L"milli");}
};
#endif
#endif

// centi

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<centi, CharT> :
    ratio_detail::ratio_string_static<centi,CharT>
{};

#else
template <>
struct ratio_string<centi, char>
{
    static std::string symbol() {return std::string(1, 'c');}
    static std::string prefix()  {return std::string("centi");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<centi, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'c');}
    static std::u16string prefix()  {return std::u16string(u"centi");}
};

template <>
struct ratio_string<centi, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'c');}
    static std::u32string prefix()  {return std::u32string(U"centi");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<centi, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'c');}
    static std::wstring prefix()  {return std::wstring(L"centi");}
};
#endif
#endif

// deci

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<deci, CharT> :
    ratio_detail::ratio_string_static<deci,CharT>
{};

#else

template <>
struct ratio_string<deci, char>
{
    static std::string symbol() {return std::string(1, 'd');}
    static std::string prefix()  {return std::string("deci");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<deci, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'd');}
    static std::u16string prefix()  {return std::u16string(u"deci");}
};

template <>
struct ratio_string<deci, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'd');}
    static std::u32string prefix()  {return std::u32string(U"deci");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<deci, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'd');}
    static std::wstring prefix()  {return std::wstring(L"deci");}
};
#endif
#endif

// unit

// deca


#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<deca, CharT> :
    ratio_detail::ratio_string_static<deca,CharT>
{};

#else
template <>
struct ratio_string<deca, char>
{
    static std::string symbol() {return std::string("da");}
    static std::string prefix()  {return std::string("deca");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<deca, char16_t>
{
    static std::u16string symbol() {return std::u16string(u"da");}
    static std::u16string prefix()  {return std::u16string(u"deca");}
};

template <>
struct ratio_string<deca, char32_t>
{
    static std::u32string symbol() {return std::u32string(U"da");}
    static std::u32string prefix()  {return std::u32string(U"deca");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<deca, wchar_t>
{
    static std::wstring symbol() {return std::wstring(L"da");}
    static std::wstring prefix()  {return std::wstring(L"deca");}
};
#endif
#endif

// hecto

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<hecto, CharT> :
    ratio_detail::ratio_string_static<hecto,CharT>
{};

#else
template <>
struct ratio_string<hecto, char>
{
    static std::string symbol() {return std::string(1, 'h');}
    static std::string prefix()  {return std::string("hecto");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<hecto, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'h');}
    static std::u16string prefix()  {return std::u16string(u"hecto");}
};

template <>
struct ratio_string<hecto, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'h');}
    static std::u32string prefix()  {return std::u32string(U"hecto");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<hecto, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'h');}
    static std::wstring prefix()  {return std::wstring(L"hecto");}
};
#endif
#endif

// kilo

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<kilo, CharT> :
    ratio_detail::ratio_string_static<kilo,CharT>
{};

#else
template <>
struct ratio_string<kilo, char>
{
    static std::string symbol() {return std::string(1, 'k');}
    static std::string prefix()  {return std::string("kilo");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<kilo, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'k');}
    static std::u16string prefix()  {return std::u16string(u"kilo");}
};

template <>
struct ratio_string<kilo, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'k');}
    static std::u32string prefix()  {return std::u32string(U"kilo");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<kilo, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'k');}
    static std::wstring prefix()  {return std::wstring(L"kilo");}
};
#endif
#endif

// mega

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<mega, CharT> :
    ratio_detail::ratio_string_static<mega,CharT>
{};

#else

template <>
struct ratio_string<mega, char>
{
    static std::string symbol() {return std::string(1, 'M');}
    static std::string prefix()  {return std::string("mega");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<mega, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'M');}
    static std::u16string prefix()  {return std::u16string(u"mega");}
};

template <>
struct ratio_string<mega, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'M');}
    static std::u32string prefix()  {return std::u32string(U"mega");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<mega, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'M');}
    static std::wstring prefix()  {return std::wstring(L"mega");}
};
#endif
#endif

// giga

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<giga, CharT> :
    ratio_detail::ratio_string_static<giga,CharT>
{};

#else

template <>
struct ratio_string<giga, char>
{
    static std::string symbol() {return std::string(1, 'G');}
    static std::string prefix()  {return std::string("giga");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<giga, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'G');}
    static std::u16string prefix()  {return std::u16string(u"giga");}
};

template <>
struct ratio_string<giga, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'G');}
    static std::u32string prefix()  {return std::u32string(U"giga");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<giga, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'G');}
    static std::wstring prefix()  {return std::wstring(L"giga");}
};
#endif
#endif

// tera

//template <>
#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<tera, CharT> :
    ratio_detail::ratio_string_static<tera,CharT>
{};

#else
template <>
struct ratio_string<tera, char>
{
    static std::string symbol() {return std::string(1, 'T');}
    static std::string prefix()  {return std::string("tera");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<tera, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'T');}
    static std::u16string prefix()  {return std::u16string(u"tera");}
};

template <>
struct ratio_string<tera, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'T');}
    static std::u32string prefix()  {return std::u32string(U"tera");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<tera, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'T');}
    static std::wstring prefix()  {return std::wstring(L"tera");}
};
#endif
#endif

// peta

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<peta, CharT> :
    ratio_detail::ratio_string_static<peta,CharT>
{};

#else
template <>
struct ratio_string<peta, char>
{
    static std::string symbol() {return std::string(1, 'P');}
    static std::string prefix()  {return std::string("peta");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<peta, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'P');}
    static std::u16string prefix()  {return std::u16string(u"peta");}
};

template <>
struct ratio_string<peta, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'P');}
    static std::u32string prefix()  {return std::u32string(U"peta");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<peta, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'P');}
    static std::wstring prefix()  {return std::wstring(L"peta");}
};
#endif
#endif

// exa

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<exa, CharT> :
    ratio_detail::ratio_string_static<exa,CharT>
{};

#else
template <>
struct ratio_string<exa, char>
{
    static std::string symbol() {return std::string(1, 'E');}
    static std::string prefix()  {return std::string("exa");}
};

#if defined BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<exa, char16_t>
{
    static std::u16string symbol() {return std::u16string(1, u'E');}
    static std::u16string prefix()  {return std::u16string(u"exa");}
};

template <>
struct ratio_string<exa, char32_t>
{
    static std::u32string symbol() {return std::u32string(1, U'E');}
    static std::u32string prefix()  {return std::u32string(U"exa");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<exa, wchar_t>
{
    static std::wstring symbol() {return std::wstring(1, L'E');}
    static std::wstring prefix()  {return std::wstring(L"exa");}
};
#endif
#endif


#ifdef BOOST_RATIO_EXTENSIONS

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<kibi, CharT> :
    ratio_detail::ratio_string_static<kibi,CharT>
{};

#else
template <>
struct ratio_string<kibi, char>
{
    static std::string symbol() {return std::string("Ki");}
    static std::string prefix()  {return std::string("kibi");}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<kibi, char16_t>
{
    static std::u16string symbol() {return std::u16string(u"Ki");}
    static std::u16string prefix()  {return std::u16string(u"kibi");}
};

template <>
struct ratio_string<kibi, char32_t>
{
    static std::u32string symbol() {return std::u32string(U"Ki");}
    static std::u32string prefix()  {return std::u32string(U"kibi");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<kibi, wchar_t>
{
    static std::wstring symbol() {return std::wstring(L"Ki");}
    static std::wstring prefix()  {return std::wstring(L"kibi");}
};
#endif
#endif

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<mebi, CharT> :
    ratio_detail::ratio_string_static<mebi,CharT>
{};

#else
template <>
struct ratio_string<mebi, char>
{
    static std::string symbol() {return std::string("Mi");}
    static std::string prefix()  {return std::string("mebi");}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<mebi, char16_t>
{
    static std::u16string symbol() {return std::u16string(u"Mi");}
    static std::u16string prefix()  {return std::u16string(u"mebi");}
};

template <>
struct ratio_string<mebi, char32_t>
{
    static std::u32string symbol() {return std::u32string(U"Mi");}
    static std::u32string prefix()  {return std::u32string(U"mebi");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<mebi, wchar_t>
{
    static std::wstring symbol() {return std::wstring(L"Mi");}
    static std::wstring prefix()  {return std::wstring(L"mebi");}
};
#endif
#endif

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<gibi, CharT> :
    ratio_detail::ratio_string_static<gibi,CharT>
{};

#else
template <>
struct ratio_string<gibi, char>
{
    static std::string symbol() {return std::string("Gi");}
    static std::string prefix()  {return std::string("gibi");}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<gibi, char16_t>
{
    static std::u16string symbol() {return std::u16string(u"Gi");}
    static std::u16string prefix()  {return std::u16string(u"gibi");}
};

template <>
struct ratio_string<gibi, char32_t>
{
    static std::u32string symbol() {return std::u32string(U"Gi");}
    static std::u32string prefix()  {return std::u32string(U"gibi");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<gibi, wchar_t>
{
    static std::wstring symbol() {return std::wstring(L"Gi");}
    static std::wstring prefix()  {return std::wstring(L"gibi");}
};
#endif
#endif

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<tebi, CharT> :
    ratio_detail::ratio_string_static<tebi,CharT>
{};

#else
template <>
struct ratio_string<tebi, char>
{
    static std::string symbol() {return std::string("Ti");}
    static std::string prefix()  {return std::string("tebi");}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<tebi, char16_t>
{
    static std::u16string symbol() {return std::u16string(u"Ti");}
    static std::u16string prefix()  {return std::u16string(u"tebi");}
};

template <>
struct ratio_string<tebi, char32_t>
{
    static std::u32string symbol() {return std::u32string(U"Ti");}
    static std::u32string prefix()  {return std::u32string(U"tebi");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<tebi, wchar_t>
{
    static std::wstring symbol() {return std::wstring(L"Ti");}
    static std::wstring prefix()  {return std::wstring(L"tebi");}
};
#endif
#endif

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<pebi, CharT> :
    ratio_detail::ratio_string_static<pebi,CharT>
{};

#else
template <>
struct ratio_string<pebi, char>
{
    static std::string symbol() {return std::string("Pi");}
    static std::string prefix()  {return std::string("pebi");}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<pebi, char16_t>
{
    static std::u16string symbol() {return std::u16string(u"Pi");}
    static std::u16string prefix()  {return std::u16string(u"pebi");}
};

template <>
struct ratio_string<pebi, char32_t>
{
    static std::u32string symbol() {return std::u32string(U"Pi");}
    static std::u32string prefix()  {return std::u32string(U"pebi");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<pebi, wchar_t>
{
    static std::wstring symbol() {return std::wstring(L"Pi");}
    static std::wstring prefix()  {return std::wstring(L"pebi");}
};
#endif
#endif

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<exbi, CharT> :
    ratio_detail::ratio_string_static<exbi,CharT>
{};

#else
template <>
struct ratio_string<exbi, char>
{
    static std::string symbol() {return std::string("Ei");}
    static std::string prefix()  {return std::string("exbi");}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<exbi, char16_t>
{
    static std::u16string symbol() {return std::u16string(u"Ei");}
    static std::u16string prefix()  {return std::u16string(u"exbi");}
};

template <>
struct ratio_string<exbi, char32_t>
{
    static std::u32string symbol() {return std::u32string(U"Ei");}
    static std::u32string prefix()  {return std::u32string(U"exbi");}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<exbi, wchar_t>
{
    static std::wstring symbol() {return std::wstring(L"Ei");}
    static std::wstring prefix()  {return std::wstring(L"exbi");}
};
#endif
#endif
#endif

}

#endif  // BOOST_RATIO_PROVIDES_DEPRECATED_FEATURES_SINCE_V2_0_0
#endif  // BOOST_RATIO_RATIO_IO_HPP

/* ratio_io.hpp
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
*/