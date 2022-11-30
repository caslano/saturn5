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

#ifndef BOOST_RATIO_DETAIL_RATIO_IO_HPP
#define BOOST_RATIO_DETAIL_RATIO_IO_HPP

/*

    ratio_io synopsis

#include <ratio>
#include <string>

namespace boost
{

template <class Ratio, class CharT>
struct ratio_string
{
    static basic_string<CharT> short_name();
    static basic_string<CharT> long_name();
};

}  // boost

*/

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
    static std::basic_string<CharT> short_name() {return long_name();}
    static std::basic_string<CharT> long_name();
    static std::basic_string<CharT> symbol() {return short_name();}
    static std::basic_string<CharT> prefix() {return long_name();}
};

template <class Ratio, class CharT>
std::basic_string<CharT>
ratio_string<Ratio, CharT>::long_name()
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
    static std::string short_name() {
        return std::basic_string<CharT>(
                static_string::c_str<
                        typename ratio_static_string<Ratio, CharT>::short_name
                    >::value);
    }
    static std::string long_name()  {
        return std::basic_string<CharT>(
                static_string::c_str<
                    typename ratio_static_string<Ratio, CharT>::long_name
                >::value);
    }
    static std::basic_string<CharT> symbol() {return short_name();}
    static std::basic_string<CharT> prefix() {return long_name();}
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
    static std::string short_name() {return std::string(1, 'a');}
    static std::string long_name()  {return std::string("atto");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<atto, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'a');}
    static std::u16string long_name()  {return std::u16string(u"atto");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<atto, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'a');}
    static std::u32string long_name()  {return std::u32string(U"atto");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<atto, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'a');}
    static std::wstring long_name()  {return std::wstring(L"atto");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// femto

//template <>
//struct ratio_string_is_localizable<femto> : true_type {};
//
//template <>
//struct ratio_string_id<femto> : integral_constant<int,-15> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<femto, CharT> :
    ratio_detail::ratio_string_static<femto,CharT>
{};

#else

template <>
struct ratio_string<femto, char>
{
    static std::string short_name() {return std::string(1, 'f');}
    static std::string long_name()  {return std::string("femto");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<femto, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'f');}
    static std::u16string long_name()  {return std::u16string(u"femto");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<femto, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'f');}
    static std::u32string long_name()  {return std::u32string(U"femto");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<femto, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'f');}
    static std::wstring long_name()  {return std::wstring(L"femto");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// pico

//template <>
//struct ratio_string_is_localizable<pico> : true_type {};
//
//template <>
//struct ratio_string_id<pico> : integral_constant<int,-12> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<pico, CharT> :
    ratio_detail::ratio_string_static<pico,CharT>
{};

#else
template <>
struct ratio_string<pico, char>
{
    static std::string short_name() {return std::string(1, 'p');}
    static std::string long_name()  {return std::string("pico");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<pico, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'p');}
    static std::u16string long_name()  {return std::u16string(u"pico");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<pico, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'p');}
    static std::u32string long_name()  {return std::u32string(U"pico");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<pico, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'p');}
    static std::wstring long_name()  {return std::wstring(L"pico");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// nano

//template <>
//struct ratio_string_is_localizable<nano> : true_type {};
//
//template <>
//struct ratio_string_id<nano> : integral_constant<int,-9> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<nano, CharT> :
    ratio_detail::ratio_string_static<nano,CharT>
{};

#else
template <>
struct ratio_string<nano, char>
{
    static std::string short_name() {return std::string(1, 'n');}
    static std::string long_name()  {return std::string("nano");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<nano, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'n');}
    static std::u16string long_name()  {return std::u16string(u"nano");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<nano, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'n');}
    static std::u32string long_name()  {return std::u32string(U"nano");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<nano, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'n');}
    static std::wstring long_name()  {return std::wstring(L"nano");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// micro

//template <>
//struct ratio_string_is_localizable<micro> : true_type {};
//
//template <>
//struct ratio_string_id<micro> : integral_constant<int,-6> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<micro, CharT> :
    ratio_detail::ratio_string_static<micro,CharT>
{};

#else
template <>
struct ratio_string<micro, char>
{
    static std::string short_name() {return std::string("\xC2\xB5");}
    static std::string long_name()  {return std::string("micro");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<micro, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'\xB5');}
    static std::u16string long_name()  {return std::u16string(u"micro");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<micro, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'\xB5');}
    static std::u32string long_name()  {return std::u32string(U"micro");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<micro, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'\xB5');}
    static std::wstring long_name()  {return std::wstring(L"micro");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// milli

//template <>
//struct ratio_string_is_localizable<milli> : true_type {};
//
//template <>
//struct ratio_string_id<milli> : integral_constant<int,-3> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<milli, CharT> :
    ratio_detail::ratio_string_static<milli,CharT>
{};

#else
template <>
struct ratio_string<milli, char>
{
    static std::string short_name() {return std::string(1, 'm');}
    static std::string long_name()  {return std::string("milli");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<milli, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'm');}
    static std::u16string long_name()  {return std::u16string(u"milli");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<milli, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'm');}
    static std::u32string long_name()  {return std::u32string(U"milli");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<milli, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'm');}
    static std::wstring long_name()  {return std::wstring(L"milli");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// centi

//template <>
//struct ratio_string_is_localizable<centi> : true_type {};
//
//template <>
//struct ratio_string_id<centi> : integral_constant<int,-2> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<centi, CharT> :
    ratio_detail::ratio_string_static<centi,CharT>
{};

#else
template <>
struct ratio_string<centi, char>
{
    static std::string short_name() {return std::string(1, 'c');}
    static std::string long_name()  {return std::string("centi");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<centi, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'c');}
    static std::u16string long_name()  {return std::u16string(u"centi");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<centi, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'c');}
    static std::u32string long_name()  {return std::u32string(U"centi");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<centi, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'c');}
    static std::wstring long_name()  {return std::wstring(L"centi");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// deci

//template <>
//struct ratio_string_is_localizable<deci> : true_type {};
//
//template <>
//struct ratio_string_id<deci> : integral_constant<int,-1> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<deci, CharT> :
    ratio_detail::ratio_string_static<deci,CharT>
{};

#else

template <>
struct ratio_string<deci, char>
{
    static std::string short_name() {return std::string(1, 'd');}
    static std::string long_name()  {return std::string("deci");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<deci, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'd');}
    static std::u16string long_name()  {return std::u16string(u"deci");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<deci, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'd');}
    static std::u32string long_name()  {return std::u32string(U"deci");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<deci, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'd');}
    static std::wstring long_name()  {return std::wstring(L"deci");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// unit

//template <>
//struct ratio_string_is_localizable<ratio<1> > : true_type {};
//
//template <>
//struct ratio_string_id<ratio<1> > : integral_constant<int,0> {};
// deca

//template <>
//struct ratio_string_is_localizable<deca> : true_type {};
//
//template <>
//struct ratio_string_id<deca> : integral_constant<int,1> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<deca, CharT> :
    ratio_detail::ratio_string_static<deca,CharT>
{};

#else
template <>
struct ratio_string<deca, char>
{
    static std::string short_name() {return std::string("da");}
    static std::string long_name()  {return std::string("deca");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<deca, char16_t>
{
    static std::u16string short_name() {return std::u16string(u"da");}
    static std::u16string long_name()  {return std::u16string(u"deca");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<deca, char32_t>
{
    static std::u32string short_name() {return std::u32string(U"da");}
    static std::u32string long_name()  {return std::u32string(U"deca");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<deca, wchar_t>
{
    static std::wstring short_name() {return std::wstring(L"da");}
    static std::wstring long_name()  {return std::wstring(L"deca");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// hecto

//template <>
//struct ratio_string_is_localizable<hecto> : true_type {};
//
//template <>
//struct ratio_string_id<hecto> : integral_constant<int,2> {};


#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<hecto, CharT> :
    ratio_detail::ratio_string_static<hecto,CharT>
{};

#else
template <>
struct ratio_string<hecto, char>
{
    static std::string short_name() {return std::string(1, 'h');}
    static std::string long_name()  {return std::string("hecto");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<hecto, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'h');}
    static std::u16string long_name()  {return std::u16string(u"hecto");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<hecto, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'h');}
    static std::u32string long_name()  {return std::u32string(U"hecto");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<hecto, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'h');}
    static std::wstring long_name()  {return std::wstring(L"hecto");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// kilo

//template <>
//struct ratio_string_is_localizable<kilo> : true_type {};
//
//template <>
//struct ratio_string_id<kilo> : integral_constant<int,3> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<kilo, CharT> :
    ratio_detail::ratio_string_static<kilo,CharT>
{};

#else
template <>
struct ratio_string<kilo, char>
{
    static std::string short_name() {return std::string(1, 'k');}
    static std::string long_name()  {return std::string("kilo");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<kilo, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'k');}
    static std::u16string long_name()  {return std::u16string(u"kilo");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<kilo, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'k');}
    static std::u32string long_name()  {return std::u32string(U"kilo");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<kilo, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'k');}
    static std::wstring long_name()  {return std::wstring(L"kilo");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// mega

//template <>
//struct ratio_string_is_localizable<mega> : true_type {};
//
//template <>
//struct ratio_string_id<mega> : integral_constant<int,6> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<mega, CharT> :
    ratio_detail::ratio_string_static<mega,CharT>
{};

#else

template <>
struct ratio_string<mega, char>
{
    static std::string short_name() {return std::string(1, 'M');}
    static std::string long_name()  {return std::string("mega");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<mega, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'M');}
    static std::u16string long_name()  {return std::u16string(u"mega");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<mega, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'M');}
    static std::u32string long_name()  {return std::u32string(U"mega");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<mega, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'M');}
    static std::wstring long_name()  {return std::wstring(L"mega");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// giga

//template <>
//struct ratio_string_is_localizable<giga> : true_type {};
//
//template <>
//struct ratio_string_id<giga> : integral_constant<int,9> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<giga, CharT> :
    ratio_detail::ratio_string_static<giga,CharT>
{};

#else

template <>
struct ratio_string<giga, char>
{
    static std::string short_name() {return std::string(1, 'G');}
    static std::string long_name()  {return std::string("giga");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<giga, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'G');}
    static std::u16string long_name()  {return std::u16string(u"giga");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<giga, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'G');}
    static std::u32string long_name()  {return std::u32string(U"giga");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<giga, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'G');}
    static std::wstring long_name()  {return std::wstring(L"giga");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// tera

//template <>
//struct ratio_string_is_localizable<tera> : true_type {};
//
//template <>
//struct ratio_string_id<tera> : integral_constant<int,12> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<tera, CharT> :
    ratio_detail::ratio_string_static<tera,CharT>
{};

#else
template <>
struct ratio_string<tera, char>
{
    static std::string short_name() {return std::string(1, 'T');}
    static std::string long_name()  {return std::string("tera");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<tera, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'T');}
    static std::u16string long_name()  {return std::u16string(u"tera");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<tera, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'T');}
    static std::u32string long_name()  {return std::u32string(U"tera");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<tera, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'T');}
    static std::wstring long_name()  {return std::wstring(L"tera");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// peta

//template <>
//struct ratio_string_is_localizable<peta> : true_type {};
//
//template <>
//struct ratio_string_id<peta> : integral_constant<int,15> {};


#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<peta, CharT> :
    ratio_detail::ratio_string_static<peta,CharT>
{};

#else
template <>
struct ratio_string<peta, char>
{
    static std::string short_name() {return std::string(1, 'P');}
    static std::string long_name()  {return std::string("peta");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<peta, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'P');}
    static std::u16string long_name()  {return std::u16string(u"peta");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<peta, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'P');}
    static std::u32string long_name()  {return std::u32string(U"peta");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<peta, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'P');}
    static std::wstring long_name()  {return std::wstring(L"peta");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif

// exa

//template <>
//struct ratio_string_is_localizable<exa> : true_type {};
//
//template <>
//struct ratio_string_id<exa> : integral_constant<int,18> {};

#ifdef BOOST_RATIO_HAS_STATIC_STRING
template <typename CharT>
struct ratio_string<exa, CharT> :
    ratio_detail::ratio_string_static<exa,CharT>
{};

#else
template <>
struct ratio_string<exa, char>
{
    static std::string short_name() {return std::string(1, 'E');}
    static std::string long_name()  {return std::string("exa");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<exa, char16_t>
{
    static std::u16string short_name() {return std::u16string(1, u'E');}
    static std::u16string long_name()  {return std::u16string(u"exa");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<exa, char32_t>
{
    static std::u32string short_name() {return std::u32string(1, U'E');}
    static std::u32string long_name()  {return std::u32string(U"exa");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<exa, wchar_t>
{
    static std::wstring short_name() {return std::wstring(1, L'E');}
    static std::wstring long_name()  {return std::wstring(L"exa");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
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
    static std::string short_name() {return std::string("Ki");}
    static std::string long_name()  {return std::string("kibi");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<kibi, char16_t>
{
    static std::u16string short_name() {return std::u16string(u"Ki");}
    static std::u16string long_name()  {return std::u16string(u"kibi");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<kibi, char32_t>
{
    static std::u32string short_name() {return std::u32string(U"Ki");}
    static std::u32string long_name()  {return std::u32string(U"kibi");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<kibi, wchar_t>
{
    static std::wstring short_name() {return std::wstring(L"Ki");}
    static std::wstring long_name()  {return std::wstring(L"kibi");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
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
    static std::string short_name() {return std::string("Mi");}
    static std::string long_name()  {return std::string("mebi");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<mebi, char16_t>
{
    static std::u16string short_name() {return std::u16string(u"Mi");}
    static std::u16string long_name()  {return std::u16string(u"mebi");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<mebi, char32_t>
{
    static std::u32string short_name() {return std::u32string(U"Mi");}
    static std::u32string long_name()  {return std::u32string(U"mebi");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<mebi, wchar_t>
{
    static std::wstring short_name() {return std::wstring(L"Mi");}
    static std::wstring long_name()  {return std::wstring(L"mebi");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
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
    static std::string short_name() {return std::string("Gi");}
    static std::string long_name()  {return std::string("gibi");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<gibi, char16_t>
{
    static std::u16string short_name() {return std::u16string(u"Gi");}
    static std::u16string long_name()  {return std::u16string(u"gibi");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<gibi, char32_t>
{
    static std::u32string short_name() {return std::u32string(U"Gi");}
    static std::u32string long_name()  {return std::u32string(U"gibi");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<gibi, wchar_t>
{
    static std::wstring short_name() {return std::wstring(L"Gi");}
    static std::wstring long_name()  {return std::wstring(L"gibi");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
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
    static std::string short_name() {return std::string("Ti");}
    static std::string long_name()  {return std::string("tebi");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<tebi, char16_t>
{
    static std::u16string short_name() {return std::u16string(u"Ti");}
    static std::u16string long_name()  {return std::u16string(u"tebi");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<tebi, char32_t>
{
    static std::u32string short_name() {return std::u32string(U"Ti");}
    static std::u32string long_name()  {return std::u32string(U"tebi");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<tebi, wchar_t>
{
    static std::wstring short_name() {return std::wstring(L"Ti");}
    static std::wstring long_name()  {return std::wstring(L"tebi");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
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
    static std::string short_name() {return std::string("Pi");}
    static std::string long_name()  {return std::string("pebi");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<pebi, char16_t>
{
    static std::u16string short_name() {return std::u16string(u"Pi");}
    static std::u16string long_name()  {return std::u16string(u"pebi");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<pebi, char32_t>
{
    static std::u32string short_name() {return std::u32string(U"Pi");}
    static std::u32string long_name()  {return std::u32string(U"pebi");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<pebi, wchar_t>
{
    static std::wstring short_name() {return std::wstring(L"Pi");}
    static std::wstring long_name()  {return std::wstring(L"pebi");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
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
    static std::string short_name() {return std::string("Ei");}
    static std::string long_name()  {return std::string("exbi");}
    static std::string symbol() {return short_name();}
    static std::string prefix() {return long_name();}
};

#if BOOST_RATIO_HAS_UNICODE_SUPPORT

template <>
struct ratio_string<exbi, char16_t>
{
    static std::u16string short_name() {return std::u16string(u"Ei");}
    static std::u16string long_name()  {return std::u16string(u"exbi");}
    static std::u16string symbol() {return short_name();}
    static std::u16string prefix() {return long_name();}
};

template <>
struct ratio_string<exbi, char32_t>
{
    static std::u32string short_name() {return std::u32string(U"Ei");}
    static std::u32string long_name()  {return std::u32string(U"exbi");}
    static std::u32string symbol() {return short_name();}
    static std::u32string prefix() {return long_name();}
};

#endif

#ifndef BOOST_NO_STD_WSTRING
template <>
struct ratio_string<exbi, wchar_t>
{
    static std::wstring short_name() {return std::wstring(L"Ei");}
    static std::wstring long_name()  {return std::wstring(L"exbi");}
    static std::wstring symbol() {return short_name();}
    static std::wstring prefix() {return long_name();}
};
#endif
#endif
#endif
}

#endif  // BOOST_RATIO_RATIO_IO_HPP

/* ratio_io.hpp
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
*/