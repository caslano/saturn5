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
10H2z52zafzShSdNoj6EvgIqNfApl/Vgu8Bv7sN8Zdcb3ePkmWbktlQFMqEn2erzgqbRgQe+282WtVGWSqzSyx+ZO87NZ3rzsh61AzIqJu71SX7ZKn9zf9R2Pg2tbB1vYL0e+K21Tj3pvhS2ZT0Fv9/N5MepgaMzVazWg79v/Ry+sv+A5Uid0vNSiQ2I4DN5m2U95tz1Qt/O5kjsTB7b+ugboQHwb8yQBL9L9aT76JUXYFUK+RniSev1bbUe9dCN8Oq9vGtqn0fFr54I3Qc9wty3jW7tNgadRLCITLgAO0/5sdRv4Hx3QXy/+CPPE94p+uJu815tv1O9evwA6Ib7o6jHOh6ivmql6kb4lrEr5jn3q/XoTCkVZTD9bulf6HVe+GofdGugwmy9+pRvu9F5g4flWVHkl/RieT4O0RK1C25AG+4WSNcrphNqxIGKi/XWfcYXz7lXfIWGCv1B9Wo9mAS7eX/jnO9XOjmu8Jwpw870DKlRDwl+Cpa8U86Kov8Yrn94xg0YszmV5t4zUww1n2W9PGAj7ZR1bIVxOd/H3htNhs/TKo+DX5St9gdivAlXfbENwxwLkCOCIYF+NLJ+MDw5bel6xr04YehS7PV+bZ8r2WzPAQKnoko6rD4vEzHJtWHoEpNwPwbFf6OsN/2Djnfy2AsPT9fbh1mt8B3d9Yu9It4d5swG9gHcv73ypfR+0NW3F14Gw9mV1m1Y
*/