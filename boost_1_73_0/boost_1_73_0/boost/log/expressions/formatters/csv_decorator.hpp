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
1j+H/nPgDz5pxHUS/Q+fZuXQjvOFif/BqPfwuY3IMcuHfHHqbPuQL6xGQxxJ5Sf87jjbCL1H3vCfYxz53sGv0ALDcGQ3iu8Tf77IWK1bZyc//vhf7JCdtk5bTXbuhj4P2Djj4Q1P5k32k0ct/1i4nz4dpfxlk/GMucGRRDVZ+ClLo1l25yacwffAn/Iw5R5zU+bxdJr4N/DDD1m24GzmB5x1h9fv+oNXTXa38KcLRHIfrVi6iFaBxxbuLWcJn3L/VuCI3SRj0QyGA3LPTzNAuMr8KDwC2pxlPFmmiAPJu0EaMffW9QP3Bgi5GVtkWZy+OD6erpIAuD/2oml6PFXTP1pkSz2Td8DE0r1nUZyxLGKrlDcZQjbZMvL8GX6CQKAxXt0Efrpo5twAqdA7jhKW8iBAXDDO56lgm7OxFE8TwVgMHPsZfqRRmCKpu0W0tABBjohltkpCIARyACAvAjE32Sr0eELANHNFQsqUBFypmpxfj0UhMMP2O2PWH++zGzf10yZ725+8Hr6ZsLed0agzmLxjwwvWGbxDZL/0B+egeh+IJYx/ihOeAvGE+cs48LknaX67v+O9v/nhNFh5nO1nURQ4Kc9W8dFifw86Zh6fsTfjnnPVm3Qu+4Nf9nLon9L79DjNXFDuS7M18wL/
*/