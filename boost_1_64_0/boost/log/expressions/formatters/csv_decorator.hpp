/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/csv_decorator.hpp
 * \author Andrey Semashev
 * \date   18.11.2012
 *
 * The header contains implementation of a CSV-style character decorator.
 * See: http://en.wikipedia.org/wiki/Comma-separated_values
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_CSV_DECORATOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_CSV_DECORATOR_HPP_INCLUDED_

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
struct csv_decorator_traits;

#ifdef BOOST_LOG_USE_CHAR
template< >
struct csv_decorator_traits< char >
{
    static boost::iterator_range< const char* const* > get_patterns()
    {
        static const char* const patterns[] =
        {
            "\""
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const char* const* > get_replacements()
    {
        static const char* const replacements[] =
        {
            "\"\""
        };
        return boost::make_iterator_range(replacements);
    }
};
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T
template< >
struct csv_decorator_traits< wchar_t >
{
    static boost::iterator_range< const wchar_t* const* > get_patterns()
    {
        static const wchar_t* const patterns[] =
        {
            L"\""
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const wchar_t* const* > get_replacements()
    {
        static const wchar_t* const replacements[] =
        {
            L"\"\""
        };
        return boost::make_iterator_range(replacements);
    }
};
#endif // BOOST_LOG_USE_WCHAR_T

template< typename CharT >
struct csv_decorator_gen
{
    typedef CharT char_type;

    template< typename SubactorT >
    BOOST_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef csv_decorator_traits< char_type > traits_type;
        typedef pattern_replacer< char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(traits_type::get_patterns(), traits_type::get_replacements())) }};
        return result_type(act);
    }
};

} // namespace aux

/*!
 * CSV-style decorator generator object. The decorator doubles double quotes that may be found
 * in the output. See http://en.wikipedia.org/wiki/Comma-separated_values for more information on
 * the CSV format. The generator provides <tt>operator[]</tt> that can be used to construct
 * the actual decorator. For example:
 *
 * <code>
 * csv_decor[ stream << attr< std::string >("MyAttr") ]
 * </code>
 *
 * For wide-character formatting there is the similar \c wcsv_decor decorator generator object.
 */
#ifdef BOOST_LOG_USE_CHAR
const aux::csv_decorator_gen< char > csv_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
const aux::csv_decorator_gen< wchar_t > wcsv_decor = {};
#endif

/*!
 * The function creates an CSV-style decorator generator for arbitrary character type.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::csv_decorator_gen< CharT > make_csv_decor()
{
    return aux::csv_decorator_gen< CharT >();
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_CSV_DECORATOR_HPP_INCLUDED_

/* csv_decorator.hpp
HR+4SvPkSuSywVzv4bMlMHfOtOLlZfXDsEddXoK6u/+TUlZQ6xrVGvnwlStmne9L4j/b6kYup+mayeyeXOMtOJl/+/B93J5rt/NFOpH4bFL2SeP92yetrtW3v/mf62G++YO+kevjnH5U55e8aewZSFeFL1vs9BWXV5Ysr9P0XJYua+VLLfdvfA3D0+r3tN+WgB1eFwkvOI6Z8SZuZv3eVOLY5B5HLcXo4th0lOK4Kz48Hz/gA2dLhDjKcEWU+bjlCOPoX/9YmhAex2nk4/YIcWyoqy0uZZF1tPHcfoTx9OdlUjv3vGyOEM/VJZUNZVHGsfkoxfFAu+B1vinIDPJyj0sc60LazdrDx1HD8BibAh5LfLvbo29jetZqepx23XkG1+QZQfVlX2J4GmeRxv3uaQzUlyjTuV/jruvH+cuE4JrW/UeQ1q6aVp7DNfOcoHVdCVrhevrHP5D3qXctjvRqcktKCTVsfxa3tZuOsnzveLEXY2ujuaQv2O3sDCl3ceu2jkvdmjVUk6IYM5V8Cd4HxdQB4sY1iZux90EcuCZxCKr7dyWFt8+TqRfZvQL55NKNSLrOlDpRw23X/CKMtpUx4RFHCS8ojhuTw+vuXOKYFx7HurbGMa9X2+pt3hGkyb3eBo/Tv6U2M27RwL7tH+cOS2sd7yNVFXUrTPvkqOBWwCbREvFTpudYYpDzjrK+82byNJdnTc4hXzvxfy3+qH9xdn1M9YnYVFC383A7Rdw2XuGvpwfVTR91swE3U3ET3zdlSsrglAEpfRLj4rskxnnT04wO5eZUFfXrj8sO/E6zw09J98Z3tExbKMuwXNeRJri8F62S9EldD8rTjbpG/4eIB7kbWUz9Se0dlqeiAOrv897sLntGVZXrPjJdYRfxc5eVxL8nIUvc9yHRsD2HnVvqI27S3OoZ/l1/N8xeKAPl/g3WcFrsyaTWrV8xYRjbI7Vl0Dx/k9xP13OPdb+cs6+OcV9h6tJX5F6RhNVX6trqSssR1tfkfkeztpT7dWXLMJzg2HuqQNyMsLy4628lmecWOfzelmZxyFtAnXMflvPEzTx8xVtZ1JkDHaijJDKHgL2e5d6keK8n15sU51qH1X1GR/Lcdt9+talf76qbLM7b2e0uTUTmrq6G01364tQIbd2uL12kvmhbd5nTkv44/Hfa9HU1anNgk9ajbyLjRpKWCHVVP0oc9cy+IA8ztnPism2/V7n/pkWup+6/a+710qX+Bbt9qbvFYX9IWca+WYLE6zLX+tkVfiD+rw/93jJ18pDcv87y70d2LGU1A+mBXNzFV4YzdU+mnlGUo21Xa1l2+H5MUoYmX9tetv5+qLRzYB8kj+6DNJ94bc8OL9uGKumJTN5QLpWV0F+me8TPErcy1fA8ru34F3JvjflttOSdKlAmr8j9ecb20TNy3kns99RTNxeT5ll2P52aaNqQaWfqZo264beiMdRNlrrZzvlJuIk/OWWg7xcioGc/rpf+RgSHK7+Ds+1wvRPNs/Eobrqqm09xc7K4yfHGd7JC27kJK5uymOOL4zdCf8/853NzWt9z6Z/snQlgFNUZgGezSchFEnIRAgLhBhGDIKCABkRFigICFpUrkHBICDEJeKAYES0e1dhKi5YqVurVi7baYmsrKq202or1woptVKS0okVEay3afvPvv29nd98mu0DvjP58mZn33rx73nvz/n+17as9NSmjsHHo+IKA4z9ome9BXqVyN5WGyry2oq6+ak616qeb34zjfI6tfPEbaXeuvqrW1l6tbmuW1dfax6G4NX3BK0UmDvPneX6D7XFx831nHKm80BlstTNgnmnGVBV1Cx2rjQHctvyOuqBHwC5Vkb4rnhA=
*/