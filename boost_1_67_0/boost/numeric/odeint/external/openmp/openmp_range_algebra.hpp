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