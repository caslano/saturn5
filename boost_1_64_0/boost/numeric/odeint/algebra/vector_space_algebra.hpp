/*
 [auto_generated]
 boost/numeric/odeint/algebra/vector_space_algebra.hpp

 [begin_description]
 An algebra for types which have vector space semantics, hence types on which the operators +,-,* are well defined.
 [end_description]

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_VECTOR_SPACE_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_VECTOR_SPACE_ALGEBRA_HPP_INCLUDED

#include <complex>

#include <boost/type_traits/remove_reference.hpp>


namespace boost {
namespace numeric {
namespace odeint {

/*
 * This class template has to be overload in order to call vector_space_algebra::norm_inf
 */
template< class State, class Enabler = void > struct vector_space_norm_inf;

/*
 * Example: instantiation for sole doubles and complex
 */
template<>
struct vector_space_norm_inf< double >
{
    typedef double result_type;
    double operator()( double x ) const
    {
        using std::abs;
        return abs(x);
    }
};

template<>
struct vector_space_norm_inf< float >
{
    typedef float result_type;
    result_type operator()( float x ) const
    {
        using std::abs;
        return abs(x);
    }
};

template< typename T >
struct vector_space_norm_inf< std::complex<T> >
{
    typedef T result_type;
    result_type operator()( std::complex<T> x ) const
    {
        using std::abs;
        return abs( x );
    }
};

struct vector_space_algebra
{
    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        // ToDo : build checks, that the +-*/ operators are well defined
        op( s1 );
    }

    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        op( s1 , s2 );
    }

    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        op( s1 , s2 , s3 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        op( s1 , s2 , s3 , s4 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 , s15 );
    }

    template< class S >
    static typename boost::numeric::odeint::vector_space_norm_inf< S >::result_type norm_inf( const S &s )
    {
        boost::numeric::odeint::vector_space_norm_inf< S > n;
        return n( s );
    }
};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_VECTOR_SPACE_ALGEBRA_HPP_INCLUDED

/* vector_space_algebra.hpp
xPufck/gm5P8oVE8+QzlO/b+wXuJl/Db8I87Zej9yZKvkH/BE1v74ncD7cuTDfX84dv09z/Ah6pf/YD2z7/aLy2/X//swMj4rV+4y68Yf0by5wTusfwDPi/xGn4IW5/xN0dGsvwF3hD3/3DkerZ+G656Fda+AqftK/BFiFdwuj9Qy8j8xGP47MRzOHu//baRedj3o3ipuOnhHvc7aR+AT8zqx3DafgcPiPvDjNzO1hfqNbI6aZ9LFW8Uj8cwfH26Mfj7Eww3tH6ZKl7BFyXuj8njE/g8rPw3Jn9+NXxSEm/GMjR9iOHLk/1RS/g+xOOxjSzGxhfCxyLjG2Vcw+vf8CXZ+wNn879r+CotxNrW1+3j8Q18ScSPtKT/mTFyNqkf5R0jO8PXsXjSNTIVWT+oHt/IiWx+/wRGpmvZz99MxOMr+K8t0j8yKT+/cjJ+/HRyI1OQ+GYKI8eT+GJKI0ex/Yt9Hu9PZWQE+f1sah4fTcPzpxg+N2ufhNP2ffjrrHw1rXJ/pjNyLBt/Ob2Rb8nx8xH8+PEMRiZh9T/42uz7gXukfB/NZORVEh/PbCRskfFhsxjZlZWPZuXPL1e8ULxUvFK8hu/B1m+ZzciEbHyH4uVfTvKHGs7eT5mduw9fgY2vgG/A6teBkTla5P2aw/TvX7GnrX10TkPHVyXw6dn6T3DD7p/iNXwEy3/n4h4qniiew+n5K/GN4v7c3CPFU8ULxWvFzTxGlmPlKzjtv1e8gLPvp1K8UdzMyz2As/OLlPhE8UzxQvFK8UZxMx/3AO4Tj+Gnt+zrx8QL8PJlCmf9T6USX8Np/9KCPN6Hs/hQiY/hn/b0p4//1HN/WGXQ+OTFkL+PjfLroOPfFA2an7eikTNbOM6g8sNa0cD45GxlIy/04NgD7SuYfzdo/avVkf62cXxL+5+/FuqHOP5SFo/WMXIeGf/hr2v4+EP4lmT/2mB9IwU8tP3+hkbupPtzGDq+NoZvR9ZXbeBsfcxoY0PXp0zg/fVzy/7tKbyXeKZ4Dr+Urc8XG94+DafrS8Lp+pKK13C2fqNswuN9OP2+4HR8uRKfKL+fwdn5F0p8BaftM/CI1V82Rf2EtD/m8BHs9+HbsvL5Zkg/2P7/mxu6vmMJ34V4tIWRq1n7+JZonyNewDdl4w+2MrIfWX+hgt/PfBTSH1Y+2trIsuT+FfA7BH9b2p/zbYzcyN6vbY2sx/Kf7fj7Y+Crsv054MfQ/T3Q/sXyV/iVYs8f4h2MzMfaj+Bj4x8ni2V8785GZmDtZ3CPfT/wdYlHuxh5eRyRWSz5i3+QkQ8c+/7vcqqRnl7EW55vdLaRYWT8eX0uT58a+Lb4Y37L+KL0IoP9pezrV1aXGFltGFk//Sq0b5H1q83Vf38/xuIFfMyWPX+Ua42MO4bII7bxRzcbuv59AWf5Z6V4o7i5hXsAn4p4rMSn8BPI+trhrTw+hk9NPFPiC8UrxRvFzW3cA8UjxRPFM8ULxSvFG/g2rP3zdtQvSPpawtnxazj9/pV4cwfKH+z+w+n9h9P5wUp8Ct9V7POv/DuRf7DyFZyVvzJ4lz1fOH2+8A1apH58t5ED2fy2e9A+yfavgKfEgxLtv2z9h/uM7DY6/5x2qPnJ9/9dv9rc0j8RP4j+DVK+KOFs/o7/EL++BL4Z8Qa+EVtf5hEjK5L6e/SYkcPJ/ZfHUX9pi4yyXH/0FPLHv45vuX6/QvmJ9Y/D9yb10+AZHp/D+8j8Q3mOxyfwQ1tsfKWRJwT31hIfv4j+QVZ+hE9Oxycq7dvw00n/YPYSj8/hw1v2829exvdBrs+8ivYHVn+Ab0ueXw2n7d+vGbmYlG8q+DJkf+PkDaQfArf0P/lvon4=
*/