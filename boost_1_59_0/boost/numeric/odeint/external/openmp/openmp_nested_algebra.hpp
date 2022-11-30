/*
 [auto_generated]
 boost/numeric/odeint/external/openmp/openmp_nested_algebra.hpp

 [begin_description]
 Nested parallelized algebra for OpenMP.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_OPENMP_OPENMP_NESTED_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_OPENMP_OPENMP_NESTED_ALGEBRA_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/range.hpp>
#include <boost/numeric/odeint/algebra/norm_result_type.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {

/** \brief OpenMP-parallelized algebra, wrapping another, non-parallelized algebra.
 *
 * NestedState must be a model of Random Access Range, where the elements are sub-states
 * which will be processed in parallel.
 */
template< class InnerAlgebra >
struct openmp_nested_algebra
{

#if __cplusplus >= 201103L // C++11 supports _Pragma

#define BOOST_ODEINT_GEN_LOCAL(z, n, unused) \
    BOOST_ASSERT_MSG( len == boost::size(s ## n), "All nested state ranges must have the same size." ); \
    typename boost::range_iterator<S ## n>::type beg ## n = boost::begin(s ## n);
#define BOOST_ODEINT_GEN_BODY(n) \
    const size_t len = boost::size(s0); \
    BOOST_PP_REPEAT(n, BOOST_ODEINT_GEN_LOCAL, ~) \
    _Pragma("omp parallel for schedule(runtime)") \
    for( size_t i = 0 ; i < len ; i++ ) \
        InnerAlgebra::for_each##n( \
            BOOST_PP_ENUM_BINARY_PARAMS(n, beg, [i] BOOST_PP_INTERCEPT) , \
            op \
        );
BOOST_ODEINT_GEN_FOR_EACH(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY
#undef BOOST_ODEINT_GEN_LOCAL

#else

    template< class S0 , class Op > static void for_each1 ( S0 &s0 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each1( beg0 [i] , op );
    }
    template< class S0 , class S1 , class Op > static void for_each2 ( S0 &s0 , S1 &s1 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each2( beg0 [i] , beg1 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class Op > static void for_each3 ( S0 &s0 , S1 &s1 , S2 &s2 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each3( beg0 [i] , beg1 [i] , beg2 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class Op > static void for_each4 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each4( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class Op > static void for_each5 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each5( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each6( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each7( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each8( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each9( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each10( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each11( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each12( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each13( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each14( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] , beg13 [i] , op );
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
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each15( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] , beg13 [i] , beg14 [i] , op );
    }

#endif


    template< class NestedState >
    static typename norm_result_type< typename NestedState::value_type >::type norm_inf( const NestedState &s )
    {
        typedef typename boost::range_iterator<const NestedState>::type iterator;
        typedef typename std::iterator_traits<iterator>::value_type value_type;
        typedef typename norm_result_type<value_type>::type result_type;
        result_type init = static_cast< result_type >( 0 );
        const size_t len = boost::size(s);
        iterator beg = boost::begin(s);
#       pragma omp parallel for reduction(max: init) schedule(dynamic)
        for( size_t i = 0 ; i < len ; i++ )
            init = (std::max)( init , InnerAlgebra::norm_inf( beg[i] ) );
        return init;
    }

};


}
}
}

#endif

/* openmp_nested_algebra.hpp
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
*/