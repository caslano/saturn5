/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/adams_moulton_coefficients.hpp

 [begin_description]
 Coefficients for the Adams Moulton method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_COEFFICIENTS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_COEFFICIENTS_HPP_INCLUDED


#include <boost/array.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< class Value , size_t Steps >
class adams_moulton_coefficients ;

template< class Value >
class adams_moulton_coefficients< Value , 1 > : public boost::array< Value , 1 >
{
public:
    adams_moulton_coefficients( void )
    : boost::array< Value , 1 >()
      {
        (*this)[0] = static_cast< Value >( 1 );
      }
};


template< class Value >
class adams_moulton_coefficients< Value , 2 > : public boost::array< Value , 2 >
{
public:
    adams_moulton_coefficients( void )
    : boost::array< Value , 2 >()
      {
        (*this)[0] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
        (*this)[1] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
      }
};


template< class Value >
class adams_moulton_coefficients< Value , 3 > : public boost::array< Value , 3 >
{
public:
    adams_moulton_coefficients( void )
    : boost::array< Value , 3 >()
      {
        (*this)[0] = static_cast< Value >( 5 ) / static_cast< Value >( 12 );
        (*this)[1] = static_cast< Value >( 2 ) / static_cast< Value >( 3 );
        (*this)[2] = -static_cast< Value >( 1 ) / static_cast< Value >( 12 );
      }
};


template< class Value >
class adams_moulton_coefficients< Value , 4 > : public boost::array< Value , 4 >
{
public:
    adams_moulton_coefficients( void )
    : boost::array< Value , 4 >()
      {
        (*this)[0] = static_cast< Value >( 3 ) / static_cast< Value >( 8 );
        (*this)[1] = static_cast< Value >( 19 ) / static_cast< Value >( 24 );
        (*this)[2] = -static_cast< Value >( 5 ) / static_cast< Value >( 24 );
        (*this)[3] = static_cast< Value >( 1 ) / static_cast< Value >( 24 );
      }
};


template< class Value >
class adams_moulton_coefficients< Value , 5 > : public boost::array< Value , 5 >
{
public:
    adams_moulton_coefficients( void )
    : boost::array< Value , 5 >()
      {
        (*this)[0] = static_cast< Value >( 251 ) / static_cast< Value >( 720 );
        (*this)[1] = static_cast< Value >( 323 ) / static_cast< Value >( 360 );
        (*this)[2] = -static_cast< Value >( 11 ) / static_cast< Value >( 30 );
        (*this)[3] = static_cast< Value >( 53 ) / static_cast< Value >( 360 );
        (*this)[4] = -static_cast< Value >( 19 ) / static_cast< Value >( 720 );
      }
};


template< class Value >
class adams_moulton_coefficients< Value , 6 > : public boost::array< Value , 6 >
{
public:
    adams_moulton_coefficients( void )
    : boost::array< Value , 6 >()
      {
        (*this)[0] = static_cast< Value >( 95 ) / static_cast< Value >( 288 );
        (*this)[1] = static_cast< Value >( 1427 ) / static_cast< Value >( 1440 );
        (*this)[2] = -static_cast< Value >( 133 ) / static_cast< Value >( 240 );
        (*this)[3] = static_cast< Value >( 241 ) / static_cast< Value >( 720 );
        (*this)[4] = -static_cast< Value >( 173 ) / static_cast< Value >( 1440 );
        (*this)[5] = static_cast< Value >( 3 ) / static_cast< Value >( 160 );
      }
};

template< class Value >
class adams_moulton_coefficients< Value , 7 > : public boost::array< Value , 7 >
{
public:
    adams_moulton_coefficients( void )
    : boost::array< Value , 7 >()
      {
        (*this)[0] = static_cast< Value >( 19087 ) / static_cast< Value >( 60480 );
        (*this)[1] = static_cast< Value >( 2713 ) / static_cast< Value >( 2520 );
        (*this)[2] = -static_cast< Value >( 15487 ) / static_cast< Value >( 20160 );
        (*this)[3] = static_cast< Value >( 586 ) / static_cast< Value >( 945 );
        (*this)[4] = -static_cast< Value >( 6737 ) / static_cast< Value >( 20160 );
        (*this)[5] = static_cast< Value >( 263 ) / static_cast< Value >( 2520 );
        (*this)[6] = -static_cast< Value >( 863 ) / static_cast< Value >( 60480 );
      }
};


template< class Value >
class adams_moulton_coefficients< Value , 8 > : public boost::array< Value , 8 >
{
public:
    adams_moulton_coefficients( void )
    : boost::array< Value , 8 >()
      {
        (*this)[0] = static_cast< Value >( 5257 ) / static_cast< Value >( 17280 );
        (*this)[1] = static_cast< Value >( 139849 ) / static_cast< Value >( 120960 );
        (*this)[2] = -static_cast< Value >( 4511 ) / static_cast< Value >( 4480 );
        (*this)[3] = static_cast< Value >( 123133 ) / static_cast< Value >( 120960 );
        (*this)[4] = -static_cast< Value >( 88547 ) / static_cast< Value >( 120960 );
        (*this)[5] = static_cast< Value >( 1537 ) / static_cast< Value >( 4480 );
        (*this)[6] = -static_cast< Value >( 11351 ) / static_cast< Value >( 120960 );
        (*this)[7] = static_cast< Value >( 275 ) / static_cast< Value >( 24192 );
      }
};







} // detail
} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_COEFFICIENTS_HPP_INCLUDED

/* adams_moulton_coefficients.hpp
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
*/