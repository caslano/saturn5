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