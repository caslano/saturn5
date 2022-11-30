/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   decomposed_time.hpp
 * \author Andrey Semashev
 * \date   07.11.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_DECOMPOSED_TIME_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_DECOMPOSED_TIME_HPP_INCLUDED_

#include <ctime>
#include <string>
#include <vector>
#include <locale>
#include <boost/cstdint.hpp>
#include <boost/move/core.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/date_time_format_parser.hpp>
#include <boost/log/detail/attachable_sstream_buf.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Date and time suitable for formatting
struct decomposed_time
{
    // Subseconds are microseconds
    enum _
    {
        subseconds_per_second = 1000000,
        subseconds_digits10 = 6
    };

    uint32_t year, month, day, hours, minutes, seconds, subseconds;
    bool negative;

    decomposed_time() : year(0), month(1), day(1), hours(0), minutes(0), seconds(0), subseconds(0), negative(false)
    {
    }

    decomposed_time(uint32_t y, uint32_t mo, uint32_t d, uint32_t h, uint32_t mi, uint32_t s, uint32_t ss = 0, bool neg = false) :
        year(y), month(mo), day(d), hours(h), minutes(mi), seconds(s), subseconds(ss), negative(neg)
    {
    }

    unsigned int week_day() const
    {
        unsigned int a = (14u - month) / 12u;
        unsigned int y = year - a;
        unsigned int m = month + 12u * a - 2u;
        return (day + y + (y / 4u) - (y / 100u) + (y / 400u) + (31u * m) / 12u) % 7u;
    }

    unsigned int year_day() const
    {
        bool is_leap_year = (!(year % 4u)) && ((year % 100u) || (!(year % 400u)));
        static const unsigned int first_day_offset[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
        return first_day_offset[month - 1] + day + (month > 2 && is_leap_year);
    }
};

inline std::tm to_tm(decomposed_time const& t)
{
    std::tm res = {};
    res.tm_year = static_cast< int >(t.year) - 1900;
    res.tm_mon = t.month - 1;
    res.tm_mday = t.day;
    res.tm_hour = t.hours;
    res.tm_min = t.minutes;
    res.tm_sec = t.seconds;
    res.tm_wday = t.week_day();
    res.tm_yday = t.year_day();
    res.tm_isdst = -1;

    return res;
}

template< typename T >
struct decomposed_time_wrapper :
    public boost::log::aux::decomposed_time
{
    typedef boost::log::aux::decomposed_time base_type;
    typedef T value_type;
    value_type m_time;

    BOOST_DEFAULTED_FUNCTION(decomposed_time_wrapper(), {})

    explicit decomposed_time_wrapper(value_type const& time) : m_time(time)
    {
    }
};

template< typename CharT >
BOOST_LOG_API void put_integer(boost::log::aux::basic_ostringstreambuf< CharT >& strbuf, uint32_t value, unsigned int width, CharT fill_char);

template< typename T, typename CharT >
class date_time_formatter
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(date_time_formatter)

protected:
    // Note: This typedef is needed to work around MSVC 2012 crappy name lookup in the derived classes
    typedef date_time_formatter date_time_formatter_;

public:
    typedef void result_type;
    typedef T value_type;
    typedef CharT char_type;
    typedef std::basic_string< char_type > string_type;
    typedef basic_formatting_ostream< char_type > stream_type;

    struct context
    {
        date_time_formatter const& self;
        stream_type& strm;
        value_type const& value;
        unsigned int literal_index, literal_pos;

        context(date_time_formatter const& self_, stream_type& strm_, value_type const& value_) :
            self(self_),
            strm(strm_),
            value(value_),
            literal_index(0),
            literal_pos(0)
        {
        }

        BOOST_DELETED_FUNCTION(context(context const&))
        BOOST_DELETED_FUNCTION(context& operator=(context const&))
    };

private:
    typedef void (*formatter_type)(context&);
    typedef std::vector< formatter_type > formatters;
    typedef std::vector< unsigned int > literal_lens;

protected:
    formatters m_formatters;
    literal_lens m_literal_lens;
    string_type m_literal_chars;

public:
    BOOST_DEFAULTED_FUNCTION(date_time_formatter(), {})
    date_time_formatter(date_time_formatter const& that) :
        m_formatters(that.m_formatters),
        m_literal_lens(that.m_literal_lens),
        m_literal_chars(that.m_literal_chars)
    {
    }
    date_time_formatter(BOOST_RV_REF(date_time_formatter) that) BOOST_NOEXCEPT
    {
        this->swap(static_cast< date_time_formatter& >(that));
    }

    date_time_formatter& operator= (date_time_formatter that) BOOST_NOEXCEPT
    {
        this->swap(that);
        return *this;
    }

    result_type operator() (stream_type& strm, value_type const& value) const
    {
        // Some formatters will put characters directly to the underlying string, so we have to flush stream buffers before formatting
        strm.flush();
        context ctx(*this, strm, value);
        for (typename formatters::const_iterator it = m_formatters.begin(), end = m_formatters.end(); strm.good() && it != end; ++it)
        {
            (*it)(ctx);
        }
    }

    void add_formatter(formatter_type fun)
    {
        m_formatters.push_back(fun);
    }

    void add_literal(iterator_range< const char_type* > const& lit)
    {
        m_literal_chars.append(lit.begin(), lit.end());
        m_literal_lens.push_back(static_cast< unsigned int >(lit.size()));
        m_formatters.push_back(&date_time_formatter_::format_literal);
    }

    void swap(date_time_formatter& that) BOOST_NOEXCEPT
    {
        m_formatters.swap(that.m_formatters);
        m_literal_lens.swap(that.m_literal_lens);
        m_literal_chars.swap(that.m_literal_chars);
    }

public:
    template< char FormatCharV >
    static void format_through_locale(context& ctx)
    {
        typedef std::time_put< char_type > facet_type;
        typedef typename facet_type::iter_type iter_type;
        std::tm t = to_tm(static_cast< decomposed_time const& >(ctx.value));
        std::use_facet< facet_type >(ctx.strm.getloc()).put(iter_type(ctx.strm.stream()), ctx.strm.stream(), ' ', &t, FormatCharV);
        ctx.strm.flush();
    }

    static void format_full_year(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.year, 4, static_cast< char_type >('0'));
    }

    static void format_short_year(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.year % 100u, 2, static_cast< char_type >('0'));
    }

    static void format_numeric_month(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.month, 2, static_cast< char_type >('0'));
    }

    template< char_type FillCharV >
    static void format_month_day(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.day, 2, static_cast< char_type >(FillCharV));
    }

    static void format_week_day(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), static_cast< decomposed_time const& >(ctx.value).week_day(), 1, static_cast< char_type >('0'));
    }

    template< char_type FillCharV >
    static void format_hours(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.hours, 2, static_cast< char_type >(FillCharV));
    }

    template< char_type FillCharV >
    static void format_hours_12(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.hours % 12u + 1u, 2, static_cast< char_type >(FillCharV));
    }

    static void format_minutes(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.minutes, 2, static_cast< char_type >('0'));
    }

    static void format_seconds(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.seconds, 2, static_cast< char_type >('0'));
    }

    static void format_fractional_seconds(context& ctx)
    {
        (put_integer)(*ctx.strm.rdbuf(), ctx.value.subseconds, decomposed_time::subseconds_digits10, static_cast< char_type >('0'));
    }

    template< bool UpperCaseV >
    static void format_am_pm(context& ctx)
    {
        static const char_type am[] = { static_cast< char_type >(UpperCaseV ? 'A' : 'a'), static_cast< char_type >(UpperCaseV ? 'M' : 'm'), static_cast< char_type >(0) };
        static const char_type pm[] = { static_cast< char_type >(UpperCaseV ? 'P' : 'p'), static_cast< char_type >(UpperCaseV ? 'M' : 'm'), static_cast< char_type >(0) };

        ctx.strm.rdbuf()->append(((static_cast< decomposed_time const& >(ctx.value).hours > 11) ? pm : am), 2u);
    }

    template< bool DisplayPositiveV >
    static void format_sign(context& ctx)
    {
        if (static_cast< decomposed_time const& >(ctx.value).negative)
            ctx.strm.rdbuf()->push_back('-');
        else if (DisplayPositiveV)
            ctx.strm.rdbuf()->push_back('+');
    }

private:
    static void format_literal(context& ctx)
    {
        unsigned int len = ctx.self.m_literal_lens[ctx.literal_index], pos = ctx.literal_pos;
        ++ctx.literal_index;
        ctx.literal_pos += len;
        const char_type* lit = ctx.self.m_literal_chars.c_str();
        ctx.strm.rdbuf()->append(lit + pos, len);
    }
};

template< typename FormatterT, typename CharT >
class decomposed_time_formatter_builder :
    public date_time_format_parser_callback< CharT >
{
public:
    typedef date_time_format_parser_callback< CharT > base_type;
    typedef typename base_type::char_type char_type;
    typedef FormatterT formatter_type;
    typedef typename formatter_type::value_type value_type;
    typedef typename formatter_type::stream_type stream_type;
    typedef typename stream_type::string_type string_type;

protected:
    formatter_type& m_formatter;

public:
    explicit decomposed_time_formatter_builder(formatter_type& fmt) : m_formatter(fmt)
    {
    }

    void on_literal(iterator_range< const char_type* > const& lit)
    {
        m_formatter.add_literal(lit);
    }

    void on_short_year()
    {
        m_formatter.add_formatter(&formatter_type::format_short_year);
    }

    void on_full_year()
    {
        m_formatter.add_formatter(&formatter_type::format_full_year);
    }

    void on_numeric_month()
    {
        m_formatter.add_formatter(&formatter_type::format_numeric_month);
    }

    void on_short_month()
    {
        m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_through_locale< 'b' >);
    }

    void on_full_month()
    {
        m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_through_locale< 'B' >);
    }

    void on_month_day(bool leading_zero)
    {
        if (leading_zero)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_month_day< '0' >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_month_day< ' ' >);
    }

    void on_numeric_week_day()
    {
        m_formatter.add_formatter(&formatter_type::format_week_day);
    }

    void on_short_week_day()
    {
        m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_through_locale< 'a' >);
    }

    void on_full_week_day()
    {
        m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_through_locale< 'A' >);
    }

    void on_hours(bool leading_zero)
    {
        if (leading_zero)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_hours< '0' >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_hours< ' ' >);
    }

    void on_hours_12(bool leading_zero)
    {
        if (leading_zero)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_hours_12< '0' >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_hours_12< ' ' >);
    }

    void on_minutes()
    {
        m_formatter.add_formatter(&formatter_type::format_minutes);
    }

    void on_seconds()
    {
        m_formatter.add_formatter(&formatter_type::format_seconds);
    }

    void on_fractional_seconds()
    {
        m_formatter.add_formatter(&formatter_type::format_fractional_seconds);
    }

    void on_am_pm(bool upper_case)
    {
        if (upper_case)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_am_pm< true >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_am_pm< false >);
    }

    void on_duration_sign(bool display_positive)
    {
        if (display_positive)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_sign< true >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_sign< false >);
    }

    void on_iso_time_zone()
    {
    }

    void on_extended_iso_time_zone()
    {
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_DECOMPOSED_TIME_HPP_INCLUDED_

/* decomposed_time.hpp
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
*/