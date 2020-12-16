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
k80zDfX5tNZCQduMcUqZySRmJmWSiYWELg20qfM1SWaru9ZCkmGo7csk3NoZJmEX3hlp/wCk7dNGGy12A3yN74SRuymSVS6/R2Kxqil+yP5q+ydBTEeaPZ+DFExd1wqjCZbzp7Zi+v69zUzbpVTWeMPaYDNPQVsDYP+iI7W5Aim6PbXRLdQ8t09RMqfkOSTFbvTMikvw98AFEIvIIy9XvWatpirm8sPystsw/sQAcaQyLS4LYo+hDeNYv3B5KYeji+Qlr4QiBETcJzvLS38JQMmcA+Xr4b/daXN0zrNLgYGYfyeUBCTLfhrKkf8oyTvBD0qx3jxd+Ta5bJwI1Y/mmDpKLr8C4LCTEsLKO8PrPqqTFx/CSHu0+6hJXvwZfN/Ixel6d6PJXRdeKL8LFj2T4+LcR/Xy4oYQkhrobtTLa9J17jp97WemiEPJr8uLnwsJlOYLw7vgOQ5JEsowBV2M8LJP5PKf400W80MCLFo1Fsfr3McM8uJMEXyF+wuDvCZNV/upKUKFRy887mPIubdAuM3g/kKPCKPI1+OMGyJSd9IiQ7TkoSISnrAgVoLA+pNRYJk0rE5BrHCtDO/Ki+uAoMl+HqxYUxdvWoTyAbhkh6qp7cPA6PuuXL4Sb4pTJ5ffoXmH6OUl18GbhHLL5SnwJX8nLxnEOp44BwYqCpXmzTDbsv1gBw128CT/mxwNH0fZcHhMm9w16f8g+clkOMVb+5EpogGTNiWh9KRYBNgqj9xSepReeeRryQ3zzGRWh3rM0YOH47Hy4gcN8NRdIuqrKVYuW2oQ1LzpurHJe+TFdwI01HIpou8euexWEWkam8qon5KHnX33iOhoMHyxsiSSmaYuZMF3IIecSTZqmhlwebpeUz223+rdgfbb7SWo96y4FE3dudChjn9JdBDBpu4Non7+e6AyA2HcU+czjw2g6R0Xl5IDJzunOa+yx/VCtVKG+am0S+4FmO0dGZed7R11Xraqvg1js3PrqM6GyjyLsr220YJkleO71KqmylGyb1RXCc/WUT2kyvFR3jHmyrxoNIvKUT23jpKiINzSIRShK6zQpz/pbzIrYbVHTJX6qrDKdJ1CzU/X45XlSQ9VaklxTIS7tnNlejhaomdcXNwpWqNOtEb1OhbwEDX+bYRbEdGfhl49+KLoz8prirsysB8nfuoeLdCq9mEqyM2aJ8Jf0cKTt8pLcaKQMZFC6BFW9YkgHXlZrsi4taXh2o6668UWY3PXU8chJdhjhylX/f2LQVM3HJZsehtTVvxui2FcpA8a3gjAQRt4q0gdSWKJBxySeruAjUFleObdQA2HaAyiacRIzm6CL6p+rjpURJiVLU1lSuasdWxahZ5KM94A4TM1+8Lh86ISsr1LEljp6hH0RnZe2bOpE/dwHmdFbpDKZHATJ2Scq3pfIHnUzCJMLPcLwPgHZkIbixdOrvlBZVVz4X7RqnD3CPzIxk/QsBwma1OowyRkWSLCTdR8A1I3bka83a9v7iAaP2DAxmaay1vRHB6guZwoVc0ovyYrTzJsXtuwXzBsVnPY3ez0FjGsoDnsHob9jGHXNod9y7Q2hk1uS28Ew0a1xbuKYclt8S5gWGJzmZyN4Qzo0zbh4RMIu6xtwo8Zdn5zWB8y9zrDIpqJjQwKY8DzmjDcjH+1uWcvkVrk1QUoUMgpgLSee2oBFPPTt4KKeVZDy3PPuafDg77WXHpM9POGxJp6zDKNMPImj070854cY0DFOo7Xk4qNRTE2/9XCKLyHu1C64TBlVxRr6++nm22AOOaw9W1gsWacZUzePpcs6Cx9t3uyNCr1p+LX6P65UXJGKXp02IJXbc7r1/vHGOtBoAM+ebYkFRmLIoE=
*/