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