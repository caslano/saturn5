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