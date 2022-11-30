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
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
*/