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
/VbH9sssL32BZpglakxj/+GF79ccuqzfSi1hc/mGKZpojOZtp72nXKbtYQpGDEwD8gGOfVb+lvbqDfieJbul31H/3kfYNcfghA+H8yzFHvsw2HhgI+2BB87dBkawu/t+Gkjds5/9+WD2b+Phy6WEDtpo/6jt317M9pEK5Kpb4BtVz7ZVzVHfJKA8MYD8sQbHrWb73cT6fQOxXhqtht8BfOwptg82q6O/Y12+Sv3bjthjA+B8xxTZdJKfpv4ROSeRys+iltOZxP6t8+9Y3iepf6yokxz/nbec9Kh/15CD7ayoXLaF64uozyzqfcPg+4iML6VF6rkIjp7CfovV08CePXcW20cZ+WPE5O5sv/3g/Jzyu+k4wnZSlS9gw6mgr3QfxwcU5+dXI3YXW8qwsWwfvckfLc195O9oN/gmD+P4lM7PB0oB/mKfhjM2FM4TlP2fOYxPodKspQo8uor9EXV3dQoN7VbgDWfETOLlkfG7WN4x7BZ7EO95yvmVkdRnNohaRiw4yvaWwv6NadO/BxhPGcxiD3uSlnAVq2xzBfvzI3B+RpW6dx6c/dXAS55L/TOyfbBtLWTz+56W66d/RuyFbFZD/FR0Ks1zjPCw8t7+FQ0e663PXYjIS4fTk+DUh+BUjAXY9TfwjaNeDaaELplN/eOg48gy6gvF2eUgnGtJasY7iH2DYceeZn1UkDzDnklEWAZLPmAF7elGznHq4HxMszk+mfpHXbuRQtxIcB0rdEUPOEspnKq57I+o6NdfBGdBGYhWUEwD2CRTOOH44jPqH0Vy5eDg+CqXpCbQNm37AL7IF4Q94PiKrOWxWDWz4dtLZ94Yjl/m0J7GwXmSEv+arfa1OtoXWp/f92H7oMIlLWP/NgZgwfe0B8cov4/hzPmM9v5LtrciODeMhzOOlNcOZXv7I5zf3g1wJaU790rOP9jPdP8Kvs1p1JfZLEwefHkchiZUwXmGXW/oZjgvlLN/Yzdx+VG2jy0sbyr1mRXq3gLnIlZjI/vzOPI37gjt6Tccn8bSnlpo72kZilnTpXs5HmftP0lb8ihjf0V2p7zL8SnNcD5iA+2Dc4gscjr0HupzEucLNLR9fwUn6gnq30T2b5Rz5gk4RW+yfcyEs3oBwLdqWb+0INueBN637LLu+or2r4LzI+Z7PfVqKvPoTXAAxbmPGWVeCWdxFeX3FCJMBB/bRfnVwje6HwdA7DoKaBTG0Oq9Mw6OdBjgXnbMFczy7mtoX3bD+Zyxj5LyazRVQ+awvDLLy3w998B5nCkWRXN80IX2j07sHvYfZOPmr0jvDdbvYNbHvQAfPYmIO9hqGybAuZFS++B1+LYpcMrmsb+U4Rzby/EuO4dDjH3gJHzzELHj3HPuOfece849555zz7nn3HPuOfece849555zz7nnjJ7cPGVWnCVxb/kBV8j0xJqp9VabsjAu0qauxfqkcsgh25RQz8i4ONUD2O+Mi8+D00+d/6Xfr6j0D1Kz9/v97s2x7iNh8pKDPNYUV/7JAMlSfkBe9iFAJcNUXuO8WDfbnJRhnncekkT7M4yefLMaojKhsZpHTJr0iTVJ+Ra54lkA5TVy+eN4Z/t7zCkNsSgTLEAzTIhMrpUrliI8SCMjUq39XNDItanXgUH3ZpOypSB/+tR6R7hN3blFhCBueNu4Tjb1pea4S9rGmW3qSi3uFfIFBF0HhNuB8IoesRqF/VtaIxQu/yJBsrwJCZThZ8fvYfzeDPxq8dvxL3xOW7/vbW5bv09tbl2/mz9qqd85HwTq1yQvkXVa/SZq9Svpfqx+L/vsFPX7WqB+t5ymfn/btn4/+jRYvz/f3L4OD9UH6zB/c/u6f7s5Ln1z++qrrm8=
*/