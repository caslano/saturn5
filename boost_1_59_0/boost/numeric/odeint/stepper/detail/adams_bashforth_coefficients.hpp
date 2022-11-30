/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/adams_bashforth_coefficients.hpp

 [begin_description]
 Definition of the coefficients for the Adams-Bashforth method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_BASHFORTH_COEFFICIENTS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_BASHFORTH_COEFFICIENTS_HPP_INCLUDED

#include <boost/array.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< class Value , size_t Steps >
class adams_bashforth_coefficients ;

template< class Value >
class adams_bashforth_coefficients< Value , 1 > : public boost::array< Value , 1 >
{
public:
    adams_bashforth_coefficients( void )
    : boost::array< Value , 1 >()
      {
        (*this)[0] = static_cast< Value >( 1 );
      }
};


template< class Value >
class adams_bashforth_coefficients< Value , 2 > : public boost::array< Value , 2 >
{
public:
    adams_bashforth_coefficients( void )
    : boost::array< Value , 2 >()
      {
        (*this)[0] = static_cast< Value >( 3 ) / static_cast< Value >( 2 );
        (*this)[1] = -static_cast< Value >( 1 ) / static_cast< Value >( 2 );
      }
};


template< class Value >
class adams_bashforth_coefficients< Value , 3 > : public boost::array< Value , 3 >
{
public:
    adams_bashforth_coefficients( void )
    : boost::array< Value , 3 >()
      {
        (*this)[0] = static_cast< Value >( 23 ) / static_cast< Value >( 12 );
        (*this)[1] = -static_cast< Value >( 4 ) / static_cast< Value >( 3 );
        (*this)[2] = static_cast< Value >( 5 ) / static_cast< Value >( 12 );
      }
};


template< class Value >
class adams_bashforth_coefficients< Value , 4 > : public boost::array< Value , 4 >
{
public:
    adams_bashforth_coefficients( void )
    : boost::array< Value , 4 >()
      {
        (*this)[0] = static_cast< Value >( 55 ) / static_cast< Value >( 24 );
        (*this)[1] = -static_cast< Value >( 59 ) / static_cast< Value >( 24 );
        (*this)[2] = static_cast< Value >( 37 ) / static_cast< Value >( 24 );
        (*this)[3] = -static_cast< Value >( 3 ) / static_cast< Value >( 8 );
      }
};


template< class Value >
class adams_bashforth_coefficients< Value , 5 > : public boost::array< Value , 5 >
{
public:
    adams_bashforth_coefficients( void )
    : boost::array< Value , 5 >()
      {
        (*this)[0] = static_cast< Value >( 1901 ) / static_cast< Value >( 720 );
        (*this)[1] = -static_cast< Value >( 1387 ) / static_cast< Value >( 360 );
        (*this)[2] = static_cast< Value >( 109 ) / static_cast< Value >( 30 );
        (*this)[3] = -static_cast< Value >( 637 ) / static_cast< Value >( 360 );
        (*this)[4] = static_cast< Value >( 251 ) / static_cast< Value >( 720 );
      }
};


template< class Value >
class adams_bashforth_coefficients< Value , 6 > : public boost::array< Value , 6 >
{
public:
    adams_bashforth_coefficients( void )
    : boost::array< Value , 6 >()
      {
        (*this)[0] = static_cast< Value >( 4277 ) / static_cast< Value >( 1440 );
        (*this)[1] = -static_cast< Value >( 2641 ) / static_cast< Value >( 480 );
        (*this)[2] = static_cast< Value >( 4991 ) / static_cast< Value >( 720 );
        (*this)[3] = -static_cast< Value >( 3649 ) / static_cast< Value >( 720 );
        (*this)[4] = static_cast< Value >( 959 ) / static_cast< Value >( 480 );
        (*this)[5] = -static_cast< Value >( 95 ) / static_cast< Value >( 288 );
      }
};


template< class Value >
class adams_bashforth_coefficients< Value , 7 > : public boost::array< Value , 7 >
{
public:
    adams_bashforth_coefficients( void )
    : boost::array< Value , 7 >()
      {
        (*this)[0] = static_cast< Value >( 198721 ) / static_cast< Value >( 60480 );
        (*this)[1] = -static_cast< Value >( 18637 ) / static_cast< Value >( 2520 );
        (*this)[2] = static_cast< Value >( 235183 ) / static_cast< Value >( 20160 );
        (*this)[3] = -static_cast< Value >( 10754 ) / static_cast< Value >( 945 );
        (*this)[4] = static_cast< Value >( 135713 ) / static_cast< Value >( 20160 );
        (*this)[5] = -static_cast< Value >( 5603 ) / static_cast< Value >( 2520 );
        (*this)[6] = static_cast< Value >( 19087 ) / static_cast< Value >( 60480 );
      }
};


template< class Value >
class adams_bashforth_coefficients< Value , 8 > : public boost::array< Value , 8 >
{
public:
    adams_bashforth_coefficients( void )
    : boost::array< Value , 8 >()
      {
        (*this)[0] = static_cast< Value >( 16083 ) / static_cast< Value >( 4480 );
        (*this)[1] = -static_cast< Value >( 1152169 ) / static_cast< Value >( 120960 );
        (*this)[2] = static_cast< Value >( 242653 ) / static_cast< Value >( 13440 );
        (*this)[3] = -static_cast< Value >( 296053 ) / static_cast< Value >( 13440 );
        (*this)[4] = static_cast< Value >( 2102243 ) / static_cast< Value >( 120960 );
        (*this)[5] = -static_cast< Value >( 115747 ) / static_cast< Value >( 13440 );
        (*this)[6] = static_cast< Value >( 32863 ) / static_cast< Value >( 13440 );
        (*this)[7] = -static_cast< Value >( 5257 ) / static_cast< Value >( 17280 );
      }
};







} // detail
} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_BASHFORTH_COEFFICIENTS_HPP_INCLUDED

/* adams_bashforth_coefficients.hpp
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
*/