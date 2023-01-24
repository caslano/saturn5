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
bbw2RoFLTps/m1cR8VDreR62FsgmP5DKtIzzOjGJzFCg/hEml/2VHQFPl85dBpq48H3AYxnCRiFE/FT8TJwgLhV3A7cTpRQ4jt2I4GeSn1xNXiavgc84I0crnymTlVXogevI5bJQuq3VPmo+vF+WflEPN4YZ6cYu4ydjI3yDtdbpYX8nuROpSnQSTQaRr8hq9H0xOhhqaRicUDp7hP2TqwDOHgzc+gU8EwFk8gGDFJXCENWWDgqHLhsFHVRTbay2U4erOeoV9Tc1Wluprde2abu1H7WftHT9hO5nVAC/DrbrFDxtDVKM1CMcGUrGk8XkE3DBVqabcEjYJtaQ6knHZcmu516hrIFbqq8JWrYh2lrD09YaIh2PPODg2FqyA9mpuM7L7ADuS8TIY2DwDzwn9BA+E5KEL4XdwvfCCWGoqEpNECEnlXpAtkhg2krV0MKBXAe061qanmAMMm5Bx9s3wwV62jXRNcly9MVOqPV05gLzGAqwolhTbAn/M0Q8KWZILZTrappWB560rBlk6wRPG8vCoD+tOoBP6a6IqHv0S8aZ/Zltzc3g/HkChh4lTBRaia/EsmodaLiB6ga1BnL/rT7RrifwtDXWIvKYTKBPcnlcCTC95e8c27exe+HDj0MV5NozMFSKp11/0FTuDVU2CYq5QP5TLq1UV1ilg7W2mOZpf/fRfmttJN3xdxt7zdHxdx9rILIdf9tjk+Np
*/