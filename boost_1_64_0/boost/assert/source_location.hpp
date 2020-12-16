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
AxbDVsDucchWLF9FxUHOgVXlrCQwE3YyrLvMdRhMBs+BDrnrKn4HtMX5YIfB5sDOhl3O8tgu2MOwZ1g2M8XjGmG1MlqxRk5bFF9ZViuDXwXsLliH3HYYv9NAocpqsI1htXLcbNjlrvKclOUOwH0a9iKstZ1TtksCB8BOhl1VhZwX3B7vEjYONhl2LGwhbGYqwoOrYDdABtwFe1aXBXWjm/8oU03yPwKr4v+v1/3PjxFSDtvOc/+NihC1maq8faCrR3k7PX3ADHVogDeZm+PdhW9xhDd5i8MUiNaiVSU5i+VpDtNQhLOe5Ty5/yoS1ZFhsO4yl2Pc3NcU7oyIQ4vrMCzL2pxefVeZisexje6mHisRv3GVxaU+9yLFPYU0LWibWJGuxUUGD+WxD0mUzsOI2VzKpZvIz5fHRyhiG7n9XGSkPqGq/ffK46Usjy9jeXwRy+PR3T3L45wTvMnjHC9MNIR7KNwJ5C5QGuP57cIZfoK9TQkQPZRAb/0wnEawaMjjCOPIPVVphjR2q1eJuBFIoxfoRV7nNGYr8Qi/RjyGew91zzuUfp4MO12JRj5RRzOYoP+OQfqpoHe5neN5kdsjWXZeQGE+Fza0tjcin70uQlzyWhDL977Jdj17PZbfF1O8C2IG7nkh/LeCe4XZRYaPZBl+OoU9IybiqspgD4kAOa5mPqVr1pxzkgjicfV7u3NZI7cidtrfOXJtF4QKFZHIq2Ypz+tyvS7Xe5frB5Ncv2bbuvVnx+f/6f71sz87fPzbu/835PoKx7cLNLL8qtZTG9zk6nCwOetMU8HaLK+2B0eznP0b1pFOZh1pKcvZy1jOXsU60jKWs59l+fpPrCN9jeXrvSxfnwLbgV/xeX4GW7DcHS3rNtTvfN0N8LsmKFinGgZ24+vvzrrBZJa/c0D4iRS+/r5gIdgPnMnuUpa7HwCH8nWng5vY/Rx4B7id5esPWI4+yXL0KT7PGZazvwTHgN9wuNtYro5Q7OHqgtlgDDgebMP+7cBBIOpmijeS42Xy8WzWEc8He4GL2H+YLq/r8vpNlNfHHjeJpcd1WV03uvlfN9Ul/+dNLLgp+v+5MUK0ZrnvKuvbVZ1pFNgdjESDIriDQ+6j82pltLsLbXZ5O1Q4wm2FbtEsZvMY5VD4HCZ/o2becT7rGh1xtlCcqaIhyyiOOFaeo0dxstDoZ7nEEW8jxSsVYSy/OOOFSlkUl0xDsnncJsfVjvPsRO6mSqh6LkccnMxtzD/H4zX/K897kONA21G4VoqcA+AWF3qHSuPFHXPtWneka2FZmubD5RcWOceQ9qF06ihIh+aZhst0eHY3PSUhZci6lF5L13BTcmw5HM4x76+c0t0sDKIRXSOumeefauKo6fIYhmQKX1upB3nQh+XBeTHIN03tvy80Q7syxC4TJgs2XsZOx3WUY0jdZDrKXzRWNFfKg/lyv4PpFIbzBfxKpGwp3zn5l6ph2V++V/gv9TBONVGmYX/ukfCLk9fDz0E+404hE+g5oP2d4DrP9xj3oQzmdTT7wdZDmJ0dZVmagSk0EyAOVSpPPI6Gw/bTlhsuH/KYe/ngciCP8zvkPD1u+gRZDmSYJIThNDznew7He2h4yvfcr/MBhUsUMt+7xS3R7JMxNeb698lwzwsZbnlhrHtecMkvzvsOl/mmcl4o0eYFfref0rXjPuS7rWEfr8JrLdTDwQjQF2ydgHCJ9G7tmSSrcNL4Ivt4pNkhruuf9lMcYevIct2f3Aaqg4p9ODzdjXM+1UQK8zHnAUcaHT3mn1x5PMk1/3D5zaFjn3FecIRt556fNPmAw/C7rOB84BspYPAs8Z/rJMpP4+yryWZPy863FdumuYylKQg=
*/