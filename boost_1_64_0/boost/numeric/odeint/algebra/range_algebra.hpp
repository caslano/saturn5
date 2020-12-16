/*
 [auto_generated]
 boost/numeric/odeint/algebra/range_algebra.hpp

 [begin_description]
 Default algebra, which works with the most state types, like vector< double >, boost::array< double >, boost::range.
 Internally is uses boost::range to obtain the begin and end iterator of the according sequence.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED

#include <boost/range.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/numeric/odeint/algebra/detail/macros.hpp>
#include <boost/numeric/odeint/algebra/detail/for_each.hpp>
#include <boost/numeric/odeint/algebra/detail/norm_inf.hpp>
#include <boost/numeric/odeint/algebra/norm_result_type.hpp>

namespace boost {
namespace numeric {
namespace odeint {

struct range_algebra
{
    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        detail::for_each1( boost::begin( s1 ) , boost::end( s1 ) ,
                op );
    }

    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        detail::for_each2( boost::begin( s1 ) , boost::end( s1 ) ,
                boost::begin( s2 ) , op );
    }

    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        detail::for_each3( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        detail::for_each4( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        detail::for_each5( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        detail::for_each6( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        detail::for_each7( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        detail::for_each8( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        detail::for_each9( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        detail::for_each10( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        detail::for_each11( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        detail::for_each12( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        detail::for_each13( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        detail::for_each14( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , boost::begin( s14 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        detail::for_each15( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , boost::begin( s14 ) , boost::begin( s15 ) , op );
    }

    template< typename S >
    static typename norm_result_type<S>::type norm_inf( const S &s )
    {
        return detail::norm_inf( boost::begin( s ) , boost::end( s ) ,
                                 static_cast< typename norm_result_type<S>::type >( 0 ) );
    }

};

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED

/* range_algebra.hpp
S8UrxWvFG8VlEe5GcV/xQPFQ8UjxWPFE8VTxTPFc8ULxUvEKztIvsyhPv2Qxnn6ZkKdfZcjTr2Zx5f1agrtR3Fc8gM/WIvWzJR3U8Uj6tgzSp/+sL/P97KiPQuGSjXTksDFQDLHkj2WE+g1r/13VkRt7ReYfFP/lEgPHD9dR3n/FY/iqLP2Er0DS72Bd/vxrOHv+Zn1HXFK/SzZwpK9Fzm9DR3b7T/r947oD9btiY0duY+PnY+X7U7xUvFK8VrxRXDZx5Gz2/OCnEs825fHxZo48xHxzh+7v5G/pyCLk+RZbOZKS+GxrR3b4z/pQdy07qP6+7V/fL1l/YztHzmf959srz1fxSvFa8UZx2YG7UdxXPFA8VDxSPFY8UTyFf9Sy1y+axJEF4RNZPN3Z6d8/83WL57s4dP33cFelfL8bT9/i3Xn+meyhXL/imeK54kW/k/XL4NMTb5Tjy57cjeK+4oHioeKR4rHiieKp4pniOfx7lr/u5cgSrH66tyObkfmpJXzSFsontv0x93XkxP/k/4P3n2zgd7D1j/Zz5A1y/nKAI8cTL+E0/VW8VrxRXFLuRnEfzuYfpfC12fqbKS+/Bwc6MjPxBE7fT8Uz+GmDnv9/11+PDnJk4f+07/wOn3i0+4c6sgB8nUE+7jwD3hyu3P8jHJmGjk/j6bN/JE9/g6OU8iucll+PUZ6/4oHioeIR/Awh/S/HOjKMlI/i45T0Df494n3b+IfMofvnpSc4Mgvrf4ef2LavLyenODIZ69+Es/79CD4Buz44nd8Iv4Ot33oav/7wdIeuL5DAfyXrNzZnOjIFiffPcuj4zxC+Mtk/qznb4fMHz3H4/EH47i27m/McuYL1z8Fp/3KuXB+czf/M4Vew53u+I/uReP8CR+YlnsAXJP3zpeLmQkdmJ+vHRfBRw+zrt9aXObI8iQ8vR/7Avk94q032F73KoeuvhfBp2Pqf8H3a9vWrsmv5+VXwjcn+qdl1/PxKODu/Bj5LD45v+/5uQv4g9t/Pb3bo+kRyC/qncf3b4U9/qPrH7Tg/Vr6Bs+uTO1A++Ov7buO/oeo/dzqyE9vf+i6Hzg/34XR+I3xs4iGc7Q8TK8dPFE8VzxTPlesvlPhS8Qo+LvFaiW8Ul7sdvj8TfHq2fhWcrb+aKMfPFC/gbP3y4h7l/ipewS9l+1uXPL5QvFS8gtP9eeBfkes39zmyKzn/An5h275+jDyE8gUrH8PZ9xfB2fquCZx+f4pncPZ+FfA+4pXijfL78jB3o7gPX4qNT4dPyt4vOH2/FK8UrxVvFJdHuBvFfcUDxUPFI/gSJP0q4HR+uOKN4uZR7oHikeKJ4pniheKV4g2cvh+POXT+YwQfm3gMv7gl/XWkiYYonyRPOLIV6x+Evyz2+WXyFNI/Vr+GPyr29c2Dpx1Zie2/BfdZ+R7Ovv8GPhd5f4PKkVlJ/pDAFyLxJZzOT6p4/U6e4fG+4qHiMRzjN//eI2yo9vtnHfmJra/2vEPX747hc5Dyfa54rbj/AtoX2PUrHsPZ+O1M8RLO8ucaPglxeRHfB9s/HD4FO384bR+Cs9/PlN8vld9vlN+Xl1D/YvMD4auz+iV8ZfJ9hS8j/fnr/bX0H2WvKu33cHZ/Sji7Pw2c3R//NaV9EU7rZ/1O9t/sd/J+KL+fwOn7AafvB5y+H8rvy+v89304+/0ITtfPg6/YElnKNv7xTf77oeIxnJ1fBmfnVyrHrxWXt5T0A07TDzh9PxRPFc8UzxUv4Ge1cZ6W9Q3kXd5+FMAx/0HWsMTX7/F48/7f6cswS/te/CF/PimcPZ8Czp5PDaf9Y/BF2fouH3HPFK8VDz5G+ydbnxX+Cmnfqj5B+Yk=
*/