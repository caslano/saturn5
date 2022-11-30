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
    ~date_time_format_parser_callback() BOOST_OVERRIDE {}

    /*!
     * \brief The function is called when the parser discovers a string literal in the format string
     *
     * \param lit The string of characters not interpreted as a placeholder
     */
    void on_literal(iterator_range< const char_type* > const& lit) BOOST_OVERRIDE = 0;

    /*!
     * \brief The method is called when an unknown placeholder is found in the format string
     *
     * \param ph The placeholder with the leading percent sign
     */
    void on_placeholder(iterator_range< const char_type* > const& ph) BOOST_OVERRIDE
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