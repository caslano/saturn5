/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/date_time.hpp
 * \author Andrey Semashev
 * \date   07.11.2012
 *
 * This header enables Boost.DateTime support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_DATE_TIME_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_DATE_TIME_HPP_INCLUDED_

#include <ctime>
#include <string>
#include <locale>
#include <ostream>
#include <iterator>
#include <boost/cstdint.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/date_time/time.hpp>
#include <boost/date_time/date.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/local_time/local_time_types.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/date_time_format_parser.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/decomposed_time.hpp>
#include <boost/log/detail/date_time_fmt_gen_traits_fwd.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

namespace date_time_support {

template< typename DateT, typename ValueT >
inline void decompose_date(DateT const& d, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    typedef typename DateT::ymd_type ymd_type;
    ymd_type ymd = d.year_month_day();
    v.year = static_cast< uint32_t >(ymd.year);
    v.month = static_cast< uint32_t >(ymd.month);
    v.day = static_cast< uint32_t >(ymd.day);
}

template< typename TimeDurationT, typename ValueT >
inline void decompose_time_of_day(TimeDurationT const& tod, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    v.hours = static_cast< uint32_t >(tod.hours());
    v.minutes = static_cast< uint32_t >(tod.minutes());
    v.seconds = static_cast< uint32_t >(tod.seconds());

    typedef typename TimeDurationT::traits_type traits_type;
    enum
    {
        adjustment_ratio = (traits_type::ticks_per_second > boost::log::aux::decomposed_time::subseconds_per_second ?
            traits_type::ticks_per_second / boost::log::aux::decomposed_time::subseconds_per_second :
            boost::log::aux::decomposed_time::subseconds_per_second / traits_type::ticks_per_second)
    };
    uint64_t frac = tod.fractional_seconds();
    v.subseconds = static_cast< uint32_t >(traits_type::ticks_per_second > boost::log::aux::decomposed_time::subseconds_per_second ? frac / adjustment_ratio : frac * adjustment_ratio);
}

template< typename TimeDurationT, typename ValueT >
inline void decompose_time_duration(TimeDurationT const& dur, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    if (dur.is_negative())
    {
        v.negative = true;
        (decompose_time_of_day)(-dur, v);
    }
    else
        (decompose_time_of_day)(dur, v);
}

template< typename DateDurationT, typename ValueT >
inline void decompose_date_duration(DateDurationT const& dur, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    if (dur.is_negative())
    {
        v.negative = true;
        v.day = static_cast< uint32_t >((-dur).days());
    }
    else
        v.day = static_cast< uint32_t >(dur.days());
}

template< typename TimeT, typename ValueT >
inline void decompose_time(TimeT const& t, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    (decompose_date)(t.date(), v);
    (decompose_time_of_day)(t.time_of_day(), v);
}

} // namespace date_time_support

template< typename TimeT, typename CharT >
struct date_time_formatter_generator_traits_impl
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Value type
    typedef TimeT value_type;

    //! Formatter function
    typedef boost::log::aux::light_function< void (stream_type&, value_type const&) > formatter_function_type;

    //! Formatter implementation
    class formatter :
        public boost::log::aux::date_time_formatter< boost::log::aux::decomposed_time_wrapper< value_type >, char_type >
    {
        BOOST_COPYABLE_AND_MOVABLE_ALT(formatter)

    private:
        // Do not change this typedef, copy-pasting the inherited class from above will break compilation with MSVC 2012 because it incorrectly binds value_type.
        typedef typename formatter::date_time_formatter_ base_type;

    public:
        typedef typename base_type::result_type result_type;
        // This typedef is needed to work around MSVC 2012 crappy name lookup. Otherwise base_type::value_type is bound instead.
        typedef typename date_time_formatter_generator_traits_impl< TimeT, CharT >::value_type value_type;

    public:
        BOOST_DEFAULTED_FUNCTION(formatter(), {})
        formatter(formatter const& that) : base_type(static_cast< base_type const& >(that)) {}
        formatter(BOOST_RV_REF(formatter) that) { this->swap(that); }

        formatter& operator= (formatter that)
        {
            this->swap(that);
            return *this;
        }

        result_type operator() (stream_type& strm, value_type const& value) const
        {
            if (value.is_not_a_date_time())
                strm << "not-a-date-time";
            else if (value.is_pos_infinity())
                strm << "+infinity";
            else if (value.is_neg_infinity())
                strm << "-infinity";
            else
            {
                boost::log::aux::decomposed_time_wrapper< value_type > val(value);
                date_time_support::decompose_time(value, val);
                base_type::operator() (strm, val);
            }
        }
    };

    //! The function parses format string and constructs formatter function
    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > builder(fmt);
        boost::log::aux::parse_date_time_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }
};

template< typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< posix_time::ptime, CharT, VoidT > :
    public date_time_formatter_generator_traits_impl< posix_time::ptime, CharT >
{
};

template< typename TimeT, typename TimeZoneT, typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< local_time::local_date_time_base< TimeT, TimeZoneT >, CharT, VoidT >
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Value type
    typedef local_time::local_date_time_base< TimeT, TimeZoneT > value_type;

    //! Formatter function
    typedef boost::log::aux::light_function< void (stream_type&, value_type const&) > formatter_function_type;

    //! Formatter implementation
    class formatter :
        public boost::log::aux::date_time_formatter< boost::log::aux::decomposed_time_wrapper< value_type >, char_type >
    {
        BOOST_COPYABLE_AND_MOVABLE_ALT(formatter)

    private:
        // Do not change this typedef, copy-pasting the inherited class from above will break compilation with MSVC 2012 because it incorrectly binds value_type.
        typedef typename formatter::date_time_formatter_ base_type;

    public:
        typedef typename base_type::result_type result_type;
        typedef typename base_type::context context;
        // This typedef is needed to work around MSVC 2012 crappy name lookup. Otherwise base_type::value_type is bound instead.
        typedef typename date_time_formatter_generator_traits< local_time::local_date_time_base< TimeT, TimeZoneT >, CharT, VoidT >::value_type value_type;

    public:
        BOOST_DEFAULTED_FUNCTION(formatter(), {})
        formatter(formatter const& that) : base_type(static_cast< base_type const& >(that)) {}
        formatter(BOOST_RV_REF(formatter) that) { this->swap(that); }

        formatter& operator= (formatter that)
        {
            this->swap(that);
            return *this;
        }

        result_type operator() (stream_type& strm, value_type const& value) const
        {
            if (value.is_not_a_date_time())
                strm << "not-a-date-time";
            else if (value.is_pos_infinity())
                strm << "+infinity";
            else if (value.is_neg_infinity())
                strm << "-infinity";
            else
            {
                boost::log::aux::decomposed_time_wrapper< value_type > val(value);
                date_time_support::decompose_time(value.local_time(), val);
                base_type::operator() (strm, val);
            }
        }

    public:
        static void format_iso_time_zone(context& ctx)
        {
            ctx.strm << ctx.value.m_time.zone_abbrev(true);
            ctx.strm.flush();
        }

        static void format_extended_iso_time_zone(context& ctx)
        {
            ctx.strm << ctx.value.m_time.zone_name(true);
            ctx.strm.flush();
        }
    };

    class formatter_builder :
        public boost::log::aux::decomposed_time_formatter_builder< formatter, char_type >
    {
    private:
        typedef boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > base_type;

    public:
        explicit formatter_builder(formatter& fmt) : base_type(fmt)
        {
        }

        void on_iso_time_zone()
        {
            this->m_formatter.add_formatter(&formatter::format_iso_time_zone);
        }

        void on_extended_iso_time_zone()
        {
            this->m_formatter.add_formatter(&formatter::format_extended_iso_time_zone);
        }
    };

    //! The function parses format string and constructs formatter function
    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        formatter_builder builder(fmt);
        boost::log::aux::parse_date_time_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }
};

template< typename DateT, typename CharT >
struct date_formatter_generator_traits_impl
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Value type
    typedef DateT value_type;

    //! Formatter function
    typedef boost::log::aux::light_function< void (stream_type&, value_type const&) > formatter_function_type;

    //! Formatter implementation
    class formatter :
        public boost::log::aux::date_time_formatter< boost::log::aux::decomposed_time_wrapper< value_type >, char_type >
    {
        BOOST_COPYABLE_AND_MOVABLE_ALT(formatter)

    private:
        // Do not change this typedef, copy-pasting the inherited class from above will break compilation with MSVC 2012 because it incorrectly binds value_type.
        typedef typename formatter::date_time_formatter_ base_type;

    public:
        typedef typename base_type::result_type result_type;
        // This typedef is needed to work around MSVC 2012 crappy name lookup. Otherwise base_type::value_type is bound instead.
        typedef typename date_formatter_generator_traits_impl< DateT, CharT >::value_type value_type;

    public:
        BOOST_DEFAULTED_FUNCTION(formatter(), {})
        formatter(formatter const& that) : base_type(static_cast< base_type const& >(that)) {}
        formatter(BOOST_RV_REF(formatter) that) { this->swap(that); }

        formatter& operator= (formatter that)
        {
            this->swap(that);
            return *this;
        }

        result_type operator() (stream_type& strm, value_type const& value) const
        {
            if (value.is_not_a_date())
                strm << "not-a-date-time";
            else if (value.is_pos_infinity())
                strm << "+infinity";
            else if (value.is_neg_infinity())
                strm << "-infinity";
            else
            {
                boost::log::aux::decomposed_time_wrapper< value_type > val(value);
                date_time_support::decompose_date(value, val);
                base_type::operator() (strm, val);
            }
        }
    };

    //! The function parses format string and constructs formatter function
    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > builder(fmt);
        boost::log::aux::parse_date_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }
};

template< typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< gregorian::date, CharT, VoidT > :
    public date_formatter_generator_traits_impl< gregorian::date, CharT >
{
};

template< typename TimeDurationT, typename CharT >
struct time_duration_formatter_generator_traits_impl
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Value type
    typedef TimeDurationT value_type;

    //! Formatter function
    typedef boost::log::aux::light_function< void (stream_type&, value_type const&) > formatter_function_type;

    //! Formatter implementation
    class formatter :
        public boost::log::aux::date_time_formatter< boost::log::aux::decomposed_time_wrapper< value_type >, char_type >
    {
        BOOST_COPYABLE_AND_MOVABLE_ALT(formatter)

    private:
        // Do not change this typedef, copy-pasting the inherited class from above will break compilation with MSVC 2012 because it incorrectly binds value_type.
        typedef typename formatter::date_time_formatter_ base_type;

    public:
        typedef typename base_type::result_type result_type;
        // This typedef is needed to work around MSVC 2012 crappy name lookup. Otherwise base_type::value_type is bound instead.
        typedef typename time_duration_formatter_generator_traits_impl< TimeDurationT, CharT >::value_type value_type;

    public:
        BOOST_DEFAULTED_FUNCTION(formatter(), {})
        formatter(formatter const& that) : base_type(static_cast< base_type const& >(that)) {}
        formatter(BOOST_RV_REF(formatter) that) { this->swap(that); }

        formatter& operator= (formatter that)
        {
            this->swap(that);
            return *this;
        }

        result_type operator() (stream_type& strm, value_type const& value) const
        {
            if (value.is_not_a_date_time())
                strm << "not-a-date-time";
            else if (value.is_pos_infinity())
                strm << "+infinity";
            else if (value.is_neg_infinity())
                strm << "-infinity";
            else
            {
                boost::log::aux::decomposed_time_wrapper< value_type > val(value);
                date_time_support::decompose_time_duration(value, val);
                base_type::operator() (strm, val);
            }
        }
    };

    //! The function parses format string and constructs formatter function
    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > builder(fmt);
        boost::log::aux::parse_time_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }
};

template< typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< posix_time::time_duration, CharT, VoidT > :
    public time_duration_formatter_generator_traits_impl< posix_time::time_duration, CharT >
{
};

template< typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< posix_time::hours, CharT, VoidT > :
    public time_duration_formatter_generator_traits_impl< posix_time::hours, CharT >
{
};

template< typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< posix_time::minutes, CharT, VoidT > :
    public time_duration_formatter_generator_traits_impl< posix_time::minutes, CharT >
{
};

template< typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< posix_time::seconds, CharT, VoidT > :
    public time_duration_formatter_generator_traits_impl< posix_time::seconds, CharT >
{
};

template< typename BaseDurationT, uint64_t FracOfSecondV, typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< date_time::subsecond_duration< BaseDurationT, FracOfSecondV >, CharT, VoidT > :
    public time_duration_formatter_generator_traits_impl< date_time::subsecond_duration< BaseDurationT, FracOfSecondV >, CharT >
{
};

template< typename DateDurationT, typename CharT >
struct date_duration_formatter_generator_traits_impl
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Formatting stream type
    typedef basic_formatting_ostream< char_type > stream_type;
    //! Value type
    typedef DateDurationT value_type;

    //! Formatter function
    typedef boost::log::aux::light_function< void (stream_type&, value_type const&) > formatter_function_type;

    //! Formatter implementation
    class formatter :
        public boost::log::aux::date_time_formatter< boost::log::aux::decomposed_time_wrapper< value_type >, char_type >
    {
        BOOST_COPYABLE_AND_MOVABLE_ALT(formatter)

    private:
        // Do not change this typedef, copy-pasting the inherited class from above will break compilation with MSVC 2012 because it incorrectly binds value_type.
        typedef typename formatter::date_time_formatter_ base_type;

    public:
        typedef typename base_type::result_type result_type;
        // This typedef is needed to work around MSVC 2012 crappy name lookup. Otherwise base_type::value_type is bound instead.
        typedef typename date_duration_formatter_generator_traits_impl< DateDurationT, CharT >::value_type value_type;

    public:
        BOOST_DEFAULTED_FUNCTION(formatter(), {})
        formatter(formatter const& that) : base_type(static_cast< base_type const& >(that)) {}
        formatter(BOOST_RV_REF(formatter) that) { this->swap(that); }

        formatter& operator= (formatter that)
        {
            this->swap(that);
            return *this;
        }

        result_type operator() (stream_type& strm, value_type const& value) const
        {
            if (value.is_not_a_date())
                strm << "not-a-date-time";
            else if (value.is_pos_infinity())
                strm << "+infinity";
            else if (value.is_neg_infinity())
                strm << "-infinity";
            else
            {
                boost::log::aux::decomposed_time_wrapper< value_type > val(value);
                date_time_support::decompose_date_duration(value, val);
                base_type::operator() (strm, val);
            }
        }
    };

    //! The function parses format string and constructs formatter function
    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > builder(fmt);
        boost::log::aux::parse_date_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }
};

template< typename CharT, typename VoidT >
struct date_time_formatter_generator_traits< gregorian::date_duration, CharT, VoidT > :
    public date_formatter_generator_traits_impl< gregorian::date_duration, CharT >
{
};

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_DATE_TIME_HPP_INCLUDED_

/* date_time.hpp
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
*/