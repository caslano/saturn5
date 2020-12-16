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
XhDits9bJPaND2k5l9IV2Jdm2qeWLiyXgSgc25xHRWcjeoGPQUmbE1h/YUf73Ca68Se2cYYN3sDSZxgPPfBK0pTZnCYPk8OMo23asp55uTmfz1wVLsX9NrF+RMt5sjtC1pKROIj5CdfB9nGmlnQP7mF+q2HO9Veq9k9wN8/zk6+O57UvR+3r5b7Hu2qRO4zjhZnzLB53OPuY2aJZbwF6skaS0uvsvgG9byjRUe5I9Nhn6qVZ9MqUXiK/8pRed/dtlNJf6VWLV/Mkss/UG0raTL3ywoXeYSwuc563DBUmwZyPsVLFN85t0amap1Sa57DroXRSqXohciz6NJRfiLlGyii1vVCdy36uHcw5k7pJOOMcJKrtKzkDXV2jqQsd8dsphTnqE5ult2W7T4rM1+YjfWVenaitzNdGnsh8bWzb6lO5stWo66+Gt1x7P5/8SMkyyp36TMZSh8rN8Yx9VZhlkkbRIaYUzrelnIm/2z7HnuhkqH0VrsHkSTu248j4i4g8qwv1mgjWJPpKYN/Z2OtfuWwb9a9Qzdd0iPfYbF+fbr++FGjG7scQT2NznqhPW3JL8wtLc7d+fWnM+nPXDOv1YbWMh99BFHoh3TmfG31sogRbrg8ecx3RLSpcktY+4jDHTPzYFz2zLjR/87VZhdGs1anTt9Y/0Q/PJgyWaddNDDJ/5L5gjr/gmGybNiv/GNPftMWWn2nS7D5QDjAA6Uq8Kdn2/CxbkG/PT0lParbfb+AkDlLbnB/meejDPm0+avUWmHq7q30dNPmn08s39cZKvmvm7ELvz+U729Z8Z9ua3wvUdqy5nW8b6/Sq5Hu8HKCLzC+cbcv3LHlQMR9SzOeH94h4J9dU9Uzz+On4ROifacw5RlW80VtdG9Ja/++QMf/AZEdsrLHbmFutxotvvf6j5/N8UeiphroyIGHN9M7osvXnpdafNTiW7/NT+5bXtxu4Btba0yeZufX01QZZjsRO232oXmwCZp7HUt7qTJvUJxZmvjwewPrS1jSnyzj+3VF2e7f5dyh2rLLFb6ZZXcv6q3kf5SpvWZ9yxFyvzvW6vCA+6xy79vlqk+DDan9v9w78n4Ekslb0ShJdFsN10DtH9xGsEd0u2lre1drPQ9luL9931CAcEMp3p0Tcj+eCnRFPlyb/F4OsJzuoNEVv9bsA77PFa3Obny0S5ZySVyTXklfcX++ea95fbWP/Nsu5GC7PHMPk/SJjnnkuKnJzqsoLKxerFw12W6/B5vcv+6rwQ7iGu3XnQuKT7x8sc+peHsBauvZrnv1ePFvGwu+HqHFUyCwOWmux33ovJgKb3eepcBlsa+2WeNzyPGu7H5vfd1yswvB2p1831jcO+z1Z4rhfhemivaeIvnzfLM+fAXw3Yqnjtns0Nuju0fj7v0dvkSNVi02LkBmE3+iTz9yjtfn8swqXy3i7cP1zj6SxXXMemfOufq/2FbnSCKnJX43uAvO9oVNOpKrd3fivyVuNbr55Xnsq3bFqdUrdPXujvUxzTkQCmB/V59ywbTs3bFvPidzHZdv3Pr6is/0eGY3c6L2H5FjOje993Pb9o9fLpS//OYHdT2zf7qn47Nf8++Na3sf7cZA6i43B3MfrcgK/j1vDynds5dp52VVY+z1/5ja658ucqfJ9mzq+LX9qu9jXDm4v7SirbPkjrSgBPAesygm8HWVVgOc40HYUI01r40VZ7i1jkJtIU4MtTVIeNXNaG++2j6vwo3TplLjcvmXZvJd+oPbH6tLtq4sr4eO9Zt2n1P5QsyxcFMC9SjePrsone91Q9+Q1OeY9WW1/b9mW5zHb+PzpUm+myj06xdOcj4VH5traouSdXsIkWvMMv9bXoq0=
*/