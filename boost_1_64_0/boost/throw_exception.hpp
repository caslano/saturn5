#ifndef BOOST_THROW_EXCEPTION_HPP_INCLUDED
#define BOOST_THROW_EXCEPTION_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/throw_exception.hpp
//
//  Copyright (c) 2002, 2018, 2019 Peter Dimov
//  Copyright (c) 2008-2009 Emil Dotchevski and Reverge Studios, Inc.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  http://www.boost.org/libs/throw_exception
//

#include <boost/assert/source_location.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <exception>

#if !defined( BOOST_EXCEPTION_DISABLE ) && defined( __BORLANDC__ ) && BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x593) )
# define BOOST_EXCEPTION_DISABLE
#endif

namespace boost
{

// All boost exceptions are required to derive from std::exception,
// to ensure compatibility with BOOST_NO_EXCEPTIONS.

inline void throw_exception_assert_compatibility( std::exception const & ) {}

} // namespace boost

#if defined( BOOST_NO_EXCEPTIONS )

namespace boost
{

BOOST_NORETURN void throw_exception( std::exception const & e ); // user defined
BOOST_NORETURN void throw_exception( std::exception const & e, boost::source_location const & loc ); // user defined

} // namespace boost

#elif defined( BOOST_EXCEPTION_DISABLE )

namespace boost
{

template<class E> BOOST_NORETURN void throw_exception( E const & e )
{
    throw_exception_assert_compatibility( e );
    throw e;
}

template<class E> BOOST_NORETURN void throw_exception( E const & e, boost::source_location const & )
{
    throw_exception_assert_compatibility( e );
    throw e;
}

} // namespace boost

#else // !defined( BOOST_NO_EXCEPTIONS ) && !defined( BOOST_EXCEPTION_DISABLE )

#include <boost/exception/exception.hpp>

namespace boost
{

// boost::wrapexcept<E>

namespace detail
{

typedef char (&wrapexcept_s1)[ 1 ];
typedef char (&wrapexcept_s2)[ 2 ];

template<class T> wrapexcept_s1 wrapexcept_is_convertible( T* );
template<class T> wrapexcept_s2 wrapexcept_is_convertible( void* );

template<class E, class B, int I = sizeof( wrapexcept_is_convertible<B>( static_cast< E* >( 0 ) ) ) > struct wrapexcept_add_base;

template<class E, class B> struct wrapexcept_add_base<E, B, 1>
{
    struct type {};
};

template<class E, class B> struct wrapexcept_add_base<E, B, 2>
{
    typedef B type;
};

} // namespace detail

template<class E> struct BOOST_SYMBOL_VISIBLE wrapexcept:
    public detail::wrapexcept_add_base<E, boost::exception_detail::clone_base>::type,
    public E,
    public detail::wrapexcept_add_base<E, boost::exception>::type
{
private:

    struct deleter
    {
        wrapexcept * p_;
        ~deleter() { delete p_; }
    };

private:

    void copy_from( void const* )
    {
    }

    void copy_from( boost::exception const* p )
    {
        static_cast<boost::exception&>( *this ) = *p;
    }

public:

    explicit wrapexcept( E const & e ): E( e )
    {
        copy_from( &e );
    }

    explicit wrapexcept( E const & e, boost::source_location const & loc ): E( e )
    {
        copy_from( &e );

        set_info( *this, throw_file( loc.file_name() ) );
        set_info( *this, throw_line( loc.line() ) );
        set_info( *this, throw_function( loc.function_name() ) );
    }

    virtual boost::exception_detail::clone_base const * clone() const
    {
        wrapexcept * p = new wrapexcept( *this );
        deleter del = { p };

        boost::exception_detail::copy_boost_exception( p, this );

        del.p_ = 0;
        return p;
    }

    virtual void rethrow() const
    {
        throw *this;
    }
};

// boost::throw_exception

template<class E> BOOST_NORETURN void throw_exception( E const & e )
{
    throw_exception_assert_compatibility( e );
    throw wrapexcept<E>( e );
}

template<class E> BOOST_NORETURN void throw_exception( E const & e, boost::source_location const & loc )
{
    throw_exception_assert_compatibility( e );
    throw wrapexcept<E>( e, loc );
}

} // namespace boost

#endif

// BOOST_THROW_EXCEPTION

#define BOOST_THROW_EXCEPTION(x) ::boost::throw_exception(x, BOOST_CURRENT_LOCATION)

#endif // #ifndef BOOST_THROW_EXCEPTION_HPP_INCLUDED

/* throw_exception.hpp
AvBtfJ+D78vM75GM4SR+TpZcFd/H7j2gRparPVd6m6AgRJDfEI7AJUyBG63AAHP7QVKaxgu8BzquH1gktWToRqI4PsEmdOhw7c5cnuWoub6Ic3FltTM5l4H9BOeSTQXNR0Ee3NqTF7zZyaVNjSPuB7MXy/14IiXoblZbUQZqwn0dVmJu1Apqx8q8UF8nnzJ/BAGlmGbawsflkun40tyMj9AeXAlg6eNY0NDuyijxJQHisCWF3YavMvn1Ihiv8my3jcblH5Jx5MuSpj5fHANrniaxEDCfTzDI4dQQ42ZefFxso930RnETxu/wBd+V0EC64qZGxgXTXNpK3DIw9keHZXEjxrjwJa0XbUHXyAs+S6hp3PC1/jnOLzxkJ97zsLeR3uAARq/c7ZSWHV4FFwcRRbZXJapqNA1wHOpCLElEPuPYMRS7007Nuk00qxTxJK3fyO4oCY9OpjOkRy01/D0QEom97sCjLcvjU3gaoxs+EipVdFIuBgFIT8HVDBJzq8PX6tuJEadxvOrHSIQGyTRTWyXvzUY7hKz+AX0IuFMgycq3jgo/CpPj2JeFaHATVYxjJ7skJCr7YsWbxTUR8xPuaxQX1huhuMrhKIvSByGdMlOmZWamisruR2MKyRGFvBxN1ytAvzNoVZ4pS+qJTOG3zW/OF99MML/ZWfndkf87h/zf/En6d4+k1zzOXK0UsHtxHNHcb1aflAKGPBjUwHrg9Hz/FmvtTI4lpX69a1ns+UNwCc4fYt7PpfdfKj/JRf2LLExQxI1UChtmOwpJ9VLSWxzNZIAXREEf2pw5k1dfFmcpk2kzHIWVhDUWW+Ipf7KCzqjIVupV6RuXYwkEjP2Y4LH72jmWFCsgmho6lihWCjRBI+UmxTm8XzmWYC8aQImqw72ucjrK/lO2d5CsnzNRmUyYXCCK83assqZ7G8dm8fWLfWPi5mPHkji0RJa8Ajx2uOOfQLZQRgV7RvaMrfaqzWorMDDFcaD+wkl/svvORBFmR2e1AQZC138xuX/Sn7T/3MXwRHdbQbqVq1nJY1UbwAoh+O45hMhXCJ+2C7E1smoHErqKBHqtnIv44823sogoOEPeFYf5aphdVXKigdiM6VxOBFxpGFvtieRdVD7KrE1R8lzEUJR1FmOe/+2MykuefT22Jy7MIQrCyMhqFAOmigmm0H4EmiBHtEaFYSpZDVFiBWb+RO13ISf14Vjg8Z0tIa05QdrW2GTvx9QXs4blRg318i/OrJ9wL54drpYH9Nhl2IxT3OgKKvOZL6WiJXQB+ZiNfEdL5S9W58+yeZvxfMau/Oysc8XKz5WOxiPFuUQKY5uGFoLwNp71k5TZtyNn7++Sd29lUQMmAWk5z8YFSnQvXe7wg1jV/bAOx4DOpOWHBBdFMal5qWNJCQ3OJXhL9zbCtUxEjlbFQ1ra3gMSyI63yFIl0DDRE1kmizS/9pY6lthEdShD1O67D1+EZwLsir03iBpL8B2XeDHCcrpzeLo7IINjgS2y1KPlclVKIL6xUdHl9qp41e5diTqQl6ohG5eOWMfIWEnrGShgsospaH9ZXB+ilB2Fc8mYbEb1BN8Z3Pw3GonWV34PkgDxtxvxyTJ+tYj/vRFvl/ELEM8xSPRiaVUoDtdymfY00v6EujJR14zDHRyFN2PwqR24e9IKPq/XVF+yG0TiNA/4pjN6dfalKItIBYpebVDDQHGWXOJDqke6Clv3AYYGvS9ZN47x7Z9xWQ9fzxnTwZZcvCwJmbcjOU71l8eRp788bS0BWg82UeQvFEKh5veKbz+G/bJcbQ++dWP9N3T3POwopAMC5PBofE/XfCYf90K91GvXUBqGvoM7MM3C50/EYtIZx4Y=
*/