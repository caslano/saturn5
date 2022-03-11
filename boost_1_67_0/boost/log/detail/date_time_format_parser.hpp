/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   date_time_format_parser.hpp
 * \author Andrey Semashev
 * \date   16.09.2012
 *
 * The header contains a parser for date and time format strings.
 */

#ifndef BOOST_LOG_DETAIL_DATE_TIME_FORMAT_PARSER_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_DATE_TIME_FORMAT_PARSER_HPP_INCLUDED_

#include <string>
#include <boost/range/as_literal.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

/*!
 * This is the interface the parser will use to notify the caller about various components of date in the format string.
 */
template< typename CharT >
struct date_format_parser_callback
{
    //! Character type used by the parser
    typedef CharT char_type;

    //! Destructor
    virtual ~date_format_parser_callback() {}

    /*!
     * \brief The function is called when the parser discovers a string literal in the format string
     *
     * \param lit The string of characters not interpreted as a placeholder
     */
    virtual void on_literal(iterator_range< const char_type* > const& lit) = 0;

    /*!
     * \brief The method is called when an unknown placeholder is found in the format string
     *
     * \param ph The placeholder with the leading percent sign
     */
    virtual void on_placeholder(iterator_range< const char_type* > const& ph)
    {
        // By default interpret all unrecognized placeholders as literals
        on_literal(ph);
    }

    /*!
     * \brief The function is called when the short year placeholder is found in the format string
     */
    virtual void on_short_year()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('y'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the full year placeholder is found in the format string
     */
    virtual void on_full_year()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('Y'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the numeric month placeholder is found in the format string
     */
    virtual void on_numeric_month()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('m'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the short alphabetic month placeholder is found in the format string
     */
    virtual void on_short_month()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('b'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the full alphabetic month placeholder is found in the format string
     */
    virtual void on_full_month()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('B'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the numeric day of month placeholder is found in the format string
     *
     * \param leading_zero If \c true, the day should be formatted with leading zero, otherwise with leading space
     */
    virtual void on_month_day(bool leading_zero)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (leading_zero ? static_cast< char_type >('d') : static_cast< char_type >('e')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the numeric day of week placeholder is found in the format string
     */
    virtual void on_numeric_week_day()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('w'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the short alphabetic day of week placeholder is found in the format string
     */
    virtual void on_short_week_day()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('a'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the full alphabetic day of week placeholder is found in the format string
     */
    virtual void on_full_week_day()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('A'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the ISO-formatted date is found in the format string
     */
    virtual void on_iso_date()
    {
        on_full_year();
        on_numeric_month();
        on_month_day(true);
    }

    /*!
     * \brief The function is called when the extended ISO-formatted date is found in the format string
     */
    virtual void on_extended_iso_date()
    {
        const char_type delimiter[2] = { static_cast< char_type >('-'), static_cast< char_type >('\0') };
        on_full_year();
        on_literal(boost::as_literal(delimiter));
        on_numeric_month();
        on_literal(boost::as_literal(delimiter));
        on_month_day(true);
    }
};

/*!
 * This is the interface the parser will use to notify the caller about various components of date in the format string.
 */
template< typename CharT >
struct time_format_parser_callback
{
    //! Character type used by the parser
    typedef CharT char_type;

    //! Destructor
    virtual ~time_format_parser_callback() {}

    /*!
     * \brief The function is called when the parser discovers a string literal in the format string
     *
     * \param lit The string of characters not interpreted as a placeholder
     */
    virtual void on_literal(iterator_range< const char_type* > const& lit) = 0;

    /*!
     * \brief The method is called when an unknown placeholder is found in the format string
     *
     * \param ph The placeholder with the leading percent sign
     */
    virtual void on_placeholder(iterator_range< const char_type* > const& ph)
    {
        // By default interpret all unrecognized placeholders as literals
        on_literal(ph);
    }

    /*!
     * \brief The function is called when the hours placeholder is found in the format string
     *
     * The placeholder is used for 24-hour clock and duration formatting.
     *
     * \param leading_zero If \c true, the one-digit number of hours should be formatted with leading zero, otherwise with leading space
     */
    virtual void on_hours(bool leading_zero)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (leading_zero ? static_cast< char_type >('O') : static_cast< char_type >('k')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the hours placeholder is found in the format string
     *
     * The placeholder is used for 12-hour clock formatting. It should not be used for duration formatting.
     *
     * \param leading_zero If \c true, the one-digit number of hours should be formatted with leading zero, otherwise with leading space
     */
    virtual void on_hours_12(bool leading_zero)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (leading_zero ? static_cast< char_type >('I') : static_cast< char_type >('l')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the minutes placeholder is found in the format string
     */
    virtual void on_minutes()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('M'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the seconds placeholder is found in the format string
     */
    virtual void on_seconds()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('S'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the fractional seconds placeholder is found in the format string
     */
    virtual void on_fractional_seconds()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('f'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the day period (AM/PM) placeholder is found in the format string
     *
     * The placeholder is used for 12-hour clock formatting. It should not be used for duration formatting.
     *
     * \param upper_case If \c true, the day period will be upper case, and lower case otherwise
     */
    virtual void on_am_pm(bool upper_case)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (upper_case ? static_cast< char_type >('p') : static_cast< char_type >('P')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the time duration sign placeholder is found in the format string
     *
     * The placeholder is used for duration formatting. It should not be used for time point formatting.
     *
     * \param display_positive If \c true, the positive sign will be explicitly displayed, otherwise only negative sign will be displayed
     */
    virtual void on_duration_sign(bool display_positive)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (display_positive ? static_cast< char_type >('+') : static_cast< char_type >('-')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the ISO time zone placeholder is found in the format string
     */
    virtual void on_iso_time_zone()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('q'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the extended ISO time zone placeholder is found in the format string
     */
    virtual void on_extended_iso_time_zone()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('Q'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    /*!
     * \brief The function is called when the ISO-formatted time is found in the format string
     */
    virtual void on_iso_time()
    {
        on_hours(true);
        on_minutes();
        on_seconds();
    }

    /*!
     * \brief The function is called when the extended ISO-formatted time is found in the format string
     */
    virtual void on_extended_iso_time()
    {
        const char_type delimiter[2] = { static_cast< char_type >(':'), static_cast< char_type >('\0') };
        on_hours(true);
        on_literal(boost::as_literal(delimiter));
        on_minutes();
        on_literal(boost::as_literal(delimiter));
        on_seconds();
    }

    /*!
     * \brief The function is called when the extended ISO-formatted time with fractional seconds is found in the format string
     */
    virtual void on_default_time()
    {
        on_extended_iso_time();

        const char_type delimiter[2] = { static_cast< char_type >('.'), static_cast< char_type >('\0') };
        on_literal(boost::as_literal(delimiter));
        on_fractional_seconds();
    }
};

/*!
 * This is the interface the parser will use to notify the caller about various components of date in the format string.
 */
template< typename CharT >
struct date_time_format_parser_callback :
    public date_format_parser_callback< CharT >,
    public time_format_parser_callback< CharT >
{
    //! Character type used by the parser
    typedef CharT char_type;

    //! Destructor
    virtual ~date_time_format_parser_callback() {}

    /*!
     * \brief The function is called when the parser discovers a string literal in the format string
     *
     * \param lit The string of characters not interpreted as a placeholder
     */
    virtual void on_literal(iterator_range< const char_type* > const& lit) = 0;

    /*!
     * \brief The method is called when an unknown placeholder is found in the format string
     *
     * \param ph The placeholder with the leading percent sign
     */
    virtual void on_placeholder(iterator_range< const char_type* > const& ph)
    {
        // By default interpret all unrecognized placeholders as literals
        on_literal(ph);
    }
};

/*!
 * \brief Parses the date format string and invokes the callback object
 *
 * \pre <tt>begin <= end</tt>, both pointers must not be \c NULL
 * \param begin Pointer to the first character of the sequence
 * \param end Pointer to the after-the-last character of the sequence
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT >
BOOST_LOG_API void parse_date_format(const CharT* begin, const CharT* end, date_format_parser_callback< CharT >& callback);

/*!
 * \brief Parses the date format string and invokes the callback object
 *
 * \param str The format string to parse
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
inline void parse_date_format(std::basic_string< CharT, TraitsT, AllocatorT > const& str, date_format_parser_callback< CharT >& callback)
{
    const CharT* p = str.c_str();
    return parse_date_format(p, p + str.size(), callback);
}

/*!
 * \brief Parses the date format string and invokes the callback object
 *
 * \pre <tt>str != NULL</tt>, <tt>str</tt> points to a zero-terminated string.
 * \param str The format string to parse
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT >
inline void parse_date_format(const CharT* str, date_format_parser_callback< CharT >& callback)
{
    return parse_date_format(str, str + std::char_traits< CharT >::length(str), callback);
}

/*!
 * \brief Parses the time format string and invokes the callback object
 *
 * \pre <tt>begin <= end</tt>, both pointers must not be \c NULL
 * \param begin Pointer to the first character of the sequence
 * \param end Pointer to the after-the-last character of the sequence
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT >
BOOST_LOG_API void parse_time_format(const CharT* begin, const CharT* end, time_format_parser_callback< CharT >& callback);

/*!
 * \brief Parses the time format string and invokes the callback object
 *
 * \param str The format string to parse
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
inline void parse_time_format(std::basic_string< CharT, TraitsT, AllocatorT > const& str, time_format_parser_callback< CharT >& callback)
{
    const CharT* p = str.c_str();
    return parse_time_format(p, p + str.size(), callback);
}

/*!
 * \brief Parses the time format string and invokes the callback object
 *
 * \pre <tt>str != NULL</tt>, <tt>str</tt> points to a zero-terminated string.
 * \param str The format string to parse
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT >
inline void parse_time_format(const CharT* str, time_format_parser_callback< CharT >& callback)
{
    return parse_time_format(str, str + std::char_traits< CharT >::length(str), callback);
}

/*!
 * \brief Parses the date and time format string and invokes the callback object
 *
 * \pre <tt>begin <= end</tt>, both pointers must not be \c NULL
 * \param begin Pointer to the first character of the sequence
 * \param end Pointer to the after-the-last character of the sequence
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT >
BOOST_LOG_API void parse_date_time_format(const CharT* begin, const CharT* end, date_time_format_parser_callback< CharT >& callback);

/*!
 * \brief Parses the date and time format string and invokes the callback object
 *
 * \param str The format string to parse
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
inline void parse_date_time_format(std::basic_string< CharT, TraitsT, AllocatorT > const& str, date_time_format_parser_callback< CharT >& callback)
{
    const CharT* p = str.c_str();
    return parse_date_time_format(p, p + str.size(), callback);
}

/*!
 * \brief Parses the date and time format string and invokes the callback object
 *
 * \pre <tt>str != NULL</tt>, <tt>str</tt> points to a zero-terminated string.
 * \param str The format string to parse
 * \param callback Reference to the callback object that will be invoked by the parser as it processes the input
 */
template< typename CharT >
inline void parse_date_time_format(const CharT* str, date_time_format_parser_callback< CharT >& callback)
{
    return parse_date_time_format(str, str + std::char_traits< CharT >::length(str), callback);
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_DATE_TIME_FORMAT_PARSER_HPP_INCLUDED_

/* date_time_format_parser.hpp
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
*/