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
+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
*/