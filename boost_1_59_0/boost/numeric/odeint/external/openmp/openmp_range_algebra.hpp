/*
 [auto_generated]
 boost/numeric/odeint/external/openmp/openmp_range_algebra.hpp

 [begin_description]
 Range algebra for OpenMP.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_OPENMP_OPENMP_RANGE_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_OPENMP_OPENMP_RANGE_ALGEBRA_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/range.hpp>
#include <boost/numeric/odeint/algebra/norm_result_type.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {

/** \brief OpenMP-parallelized range algebra.
 *
 * State must be a model of Random Access Range.
 */
struct openmp_range_algebra
{

#if __cplusplus >= 201103L // C++11 supports _Pragma

#define BOOST_ODEINT_GEN_LOCAL(z, n, unused) \
    BOOST_ASSERT_MSG( len == boost::size(s ## n), "All state ranges must have the same size." ); \
    typename boost::range_iterator<S ## n>::type beg ## n = boost::begin(s ## n);
#define BOOST_ODEINT_GEN_BODY(n) \
    const size_t len = boost::size(s0); \
    BOOST_PP_REPEAT(n, BOOST_ODEINT_GEN_LOCAL, ~) \
    _Pragma("omp parallel for schedule(runtime)") \
    for( size_t i = 0 ; i < len ; i++ ) \
        op( BOOST_PP_ENUM_BINARY_PARAMS(n, beg, [i] BOOST_PP_INTERCEPT) );
BOOST_ODEINT_GEN_FOR_EACH(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY
#undef BOOST_ODEINT_GEN_LOCAL

#else

    template< class S0 , class Op > static void for_each1 ( S0 &s0 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] );
    }
    template< class S0 , class S1 , class Op > static void for_each2 ( S0 &s0 , S1 &s1 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] );
    }
    template< class S0 , class S1 , class S2 , class Op > static void for_each3 ( S0 &s0 , S1 &s1 , S2 &s2 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class Op > static void for_each4 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class Op > static void for_each5 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class Op > static void for_each6 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op > static void for_each7 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class Op > static void for_each8 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class Op > static void for_each9 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class Op > static void for_each10 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class Op > static void for_each11 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class Op > static void for_each12 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        typename boost::range_iterator<S11>::type beg11 = boost::begin(s11);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op > static void for_each13 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        typename boost::range_iterator<S11>::type beg11 = boost::begin(s11);
        typename boost::range_iterator<S12>::type beg12 = boost::begin(s12);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op > static void for_each14 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        typename boost::range_iterator<S11>::type beg11 = boost::begin(s11);
        typename boost::range_iterator<S12>::type beg12 = boost::begin(s12);
        typename boost::range_iterator<S13>::type beg13 = boost::begin(s13);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] , beg13 [i] );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op > static void for_each15 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        typename boost::range_iterator<S11>::type beg11 = boost::begin(s11);
        typename boost::range_iterator<S12>::type beg12 = boost::begin(s12);
        typename boost::range_iterator<S13>::type beg13 = boost::begin(s13);
        typename boost::range_iterator<S14>::type beg14 = boost::begin(s14);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) op( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] , beg13 [i] , beg14 [i] );
    }

#endif


    template< class S >
    static typename norm_result_type< S >::type norm_inf( const S &s )
    {
        using std::max;
        using std::abs;
        typedef typename norm_result_type< S >::type result_type;
        result_type init = static_cast< result_type >( 0 );
        const size_t len = boost::size(s);
        typename boost::range_iterator<const S>::type beg = boost::begin(s);
#       pragma omp parallel for reduction(max: init) schedule(dynamic)
        for( size_t i = 0 ; i < len ; ++i )
            init = max( init , abs( beg[i] ) );
        return init;
    }

};


}
}
}

#endif

/* openmp_range_algebra.hpp
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
*/