/*
  [auto_generated]
  boost/numeric/odeint/algebra/multi_array_algebra.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_MULTI_ARRAY_ALGEBRA_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_MULTI_ARRAY_ALGEBRA_HPP_DEFINED


#include <boost/multi_array.hpp>

#include <boost/numeric/odeint/algebra/detail/for_each.hpp>
#include <boost/numeric/odeint/algebra/detail/norm_inf.hpp>
#include <boost/numeric/odeint/algebra/norm_result_type.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>


namespace boost {
namespace numeric {
namespace odeint {

// not ready
struct multi_array_algebra
{
    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        detail::for_each1( s1.data() , s1.data() + s1.num_elements() , op );
    }

    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        detail::for_each2( s1.data() , s1.data() + s1.num_elements() , s2.data() , op );
    }

    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        detail::for_each3( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        detail::for_each4( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        detail::for_each5( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        detail::for_each6( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        detail::for_each7( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        detail::for_each8( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        detail::for_each9( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        detail::for_each10( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        detail::for_each11( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        detail::for_each12( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , s12.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        detail::for_each13( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , s12.data() , s13.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        detail::for_each14( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , s12.data() , s13.data() , s14.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        detail::for_each15( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , s12.data() , s13.data() , s14.data() , s15.data() , op );
    }

    template< typename S >
    static typename norm_result_type<S>::type norm_inf( const S &s )
    {
        return detail::norm_inf( s.data() , s.data() + s.num_elements()  , static_cast< typename norm_result_type<S>::type >( 0 ) );
    }
};

template< class T , size_t N >
struct algebra_dispatcher< boost::multi_array< T , N > >
{
    typedef multi_array_algebra algebra_type;
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_MULTI_ARRAY_ALGEBRA_HPP_DEFINED

/* multi_array_algebra.hpp
8bWBN8XH0fjKFmzyZ77vUccPOb9enPynlvhXQT7KFWybPj2HS7+WCjZLF7vKVR97hNpvJen03sHrXzvk+uEmBXtf17/XFd/cumDb0fqO+NPq+PPTg/yjIde3vQp2+ufcvHt0wcbD+bzRMQX7cp87PptMLdh6S/Mjhhm/0wu2P9lv4jHwKC7Yu8Os36+wNP5fsG1pfhTfSX+f6pCvzizY9mR/im9A1xd/Vm270DV+5hRsJu3PnVvA8z0S8TVpf8OJBdsvrfu48rtOLnD9lVMKdlWP+mdqePnWaQWuvyqe7YXzZc8o8P7RMws2LS1ZR/ypfE7Bzk6541N2bsGOBv3fPq9gD/YsZuFw+rtRsGN63Pmz7e8X7JVF3BG/bF1YsL+k3fLRjws2l/xX8Y2AV35SsMuB26UFuzLlPj+//NOC7ZGC8+Uv0/yw6LeDx5cXMD7bEH8U7MPmFfz+1Sv5/evi21D/E49J//6sgOcPNcSfgfdv/rxg/wKeXFWwhPKvf11A/7N8bcGmkP8gTvGttvijsL5Yvq5gb8H6Rn1+wTZLwf7m3xXsQPIPxNek85nEQ8qf8MiXbyhwfWbxSWAfNMVJ/7fFaf2p6+Hhjcwjcco/7YjT89lNBdnG7u/XuVn9i/JnbylofdHNG7cu0j+wPnpbwd4E+Xq7YJekpD+G8LePHcxfbtxR4PVR8ZVJv4rT/r76nQVbF+Tb4pQ/Ed9VsGOpfs0Cfv5QnPJTq+KTDPbHih8M+Xntewv2D8q/ua9g5+tH5OCNhwqWA/+skxRsDuxfaj9SsNFpcdf3f7xgPSnw757Q/AL9s/YUj+/Yw+se3vDwpoe3PLzt4YmHd8SrpP+fLuD6bk0c2098AqzvJuK0vlt5pjCwPhi67Ndn2T6oiI+g9SePfOyRb4hTfLSysGDXw/745l8X98/PO+NnBXuH8hOeL9hPaPy/ULAb9e+K6/lek/8L8bHm69w+bXHsf+LUfl3P9ctdlq90WT7yyMfiGD/18ES8A/Nr942CvUrxj7cKdm0a6ge9y/dviZf1o+Lyjz+Ufd7j9p9r+oXnY3l4W/ynlL+VKuL5gB3xuwfsC8fz9XmeT/zQFMR/skW7nNo/V7THqX58v56PzufJF2087U8X3xd4tVC086h+n/gJ+lF15QctW7RJkL9fHlG004C3xLG+4eeLmD8RiX8DuC1XxPyIUPz+NOQvrsjtVx5ZtA1g/mqsVLQZZD99ocj5Cx5e9fDIw2seHnt4XXxH8m/EMX99VNHOofi7+CWUf79yEf3H8ipF9H+r4t8j+3dVvn5DfDWan8TXBW5hEfMrQnHMjxefQ+dviS8gvlrRvgq8vrquD+vLzS8WMf+julbRbkzD+RXrFG0i5D/VvlS00RQfFz+P8mPW0/eF+bf85aLVaP1O/H2o75WsX7S1aP7ZwDP/iB8P+3taHvlEnPKrwkoR87Mi8c/WN77sgEH/Nalw/+yKbw3PX92Q5WviFB9piK9A9oc4+icengxw8L/Fr0pB/HmToq1K87f4FKp/Lj6W+semRbuL9MdmRXszrfsMaZ8FXxhcv0i2LNodoN+iMUX5D7B/SvzHZH9vy/oh8fCOh3c93LZjXhan/OmGeATxN6syj6se/ShepfbxyHfED4bnr23v0d8eXhcfR/cXp/HRFd8Axke8I9tPHfG9aP1rLM8fsTh9n4747sCrO3nmJ/GVU5C/Ms4zP4o3aX/BzkXeXyBO+Z/l8fx9Q/Fvwvsn4oeR/biL7HeKD4ufSP7RrrIvQL6ym/Qvne8svh2N/wnFpedPrzgMb4qfQt9/d/k31H/EZ0H7x3sU7Viy7/Ys2lSyHz08jHj8VcSnD8g66tuIP0I=
*/