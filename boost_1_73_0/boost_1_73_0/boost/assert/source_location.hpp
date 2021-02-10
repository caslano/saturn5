#ifndef BOOST_ASSERT_SOURCE_LOCATION_HPP_INCLUDED
#define BOOST_ASSERT_SOURCE_LOCATION_HPP_INCLUDED

//  http://www.boost.org/libs/assert
//
//  Copyright 2019 Peter Dimov
//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/current_function.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <iosfwd>

namespace boost
{

struct source_location
{
private:

    char const * file_;
    char const * function_;
    boost::uint_least32_t line_;
    boost::uint_least32_t column_;

public:

    BOOST_CONSTEXPR source_location() BOOST_NOEXCEPT: file_( "(unknown)" ), function_( "(unknown)" ), line_( 0 ), column_( 0 )
    {
    }

    BOOST_CONSTEXPR source_location( char const * file, boost::uint_least32_t ln, char const * function, boost::uint_least32_t col = 0 ) BOOST_NOEXCEPT: file_( file ), function_( function ), line_( ln ), column_( col )
    {
    }

    BOOST_CONSTEXPR char const * file_name() const BOOST_NOEXCEPT
    {
        return file_;
    }

    BOOST_CONSTEXPR char const * function_name() const BOOST_NOEXCEPT
    {
        return function_;
    }

    BOOST_CONSTEXPR boost::uint_least32_t line() const BOOST_NOEXCEPT
    {
        return line_;
    }

    BOOST_CONSTEXPR boost::uint_least32_t column() const BOOST_NOEXCEPT
    {
        return column_;
    }
};

template<class E, class T> std::basic_ostream<E, T> & operator<<( std::basic_ostream<E, T> & os, source_location const & loc )
{
    os.width( 0 );

    if( loc.line() == 0 )
    {
        os << "(unknown source location)";
    }
    else
    {
        os << loc.file_name() << ':' << loc.line();

        if( loc.column() )
        {
            os << ':' << loc.column();
        }

        os << ": in function '" << loc.function_name() << '\'';
    }

    return os;
}

} // namespace boost

#if defined( BOOST_DISABLE_CURRENT_LOCATION )

#  define BOOST_CURRENT_LOCATION ::boost::source_location()

#else

#  define BOOST_CURRENT_LOCATION ::boost::source_location(__FILE__, __LINE__, BOOST_CURRENT_FUNCTION)

#endif

#endif // #ifndef BOOST_ASSERT_SOURCE_LOCATION_HPP_INCLUDED

/* source_location.hpp
JGBNkM1OwzAQhO9+irkBB4cWDki5VUgIpFZEJC/gxus2wvUGe9Mqb4/dH8R1dvbbnVlz2NVIyat38mONLs5o2/Vjt25VE1m4Z59qvHUNPjarBs1n84x20zVqZS3ZGi/V06JaqFcjtOM41xCflNZaqYISxpToRoTjCNkTeg6Behk4VMAXHSlKKl6DwEEn6qf434TBqbKWKGYrLFMKd4I0jSNHudEzqiWC8YmhtZNR51g6UySyhwk2q0WJ9GNV+cQOzlGkIPD5BZ/ADhT6OI/no9k3DZFslaPshzy9yCeTSo4DRT/jO/ApICt/B3F/LgZDyNUsl9XioUK3N3JdV8EccjQTkGTwHlsqBVlsJ8HpKkQ68PGCMHCTlDJy7lTqUr9QSwMECgAAAAgALWdKUqplUdHrAAAAVgEAACUACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9zc2x2Mi5kVVQFAAG2SCRgNZBNa8MwDIbv+hU6bocEmkEHvo1C6SGDUXe7Z4lIDI6VWXKy/vs5yXrRF8/7SsgOHNVgBTWH3qCInyu4Nb0Y/KIojoPAR2Tlln2eWVvDW9dRZ+A9Kf3mYtO8oHqZD3ssH7mCK/0kFykrb7UFS1Q0XtjgoDqt3JoruJCfDH4Krf55
*/