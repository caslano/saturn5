/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/xml_decorator.hpp
 * \author Andrey Semashev
 * \date   18.11.2012
 *
 * The header contains implementation of a XML-style character decorator.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_XML_DECORATOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_XML_DECORATOR_HPP_INCLUDED_

#include <boost/range/iterator_range_core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/expressions/formatters/char_decorator.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

template< typename >
struct xml_decorator_traits;

#ifdef BOOST_LOG_USE_CHAR
template< >
struct xml_decorator_traits< char >
{
    static boost::iterator_range< const char* const* > get_patterns()
    {
        static const char* const patterns[] =
        {
            "&", "<", ">", "\"", "'"
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const char* const* > get_replacements()
    {
        static const char* const replacements[] =
        {
            "&amp;", "&lt;", "&gt;", "&quot;", "&apos;"
        };
        return boost::make_iterator_range(replacements);
    }
};
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T
template< >
struct xml_decorator_traits< wchar_t >
{
    static boost::iterator_range< const wchar_t* const* > get_patterns()
    {
        static const wchar_t* const patterns[] =
        {
            L"&", L"<", L">", L"\"", L"'"
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const wchar_t* const* > get_replacements()
    {
        static const wchar_t* const replacements[] =
        {
            L"&amp;", L"&lt;", L"&gt;", L"&quot;", L"&apos;"
        };
        return boost::make_iterator_range(replacements);
    }
};
#endif // BOOST_LOG_USE_WCHAR_T

template< typename CharT >
struct xml_decorator_gen
{
    typedef CharT char_type;

    template< typename SubactorT >
    BOOST_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef xml_decorator_traits< char_type > traits_type;
        typedef pattern_replacer< char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(traits_type::get_patterns(), traits_type::get_replacements())) }};
        return result_type(act);
    }
};

} // namespace aux

/*!
 * XML-style decorator generator object. The decorator replaces characters that have special meaning
 * in XML documents with the corresponding decorated counterparts. The generator provides
 * <tt>operator[]</tt> that can be used to construct the actual decorator. For example:
 *
 * <code>
 * xml_decor[ stream << attr< std::string >("MyAttr") ]
 * </code>
 *
 * For wide-character formatting there is the similar \c wxml_decor decorator generator object.
 */
#ifdef BOOST_LOG_USE_CHAR
const aux::xml_decorator_gen< char > xml_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
const aux::xml_decorator_gen< wchar_t > wxml_decor = {};
#endif

/*!
 * The function creates an XML-style decorator generator for arbitrary character type.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::xml_decorator_gen< CharT > make_xml_decor()
{
    return aux::xml_decorator_gen< CharT >();
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_XML_DECORATOR_HPP_INCLUDED_

/* xml_decorator.hpp
IHgOzIUL9P4yvb9c718Gs+Ctev8Ovb9R72+C7eAjMA1uVXe/UHfPqrvnYR/4EuwL/wz7wQOwP2xHfR0Ac6HrvggOhN3gcbC3Xh8YsHPWqo2zb/453XkG2Ydk7U//j7Z5NjcBu2dzt9htnx0UPeho22dZM9sdsf2znWOS/mn2zzZG2EDrR1mNQ+YijcgGZAuyE9mP5L6HLjkyEalEGpENyFakGfkI6X4g3RmFzDjQpsvddrQdbUfb0Xa0HW1H29F2tB1tR9vRdvx7j3+Z/n9F7eKjof/v6uBfUeoYXfltSfotUNc0G5AvD+Ofv4r+YWDHZ0Vlpdrui2svH37NPrWe+fZ9asniJtO2T834zzb+Zde00ZFIl/v9HPbyW/eqef1/LU/2x4TpBLSX+xXkWpJXX8Lsgxss908TXeMtDoe7VkWks5JystKSQzqs+8xvCeJOf+PrylLcpffJ8meG3L1WGHCXp+4m4m6V667dCONmUYG6UbuIRlfgMPXxgvthSJtlP4xe13z12k5wovTU9TevtT608rvRJg+/Lu5HWusHYRn94O3kxUwSfJWbH5lDTX68oXkWdNPoR1w37fsaN0tKwt1sws3Vrpuc4kg9Y+NmO25Wu27Sco2banVzuHriwd8y5JuSHKdoWzoZWee2pY8DeRfPbxcH931li5+BfBdvZ81Dwoz1u8Vm/1+RuMmwtjH1H17/9dmD5V67gB2CwL0Vuldb9sa59T2ZSBST3mukHh+TlZYTqu/NhaH8zPJmaBy/0xvrt49xK88mPlyX+Ojedf2t3nb6LUbzfoz+bvTkGHkfUMSoj8x/kwezxV9Puz5pHHm/IHbeG/9dyUd3I8721IC+T2ZGaqo/N7Nn5mexaZCWZi2bqwPh6jm7CeU8qcWyGkX425CWyspWXvHow8TzW9UN6fo7R/q97ilkOGWzWcumld+qNrq+z4r7+9hlm+Ksi9EuNrdSNh3hLnFzsrVs8G/V4S7Rd8djcn8LT0927kLuR6z7pTUc715b077+Ju8+U4YXynk7b3kbXcwPJJyLCXOys6CFNllCOXdpx3PTtJyTy7KS09xaFF3WQbe7jNvGtVnJWThuvQ3H8/vxMeqE5fe2re1abI0cS56Y39jkvNqch9et8RmOHEMQsXOr9hM2497ULbax6usqpv2Rh8X9ceSw3f4I4Zl31qXU51yeu8bNu7x8k2e7C4/Oe6RSM/kx3S/wU+QLvEf2R6ZJszZeXSr8x2obtraA+8hxVP0S7zjqkNzf7NxCe/TobBsd2pGH3PvTzH71Jjnv6q3nJv8/kLC2OLdrX9YzVMdNu6kW/51Nu7lBzv1SJhMpj02Z7DV0yyS1cWOwTA7qGC3oZnumjtGy6qPHZ+pmH256d8BNSopx827470Ybfc0H8+xjtCzLHmbSH9ceZmtfqrom69s7ctyie0JuRh5wdQwl7EY3INUxnO+qYXr1C40tgD+J22vYV5fMnrkUW13R8Hwe//OMLv1bcu969tlRgxBL3TH+bbr8uZ+498aQrtFOkZZlR7k2g3wayj7KDq2OeSP0E+U8zZzPC8uzidlqW0XzrBS51x3TfhKZZ4sq6hd582xFaDwrbrtY84pwwnQsLypxpfVxe3gaVoTpU5blROvifZ047+BZ0bp4zB0bquLSw8N/RLlWWstP3Zn6v7fw8PTqwsulMiyNXXKj07jBrcs8265vGJ+uIf5Nv3WnpFE82+tpRDqXHKH+IM/jmjxP0jpB0zqjQ3Ra73b79JhpnTNxvOea48SX9v2etN/Vip6lutVwW9azxO1R1bO8K0rPUt1pHLz1JDkvOu+W49/5NDrvZG4aZ17hPyxNbxxmHffGda8lrrc=
*/