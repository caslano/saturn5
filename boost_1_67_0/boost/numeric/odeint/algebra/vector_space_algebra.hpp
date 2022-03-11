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